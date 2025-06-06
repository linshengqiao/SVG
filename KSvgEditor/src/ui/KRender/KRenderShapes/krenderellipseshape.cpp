#include "krenderellipseshape.h"
#include <QPainterPath>
#include "kirendershape.h"

KRenderEllipseShape::KRenderEllipseShape(const QPointF& topLeft, 
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

void KRenderEllipseShape::draw(KIRender* pRender)
{
    if (!pRender) return;

    QRectF rect = QRectF(topLeft(), bottomRight()).normalized();
    QPainterPath path;
    path.addEllipse(rect);

    KIRenderShape::drawShapeWithSelection(pRender, path);
}

void KRenderEllipseShape::updateByDrag(const QPointF& start, const QPointF& current)
{
    m_start = start;
    m_end = current;

    setTopLeft(start);
    setBottomRight(current);
}

void KRenderEllipseShape::setTopLeft(const QPointF& p) 
{ 
    m_topLeft = p; 
}

void KRenderEllipseShape::setBottomRight(const QPointF& p) 
{ 
    m_bottomRight = p; 
}

QPointF KRenderEllipseShape::topLeft() const 
{ 
    return m_topLeft; 
}

QPointF KRenderEllipseShape::bottomRight() const 
{ 
    return m_bottomRight; 
}

void KRenderEllipseShape::setSelected(bool selected)
{
    m_isSelected = selected;
}

bool KRenderEllipseShape::contains(const QPointF& point) const
{
    QPainterPath path;
    path.addEllipse(boundingRect());
    return path.contains(point);
}

KIRenderShape::Position KRenderEllipseShape::getPosition() const
{
    return { m_topLeft.x(), m_topLeft.y() };
}

QRectF KRenderEllipseShape::boundingRect() const
{
    return QRectF(m_topLeft, m_bottomRight).normalized();
}