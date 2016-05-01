#include "tableeditorwidget.h"
#include <QMessageBox>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QSqlError>

TableEditorWidget::TableEditorWidget(QString title, QWidget *parent) :
        QWidget(parent) // megkapjuk az ablak címét
{    
    setWindowTitle(title);
}

TableEditorWidget::~TableEditorWidget()
{
}

void TableEditorWidget::setModel(QSqlTableModel* model, QVector<int> hiddenColumns)
// megkapjuk a táblamodellt és az elrejtendő oszlopok sorszámait
{
    tableModel = model; // betöltjük a modellt
    tableModel->select(); // frissítjük az adatokat

    setupGui(hiddenColumns);
}

void TableEditorWidget::setModel(QSqlTableModel* model, QAbstractItemDelegate* delegate, QVector<int> hiddenColumns)
{
    setModel(model, hiddenColumns);
    tableView->setItemDelegate(delegate);
}

void TableEditorWidget::addButton_Clicked()
{
    int row;
    if (tableView->currentIndex().isValid())  // lekérdezzük az aktuális kijelölés indexét, ha érvényes az index
    {
        row = tableView->currentIndex().row(); // sor beszúrása az aktuális helyre
    }
    else // ha nincs érvényes kijelölés
    {
        row = tableModel->rowCount(); // sor beszúrása a végére
    }

    tableModel->insertRow(row);
    QModelIndex newIndex = tableModel->index(row, 0); // az újonnan beszúrt sor indexe
    tableView->setCurrentIndex(newIndex); // beállítjuk a táblakijelölést az indexre
    tableView->edit(newIndex); // szerkesztés alá helyezzük az elemet
}

void TableEditorWidget::removeButton_Clicked()
{
    QModelIndex index = tableView->currentIndex(); // lekérdezzük az aktuális kijelölés indexét

    if (index.isValid()) // ha érvényes az index
    {
        tableModel->removeRow(index.row()); // töröljük a kijelölt sort
        tableView->setCurrentIndex(tableModel->index(index.row()-1, 0)); // beállítjuk a táblakijelölést az előző sorra
    }
    else // ha nincs érvényes kijelölés
    {
        QMessageBox::warning(this, trUtf8("Nincs kijelölés!"), trUtf8("Kérem jelölje ki előbb a törlendő sort!"));
    }
}

void TableEditorWidget::submitButton_Clicked()
{
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

void TableEditorWidget::setupGui(QVector<int> hiddenColumns)
{
    addButton = new QPushButton(trUtf8("&Beszúrás"));
    removeButton = new QPushButton(trUtf8("&Törlés"));
    submitButton = new QPushButton(trUtf8("&Mentés"));
    revertButton = new QPushButton(trUtf8("&Visszavonás"));

    buttonBox = new QDialogButtonBox(Qt::Vertical);
    buttonBox->addButton(addButton, QDialogButtonBox::ActionRole);
    buttonBox->addButton(removeButton, QDialogButtonBox::ActionRole);
    buttonBox->addButton(submitButton, QDialogButtonBox::ActionRole);
    buttonBox->addButton(revertButton, QDialogButtonBox::ActionRole);

    connect(addButton, SIGNAL(clicked()), this, SLOT(addButton_Clicked()));
    connect(removeButton, SIGNAL(clicked()), this, SLOT(removeButton_Clicked()));
    connect(submitButton, SIGNAL(clicked()), this, SLOT(submitButton_Clicked()));
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

