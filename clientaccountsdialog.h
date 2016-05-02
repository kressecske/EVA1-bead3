#ifndef CLIENTACCOUNTSDIALOG_H
#define CLIENTACCOUNTSDIALOG_H

#include <QObject>
#include <QSqlTableModel>
#include <QWidget>
#include <QDialog>
#include <QSortFilterProxyModel>

namespace Ui{
    class clientaccountsdialog;
}

class ClientAccountsDialog : public QDialog
{
    Q_OBJECT
public:
    ClientAccountsDialog(QWidget *parent=0);
    ~ClientAccountsDialog();

    void setClient(int id, QString clientName); // apartman beállítása
    void setModel(QSqlTableModel* clientModel, QSqlTableModel* accountModel); // modellek beállítása

private slots:

private:
    void setupGui();

    Ui::clientaccountsdialog *ui;

    int clientId;
    QSqlTableModel* clientTableModel;
    QSqlTableModel* accountTableModel;
    QSortFilterProxyModel *clientIdSortFilterModel; // szűrő és rendező modellek
};

#endif // CLIENTACCOUNTSDIALOG_H
