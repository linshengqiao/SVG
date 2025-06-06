#include "kishape.h"

KBaseShape::KBaseShape(ShapeType type, const QString& id)
    : m_type(type)
    , m_id(id)
    , m_fillColor(Qt::transparent)
    , m_strokeColor(Qt::white)
    , m_strokeWidth(1.0)
    , m_opacity(1.0)
    , m_position(0, 0)
{

}

KBaseShape::~KBaseShape()
{

}

IShape::ShapeType KBaseShape::type() const
{
    return m_type;
}

QString KBaseShape::id() const
{
    return m_id;
}

void KBaseShape::setId(const QString& id)
{
    m_id = id;
}

QColor KBaseShape::fillColor() const
{
    return m_fillColor;
}

void KBaseShape::setFillColor(const QColor& color)
{
    m_fillColor = color;
}

QColor KBaseShape::strokeColor() const
{
    return m_strokeColor;
}

void KBaseShape::setStrokeColor(const QColor& color)
{
    m_strokeColor = color;
}

qreal KBaseShape::strokeWidth() const
{
    return m_strokeWidth;
}

void KBaseShape::setStrokeWidth(qreal width)
{
    m_strokeWidth = width;
}

qreal KBaseShape::opacity() const
{
    return m_opacity;
}

void KBaseShape::setOpacity(qreal opacity)
{
    m_opacity = opacity;
}

QPointF KBaseShape::position() const
{
    return m_position;
}

void KBaseShape::setPosition(const QPointF& pos)
{
    m_position = pos;
}

QPointF KBaseShape::topLeft() const
{
    return m_topLeft;
}

void KBaseShape::setTopLeft(const QPointF& point)
{
    m_topLeft = point;
    updateGeometry();
}

QPointF KBaseShape::bottomRight() const
{
    return m_bottomRight;
}

void KBaseShape::setBottomRight(const QPointF& point)
{
    m_bottomRight = point;
    updateGeometry();
}

void KBaseShape::updateGeometry()
{
    qreal left = qMin(m_topLeft.x(), m_bottomRight.x());
    qreal top = qMin(m_topLeft.y(), m_bottomRight.y());
    qreal right = qMax(m_topLeft.x(), m_bottomRight.x());
    qreal bottom = qMax(m_topLeft.y(), m_bottomRight.y());

    m_topLeft = QPointF(left, top);
    m_bottomRight = QPointF(right, bottom);
    m_position = QPointF((left + right) / 2, (top + bottom) / 2);
}