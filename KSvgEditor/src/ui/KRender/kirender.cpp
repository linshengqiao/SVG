#include "kirender.h"
#include <QPainter>

QtRenderer::QtRenderer(QPainter* painter)
    : painter(painter)
{

}

void QtRenderer::drawLine(const QPointF& start, const QPointF& end, const QColor& stroke, float width)
{
    QPen pen(stroke);
    pen.setWidthF(width);
    painter->setPen(pen);
    painter->drawLine(start, end);
}

void QtRenderer::drawRect(float x, float y, float width, float height,
    const QColor& fill, const QColor& stroke, float strokeWidth)
{
    QPen pen(stroke);
    pen.setWidthF(strokeWidth);
    painter->setPen(pen);
    painter->setBrush(fill);
    painter->drawRect(x, y, width, height);
}

void QtRenderer::drawCircle(float cx, float cy, float r,
    const QColor& fill, const QColor& stroke, float strokeWidth)
{
    QPen pen(stroke);
    pen.setWidthF(strokeWidth);
    painter->setPen(pen);
    painter->setBrush(fill);
    painter->drawEllipse(QPointF(cx, cy), r, r);
}

void QtRenderer::drawPath(const QPainterPath& path,
    const QColor& fill, const QColor& stroke, float strokeWidth)
{
    QPen pen(stroke);
    pen.setWidthF(strokeWidth);
    painter->setPen(pen);
    painter->setBrush(fill);
    painter->drawPath(path);
}

void QtRenderer::drawText(const QPointF& pos, const QString& text, const QFont& font, const QColor& color)
{
    QPen pen(color);
    painter->setPen(pen);
    painter->setFont(QFont("Arial", 14));
    painter->drawText(pos, text);
}