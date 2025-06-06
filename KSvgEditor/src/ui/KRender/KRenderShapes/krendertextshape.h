// -------------------------------------------------------
// krendertextshape.h
// 创建者： 林声巧
// 创建时间： 2025/5/14
// 功能描述： 文本框渲染实现类
// Copyright 2025 Kingsoft
// --------------------------------------------------------

#ifndef KRENDERTEXTSHAPE_H
#define KRENDERTEXTSHAPE_H

#include <QFont>
#include <QColor>
#include <QPointF>
#include <QString>
#include "kirendershape.h"

class QWidget;

class KRenderTextShape : public KIRenderShape
{
public:
    explicit KRenderTextShape(const QPointF& pos, const QString& text);

    void draw(KIRender* pRender) override;
    void updateByDrag(const QPointF& start, const QPointF& current) override {}
    bool contains(const QPointF& point) const override;

    void setText(const QString& text);
    QString getText() const;

    QWidget* createEditor(QWidget* parent) override;

    void setSelected(bool selected) override {}
    Position getPosition() const override;

private:
    QPointF m_pos;
    QFont m_font;
    QColor m_color;
    QString m_text;
};
#endif // KRENDERTEXTSHAPE_H