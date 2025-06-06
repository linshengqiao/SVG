// -------------------------------------------------------
// kcanvaswidget.h
// 创建者： 林声巧
// 创建时间： 2025/5/4
// 功能描述： 中间画布控件，负责图形绘制和鼠标交互处理，只处理展示
// Copyright 2025 Kingsoft
// --------------------------------------------------------

#ifndef KCANVASWIDGET_H
#define KCANVASWIDGET_H

#include <QWidget>
#include "ktoolbarwidget.h"

class KCanvasController;

class KCanvasWidget : public QWidget
{
    Q_OBJECT

public:
    KCanvasWidget(QWidget* parent = nullptr);
    void paintEvent(QPaintEvent* event) override;
    void mousePressEvent(QMouseEvent* event) override;
    void mouseMoveEvent(QMouseEvent* event) override;
    void mouseReleaseEvent(QMouseEvent* event) override;
    void mouseDoubleClickEvent(QMouseEvent* event) override;
    void wheelEvent(QWheelEvent* event) override;

public slots:
    void onToolStateChanged(KToolBarWidget::State state);

signals:
    void canvasWidthChanged(int width);
    void canvasHeightChanged(int height);
    void zoomFactorChanged(double factor);

private:
    KCanvasController* m_controller;
};
#endif // KCANVASWIDGET_H