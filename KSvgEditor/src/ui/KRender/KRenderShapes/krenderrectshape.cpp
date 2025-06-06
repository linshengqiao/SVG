#include "krenderrectshape.h"

KRenderRectShape::KRenderRectShape(const QPointF& topLeft, 
    const QPointF& bottomRight,
    const QColor& fill,
    const QColor& stroke,
    float strokeWidth)
{
    setTopLeft(topLeft);
    setBottomRight(bottomRight);
    setFillColor(fill);
    setStrokeColor(stroke);
    setStrokeWidth(strokeWidth);
}

void KRenderRectShape::draw(KIRender* pRender)
{
    QRectF rect = QRectF(topLeft(), bottomRight()).normalized();
    
    KIRenderShape::drawShapeWithSelection(pRender, rect);
}

void KRenderRectShape::updateByDrag(const QPointF& start, const QPointF& current)
{
    m_start = start;
    m_end = current;

    setTopLeft(start);
    setBottomRight(current);
}

void KRenderRectShape::setTopLeft(const QPointF& p) 
{ 
    m_topLeft = p; 
}

void KRenderRectShape::setBottomRight(const QPointF& p) 
{ 
    m_bottomRight = p; 
}

QPointF KRenderRectShape::topLeft() const 
{ 
    return m_topLeft; 
}

QPointF KRenderRectShape::bottomRight() const 
{ 
    return m_bottomRight; 
}

void KRenderRectShape::setSelected(bool selected)
{
    m_isSelected = selected;
}

bool KRenderRectShape::contains(const QPointF& point) const
{
    return boundingRect().contains(point);
}

KIRenderShape::Position KRenderRectShape::getPosition() const 
{
    return { m_topLeft.x(), m_topLeft.y() };
}

QRectF KRenderRectShape::boundingRect() const
{
    return QRectF(m_topLeft, m_bottomRight).normalized();
}
