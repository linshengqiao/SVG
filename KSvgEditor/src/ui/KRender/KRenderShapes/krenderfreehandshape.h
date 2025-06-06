// -------------------------------------------------------
// krenderfreehandshape.h
// 创建者： 林声巧
// 创建时间： 2025/5/14
// 功能描述： 自由绘制图形渲染实现类
// Copyright 2025 Kingsoft
// --------------------------------------------------------

#ifndef KRENDERFREEHANDSHAPE_H
#define KRENDERFREEHANDSHAPE_H

#include <QVector>
#include <QPointF>
#include "kirendershape.h"

class KRenderFreehandShape : public KIRenderShape
{
public:
    KRenderFreehandShape(const QColor& stroke = Qt::black, float strokeWidth = 1.0f);

    void draw(KIRender* pRender) override;

    void updateByDrag(const QPointF& start, const QPointF& current) override;
    void setTopLeft(const QPointF& p);
    void setBottomRight(const QPointF& p);
    QPointF topLeft() const;
    QPointF bottomRight() const;
    void addPoint(const QPointF& point);

    void setSelected(bool selected) override;
    bool contains(const QPointF& point) const override;

    Position getPosition() const override;
    QRectF boundingRect() const override;

private:
    QVector<QPointF> m_points;
    QPointF m_topLeft;
    QPointF m_bottomRight;
    QPointF m_start;
    QPointF m_end;

    bool m_isSelected = false;
};
#endif // KRENDERFREEHANDSHAPE_H