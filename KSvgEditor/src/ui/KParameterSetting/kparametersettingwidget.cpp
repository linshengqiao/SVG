#include "kparametersettingwidget.h"
#include <QGroupBox>

#define STR2QString(str) QString::fromStdWString(L##str)

KParameterSettingWidget::KParameterSettingWidget(QWidget* parent) :
    QWidget(parent)
{
    setupUI();
}

KParameterSettingWidget::~KParameterSettingWidget()
{

}

void KParameterSettingWidget::setupUI()
{
    mainLayout = new QVBoxLayout(this);
    mainLayout->setSpacing(10);
    mainLayout->setContentsMargins(10, 10, 10, 10);

    QHBoxLayout* row1Layout = new QHBoxLayout();

    QGroupBox* canvasWidthGroup = new QGroupBox("", this);
    QVBoxLayout* canvasWidthLayout = new QVBoxLayout(canvasWidthGroup);
    QLabel* canvasWidthLabel = new QLabel(STR2QString("画布宽度"), canvasWidthGroup);
    canvasWidthSpinBox = new QSpinBox(canvasWidthGroup);
    canvasWidthSpinBox->setRange(100, 3000);
    canvasWidthSpinBox->setValue(800);
    canvasWidthLayout->addWidget(canvasWidthLabel);
    canvasWidthLayout->addWidget(canvasWidthSpinBox);
    row1Layout->addWidget(canvasWidthGroup);

    QGroupBox* canvasHeightGroup = new QGroupBox("", this);
    QVBoxLayout* canvasHeightLayout = new QVBoxLayout(canvasHeightGroup);
    QLabel* canvasHeightLabel = new QLabel(STR2QString("画布高度"), canvasHeightGroup);
    canvasHeightSpinBox = new QSpinBox(canvasHeightGroup);
    canvasHeightSpinBox->setRange(100, 3000);
    canvasHeightSpinBox->setValue(600);
    canvasHeightLayout->addWidget(canvasHeightLabel);
    canvasHeightLayout->addWidget(canvasHeightSpinBox);
    row1Layout->addWidget(canvasHeightGroup);

    mainLayout->addLayout(row1Layout);

    QHBoxLayout* row2Layout = new QHBoxLayout();

    QGroupBox* zoomFactorGroup = new QGroupBox("", this);
    QVBoxLayout* zoomFactorLayout = new QVBoxLayout(zoomFactorGroup);
    QLabel* zoomFactorLabel = new QLabel(STR2QString("缩放比例"), zoomFactorGroup);
    zoomFactorSpinBox = new QDoubleSpinBox(zoomFactorGroup);
    zoomFactorSpinBox->setRange(0.1, 10.0);
    zoomFactorSpinBox->setSingleStep(0.1);
    zoomFactorSpinBox->setValue(1.0);
    zoomFactorSpinBox->setSuffix("x");
    zoomFactorLayout->addWidget(zoomFactorLabel);
    zoomFactorLayout->addWidget(zoomFactorSpinBox);
    row2Layout->addWidget(zoomFactorGroup);

    QGroupBox* canvasColorGroup = new QGroupBox("", this);
    QVBoxLayout* canvasColorLayout = new QVBoxLayout(canvasColorGroup);
    QLabel* canvasColorLabelText = new QLabel(STR2QString("画布颜色"), canvasColorGroup);
    canvasColorButton = new QPushButton(STR2QString("选择颜色"), canvasColorGroup);
    canvasColorLabel = new QLabel(canvasColorGroup);
    canvasColorLabel->setFixedSize(24, 24);
    canvasColorLabel->setFrameShape(QFrame::Box);
    canvasColorLabel->setStyleSheet("background-color: white; border: 1px solid #ccc;");
    canvasColorLayout->addWidget(canvasColorLabelText);
    canvasColorLayout->addWidget(canvasColorButton);
    canvasColorLayout->addWidget(canvasColorLabel);
    row2Layout->addWidget(canvasColorGroup);

    mainLayout->addLayout(row2Layout);

    QHBoxLayout* row3Layout = new QHBoxLayout();

    QGroupBox* borderWidthGroup = new QGroupBox("", this);
    QVBoxLayout* borderWidthLayout = new QVBoxLayout(borderWidthGroup);
    QLabel* borderWidthLabel = new QLabel(STR2QString("边框宽度"), borderWidthGroup);
    borderWidthSpinBox = new QSpinBox(borderWidthGroup);
    borderWidthSpinBox->setRange(0, 20);
    borderWidthSpinBox->setValue(1);
    borderWidthLayout->addWidget(borderWidthLabel);
    borderWidthLayout->addWidget(borderWidthSpinBox);
    row3Layout->addWidget(borderWidthGroup);

    QGroupBox* borderStyleGroup = new QGroupBox("", this);
    QVBoxLayout* borderStyleLayout = new QVBoxLayout(borderStyleGroup);
    QLabel* borderStyleLabel = new QLabel(STR2QString("边框样式"), borderStyleGroup);
    borderStyleComboBox = new QComboBox(borderStyleGroup);
    borderStyleComboBox->addItems({ 
        STR2QString("实线"),
        STR2QString("虚线"), 
        STR2QString("点线"),
        STR2QString("点划线"),
        STR2QString("双点划线") 
    });

    borderStyleLayout->addWidget(borderStyleLabel);
    borderStyleLayout->addWidget(borderStyleComboBox);
    row3Layout->addWidget(borderStyleGroup);

    mainLayout->addLayout(row3Layout);

    QHBoxLayout* row4Layout = new QHBoxLayout();

    QGroupBox* borderColorGroup = new QGroupBox("", this);
    QVBoxLayout* borderColorLayout = new QVBoxLayout(borderColorGroup);
    QLabel* borderColorLabelText = new QLabel(STR2QString("边框颜色"), borderColorGroup);
    borderColorButton = new QPushButton(STR2QString("选择颜色"), borderColorGroup);
    borderColorLabel = new QLabel(borderColorGroup);
    borderColorLabel->setFixedSize(20, 20);
    borderColorLabel->setStyleSheet("background-color: black; border: 1px solid #ccc;");
    borderColorLayout->addWidget(borderColorLabelText);
    borderColorLayout->addWidget(borderColorButton);
    borderColorLayout->addWidget(borderColorLabel);
    row4Layout->addWidget(borderColorGroup);

    QGroupBox* fillColorGroup = new QGroupBox("", this);
    QVBoxLayout* fillColorLayout = new QVBoxLayout(fillColorGroup);
    QLabel* fillColorLabelText = new QLabel(STR2QString("填充颜色"), fillColorGroup);
    fillColorButton = new QPushButton(STR2QString("选择颜色"), fillColorGroup);
    fillColorLabel = new QLabel(fillColorGroup);
    fillColorLabel->setFixedSize(20, 20);
    fillColorLabel->setStyleSheet("background-color: transparent; border: 1px solid #ccc;");
    fillColorLayout->addWidget(fillColorLabelText);
    fillColorLayout->addWidget(fillColorButton);
    fillColorLayout->addWidget(fillColorLabel);
    row4Layout->addWidget(fillColorGroup);

    mainLayout->addLayout(row4Layout);
    mainLayout->addStretch();

    connect(canvasWidthSpinBox, QOverload<int>::of(&QSpinBox::valueChanged),
        this, &KParameterSettingWidget::onCanvasWidthChanged);
    connect(canvasHeightSpinBox, QOverload<int>::of(&QSpinBox::valueChanged),
        this, &KParameterSettingWidget::onCanvasHeightChanged);
    connect(zoomFactorSpinBox, QOverload<double>::of(&QDoubleSpinBox::valueChanged),
        this, &KParameterSettingWidget::onZoomFactorChanged);
    connect(canvasColorButton, &QPushButton::clicked,
        this, &KParameterSettingWidget::onCanvasColorButtonClicked);
    connect(borderWidthSpinBox, QOverload<int>::of(&QSpinBox::valueChanged),
        this, &KParameterSettingWidget::onBorderWidthChanged);
    connect(borderColorButton, &QPushButton::clicked,
        this, &KParameterSettingWidget::onBorderColorButtonClicked);
    connect(borderStyleComboBox, QOverload<int>::of(&QComboBox::currentIndexChanged),
        this, &KParameterSettingWidget::onBorderStyleChanged);
    connect(fillColorButton, &QPushButton::clicked,
        this, &KParameterSettingWidget::onFillColorButtonClicked);
}

