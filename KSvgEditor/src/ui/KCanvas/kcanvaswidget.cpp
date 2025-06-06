#include "kcanvaswidget.h"
#include <QPainter>
#include <QMouseEvent>
#include <QWheelEvent>
#include <QDebug>
#include "kcanvascontroller.h"

KCanvasWidget::KCanvasWidget(QWidget* parent)
    : QWidget(parent)
    ,m_controller(new KCanvasController(this))
{
    connect(this, &KCanvasWidget::canvasWidthChanged,
        m_controller, &KCanvasController::canvasWidthChanged);
    connect(this, &KCanvasWidget::canvasHeightChanged,
        m_controller, &KCanvasController::canvasHeightChanged);
    connect(this, &KCanvasWidget::zoomFactorChanged,
        m_controller, &KCanvasController::zoomFactorChanged);
}

void KCanvasWidget::onToolStateChanged(KToolBarWidget::State state)
{
    m_controller->setToolState(state);
}

void KCanvasWidget::paintEvent(QPaintEvent*)
{
    QPainter painter(this);
    m_controller->paint(&painter);
}

void KCanvasWidget::mousePressEvent(QMouseEvent* event)
{
    m_controller->handleMousePress(event);
}

void KCanvasWidget::mouseMoveEvent(QMouseEvent* event)
{
    m_controller->handleMouseMove(event);
}

void KCanvasWidget::mouseReleaseEvent(QMouseEvent* event)
{
    m_controller->handleMouseRelease(event);
}

void KCanvasWidget::mouseDoubleClickEvent(QMouseEvent* event)
{
    m_controller->handleDoubleClick(event);
}

void KCanvasWidget::wheelEvent(QWheelEvent* event)
{
    m_controller->handleWheel(event);
}
