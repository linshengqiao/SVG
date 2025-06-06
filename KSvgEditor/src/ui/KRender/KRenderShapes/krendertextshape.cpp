#include "krendertextshape.h"
#include <QLineEdit>
#include <QFontMetricsF>

KRenderTextShape::KRenderTextShape(const QPointF& pos, const QString& text)
    : m_pos(pos), m_text(text), m_color(Qt::black)
{
    m_font.setPointSize(12);
}

void KRenderTextShape::draw(KIRender* pRender)
{
    if (pRender && !m_text.isEmpty())
        pRender->drawText(m_pos, m_text, m_font, m_color);
}

void KRenderTextShape::setText(const QString& text)
{
    m_text = text;
}

QString KRenderTextShape::getText() const
{
    return m_text;
}

bool KRenderTextShape::contains(const QPointF& point) const
{
    QFontMetricsF metrics(m_font);
    QRectF textSize = metrics.boundingRect(m_text.isEmpty() ? "Text" : m_text);
    QRectF textRect(m_pos, textSize.size());
    return textRect.contains(point);
}

QWidget* KRenderTextShape::createEditor(QWidget* parent)
{
    QLineEdit* editor = new QLineEdit(parent);
    editor->setFont(m_font);
    editor->setText(m_text);
    editor->setPlaceholderText("ÊäÈëÎÄ×Ö...");
    editor->setFrame(true);
    editor->setFocus();

    QFontMetricsF metrics(m_font);
    QRectF textSize = metrics.boundingRect("Text");
    editor->setGeometry(QRect(m_pos.toPoint(), textSize.size().toSize()));

    QObject::connect(editor, &QLineEdit::editingFinished, [this, editor]() {
        this->setText(editor->text());
        editor->deleteLater();
        });

    return editor;
}

KIRenderShape::Position KRenderTextShape::getPosition() const
{
    return KIRenderShape::Position{ m_pos.x(), m_pos.y() };
}