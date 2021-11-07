#include "HtmlDelegate.h"
#include <QTextDocument>
#include <QApplication>
#include <QAbstractTextDocumentLayout>
#include <QStyleOptionViewItem>
#include <QPainter>
#include <QSize>

void HtmlDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    QStyleOptionViewItem optionV = option;
    initStyleOption(&optionV, index);

    QStyle *style = optionV.widget? optionV.widget->style() : QApplication::style();

    QTextDocument doc;
    doc.setHtml(optionV.text);

    /// Painting item without text
    optionV.text = QString();
    style->drawControl(QStyle::CE_ItemViewItem, &optionV, painter);

    QAbstractTextDocumentLayout::PaintContext ctx;
    QRect textRect = style->subElementRect(QStyle::SE_ItemViewItemText, &optionV);

    painter->save();
    painter->translate(textRect.topLeft());
    painter->setClipRect(textRect.translated(-textRect.topLeft()));
    doc.documentLayout()->draw(painter, ctx);
    painter->restore();
}

QSize HtmlDelegate::sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    QStyleOptionViewItem optionV = option;
    initStyleOption(&optionV, index);

    QTextDocument doc;
    doc.setHtml(optionV.text);
    doc.setTextWidth(optionV.rect.width());
    return QSize(doc.idealWidth(), 24);
}
