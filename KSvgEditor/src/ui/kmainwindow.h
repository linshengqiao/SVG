// -------------------------------------------------------
// kmainwindow.h
// 创建者： 林声巧
// 创建时间： 2025/5/3
// 功能描述： 图表应用主窗口类，管理工具栏、画布和设置面板
// Copyright 2025 Kingsoft
// --------------------------------------------------------

#ifndef KMAINWINDOW_H
#define KMAINWINDOW_H

#include<QMainWindow>
#include "ktoolbarwidget.h"
#include "kcanvaswidget.h"
#include "kparametersettingwidget.h"

QT_BEGIN_NAMESPACE
namespace Ui { class KMainWindow; }
QT_END_NAMESPACE

class KMainWindow :public QMainWindow
{
	Q_OBJECT

public:
	KMainWindow(QWidget* parent = nullptr);
	~KMainWindow();

private:
	Ui::KMainWindow* m_ui;

	KToolBarWidget* m_pToolBarWidget;
	KCanvasWidget* m_pCanvasWidget;
	KParameterSettingWidget* m_pSettingWidget;
};
#endif // !KMAINWINDOW_H