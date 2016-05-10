#include "newtransaction.h"
#include "ui_newtransaction.h"
#include <QMessageBox>
#include <QDate>
#include <QDebug>
#include <QSqlError>

NewTransaction::NewTransaction(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NewTransaction)
{
    ui->setupUi(this);

    setWindowTitle(trUtf8("Apartman foglalása"));

    accountTableModel = 0;
    transactionTableModel = 0;
}

NewTransaction::~NewTransaction()
{
    delete ui;
}

void NewTransaction::rentButton_Clicked()
{
    if (ui->ammountEdit->text().toInt() <=0 ){
        QMessageBox::warning(this, trUtf8("Hiba!"), trUtf8("Nem lehet 0 vagy negativ szám az összeg!"));
        return;
    }


    if (ui->FromAccountBox->currentText() == ui->ToAccountBox->currentText())
    // ha a befejező dátum nem több, mint a kezdő dátum
    {
        QMessageBox::warning(this, trUtf8("Hiba!"), trUtf8("Azonos számlára nem utalhat!"));
        return;
    }

    if (QMessageBox::question(this, trUtf8("Foglalás rögzítése"), trUtf8("Biztos rögzíti a foglalást?"), QMessageBox::Yes, QMessageBox::No) == QMessageBox::Yes)
    {
        transactionTableModel->insertRow(0); // sor beszúrása
        transactionTableModel->setData(transactionTableModel->index(0,1), QDate::currentDate());
        transactionTableModel->setData(transactionTableModel->index(0,2), ui->ammountEdit->text()); // apartman
        transactionTableModel->setData(transactionTableModel->index(0,3), ui->FromAccountBox->currentText());
        transactionTableModel->setData(transactionTableModel->index(0,4), ui->ToAccountBox->currentText());



        //qDebug()<<ui->FromAccountBox->currentText() + "   " + ui->ToAccountBox->currentText();
        transactionTableModel->database().transaction(); // átváltunk tranzakciós üzemmódba

        if (transactionTableModel->submitAll()) // végrehajtjuk a módosításokat, amennyiben sikerül
        {
            transactionTableModel->database().commit(); // véglegesítünk
            transactionTableModel->select(); // újra betöltjük a modellt
        } else
        {
            transactionTableModel->database().rollback(); // különben visszavonunk
            QMessageBox::warning(this, trUtf8("Hiba történt a mentéskor!"), trUtf8("Az adatbázis a kvetkező hibát jelezte: %1").arg(transactionTableModel->lastError().text()));
        }
        accountTableModel->setFilter(filter);
        close(); // ablak bezárása
    }
}



void NewTransaction::setModel(QSqlTableModel* accountsModel,QSqlTableModel* transactionModel)
{
    accountTableModel = accountsModel;  // átvesszük a modelleket
    accountTableModel->select(); // lekérjük a friss adatokat
    filter = accountTableModel->filter();
    accountTableModel->setFilter("");
    transactionTableModel = transactionModel;
    transactionTableModel->select();

    setupGui();
}

void NewTransaction::setupGui()
{
    ui->FromAccountBox->clear();
    ui->ToAccountBox->clear();
    for (int i = 0; i < accountTableModel->rowCount(); i++) // végigmegyünk az ügyfeleken
    {
        ui->FromAccountBox->addItem(accountTableModel->index(i, 1).data().toString()); // egy ügyfél felvétele
        ui->ToAccountBox->addItem(accountTableModel->index(i, 1).data().toString()); // egy ügyfél felvétele

    }
    ui->dateLabel->setText(QDate::currentDate().toString());

    connect(ui->rentButton, SIGNAL(clicked()), this, SLOT(rentButton_Clicked()));
}
