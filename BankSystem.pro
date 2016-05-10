#-------------------------------------------------
#
# Project created by QtCreator 2016-05-01T16:43:08
#
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = BankSystem
TEMPLATE = app


SOURCES += main.cpp\
    logindialog.cpp \
    mainwindow.cpp \
    tableeditorwidget.cpp \
    clientaccountsdialog.cpp \
    accounttablemodel.cpp \
    accountdelegate.cpp \
    transactiontablewidget.cpp \
    transactiontablemodel.cpp \
    newtransaction.cpp

HEADERS  += \
    logindialog.h \
    mainwindow.h \
    tableeditorwidget.h \
    clientaccountsdialog.h \
    accounttablemodel.h \
    accountdelegate.h \
    transactiontablewidget.h \
    transactiontablemodel.h \
    newtransaction.h

FORMS    += banksystem.ui \
    clientlistwidget.ui \
    appartmentlistwidget.ui \
    clientaccountsdialog.ui \
    newtransaction.ui
