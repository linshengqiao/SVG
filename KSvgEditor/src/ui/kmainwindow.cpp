#include "kmainwindow.h"
#include "ui_kmainwindow.h"
#include <QWidget>
#include <QScrollArea>
#include "ktoolbarwidget.h"
#include "kcanvaswidget.h"
#include "kparametersettingwidget.h"

KMainWindow::KMainWindow(QWidget* parent)
    : QMainWindow(parent)
    , m_ui(new Ui::KMainWindow)
{
    m_ui->setupUi(this); 
    setWindowTitle("SVG");

    m_pToolBarWidget = new KToolBarWidget(this);
    m_pCanvasWidget = new KCanvasWidget(this);
    m_pSettingWidget = new KParameterSettingWidget(this);

    m_ui->horizontalLayout->addWidget(m_pToolBarWidget, 1);

    QFrame* vLine1 = new QFrame();
    vLine1->setFrameShape(QFrame::VLine);           
    vLine1->setFrameShadow(QFrame::Sunken);         
    vLine1->setLineWidth(1);                        
    m_ui->horizontalLayout->addWidget(vLine1);

    QScrollArea* scrollArea = new QScrollArea(this);
    scrollArea->setWidgetResizable(true);
    m_pCanvasWidget->setFixedSize({ 10000, 10000 });
    scrollArea->setWidget(m_pCanvasWidget);
    scrollArea->setContentsMargins(0, 0, 0, 0);
    m_ui->horizontalLayout->addWidget(scrollArea, 12);

    QFrame* vLine2 = new QFrame();
    vLine2->setFrameShape(QFrame::VLine);           
    vLine2->setFrameShadow(QFrame::Sunken);         
    vLine2->setLineWidth(1);                        
    m_ui->horizontalLayout->addWidget(vLine2);
    m_ui->horizontalLayout->addWidget(m_pSettingWidget, 2);

    connect(m_pToolBarWidget, &KToolBarWidget::stateChanged, m_pCanvasWidget, &KCanvasWidget::onToolStateChanged);
    connect(m_pToolBarWidget, &KToolBarWidget::stateChanged, this, [this](KToolBarWidget::State state) {
        QString str;
        switch (state)
        {
        case KToolBarWidget::State::Select : 
            str = "select";
            break;
        case KToolBarWidget::State::Freehand:
            str = "freehand";
            break;
        case KToolBarWidget::State::Line:
            str = "line";
            break;
        case KToolBarWidget::State::Ellipse:
            str = "ellipse";
            break;
        case KToolBarWidget::State::Rectangle:
            str = "rectangle";
            break;
        case KToolBarWidget::State::Pentagon:
            str = "pentagon";
            break;
        case KToolBarWidget::State::Hexagon:
            str = "hexagon";
            break;
        case KToolBarWidget::State::Star:
            str = "star";
            break;
        case KToolBarWidget::State::Text:
            str = "text";
            break;
        case KToolBarWidget::State::Zoom:
            str = "zoom";
            break;
        }
        this->setWindowTitle(str);

    });
}

KMainWindow::~KMainWindow()
{
    delete m_ui;
}
