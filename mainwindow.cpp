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


    setupMenu();
    setupModels();

    setWindowTitle(trUtf8("Account Managment System"));
}

MainWindow::~MainWindow()
{

}

void MainWindow::closeEvent(QCloseEvent *event)
{
    mdiArea->closeAllSubWindows(); // minden ablak bezárása
}


void MainWindow::setupMenu()
{
    rentMenu = menuBar()->addMenu(trUtf8("&Foglalások")); // menü létrehozása

    rentListAction = new QAction(trUtf8("Foglalások listázása"), this); // menüpont létrehozása
    rentListAction->setStatusTip(trUtf8("A rendszerben lévő foglalások kilistázása."));
    //connect(rentListAction, SIGNAL(triggered()), this, SLOT(rentListAction_Triggered()));
    rentMenu->addAction(rentListAction); // felvétel a menühöz

    rentMakeAction = new QAction(trUtf8("Új foglalás"), this);
    rentMakeAction->setStatusTip(trUtf8("Új foglalás létrehozása."));
    //connect(rentMakeAction, SIGNAL(triggered()), this, SLOT(rentMakeAction_Triggered()));
    rentMenu->addAction(rentMakeAction);

    administerMenu = menuBar()->addMenu(trUtf8("&Adminisztráció"));

    cityAction = new QAction(trUtf8("Városok szerkesztése"), this);
    //connect(cityAction, SIGNAL(triggered()), this, SLOT(cityAction_Triggered()));
    administerMenu->addAction(cityAction);

    buildingAction = new QAction(trUtf8("Épületek szerkesztése"), this);
    //connect(buildingAction, SIGNAL(triggered()), this, SLOT(buildingAction_Triggered()));
    administerMenu->addAction(buildingAction);

    appartmentAction = new QAction(trUtf8("Apartmanok szerkesztése"), this);
    connect(appartmentAction, SIGNAL(triggered()), this, SLOT(appartmentAction_Triggered()));
    administerMenu->addAction(appartmentAction);

    seasonAction = new QAction(trUtf8("Szezonok szerkesztése"), this);
    //connect(seasonAction, SIGNAL(triggered()), this, SLOT(seasonAction_Triggered()));
    administerMenu->addAction(seasonAction);

    customerAction = new QAction(trUtf8("Vásárlók szerkesztése"), this);
    connect(customerAction, SIGNAL(triggered()), this, SLOT(customerAction_Triggered()));
    administerMenu->addAction(customerAction);

    userAction = new QAction(trUtf8("Felhasználók szerkesztése"), this);
   // connect(userAction, SIGNAL(triggered()), this, SLOT(userAction_Triggered()));
    administerMenu->addAction(userAction);
    userAction->setEnabled(userLevel == 0);
    // csak akkor engedélyezett, ha a felhasználó adminisztrátor
}

void MainWindow::setupModels()
{

}
