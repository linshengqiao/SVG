// -------------------------------------------------------
// kcanvascontroller.h
// 创建者： 林声巧
// 创建时间： 2025/5/18
// 功能描述： 画布控制器类，只处理逻辑
// Copyright 2025 Kingsoft
// --------------------------------------------------------

#ifndef KCANVASCONTROLLER_H
#define KCANVASCONTROLLER_H

#include "ktoolbarwidget.h"
#include "kirendershape.h"
#include <QList>
#include <QPointF>
#include <Memory>

class QWidget;
class QPainter;
class QMouseEvent;
class QWheelEvent;

class KCanvasController : public QObject
{
    Q_OBJECT

public:
    KCanvasController(QWidget* parentWidget);

    void setToolState(KToolBarWidget::State state);
    KToolBarWidget::State currentToolState() const;

    void paint(QPainter* painter);
    void handleMousePress(QMouseEvent* event);
    void handleMouseMove(QMouseEvent* event);
    void handleMouseRelease(QMouseEvent* event);
    void handleDoubleClick(QMouseEvent* event);
    void handleWheel(QWheelEvent* event);

    double zoomLevel() const;
    int canvasWidth() const;
    int canvasHeight() const;

signals:
    void canvasWidthChanged(int width);
    void canvasHeightChanged(int height);
    void zoomFactorChanged(double factor);

private:
    QWidget* m_parentWidget;
    KToolBarWidget::State m_currentToolState;

    QList<std::shared_ptr<KIRenderShape>> m_shapes;
    QList<std::shared_ptr<KIRenderShape>> m_selectedShapes;

    bool m_isDrawing = false;
    bool m_hasMovedEnough = false;
    QPointF m_startPoint;
    std::shared_ptr<KIRenderShape> m_tempShape;
    QPointF m_dragOffset;

    double m_zoomLevel = 1.0;
    int m_originalWidth = 10000;
    int m_originalHeight = 10000;

    QPointF m_dragStartPos;
    bool m_isDragging = false;
    std::shared_ptr<KIRenderShape> m_draggedShape = nullptr;
};
#endif // KCANVASCONTROLLER_H