#include "kshapefactory.h"
#include "krenderfreehandshape.h"
#include "krenderlineshape.h"
#include "krenderellipseshape.h"
#include "krenderrectshape.h"
#include "krenderpentagonshape.h"
#include "krenderhexagonshape.h"
#include "krenderstarshape.h"
#include "krendertextshape.h"

std::shared_ptr<KIRenderShape> KShapeFactory::createShape
(
    KToolBarWidget::State state,
    const QPointF& start,
    const QPointF& end
)
{
    QColor strokeColor("#000000");
    QColor fillColor(Qt::white);
    double strokeWidth = 2.0;

    using State = KToolBarWidget::State;

    switch (state)
    {
    case State::Line:
        return std::make_shared<KRenderLineShape>(start, end, strokeColor, strokeWidth);

    case State::Ellipse:
        return std::make_shared<KRenderEllipseShape>(start, end, fillColor, strokeColor, strokeWidth);

    case State::Rectangle:
        return std::make_shared<KRenderRectShape>(start, end, fillColor, strokeColor, strokeWidth);

    case State::Pentagon:
        return std::make_shared<KRenderPentagonShape>(start, end, fillColor, strokeColor, strokeWidth);

    case State::Hexagon:
        return std::make_shared<KRenderHexagonShape>(start, end, fillColor, strokeColor, strokeWidth);

    case State::Star:
        return std::make_shared<KRenderStarShape>(start, end, fillColor, strokeColor, strokeWidth);

    case State::Freehand:
    {
        auto shape = std::make_shared<KRenderFreehandShape>(strokeColor, strokeWidth);
        shape->addPoint(start);
        shape->addPoint(end);
        return shape;
    }

    case State::Text:
        return std::make_shared<KRenderTextShape>(start, "Click to edit");

    default:
        return nullptr;
    }
}