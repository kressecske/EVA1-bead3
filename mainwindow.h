#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMdiArea>
#include "tableeditorwidget.h"
#include "clientlistwidget.h"
#include "clientaccountsdialog.h"
#include "accounttablemodel.h"
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


    clientlistwidget* clientListWidget;
    TableEditorWidget* userEditorWidget;


    QSqlTableModel* userTableModel;
    QSqlTableModel* clientTableModel;
    QSqlTableModel* accountTableModel;


};

#endif // MAINWINDOW_H
