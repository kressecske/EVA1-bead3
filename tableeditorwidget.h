#ifndef TABLEEDITORWIDGET_H
#define TABLEEDITORWIDGET_H

#include <QWidget>
#include <QTableView>
#include <QDialogButtonBox>
#include <QSqlTableModel>
#include <QAbstractItemDelegate>

class TableEditorWidget : public QWidget // általános táblaszerkesztő ablak
{
    Q_OBJECT
public:
    TableEditorWidget(QString title, QWidget *parent = 0);
    ~TableEditorWidget();

    void setModel(QSqlTableModel* model, QVector<int> hiddenColumns = QVector<int>());
    // modell és rejtett oszlopok beállítása
    void setModel(QSqlTableModel* model, QAbstractItemDelegate* delegate, QVector<int> hiddenColumns = QVector<int>());
    // modell, rejtett oszlopok és delegált beállítása

private slots:
    void addButton_Clicked();
    void removeButton_Clicked();
    void submitButton_Clicked();

private:
    void setupGui(QVector<int> hiddenColumns);

    QTableView* tableView;
    QSqlTableModel* tableModel;
    QDialogButtonBox* buttonBox;
    QPushButton* addButton;
    QPushButton* removeButton;
    QPushButton* submitButton;
    QPushButton* revertButton;
};

#endif // TABLEEDITORWIDGET_H
