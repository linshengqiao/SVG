#include "kcanvascontroller.h"
#include <QPainter>
#include <QMouseEvent>
#include <QWheelEvent>
#include <QLineEdit>
#include <QDebug>
#include "kshapefactory.h"
#include "kirendershape.h"
#include "krenderfreehandshape.h"
#include "krenderlineshape.h"
#include "krenderellipseshape.h"
#include "krenderrectshape.h"
#include "krenderpentagonshape.h"
#include "krenderhexagonshape.h"
#include "krenderstarshape.h"
#include "krendertextshape.h"

KCanvasController::KCanvasController(QWidget* parentWidget)
    : QObject(parentWidget)
    ,m_parentWidget(parentWidget)
    ,m_currentToolState(KToolBarWidget::State::Select)
    ,m_isDragging(false) 
{
}

static bool isDrawingTool(KToolBarWidget::State state)
{
    using State = KToolBarWidget::State;
    switch (state)
    {
    case State::Line:
    case State::Ellipse:
    case State::Rectangle:
    case State::Pentagon:
    case State::Hexagon:
    case State::Star:
        return true;
    default:
        return false;
    }
}

void KCanvasController::setToolState(KToolBarWidget::State state)
{
    m_currentToolState = state;

    if (!m_parentWidget) return;

    if (isDrawingTool(state))
    {
        m_parentWidget->setCursor(Qt::CrossCursor);
    }
    else if (state == KToolBarWidget::State::Select)
    {
        QIcon icon(":/icons/icons/select.svg");
        QCursor cursor(icon.pixmap(QSize(32, 32)), 5, 30);
        m_parentWidget->setCursor(cursor);
    }
    else if (state == KToolBarWidget::State::Freehand)
    {
        QIcon icon(":/icons/icons/freehand.svg");
        QCursor cursor(icon.pixmap(QSize(32, 32)), 5, 30);
        m_parentWidget->setCursor(cursor);
    }
    else if (state == KToolBarWidget::State::Zoom)
    {
        QIcon icon(":/icons/icons/zoom.svg");
        QCursor cursor(icon.pixmap(QSize(32, 32)), 16, 16);
        m_parentWidget->setCursor(cursor);
    }
    else
    {
        m_parentWidget->unsetCursor();
    }

    qDebug() << "Controller updated tool state:" << static_cast<int>(state);
}

KToolBarWidget::State KCanvasController::currentToolState() const
{
    return m_currentToolState;
}

void KCanvasController::paint(QPainter* painter)
{
    QtRenderer qtRender(painter);
    for (const auto& shape : m_shapes)
        shape->draw(&qtRender);
}

QPointF toQPointF(const KIRenderShape::Position& pos)
{
    return QPointF(pos.x, pos.y);
}

void KCanvasController::handleMousePress(QMouseEvent* event)
{
    if (event->button() != Qt::LeftButton)
        return;

    m_startPoint = event->pos();
    m_isDrawing = true;
    m_tempShape.reset();
    m_hasMovedEnough = false;

    if (m_currentToolState == KToolBarWidget::State::Select)
    {
        m_selectedShapes.clear();
        for (const auto& shape : m_shapes)
        {
            if (shape->contains(event->pos()))
            {
                shape->setSelected(true);
                m_selectedShapes.append(shape);
                m_dragStartPos = event->pos();          
                m_draggedShape = shape;                 
                m_isDragging = true;                   
                m_dragOffset = event->pos() - toQPointF(shape->getPosition()); 
                if (m_parentWidget) m_parentWidget->update();
                break;
            }
        }
    }
}

void KCanvasController::handleMouseMove(QMouseEvent* event)
{
    if (!m_isDrawing)
        return;

    const QPointF currentPoint = event->pos();
    const qreal distance = (currentPoint - m_startPoint).manhattanLength();
    const qreal MIN_DISTANCE = 3.0;

    if (!m_tempShape && distance >= MIN_DISTANCE)
    {
        m_tempShape = KShapeFactory::createShape(m_currentToolState, m_startPoint, currentPoint);
        if (m_tempShape)
        {
            m_shapes.append(m_tempShape);
            m_hasMovedEnough = true;
        }
    }

    if (m_tempShape)
        m_tempShape->updateByDrag(m_startPoint, currentPoint);

    if (m_currentToolState == KToolBarWidget::State::Select && m_isDragging && m_draggedShape)
    {
        QPointF delta = event->pos() - m_dragStartPos;
        QPointF topLeft = m_draggedShape->topLeft();
        QPointF bottomRight = m_draggedShape->bottomRight();

        qreal width = bottomRight.x() - topLeft.x();
        qreal height = bottomRight.y() - topLeft.y();

        QPointF newTopLeft = topLeft + delta;

        KIRenderShape::Position newPos = { newTopLeft.x(), newTopLeft.y() };

        m_draggedShape->moveTo(newPos);
        m_dragStartPos = event->pos(); 

        if (m_parentWidget) m_parentWidget->update();
    }

    if (m_parentWidget) m_parentWidget->update();
}

void KCanvasController::handleMouseRelease(QMouseEvent* event)
{
    if (!m_isDrawing)
        return;

    m_isDrawing = false;

    if (!m_hasMovedEnough && m_tempShape)
        m_shapes.removeOne(m_tempShape);

    if (m_currentToolState == KToolBarWidget::State::Text && !m_tempShape)
    {
        auto shape = std::make_shared<KRenderTextShape>(event->pos(), "Click to edit");
        m_shapes.append(shape);
        if (m_parentWidget) m_parentWidget->update();
    }

    if (m_currentToolState == KToolBarWidget::State::Select)
    {
        bool clickedOnShape = false;
        for (const auto& shape : m_shapes)
        {
            if (shape->contains(event->pos()))
            {
                clickedOnShape = true;
                break;
            }
        }

        if (!clickedOnShape)
        {
            for (auto& shape : m_shapes)
                shape->setSelected(false);
            m_selectedShapes.clear();
        }

        m_isDragging = false;     
        m_draggedShape = nullptr; 
    }

    m_tempShape.reset();
    if (m_parentWidget) m_parentWidget->update();
}

void KCanvasController::handleDoubleClick(QMouseEvent* event)
{
    for (const auto& shape : m_shapes)
    {
        if (shape->contains(event->pos()))
        {
            QWidget* editor = shape->createEditor(m_parentWidget);
            if (editor)
            {
                editor->show();
                editor->setFocus();
            }
            break;
        }
    }
}

void KCanvasController::handleWheel(QWheelEvent* event)
{
    if (m_currentToolState != KToolBarWidget::State::Zoom)
        return;

    const double zoomFactor = 1.1;
    if (event->angleDelta().y() > 0)
    {
        m_zoomLevel *= zoomFactor;
    }
    else
    {
        m_zoomLevel /= zoomFactor;
    }

    int newWidth = m_originalWidth * m_zoomLevel;
    int newHeight = m_originalHeight * m_zoomLevel;

    if (m_parentWidget)
    {
        m_parentWidget->setFixedSize(newWidth, newHeight);
        m_parentWidget->update();
    }

    emit canvasWidthChanged(newWidth);
    emit canvasHeightChanged(newHeight);
    emit zoomFactorChanged(m_zoomLevel);
}

double KCanvasController::zoomLevel() const
{
    return m_zoomLevel;
}

int KCanvasController::canvasWidth() const
{
    return m_originalWidth * m_zoomLevel;
}

int KCanvasController::canvasHeight() const
{
    return m_originalHeight * m_zoomLevel;
}