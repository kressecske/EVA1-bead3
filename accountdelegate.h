#ifndef ACCOUNTDELEGATE_H
#define ACCOUNTDELEGATE_H

#include <QSqlRelationalDelegate>

class AccountDelegate: public QSqlRelationalDelegate // egyedi megjelenítő
{
    Q_OBJECT
public:
    AccountDelegate(QObject *parent = 0);
    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;
    // felüldefiniáljuk a kirajzoló műveletet
    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const;
    // szerkesztõmezõ létrehozása
    void setEditorData(QWidget *editor, const QModelIndex &index) const;
    // adatok beállítása
    void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const;
    // visszaírás az adatbázisba
private:
    QStringList shoreList() const; // a partok listájának betöltése
};


#endif // ACCOUNTDELEGATE_H
