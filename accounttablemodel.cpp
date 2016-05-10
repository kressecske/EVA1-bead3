#include "accounttablemodel.h"
#include <QSqlQuery>
#include <QSqlRecord>
#include <QDebug>
AccountTableModel::AccountTableModel(QObject *parent):
    QSqlRelationalTableModel(parent)
{
    setupModel();

    //connect(this, SIGNAL(primeInsert(int,QSqlRecord&)), this, SLOT(model_BeforeInsert(int,QSqlRecord&)));

}
QVariant AccountTableModel::data(const QModelIndex &index, int role) const
{
    if(!index.isValid()) return QVariant();

    if (index.column() == 5 && role == Qt::TextAlignmentRole)
    {
        return QVariant(Qt::AlignRight | Qt::AlignVCenter);
    }

    if (index.column() == 3)
    {
        switch (role)
        {
            case Qt::TextAlignmentRole:
                return QVariant(Qt::AlignCenter | Qt::AlignVCenter);
            case Qt::CheckStateRole: // a kijelölési szerep
                if (QSqlRelationalTableModel::data(index, Qt::DisplayRole).toInt() != 0){
                    // amennyiben nincs renoválás
                    return QVariant(1); // kijelölt állapotba helyezzük
                }
                else
                    return QVariant(0);
            default:
                return QVariant(); // különben nem adunk vissza megjeleníthető adatot
        }
    }
    if (index.column() == 5 && role == Qt::DisplayRole) // apartmanok száma
    {
        QSqlQuery query;
        //qDebug()<<this->data(this->index(index.row(), 0)).toString();
        query.exec("select sum(ammount) from transaction where to_account_id="+this->data(this->index(index.row(), 1)).toString());
        QSqlQuery query1;
        query1.exec("select sum(ammount) from transaction where from_account_id="+this->data(this->index(index.row(), 1)).toString());


        if (query.next()){
            int bejovo = QVariant(query.value(0).toInt()).toInt();
            if(query1.next()){
                int sum = bejovo - QVariant(query1.value(0).toInt()).toInt();
                return QVariant(sum);
            }
            else
                return QVariant(0);
        }else
            return QVariant(0);
    }
    else
        return QSqlRelationalTableModel::data(this->index(index.row(), index.column()), role);
}

bool AccountTableModel::setData(const QModelIndex& index, const QVariant& value, int role)
{
    if (index.column() == 3 && role == Qt::CheckStateRole) // a foglalható oszlop
    {
        if (value.toInt() == Qt::Checked) // ha be lett jelölve
            return QSqlRelationalTableModel::setData(index, 1); // akkor jelezzük, hogy nincs renoválás alatt
        else
            return QSqlRelationalTableModel::setData(index, 0); // renoválás alatt van
    }
    else
        return QSqlRelationalTableModel::setData(index, value);

}

int AccountTableModel::columnCount(const QModelIndex& parent) const
{
    return QSqlRelationalTableModel::columnCount(parent) + 1;
}

void AccountTableModel::setupModel()
{
    setTable("account");
    setSort(1, Qt::AscendingOrder);
    setEditStrategy(QSqlTableModel::OnManualSubmit);
    setHeaderData(0, Qt::Horizontal, trUtf8("ID"));
    setHeaderData(1, Qt::Horizontal, trUtf8("Account Number"));
    setHeaderData(2, Qt::Horizontal, trUtf8("Create Date"));
    setHeaderData(3, Qt::Horizontal, trUtf8("Closed"));
    setHeaderData(4, Qt::Horizontal, trUtf8("client_ID"));
    setHeaderData(5, Qt::Horizontal, trUtf8("Osszeg")); // számított oszlop

    setRelation(4, QSqlRelation("client", "id", "name"));
}

void AccountTableModel::model_BeforeInsert(int row,QSqlRecord& record)
 {
    qDebug() << record.value(4).isNull();

    if (record.value(4).isNull()){ // ha nincs kitöltve a clientid
         record.setValue(4,client_ID);
         //record.setValue("client_ID", client_ID); // kitöltjük
         qDebug() << record.value(4);

    }
}
