// -------------------------------------------------------
// kirendershape.h
// 创建者： 林声巧
// 创建时间： 2025/5/14
// 功能描述： 图形视图控制类，继承自图形模型，实现图形渲染和用户交互处理
// Copyright 2025 Kingsoft
// --------------------------------------------------------

#ifndef KIRENDERSHAPE_H
#define KIRENDERSHAPE_H

#include <QColor>
#include <QPainter>
#include <QPointF>
#include <QRectF>
#include "kishape.h"
#include "kirender.h"

class KIRenderShape : public KBaseShape 
{
public:
    virtual ~KIRenderShape() = default;

    enum class DragHandle 
    {
        None,
        Move,
        TopLeft,
        BottomRight
    };

    struct Position 
    {
        qreal x;
        qreal y;
        Position(qreal xVal = 0, qreal yVal = 0) : x(xVal), y(yVal) {}
    };

    virtual void draw(KIRender* pRender) = 0;
    virtual void updateByDrag(const QPointF& start, const QPointF& current) = 0;

    virtual void setSelected(bool selected);
    virtual bool isSelected() const { return m_isSelected; }

    virtual bool contains(const QPointF& point) const;

    virtual DragHandle hitTestHandle(const QPointF& point) const;
    virtual void updateByDragHandle(DragHandle handle, const QPointF& from, const QPointF& to);

    virtual void setText(const QString& text) {}
    virtual QString getText() const { return QString(); }
    virtual QWidget* createEditor(QWidget* parent) { return nullptr; }

    virtual Position getPosition() const;
    virtual void moveTo(const Position& newPos);

protected:
    void drawShapeWithSelection(KIRender* pRender, const QPainterPath& path);
    void drawShapeWithSelection(KIRender* pRender, const QRectF& rect);

protected:
    bool m_isSelected = false;
};
#endif // !KIRENDERSHAPE_H