#ifndef TRANSACTIONTABLEMODEL_H
#define TRANSACTIONTABLEMODEL_H

#include <QSqlRelationalTableModel>

class TransactionTableModel : public QSqlRelationalTableModel // egyedi táblamodell osztály az appartmanokra
{
    Q_OBJECT
public:
    TransactionTableModel(QObject* parent = 0);
    //QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const; // adatlekérdezés felüldefiniálása
    //bool setData(const QModelIndex& index, const QVariant& value, int role = Qt::EditRole); // adatbeállítás
    //int columnCount(const QModelIndex & parent = QModelIndex()) const; // oszlopszám felüldefiniálása

    void setClientID(int id){client_ID = id;}
private:
    void setupModel(); // adatok betöltése
    int client_ID;
private slots:
    //void model_BeforeInsert(int row,QSqlRecord& record);

};

#endif // TRANSACTIONTABLEMODEL_H
