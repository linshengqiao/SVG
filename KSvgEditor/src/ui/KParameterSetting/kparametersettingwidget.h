// -------------------------------------------------------
// kparametersettingwidget.h
// 创建者： 林声巧
// 创建时间： 2025/5/4
// 功能描述： 右侧参数设置面板，管理画布和图形属性配置
// Copyright 2025 Kingsoft
// --------------------------------------------------------

#ifndef KPARAMETERSETTINGWIDGET_H
#define KPARAMETERSETTINGWIDGET_H

#include <QWidget>
#include <QSpinBox>
#include <QDoubleSpinBox>
#include <QPushButton>
#include <QComboBox>
#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QColorDialog>

class KParameterSettingWidget : public QWidget
{
    Q_OBJECT

public:
    KParameterSettingWidget(QWidget* parent);
    ~KParameterSettingWidget();

signals:
    void canvasWidthChanged(int width);
    void canvasHeightChanged(int height);
    void zoomFactorChanged(double factor);
    void canvasColorChanged(const QColor& color);
    void borderWidthChanged(int width);
    void borderColorChanged(const QColor& color);
    void borderStyleChanged(int styleIndex);
    void fillColorChanged(const QColor& color);
    

private slots:
    void onCanvasWidthChanged(int width);
    void onCanvasHeightChanged(int height);
    void onZoomFactorChanged(double factor);
    void onCanvasColorButtonClicked();
    void onBorderWidthChanged(int width);
    void onBorderColorButtonClicked();
    void onBorderStyleChanged(int index);
    void onFillColorButtonClicked();

private:
    void setupUI();

    QSpinBox* canvasWidthSpinBox;
    QSpinBox* canvasHeightSpinBox;
    QDoubleSpinBox* zoomFactorSpinBox;
    QPushButton* canvasColorButton;
    QLabel* canvasColorLabel;

    QSpinBox* borderWidthSpinBox;
    QComboBox* borderStyleComboBox;
    QPushButton* borderColorButton;
    QLabel* borderColorLabel;
    QPushButton* fillColorButton;
    QLabel* fillColorLabel;

    QVBoxLayout* mainLayout;
};
#endif // KPARAMETERSETTINGWIDGET_H