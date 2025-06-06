// -------------------------------------------------------
// kshapefactory.h
// 创建者： 林声巧
// 创建时间： 2025/5/17
// 功能描述： 图形工厂类，根据工具栏状态创建对应的图形对象，实现图形对象的统一创建接口
// Copyright 2025 Kingsoft
// --------------------------------------------------------

#ifndef KSHAPEFACTORY_H
#define KSHAPEFACTORY_H

#include <QPointF>
#include <memory>
#include "ktoolbarwidget.h"

class KIRenderShape;

class KShapeFactory 
{
public:
    static std::shared_ptr<KIRenderShape> createShape
    (
        KToolBarWidget::State state,
        const QPointF& start,
        const QPointF& end
    );
};
#endif // KSHAPEFACTORY_H