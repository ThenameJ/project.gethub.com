#include "mainwindow.h"
#include <QDebug>
MainWindow::MainWindow(QWidget *parent)
    : QWidget(parent)
{
    QPalette pe;
    pe.setColor(QPalette::Background,QColor(100,100,100));
    setAutoFillBackground(true);
    setPalette(pe);
    //setWindowFlags(Qt::WindowCloseButtonHint | Qt::MSWindowsFixedSizeDialogHint);
    init();
}

MainWindow::~MainWindow()
{

}

void MainWindow::init()
{
    QVBoxLayout *vlayout = new QVBoxLayout();
    vlayout->setSpacing(1);
    vlayout->setMargin(1);
    for(int i = 0; i < 4; i++) //行
    {
        QHBoxLayout *hlayout = new QHBoxLayout();
        hlayout->setSpacing(1);
        hlayout->setMargin(1);
        for(int j = 0; j < 4; j++) //列
        {
            int m = initRandn();
            PumpState *pumpOne = new PumpState(m);
            hlayout->addWidget(pumpOne);
        }
        vlayout->addLayout(hlayout);
    }

    if(layout())
        delete layout();

    setLayout(vlayout);

}


int MainWindow::initRandn()
{
    QTime time = QTime::currentTime();
    qsrand(time.msec()*qrand()*qrand()*qrand()*qrand()*qrand()*qrand());
    int randn = qrand() % 20;
    qDebug() << randn;
    if(randn < 1)
        randn = 3;
    return randn;
}
