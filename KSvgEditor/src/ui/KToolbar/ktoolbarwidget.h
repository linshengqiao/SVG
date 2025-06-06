// -------------------------------------------------------
// ktoolbarwidget.h
// 创建者： 林声巧
// 创建时间： 2025/5/4
// 功能描述： 左侧工具栏控件，提供绘图工具选择和状态管理
// Copyright 2025 Kingsoft
// --------------------------------------------------------


#ifndef KTOOLBARWIDGET_H
#define KTOOLBARWIDGET_H

#include <Qwidget>
#include <QButtonGroup>
#include <QIcon>
#include <QRadioButton>

class KToolBarWidget : public QWidget
{
	Q_OBJECT

public:
	enum class State
	{
		Select = 0,
		Freehand,
		Line,
		Ellipse,
		Rectangle,
		Pentagon,
		Hexagon,
		Star,
		Text,
		Zoom
	};

	KToolBarWidget(QWidget* parent);

signals:
	void stateChanged(State state);

protected slots:
	void onButtonClicked(QAbstractButton* button);

protected:
	void initUi();
	QIcon getIconFromState(State state);

private:
	QButtonGroup* m_pButtonGroup = nullptr;
	QRadioButton* createToolButton(const QString & text, State state);
};
#endif // !KTOOLBARWIDGET_H