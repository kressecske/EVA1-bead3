#ifndef TRANSACTIONTABLEWIDGET_H
#define TRANSACTIONTABLEWIDGET_H
#include <QWidget>
#include <QTableView>
#include <QDialogButtonBox>
#include <QSqlTableModel>
#include <QAbstractItemDelegate>
#include <newtransaction.h>



class TransactionTableWidget : public QWidget // általános táblaszerkesztő ablak
{
    Q_OBJECT
public:
    TransactionTableWidget(QString title, QWidget *parent = 0);
    ~TransactionTableWidget();

    void setModel(QSqlTableModel* model, QVector<int> hiddenColumns = QVector<int>());
    // modell és rejtett oszlopok beállítása
    void setModel(QSqlTableModel* model, QAbstractItemDelegate* delegate, QVector<int> hiddenColumns = QVector<int>());
    // modell, rejtett oszlopok és delegált beállítása

    QTableView* tableView;
    QSqlTableModel* tableModel;
    QSqlTableModel* accountTableModel;


    void setClientTableModel(QSqlTableModel * clientModel);
    void setAccountTableModel(QSqlTableModel * accountModel);

private slots:

    void addButton_Clicked();
    void removeButton_Clicked();

private:
    void setupGui(QVector<int> hiddenColumns);

    NewTransaction* newTransaction;

    QDialogButtonBox* buttonBox;
    QPushButton* addButton;
    QPushButton* removeButton;
    QPushButton* revertButton;
};

#endif // TRANSACTIONTABLEWIDGET_H
