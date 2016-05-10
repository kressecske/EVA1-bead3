#ifndef APPARTMENTRENTWIDGET_H
#define APPARTMENTRENTWIDGET_H

#include <QDialog>
#include <QSqlTableModel>

namespace Ui {
    class NewTransaction;
}

class NewTransaction : public QDialog // apartman foglaló dialógus
{
    Q_OBJECT

public:
    explicit NewTransaction(QWidget *parent = 0);
    ~NewTransaction();
    void setModel(QSqlTableModel* accountsModel,QSqlTableModel* transactionModel); // modellek beállítása

private slots:
    void rentButton_Clicked(); // foglalás

private:
    void setupGui();
    QString filter;
    Ui::NewTransaction *ui;

    QSqlTableModel* accountTableModel;
    QSqlTableModel* transactionTableModel;


};

#endif // APPARTMENTRENTWIDGET_H
