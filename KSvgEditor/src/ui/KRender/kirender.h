// -------------------------------------------------------
// kirender.h
// 创建者： 林声巧
// 创建时间： 2025/5/13
// 功能描述： 图形渲染抽象接口及Qt实现
// Copyright 2025 Kingsoft
// --------------------------------------------------------

#ifndef KIRENDER_H
#define KIRENDER_H

#include <qpainter.h>

class KIRender {
public:
    virtual ~KIRender() = default;

    virtual void drawLine(const QPointF& start, const QPointF& end, const QColor& stroke, float width) = 0;

    virtual void drawRect(float x, float y, float width, float height,
        const QColor& fill, const QColor& stroke, float strokeWidth) = 0;

    virtual void drawCircle(float cx, float cy, float r,
        const QColor& fill, const QColor& stroke, float strokeWidth) = 0;

    virtual void drawPath(const QPainterPath& path,
        const QColor& fill, const QColor& stroke, float strokeWidth) = 0;

    virtual void drawText(const QPointF& pos, const QString& text, const QFont& font, const QColor& color) = 0;
};

class QtRenderer : public KIRender
{
public:
    QtRenderer(QPainter* painter);

    void drawLine(const QPointF& start, const QPointF& end, const QColor& stroke, float width) override;

    void drawRect(float x, float y, float width, float height,
        const QColor& fill, const QColor& stroke, float strokeWidth) override;

    void drawCircle(float cx, float cy, float r,
        const QColor& fill, const QColor& stroke, float strokeWidth) override;

    void drawPath(const QPainterPath& path,
        const QColor& fill, const QColor& stroke, float strokeWidth) override;

    void drawText(const QPointF& pos, const QString& text, const QFont& font, const QColor& color) override;

private:
    QPainter* painter;
};
#endif // !KIRENDER_H