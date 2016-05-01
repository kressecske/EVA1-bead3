#ifndef CLIENTLISTWIDGET_H
#define CLIENTLISTWIDGET_H
#include <QWidget>
#include <QSqlTableModel>
#include <QItemSelectionModel>
#include <QSortFilterProxyModel>
#include <QItemDelegate>
#include "clientaccountsdialog.h"
namespace Ui{
    class clientlistwidget;
}

class clientlistwidget : public QWidget // client listázó ablak
{
    Q_OBJECT
public:
    explicit clientlistwidget(QWidget *parent = 0);
    ~clientlistwidget();

    void setModel(QSqlTableModel* clientModel,QSqlTableModel* accountModel);
private slots:
    void clientTableView_DoubleClicked(const QModelIndex& index);


private:
    Ui::clientlistwidget *ui;
    void setupFilter(); // beállító műveletek
    void setupModel();
    void setupGui();

    QSqlTableModel *clientTableModel;
    QSqlTableModel *accountTableModel;

    ClientAccountsDialog *accountDialog;

};

#endif // CLIENTLISTWIDGET_H
