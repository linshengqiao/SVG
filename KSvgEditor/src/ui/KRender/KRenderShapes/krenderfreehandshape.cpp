#include "krenderfreehandshape.h"
#include <QPainterPath>

KRenderFreehandShape::KRenderFreehandShape(const QColor& stroke, float strokeWidth)
{
    setStrokeColor(stroke);
    setStrokeWidth(strokeWidth);
}

void KRenderFreehandShape::addPoint(const QPointF& point)
{
    m_points.append(point);

    if (m_points.size() == 1)
    {
        m_topLeft = point;
        m_bottomRight = point;
    }

    else 
    {
        m_topLeft.setX(std::min(m_topLeft.x(), point.x()));
        m_topLeft.setY(std::min(m_topLeft.y(), point.y()));
        m_bottomRight.setX(std::max(m_bottomRight.x(), point.x()));
        m_bottomRight.setY(std::max(m_bottomRight.y(), point.y()));
    }
}


void KRenderFreehandShape::draw(KIRender* pRender)
{
    if (!pRender || m_points.isEmpty()) return;

    QPainterPath path;
    path.moveTo(m_points.first());
    for (int i = 1; i < m_points.size(); ++i) 
    {
        path.lineTo(m_points[i]);
    }

    setFillColor(Qt::transparent);  
    drawShapeWithSelection(pRender, path);  
}

void KRenderFreehandShape::updateByDrag(const QPointF& /*start*/, const QPointF& current)
{
    if (m_points.isEmpty() || QLineF(m_points.last(), current).length() > 1.0)
    {
        addPoint(current);
    }
}

void KRenderFreehandShape::setTopLeft(const QPointF& p)
{
    m_topLeft = p;
}

void KRenderFreehandShape::setBottomRight(const QPointF& p)
{
    m_bottomRight = p;
}

QPointF KRenderFreehandShape::topLeft() const
{
    return m_topLeft;
}

QPointF KRenderFreehandShape::bottomRight() const
{
    return m_bottomRight;
}

void KRenderFreehandShape::setSelected(bool selected)
{
    m_isSelected = selected;
}

bool KRenderFreehandShape::contains(const QPointF& point) const
{
    if (m_points.isEmpty()) return false;

    QPainterPath path;
    path.moveTo(m_points.first());
    for (int i = 1; i < m_points.size(); ++i)
    {
        path.lineTo(m_points[i]);
    }

    QPainterPathStroker stroker;
    stroker.setWidth(strokeWidth() + 6); 
    QPainterPath strokePath = stroker.createStroke(path);

    return strokePath.contains(point);
}

KIRenderShape::Position KRenderFreehandShape::getPosition() const
{
    return { m_topLeft.x(), m_topLeft.y() };
}

QRectF KRenderFreehandShape::boundingRect() const
{
    if (m_points.isEmpty()) return QRectF();

    QPainterPath path;
    path.moveTo(m_points.first());
    for (int i = 1; i < m_points.size(); ++i) 
    {
        path.lineTo(m_points[i]);
    }

    QPainterPathStroker stroker;
    stroker.setWidth(strokeWidth() + 6);
    return stroker.createStroke(path).boundingRect();
}