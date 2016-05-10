#include "transactiontablewidget.h"
#include <QMessageBox>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QSqlError>
#include <QDate>
#include <QDebug>
TransactionTableWidget::TransactionTableWidget(QString title, QWidget *parent) :
        QWidget(parent) // megkapjuk az ablak címét
{
    setWindowTitle(title);
    tableModel = 0;
    accountTableModel =0;
}

TransactionTableWidget::~TransactionTableWidget()
{
    delete newTransaction;
}

void TransactionTableWidget::setModel(QSqlTableModel* model, QVector<int> hiddenColumns)
// megkapjuk a táblamodellt és az elrejtendő oszlopok sorszámait
{
    newTransaction = new NewTransaction(this);
    newTransaction->setModal(true);

    tableModel = model; // betöltjük a modellt
    tableModel->select(); // frissítjük az adatokat

    setupGui(hiddenColumns);
}

void TransactionTableWidget::setModel(QSqlTableModel* model, QAbstractItemDelegate* delegate, QVector<int> hiddenColumns)
{
    setModel(model, hiddenColumns);
    tableView->setItemDelegate(delegate);
}

void TransactionTableWidget::addButton_Clicked()
{
   newTransaction->setModel(accountTableModel,tableModel);
   newTransaction->show();
}

void TransactionTableWidget::removeButton_Clicked()
{
    QModelIndex index = tableView->currentIndex(); // lekérdezzük az aktuális kijelölés indexét
    const QAbstractItemModel *model = index.model();
    if (index.isValid()) // ha érvényes az index
    {
        if (QMessageBox::question(this, trUtf8("Tranzakció sztórnozása"), trUtf8("Biztos sztornozza a tranzakciót?"), QMessageBox::Yes, QMessageBox::No) == QMessageBox::Yes)
        {
            tableModel->insertRow(index.row()+1); // sor beszúrása
            tableModel->setData(tableModel->index(index.row()+1,1), QDate::currentDate());
            tableModel->setData(tableModel->index(index.row()+1,2), model->index(index.row(),2).data().toString());
            tableModel->setData(tableModel->index(index.row()+1,3), model->index(index.row(),4).data().toString());
            tableModel->setData(tableModel->index(index.row()+1,4), model->index(index.row(),3).data().toString());



            tableModel->database().transaction(); // átváltunk tranzakciós üzemmódba

            if (tableModel->submitAll()) // végrehajtjuk a módosításokat, amennyiben sikerül
            {
                tableModel->database().commit(); // véglegesítünk
                tableModel->select(); // újra betöltjük a modellt
            } else
            {
                tableModel->database().rollback(); // különben visszavonunk
                QMessageBox::warning(this, trUtf8("Hiba történt a mentéskor!"), trUtf8("Az adatbázis a kvetkező hibát jelezte: %1").arg(tableModel->lastError().text()));
            }
        }
    }
    else // ha nincs érvényes kijelölés
    {
        QMessageBox::warning(this, trUtf8("Nincs kijelölés!"), trUtf8("Kérem jelölje ki előbb a törlendő sort!"));
    }
}

void TransactionTableWidget::setupGui(QVector<int> hiddenColumns)
{
    addButton = new QPushButton(trUtf8("&Tranzakció felvétele"));
    removeButton = new QPushButton(trUtf8("&Sztornó"));
    revertButton = new QPushButton(trUtf8("&Visszavonás"));

    buttonBox = new QDialogButtonBox(Qt::Vertical);
    buttonBox->addButton(addButton, QDialogButtonBox::ActionRole);
    buttonBox->addButton(removeButton, QDialogButtonBox::ActionRole);
    buttonBox->addButton(revertButton, QDialogButtonBox::ActionRole);

    connect(addButton, SIGNAL(clicked()), this, SLOT(addButton_Clicked()));
    connect(removeButton, SIGNAL(clicked()), this, SLOT(removeButton_Clicked()));
    connect(revertButton, SIGNAL(clicked()), tableModel, SLOT(revertAll())); // visszavonás a modell segítségével

    tableView = new QTableView(this);
    tableView->setModel(tableModel); // modell hozzákapcsolása a megjelenítőhöz
    tableView->setSelectionBehavior(QAbstractItemView::SelectItems); // kijelölés módja
    tableView->resizeColumnsToContents(); // oszlopok automatikus méretezése

    // ha vannak enrejtendő oszlopok
    for(int i = 0; i < hiddenColumns.size(); i++)
    {
        tableView->setColumnHidden(hiddenColumns[i], true); // akkor azokat elrejtjük
    }

    QHBoxLayout* mainLayout = new QHBoxLayout;
    mainLayout->addWidget(tableView);
    mainLayout->addWidget(buttonBox);
    setLayout(mainLayout);

}
void TransactionTableWidget::setAccountTableModel(QSqlTableModel* accountModel){
    accountTableModel = accountModel;
    accountTableModel->select();
}
