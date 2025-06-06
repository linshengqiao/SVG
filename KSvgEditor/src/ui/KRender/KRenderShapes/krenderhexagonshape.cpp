#include "krenderhexagonshape.h"
#include <cmath>
#include <QPainterPath>
#include "kirendershape.h"

#define M_PI 3.14

KRenderHexagonShape::KRenderHexagonShape(const QPointF& topLeft, 
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

void KRenderHexagonShape::draw(KIRender* pRender)
{
    if (!pRender) return;

    QRectF rect(topLeft(), bottomRight());
    QPointF center = rect.center();
    double radius = std::min(rect.width(), rect.height()) / 2.0;

    QPainterPath path;
    for (int i = 0; i <= 6; ++i) 
    {
        double angle = i * 2 * M_PI / 6;
        QPointF point(center.x() + radius * cos(angle), center.y() + radius * sin(angle));
        (i == 0) ? path.moveTo(point) : path.lineTo(point);
    }

    KIRenderShape::drawShapeWithSelection(pRender, path);
}

void KRenderHexagonShape::setCenter(const QPointF& center) 
{
    m_center = center;
}

void KRenderHexagonShape::setRadius(double radius) 
{
    m_radius = radius;
}

void KRenderHexagonShape::updateByDrag(const QPointF& start, const QPointF& current)
{
    m_start = start;
    m_end = current;

    setTopLeft(start);
    setBottomRight(current);
}

void KRenderHexagonShape::setTopLeft(const QPointF& p)
{
    m_topLeft = p;
}

void KRenderHexagonShape::setBottomRight(const QPointF& p)
{
    m_bottomRight = p;
}

QPointF KRenderHexagonShape::topLeft() const
{
    return m_topLeft;
}

QPointF KRenderHexagonShape::bottomRight() const
{
    return m_bottomRight;
}

void KRenderHexagonShape::setSelected(bool selected)
{
    m_isSelected = selected;
}

bool KRenderHexagonShape::contains(const QPointF& point) const
{
    QPainterPath path;
    path.addEllipse(boundingRect());
    return path.contains(point);
}

KIRenderShape::Position KRenderHexagonShape::getPosition() const
{
    return { m_topLeft.x(), m_topLeft.y() };
}

QRectF KRenderHexagonShape::boundingRect() const
{
    return QRectF(m_topLeft, m_bottomRight).normalized();
}