/**
* @FileName             %{Cpp:License:FileName}
* @Brief
* @Version              1.0.0
* @Current Maintainter
* @Update Date          2021-08-20
* @Author               luteng
* @email
* @Create Date          2021-08-20
* @
*/
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWidget>

class MainWindow : public QWidget
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    void initWindow();

private slots:
    void onSlotOpenSystemConfig();

};
#endif // MAINWINDOW_H
