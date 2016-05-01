#include <QApplication>
#include <QMessageBox>
#include <QSqlDatabase>
#include "logindialog.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("localhost");
    db.setDatabaseName("banksystem");
    db.setUserName("kressecske");
    db.setPassword("test123");

    LoginDialog* loginDialog = new LoginDialog(); // bejelentkező ablak
    loginDialog->show();

    return a.exec();
}
