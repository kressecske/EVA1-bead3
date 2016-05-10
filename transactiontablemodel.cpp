#include "transactiontablemodel.h"

TransactionTableModel::TransactionTableModel(QObject *parent):
    QSqlRelationalTableModel(parent)
{
    setupModel();
}

void TransactionTableModel::setupModel()
{
    setTable("transaction");
    setSort(1, Qt::AscendingOrder);
    setEditStrategy(QSqlTableModel::OnManualSubmit);
    setHeaderData(0, Qt::Horizontal, trUtf8("ID"));
    setHeaderData(1, Qt::Horizontal, trUtf8("Date"));
    setHeaderData(2, Qt::Horizontal, trUtf8("Ammount"));
    setHeaderData(3, Qt::Horizontal, trUtf8("From Account"));
    setHeaderData(4, Qt::Horizontal, trUtf8("To Account"));
    setRelation(3, QSqlRelation("account", "number", "number"));
    setRelation(4, QSqlRelation("account", "number", "number"));
}
