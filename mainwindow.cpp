#include "mainwindow.h"

#include <QAction>
#include <QMenuBar>
#include <QSqlRelationalTableModel>
#include <QMessageBox>

MainWindow::MainWindow(int loginLevel, QWidget *parent) :
    QMainWindow(parent) // megkapjuk a bejelentkező felhasználó szintjét
{
    userLevel = loginLevel;

    mdiArea = new QMdiArea; // mdi ablakterület létrehozása
    mdiArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    mdiArea->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    setCentralWidget(mdiArea);

    userTableModel = 0;
    clientTableModel =0;
    accountTableModel =0;

    setupMenu();
    setupModels();

    setWindowTitle(trUtf8("Account Managment System"));
}

MainWindow::~MainWindow()
{
    delete clientListWidget;
    delete userTableModel;
    delete clientTableModel;
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    mdiArea->closeAllSubWindows(); // minden ablak bezárása
}


void MainWindow::userAction_Triggered()
{
    userEditorWidget = new TableEditorWidget(trUtf8("Felhasználók szerkesztése"), this);
    userEditorWidget->setModel(userTableModel);

    mdiArea->addSubWindow(userEditorWidget); // betöltjük beágyazott ablakként
    userEditorWidget->show();
}
void MainWindow::clientAction_Triggered()
{
    clientListWidget = new clientlistwidget(this);
    clientListWidget->setModel(clientTableModel,accountTableModel);
    mdiArea->addSubWindow(clientListWidget); // betöltjük beágyazott ablakként
    clientListWidget->show();

}

void MainWindow::setupMenu()
{
    //rentMenu = menuBar()->addMenu(trUtf8("&Foglalások")); // menü létrehozása

    administerMenu = menuBar()->addMenu(trUtf8("&Adminisztráció"));

    clientAction = new QAction(trUtf8("Client szerkesztése"), this);
    connect(clientAction, SIGNAL(triggered()), this, SLOT(clientAction_Triggered()));
    administerMenu->addAction(clientAction);

    userAction = new QAction(trUtf8("Felhasználók szerkesztése"), this);
    connect(userAction, SIGNAL(triggered()), this, SLOT(userAction_Triggered()));
    administerMenu->addAction(userAction);
    userAction->setVisible(userLevel == 0);
    // csak akkor engedélyezett, ha a felhasználó adminisztrátor
}

void MainWindow::setupModels()
{
    //Clients
    clientTableModel = new QSqlTableModel();
    clientTableModel->setTable("client");
    clientTableModel->setHeaderData(0, Qt::Horizontal, trUtf8("ID"));
    clientTableModel->setHeaderData(1, Qt::Horizontal, trUtf8("Name"));
    clientTableModel->setHeaderData(2, Qt::Horizontal, trUtf8("Address"));
    clientTableModel->setHeaderData(3, Qt::Horizontal, trUtf8("Phone"));
    clientTableModel->setEditStrategy(QSqlTableModel::OnManualSubmit);


    //Users
    userTableModel = new QSqlTableModel();
    userTableModel->setTable("user");
    userTableModel->setHeaderData(0, Qt::Horizontal, trUtf8("Felhasználónév"));
    userTableModel->setHeaderData(1, Qt::Horizontal, trUtf8("Teljes név"));
    userTableModel->setHeaderData(2, Qt::Horizontal, trUtf8("Jelszó"));
    userTableModel->setHeaderData(3, Qt::Horizontal, trUtf8("Szint"));
    userTableModel->setEditStrategy(QSqlTableModel::OnManualSubmit);

    //Accounts
    accountTableModel = new QSqlTableModel();
    accountTableModel->setTable("account");
    accountTableModel->setHeaderData(0, Qt::Horizontal, trUtf8("ID"));
    accountTableModel->setHeaderData(1, Qt::Horizontal, trUtf8("Number"));
    accountTableModel->setHeaderData(2, Qt::Horizontal, trUtf8("Create Date "));
    accountTableModel->setHeaderData(3, Qt::Horizontal, trUtf8("Closed"));
    accountTableModel->setHeaderData(4, Qt::Horizontal, trUtf8("Client ID"));
    accountTableModel->setEditStrategy(QSqlTableModel::OnManualSubmit);


}
