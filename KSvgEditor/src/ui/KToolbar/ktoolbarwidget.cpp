#include "ktoolbarwidget.h"
#include <QLayout>
#include <QMap>
#include <QPushButton>
#include <QRadioButton>

KToolBarWidget::KToolBarWidget(QWidget* parent)
	: QWidget(parent)
{
	initUi();
}

void KToolBarWidget::onButtonClicked(QAbstractButton* button)
{
	if (!m_pButtonGroup)
		return;

	int id = m_pButtonGroup->checkedId();
	emit stateChanged(static_cast<State>(id));
}

QRadioButton* KToolBarWidget::createToolButton(const QString& text, State state)
{
	QRadioButton* btn = new QRadioButton(text, this);
	btn->setIcon(getIconFromState(state));
	btn->setToolTip(text + QString::fromStdWString(L"测试"));
	QString styleSheet = "QRadioButton::indicator { width: 0px; height: 0px; }"
						"QRadioButton:checked { background-color: lightblue; }";
	btn->setStyleSheet(styleSheet);
	m_pButtonGroup->addButton(btn, static_cast<int>(state));
	return btn;
}

void KToolBarWidget::initUi()
{
	QVBoxLayout* pVLayout = new QVBoxLayout();
	this->setLayout(pVLayout);

	m_pButtonGroup = new QButtonGroup(this);
	m_pButtonGroup->setExclusive(true);
	connect(m_pButtonGroup, qOverload<QAbstractButton*>(&QButtonGroup::buttonClicked), this, &KToolBarWidget::onButtonClicked);

	QRadioButton* select = createToolButton("select",State::Select);
	QRadioButton* freehand = createToolButton("freehand", State::Freehand);
	QRadioButton* line = createToolButton("line", State::Line);
	QRadioButton* ellipse = createToolButton("ellipse", State::Ellipse);
	QRadioButton* rectangle = createToolButton("rectangle", State::Rectangle);
	QRadioButton* pentagon = createToolButton("pentagon", State::Pentagon);
	QRadioButton* hexagon = createToolButton("hexagon", State::Hexagon);
	QRadioButton* star = createToolButton("star", State::Star);
	QRadioButton* text = createToolButton("text", State::Text);
	QRadioButton* zoom = createToolButton("zoom", State::Zoom);
	
	pVLayout->addWidget(select);
	pVLayout->addWidget(freehand);
	pVLayout->addWidget(line);
	pVLayout->addWidget(ellipse);
	pVLayout->addWidget(rectangle);
	pVLayout->addWidget(pentagon);
	pVLayout->addWidget(hexagon);
	pVLayout->addWidget(star);
	pVLayout->addWidget(text);
	pVLayout->addWidget(zoom);

	pVLayout->addStretch();
}

QIcon KToolBarWidget::getIconFromState(State state)
{
	static QMap<State, QString> s_iconMap = {
		{State::Select, "select.svg"},
		{State::Freehand,"freehand.svg"},
		{State::Line,"line.svg"},
		{State::Ellipse,"ellipse.svg"},
		{State::Rectangle,"rectangle.svg"},
		{State::Pentagon,"pentagon.svg"},
		{State::Hexagon,"hexagon.svg"},
		{State::Star,"star.svg"},
		{State::Text,"text.svg"},
		{State::Zoom,"zoom.svg"}
	};

	return QIcon(":/icons/icons/" + s_iconMap[state]);
}
