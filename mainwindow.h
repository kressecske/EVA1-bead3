#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMdiArea>


class MainWindow : public QMainWindow // főablak
{
    Q_OBJECT
public:
    MainWindow(int loginLevel, QWidget *parent = 0);
    ~MainWindow();

protected:
    void closeEvent(QCloseEvent *event); // ablak bezárása

private slots:


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
    QAction* customerAction;
    QAction* userAction;

};

#endif // MAINWINDOW_H
