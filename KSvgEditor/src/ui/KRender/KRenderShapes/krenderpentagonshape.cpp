#include "krenderpentagonshape.h"
#include <cmath>
#include <QPainterPath>

#define M_PI 3.14

KRenderPentagonShape::KRenderPentagonShape(const QPointF& topLeft, const QPointF& bottomRight,
    const QColor& fill, const QColor& stroke, float strokeWidth)
{
    setTopLeft(topLeft);
    setBottomRight(bottomRight);
    setFillColor(fill);
    setStrokeColor(stroke);
    setStrokeWidth(strokeWidth);
}

void KRenderPentagonShape::draw(KIRender* pRender)
{
    if (!pRender) return;

    QRectF rect(topLeft(), bottomRight());
    QPointF center = rect.center();
    double radius = std::min(rect.width(), rect.height()) / 2.0;

    QPainterPath path;
    for (int i = 0; i <= 5; ++i) 
    {
        double angle = i * 2 * M_PI / 5 - M_PI / 2;
        QPointF point(center.x() + radius * cos(angle), center.y() + radius * sin(angle));
        (i == 0) ? path.moveTo(point) : path.lineTo(point);
    }

    KIRenderShape::drawShapeWithSelection(pRender, path);
}

void KRenderPentagonShape::setCenter(const QPointF& center) 
{
    m_center = center;
}

void KRenderPentagonShape::setRadius(double radius) 
{
    m_radius = radius;
}

void KRenderPentagonShape::updateByDrag(const QPointF& start, const QPointF& current)
{
    m_start = start;
    m_end = current;

    setTopLeft(start);
    setBottomRight(current);
}

void KRenderPentagonShape::setTopLeft(const QPointF& p)
{
    m_topLeft = p;
}

void KRenderPentagonShape::setBottomRight(const QPointF& p)
{
    m_bottomRight = p;
}

QPointF KRenderPentagonShape::topLeft() const
{
    return m_topLeft;
}

QPointF KRenderPentagonShape::bottomRight() const
{
    return m_bottomRight;
}

void KRenderPentagonShape::setSelected(bool selected)
{
    m_isSelected = selected;
}

bool KRenderPentagonShape::contains(const QPointF& point) const
{
    QPainterPath path;
    path.addEllipse(boundingRect());
    return path.contains(point);
}

KIRenderShape::Position KRenderPentagonShape::getPosition() const
{
    return { m_topLeft.x(), m_topLeft.y() };
}

QRectF KRenderPentagonShape::boundingRect() const
{
    return QRectF(m_topLeft, m_bottomRight).normalized();
}