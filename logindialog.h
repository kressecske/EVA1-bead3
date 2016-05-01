#ifndef LOGINDIALOG_H
#define LOGINDIALOG_H

#include <QDialog>
#include <QPushButton>
#include <QLineEdit>
#include "mainwindow.h"

class LoginDialog : public QDialog // bejelentkező dialógusablak
{
    Q_OBJECT
public:
    LoginDialog(QWidget *parent = 0);
    ~LoginDialog();

private slots:
    void login(); // bejelentkezés

private:
    MainWindow* mainWindow; // főablak

    QPushButton* okButton;
    QPushButton* cancelButton;
    QLineEdit* userNameEdit;
    QLineEdit* userPasswordEdit;
};
#endif // LOGINDIALOG_H
