#include "accounttablemodel.h"

AccountTableModel::AccountTableModel(QObject *parent):
    QSqlRelationalTableModel(parent)
{
    setupModel();
}
QVariant AccountTableModel::data(const QModelIndex &index, int role) const
{
    if(!index.isValid()) return QVariant();

    if (index.column() == 3)
    {
        switch (role)
        {
            case Qt::TextAlignmentRole:
                return QVariant(Qt::AlignCenter | Qt::AlignVCenter);
            case Qt::CheckStateRole: // a kijelölési szerep
                if (QSqlRelationalTableModel::data(index, Qt::DisplayRole).toInt() == 0)
                    // amennyiben nincs renoválás
                    return QVariant(Qt::Unchecked); // kijelölt állapotba helyezzük
                else
                    return QVariant(Qt::Checked);
            default:
                return QVariant(); // különben nem adunk vissza megjeleníthető adatot
        }
    }
    else
        return QSqlRelationalTableModel::data(this->index(index.row(), index.column()), role);
}

bool AccountTableModel::setData(const QModelIndex& index, const QVariant& value, int role)
{
    if (index.column() == 3 && role == Qt::CheckStateRole) // a foglalható oszlop
    {
        if (value.toInt() == Qt::Checked) // ha be lett jelölve
            return QSqlRelationalTableModel::setData(index, 0); // akkor jelezzük, hogy nincs renoválás alatt
        else
            return QSqlRelationalTableModel::setData(index, 1); // renoválás alatt van
    }
    else
        return QSqlRelationalTableModel::setData(index, value);

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
    setHeaderData(4, Qt::Horizontal, trUtf8("Client Id"));
    setRelation(4, QSqlRelation("client", "id", "id"));
}