void KParameterSettingWidget::onCanvasWidthChanged(int width)
{
    emit canvasWidthChanged(width);
}

void KParameterSettingWidget::onCanvasHeightChanged(int height)
{
    emit canvasHeightChanged(height);
}

void KParameterSettingWidget::onZoomFactorChanged(double factor)
{
    emit zoomFactorChanged(factor);
}

void KParameterSettingWidget::onCanvasColorButtonClicked()
{
    QColor color = QColorDialog::getColor(Qt::white, this, "选择画布颜色");
    if (color.isValid()) {
        canvasColorLabel->setStyleSheet(QString("background-color: %1").arg(color.name()));
        emit canvasColorChanged(color);
    }
}

void KParameterSettingWidget::onBorderWidthChanged(int width)
{
    emit borderWidthChanged(width);
}

void KParameterSettingWidget::onBorderColorButtonClicked()
{
    QColor color = QColorDialog::getColor(Qt::black, this, "选择边框颜色");
    if (color.isValid()) {
        borderColorLabel->setStyleSheet(QString("background-color: %1; border: 1px solid #ccc;").arg(color.name()));
        emit borderColorChanged(color);
    }
}

void KParameterSettingWidget::onBorderStyleChanged(int index)
{
    emit borderStyleChanged(index);
}

void KParameterSettingWidget::onFillColorButtonClicked()
{
    QColor color = QColorDialog::getColor(Qt::transparent, this, "选择填充颜色");
    if (color.isValid()) {
        fillColorLabel->setStyleSheet(QString("background-color: %1; border: 1px solid #ccc;").arg(color.name()));
        emit fillColorChanged(color);
    }
}