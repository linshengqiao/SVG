#include"kirendershape.h"
#include <QPainterPath>

QRectF KBaseShape::boundingRect() const
{
    qreal halfWidth = m_strokeWidth / 2;

    return QRectF(
        m_topLeft.x() - halfWidth,
        m_topLeft.y() - halfWidth,
        m_bottomRight.x() - m_topLeft.x() + m_strokeWidth,
        m_bottomRight.y() - m_topLeft.y() + m_strokeWidth
    );
}

void KIRenderShape::setSelected(bool selected) 
{
    m_isSelected = selected;
}

bool KIRenderShape::contains(const QPointF& point) const 
{
    return boundingRect().contains(point);
}

KIRenderShape::Position KIRenderShape::getPosition() const 
{
    return Position(m_topLeft.x(), m_topLeft.y());
}

void KIRenderShape::moveTo(const Position& newPos)
{
    qreal width = m_bottomRight.x() - m_topLeft.x();
    qreal height = m_bottomRight.y() - m_topLeft.y();

    m_topLeft = QPointF(newPos.x, newPos.y);

    m_bottomRight = QPointF(newPos.x + width, newPos.y + height);
}

void KIRenderShape::drawShapeWithSelection(KIRender* pRender, const QPainterPath& path)
{
    if (!pRender) return;

    pRender->drawPath(path, fillColor(), strokeColor(), strokeWidth());

    if (m_isSelected)
    {
        QRectF rect = boundingRect();
        QColor highlightColor(Qt::red);
        highlightColor.setAlpha(128);
        pRender->drawRect(rect.x(), rect.y(), rect.width(), rect.height(),
            QColor(0, 0, 0, 0), highlightColor, 1.5f);
    }
}

void KIRenderShape::drawShapeWithSelection(KIRender* pRender, const QRectF& rect)
{
    if (!pRender) return;

    if (m_isSelected)
    {
        QColor highlightColor(Qt::blue);
        highlightColor.setAlpha(128);
        pRender->drawRect(rect.x(), rect.y(), rect.width(), rect.height(),
            QColor(0, 0, 0, 0), highlightColor, 1.5f);
    }

    else
    {
        pRender->drawRect(rect.x(), rect.y(), rect.width(), rect.height(),
            fillColor(), strokeColor(), strokeWidth());
    }
}

KIRenderShape::DragHandle KIRenderShape::hitTestHandle(const QPointF& point) const 
{
    constexpr qreal handleSize = 8.0;
    QRectF topLeftHandle(m_topLeft - QPointF(handleSize / 2, handleSize / 2), QSizeF(handleSize, handleSize));
    QRectF bottomRightHandle(m_bottomRight - QPointF(handleSize / 2, handleSize / 2), QSizeF(handleSize, handleSize));

    if (topLeftHandle.contains(point)) return DragHandle::TopLeft;
    if (bottomRightHandle.contains(point)) return DragHandle::BottomRight;
    if (boundingRect().contains(point)) return DragHandle::Move;
    return DragHandle::None;
}

void KIRenderShape::updateByDragHandle(DragHandle handle, const QPointF& from, const QPointF& to) 
{
    QPointF delta = to - from;
    switch (handle) 
    {
    case DragHandle::Move:
        m_topLeft += delta;
        m_bottomRight += delta;
        break;
    case DragHandle::TopLeft:
        m_topLeft = to;
        break;
    case DragHandle::BottomRight:
        m_bottomRight = to;
        break;
    default:
        break;
    }
}