#include "mainwindow.h"

#include <QAction>
#include <QMenuBar>
#include <QSqlRelationalTableModel>
#include <QMessageBox>
#include <QDebug>
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
    delete accountDelegate;
    delete accountTableModel;
    delete userTableModel;
    delete clientTableModel;
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    mdiArea->closeAllSubWindows(); // minden ablak bezárása
}

void MainWindow::clientTableView_DoubleClicked(const QModelIndex& index)
{
    QAbstractItemModel* model = clientTableModel;
    // lekérdezzük a nézethez tartozó modellt

    int clientID = model->index(index.row(), 0).data().toInt();
    QString clientName = model->index(index.row(), 1).data().toString(); // adatok lekérése


    accountEditorWidget = new TableEditorWidget(trUtf8("Számlaszámok szerkesztése"), this);
    accountEditorWidget->setModel(accountTableModel,accountDelegate);
    accountEditorWidget->tableModel->setFilter("account.client_ID="+QString::number(clientID));
    //accountTableModel->setClientID(clientID);
    accountEditorWidget->tableView->setColumnHidden(0,true);
    accountEditorWidget->tableView->setColumnHidden(4,false);
    mdiArea->addSubWindow(accountEditorWidget);

    accountEditorWidget->show(); // foglalási ablak megjelenítése

    connect(accountEditorWidget->tableView, SIGNAL(doubleClicked(QModelIndex)),this,SLOT(accountTableView_DoubleClicked(QModelIndex)));
}
void MainWindow::accountTableView_DoubleClicked(const QModelIndex& index)
{
    QAbstractItemModel* model = accountTableModel;
    // lekérdezzük a nézethez tartozó modellt

    int accountNumber = model->index(index.row(), 1).data().toInt();

    bool open = true;
    //qDebug()<< model->index(index.row(), 3).data();

    if (!open){
        QMessageBox::information(this, trUtf8("Zárolva van a számla"), trUtf8("A számla zárolva van"), QMessageBox::Ok);
        return;
    }

    transactionEditorWidget = new TransactionTableWidget(trUtf8("Tranzakciók szerkesztése"), this);
    transactionEditorWidget->setModel(transactionTableModel);
    transactionEditorWidget->setAccountTableModel(accountTableModel);
    transactionEditorWidget->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    transactionEditorWidget->tableModel->setFilter("transaction.from_account_id="+QString::number(accountNumber) +" or transaction.to_account_id="+QString::number(accountNumber));
    //accountTableModel->setClientID(clientID);
    transactionEditorWidget->tableView->setColumnHidden(0,true);
    transactionEditorWidget->tableView->setColumnHidden(4,false);
    mdiArea->addSubWindow(transactionEditorWidget);

    transactionEditorWidget->show(); // foglalási ablak megjelenítése
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
    clientEditorWidget = new TableEditorWidget(trUtf8("Kliensek szerkesztése"), this);
    clientEditorWidget->setModel(clientTableModel);
    mdiArea->addSubWindow(clientEditorWidget);
    clientEditorWidget->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    clientEditorWidget->tableView->setColumnHidden(0, true);

    connect(clientEditorWidget->tableView, SIGNAL(doubleClicked(QModelIndex)),this,SLOT(clientTableView_DoubleClicked(QModelIndex)));

    clientEditorWidget->show();

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
    accountTableModel = new AccountTableModel();
    accountTableModel->select();

    accountDelegate  = new AccountDelegate();

    //Transactions
    transactionTableModel = new TransactionTableModel();
    transactionTableModel->select();
}
