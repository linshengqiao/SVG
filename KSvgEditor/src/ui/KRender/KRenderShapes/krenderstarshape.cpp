#include "krenderstarshape.h"
#include <cmath>
#include <QPainterPath>

#define M_PI 3.14

KRenderStarShape::KRenderStarShape(const QPointF& topLeft, const QPointF& bottomRight,
    const QColor& fill, const QColor& stroke, float strokeWidth)
{
    setTopLeft(topLeft);
    setBottomRight(bottomRight);
    setFillColor(fill);
    setStrokeColor(stroke);
    setStrokeWidth(strokeWidth);
}

void KRenderStarShape::draw(KIRender* pRender)
{
    if (!pRender) return;

    QRectF rect(topLeft(), bottomRight());
    QPointF center = rect.center();
    double outerRadius = std::min(rect.width(), rect.height()) / 2.0;
    double innerRadius = outerRadius * 0.5;

    QPainterPath path;
    for (int i = 0; i <= 10; ++i) 
    {
        double angle = i * M_PI / 5 - M_PI / 2;
        double r = (i % 2 == 0) ? outerRadius : innerRadius;
        QPointF point(center.x() + r * cos(angle), center.y() + r * sin(angle));
        (i == 0) ? path.moveTo(point) : path.lineTo(point);
    }

    KIRenderShape::drawShapeWithSelection(pRender, path);
}

void KRenderStarShape::setCenter(const QPointF& center) 
{
    m_center = center;
}

void KRenderStarShape::setOuterRadius(double radius) 
{
    m_outerRadius = radius;
}

void KRenderStarShape::setInnerRadius(double radius) 
{
    m_innerRadius = radius;
}

void KRenderStarShape::updateByDrag(const QPointF& start, const QPointF& current)
{
    m_start = start;
    m_end = current;

    setTopLeft(start);
    setBottomRight(current);
}

void KRenderStarShape::setTopLeft(const QPointF& p)
{
    m_topLeft = p;
}

void KRenderStarShape::setBottomRight(const QPointF& p)
{
    m_bottomRight = p;
}

QPointF KRenderStarShape::topLeft() const
{
    return m_topLeft;
}

QPointF KRenderStarShape::bottomRight() const
{
    return m_bottomRight;
}

void KRenderStarShape::setSelected(bool selected)
{
    m_isSelected = selected;
}

bool KRenderStarShape::contains(const QPointF& point) const
{
    QPainterPath path;
    path.addEllipse(boundingRect()); 
    return path.contains(point);
}

KIRenderShape::Position KRenderStarShape::getPosition() const
{
    return { m_topLeft.x(), m_topLeft.y() };
}

QRectF KRenderStarShape::boundingRect() const
{
    return QRectF(m_topLeft, m_bottomRight).normalized();
}