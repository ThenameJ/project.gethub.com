#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "pumpstate.h"
#include <QVBoxLayout>
#include <QHBoxLayout>

class MainWindow : public QWidget
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

public:
    void init();
    int initRandn();

};

#endif // MAINWINDOW_H
