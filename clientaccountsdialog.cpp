#include "clientaccountsdialog.h"
#include "ui_clientaccountsdialog.h"

ClientAccountsDialog::ClientAccountsDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::clientaccountsdialog)
{
    ui->setupUi(this);

    setWindowTitle(trUtf8("Client's' accounts"));

    clientTableModel = 0;
    accountTableModel = 0;
    clientIdSortFilterModel = new QSortFilterProxyModel();
}
ClientAccountsDialog::~ClientAccountsDialog()
{
    delete ui;
}

void ClientAccountsDialog::setClient(int id, QString clientName)
{
    clientId = id;
    ui->clientName->setText("Client Name: " + clientName);
}

void ClientAccountsDialog::setModel(QSqlTableModel* clientModel, QSqlTableModel* accountModel)
{
    clientTableModel = clientModel;
    accountTableModel = accountModel;

    QAbstractItemModel *currentModel = accountModel;

    clientIdSortFilterModel->setSourceModel(currentModel);
    clientIdSortFilterModel->setFilterKeyColumn(4);
    clientIdSortFilterModel->setFilterCaseSensitivity(Qt::CaseInsensitive);
    clientIdSortFilterModel->setFilterRegExp(QString::number(clientId));

    currentModel = clientIdSortFilterModel;


    setupGui();
}

void ClientAccountsDialog::setupGui()
{
    ui->accountTableView->setModel(clientIdSortFilterModel);
    ui->accountTableView->setColumnHidden(0,true);
    ui->accountTableView->setColumnHidden(4,true);
}
