// -------------------------------------------------------
// krenderlineshape.h
// 创建者： 林声巧
// 创建时间： 2025/5/14
// 功能描述： 直线渲染实现类
// Copyright 2025 Kingsoft
// --------------------------------------------------------

#ifndef KRENDERLINESHAPE_H
#define KRENDERLINESHAPE_H

#include <QPainter>
#include "kirendershape.h"

class KRenderLineShape : public KIRenderShape
{
public:
    KRenderLineShape(const QPointF& start, const QPointF& end,
        const QColor& stroke = Qt::black, float width = 1.0);

    void draw(KIRender* pRender) override;
    
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
    QPointF m_startPoint;
    QPointF m_endPoint;
    QPointF m_topLeft;
    QPointF m_bottomRight;
    QPointF m_start;
    QPointF m_end;

    bool m_isSelected = false;
};
#endif // !KRENDERLINESHAPE_H