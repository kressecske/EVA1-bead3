#include "clientlistwidget.h"
#include <QSqlQuery>
#include <QMessageBox>
#include "ui_clientlistwidget.h"

clientlistwidget::clientlistwidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::clientlistwidget)
{
    ui->setupUi(this);
    ui->retranslateUi(this);
    clientTableModel = 0;
    setWindowTitle(trUtf8("Clients list"));
}

clientlistwidget::~clientlistwidget(){
    delete ui;
}

void clientlistwidget::setModel(QSqlTableModel *clientModel,QSqlTableModel* accountModel){
    clientTableModel = clientModel;
    clientTableModel->select();

    accountTableModel = accountModel;
    accountTableModel->select();

    setupGui();
}
void clientlistwidget::clientTableView_DoubleClicked(const QModelIndex& index)
{
    QAbstractItemModel* model = ui->clientTableView->model();
    // lekérdezzük a nézethez tartozó modellt

    int clientID = model->index(index.row(), 0).data().toInt();
    QString clientName = model->index(index.row(), 1).data().toString(); // adatok lekérése

    // int available = model->data(model->index(index.row(), 5), Qt::CheckStateRole).toInt();
    // a foglalhatóság lekérése
    accountDialog->setClient(clientID, clientName);
    accountDialog->setModel(clientTableModel, accountTableModel);
    accountDialog->show(); // foglalási ablak megjelenítése

}
void clientlistwidget::setupGui()
{
    ui->clientTableView->setModel(clientTableModel);
    ui->clientTableView->resizeColumnsToContents();
    ui->clientTableView->setSelectionBehavior(QAbstractItemView::SelectRows); // teljes sor kijelölése
    ui->clientTableView->setEditTriggers(QAbstractItemView::NoEditTriggers); // a táblaszerkesztés kikapcsolása a megjelenítőn
    ui->clientTableView->setColumnHidden(0, true);


    accountDialog = new ClientAccountsDialog(this); // apartman foglaló ablak
    accountDialog->setModal(true);

    connect(ui->clientTableView, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(clientTableView_DoubleClicked(QModelIndex)));

}
