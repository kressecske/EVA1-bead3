#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMdiArea>
#include "tableeditorwidget.h"
#include "clientaccountsdialog.h"
#include "accounttablemodel.h"
#include "accountdelegate.h"
#include "transactiontablewidget.h"
#include "transactiontablemodel.h"
class MainWindow : public QMainWindow // főablak
{
    Q_OBJECT
public:
    MainWindow(int loginLevel, QWidget *parent = 0);
    ~MainWindow();

protected:
    void closeEvent(QCloseEvent *event); // ablak bezárása

private slots:
    void userAction_Triggered();
    void clientAction_Triggered();
    void clientTableView_DoubleClicked(const QModelIndex& index);
    void accountTableView_DoubleClicked(const QModelIndex& index);

private:
    void setupMenu(); // menü létrehozása
    void setupModels(); // modellek létrehozása

    int userLevel; // felhasználói szint
    QMdiArea* mdiArea;
    QMenu* rentMenu; // menük
    QMenu* administerMenu;

    QAction* rentListAction; // menüpontok
    QAction* rentMakeAction;
    QAction* cityAction;
    QAction* buildingAction;
    QAction* appartmentAction;
    QAction* seasonAction;


    QAction* clientAction;
    QAction* userAction;


    TableEditorWidget* clientEditorWidget;
    TableEditorWidget* userEditorWidget;
    TableEditorWidget *accountEditorWidget;
    TransactionTableWidget *transactionEditorWidget;


    QSqlTableModel* userTableModel;
    QSqlTableModel* clientTableModel;
    QSqlTableModel* accountTableModel;
    QSqlTableModel* transactionTableModel;

    AccountDelegate *accountDelegate;
};

#endif // MAINWINDOW_H
