// -------------------------------------------------------
// krenderpentagonshape.h
// 创建者： 林声巧
// 创建时间： 2025/5/14
// 功能描述： 五边形渲染实现类
// Copyright 2025 Kingsoft
// --------------------------------------------------------


#ifndef KRENDERPENTAGONSHAPE_H
#define KRENDERPENTAGONSHAPE_H

#include "kirendershape.h"

class KRenderPentagonShape : public KIRenderShape
{
public:
    KRenderPentagonShape(const QPointF& topLeft, 
        const QPointF& bottomRight,
        const QColor& fill = Qt::transparent,
        const QColor& stroke = Qt::black,
        float strokeWidth = 1.0f);

    void draw(KIRender* pRender) override;

    void setCenter(const QPointF& center);
    void setRadius(double radius);

    void updateByDrag(const QPointF& start, const QPointF& current) override;
    void setTopLeft(const QPointF& p);
    void setBottomRight(const QPointF& p);
    QPointF topLeft() const;
    QPointF bottomRight() const;

    void setSelected(bool selected) override;
    bool contains(const QPointF& point) const override;

    Position getPosition() const override;
    QRectF boundingRect() const override;

private:
    QPointF m_center;
    double m_radius;
    QPointF m_topLeft;
    QPointF m_bottomRight;
    QPointF m_start;
    QPointF m_end;
};
#endif // KRENDERPENTAGONSHAPE_H