// -------------------------------------------------------
// kishape.h
// 创建者： 林声巧
// 创建时间： 2025/5/13
// 功能描述： 图形模型层，定义图形数据结构和基础属性
// Copyright 2025 Kingsoft
// --------------------------------------------------------

#ifndef KISHAPE_H
#define KISHAPE_H

#include <QString>
#include <QColor>
#include <QPointF>
#include <QRectF>

class IShape
{
public:
    enum ShapeType 
    {
        Rectangle,
        Ellipse,
        Line,
        Path,
        Text
    };

    virtual ~IShape() {}

    virtual ShapeType type() const = 0;
    virtual QString id() const = 0;
    virtual void setId(const QString& id) = 0;

    virtual QColor fillColor() const = 0;
    virtual void setFillColor(const QColor& color) = 0;

    virtual QColor strokeColor() const = 0;
    virtual void setStrokeColor(const QColor& color) = 0;

    virtual qreal strokeWidth() const = 0;
    virtual void setStrokeWidth(qreal width) = 0;

    virtual qreal opacity() const = 0;
    virtual void setOpacity(qreal opacity) = 0;

    virtual QPointF position() const = 0;
    virtual void setPosition(const QPointF& pos) = 0;

    virtual QPointF topLeft() const = 0;
    virtual void setTopLeft(const QPointF& point) = 0;

    virtual QPointF bottomRight() const = 0;
    virtual void setBottomRight(const QPointF& point) = 0;

    virtual QRectF boundingRect() const = 0;
};

class KBaseShape : public IShape
{
public:
    KBaseShape() = default;
    KBaseShape(ShapeType type, const QString& id = QString());

    virtual ~KBaseShape() override;

    virtual ShapeType type() const override;
    virtual QString id() const override;
    virtual void setId(const QString& id) override;

    virtual QColor fillColor() const override;
    virtual void setFillColor(const QColor& color) override;

    virtual QColor strokeColor() const override;
    virtual void setStrokeColor(const QColor& color) override;

    virtual qreal strokeWidth() const override;
    virtual void setStrokeWidth(qreal width) override;

    virtual qreal opacity() const override;
    virtual void setOpacity(qreal opacity) override;

    virtual QPointF position() const override;
    virtual void setPosition(const QPointF& pos) override;

    virtual QPointF topLeft() const override;
    virtual void setTopLeft(const QPointF& point) override;

    virtual QPointF bottomRight() const override;
    virtual void setBottomRight(const QPointF& point) override;

    virtual QRectF boundingRect() const override;

protected:
    virtual void updateGeometry();

private:
    ShapeType m_type;
    QString m_id;
    QColor m_fillColor;
    QColor m_strokeColor;
    qreal m_strokeWidth;
    qreal m_opacity;
    QPointF m_position;

protected:
    QPointF m_topLeft;
    QPointF m_bottomRight;
};
#endif // !KISHAPE_H