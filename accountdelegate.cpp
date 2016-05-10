#include "accountdelegate.h"

AccountDelegate::AccountDelegate(QObject *parent) :
    QSqlRelationalDelegate(parent)
{
}

void AccountDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option,const QModelIndex &index) const
{
       QItemDelegate::paint(painter, option, index);
}

QWidget *AccountDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
        return QSqlRelationalDelegate::createEditor(parent, option, index); // különben a szokványos szerkesztõmezõt használjuk
}

void AccountDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
       QSqlRelationalDelegate::setEditorData(editor, index);
}

void AccountDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
   QSqlRelationalDelegate::setModelData(editor, model, index);
}

