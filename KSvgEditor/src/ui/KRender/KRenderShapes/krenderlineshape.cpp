#include "krenderlineshape.h"
#include <QPainter>
#include <QPainterPath>
#include <QPainterPathStroker>
#include <QLineF>

KRenderLineShape::KRenderLineShape(const QPointF& start, const QPointF& end, const QColor& stroke, float width)
    :m_startPoint(start)
    , m_endPoint(end)
{
    setStrokeColor(stroke);
    setStrokeWidth(width);
}

void KRenderLineShape::draw(KIRender* pRender)
{
    if (!pRender) return;

    pRender->drawLine(m_startPoint, m_endPoint, strokeColor(), strokeWidth());

    if (m_isSelected)
    {
        QRectF highlightRect = boundingRect(); 
        QColor highlightColor(Qt::blue);
        highlightColor.setAlpha(128);
        pRender->drawRect(highlightRect.x(), highlightRect.y(),
            highlightRect.width(), highlightRect.height(),
            QColor(0, 0, 0, 0), highlightColor, 1.5f);
    }
}

void KRenderLineShape::updateByDrag(const QPointF& start, const QPointF& current)
{
    m_startPoint = start;
    m_endPoint = current;
}

void KRenderLineShape::setTopLeft(const QPointF& p)
{
    m_topLeft = p;
}

void KRenderLineShape::setBottomRight(const QPointF& p)
{
    m_bottomRight = p;
}

QPointF KRenderLineShape::topLeft() const
{
    return m_topLeft;
}

QPointF KRenderLineShape::bottomRight() const
{
    return m_bottomRight;
}

void KRenderLineShape::setSelected(bool selected)
{
    m_isSelected = selected;
}

bool KRenderLineShape::contains(const QPointF& point) const
{
    QPainterPath path;
    QLineF line(m_startPoint, m_endPoint);
    path.moveTo(line.p1());
    path.lineTo(line.p2());

    QPainterPathStroker stroker;
    stroker.setWidth(strokeWidth() + 6);  
    QPainterPath stroked = stroker.createStroke(path);

    return stroked.contains(point);
}

KIRenderShape::Position KRenderLineShape::getPosition() const
{
    return KIRenderShape::Position{ m_start.x(), m_start.y() };
}

QRectF KRenderLineShape::boundingRect() const
{
    return QRectF(m_topLeft, m_bottomRight).normalized();
}