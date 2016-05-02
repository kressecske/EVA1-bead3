#ifndef ACCOUNTTABLEMODEL_H
#define ACCOUNTTABLEMODEL_H

#include <QSqlRelationalTableModel>

class AccountTableModel : public QSqlRelationalTableModel // egyedi táblamodell osztály az appartmanokra
{
    Q_OBJECT
public:
    AccountTableModel(QObject* parent = 0);
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const; // adatlekérdezés felüldefiniálása
    bool setData(const QModelIndex& index, const QVariant& value, int role = Qt::EditRole); // adatbeállítás

private:
    void setupModel(); // adatok betöltése
};

#endif // AccountTableModel
