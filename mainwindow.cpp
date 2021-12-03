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
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "server.h"
#include "eventid.h"
#include "workingspace.h"
#include "uimanager.h"
#include "systemmenuconfigwidget.h"
#include "baseclosemenupage.h"
#include <QHBoxLayout>
#include <QVBoxLayout>

MainWindow::MainWindow(QWidget *parent)
    : QWidget(parent)
{
    cmsserver->start();
    initWindow();

    connect(uimanager,&UIManager::sendCloseSignal,[&](){

        cmsserver->quit();

        close();
    });
    connect(uimanager,SIGNAL(sendOpenSystemConfig()),this,SLOT(onSlotOpenSystemConfig()));
}

MainWindow::~MainWindow()
{

}

void MainWindow::initWindow()
{
    WorkingSpace *workspace = new WorkingSpace(this);
    QHBoxLayout *hlayout = new QHBoxLayout();
    hlayout->setSpacing(0);
    hlayout->setMargin(0);
    hlayout->addWidget(workspace);
    //
    if (layout())
        delete layout();

    setLayout(hlayout);
}

void MainWindow::onSlotOpenSystemConfig()
{
    //SystemMenuConfigWidget *Demo = new SystemMenuConfigWidget();
//    BaseCloseMenuPage *systemConfigPage = new BaseCloseMenuPage(systemConfigMenu);
//    systemConfigPage->setParent(this);
//    systemConfigPage->setWindowFlags(Qt::FramelessWindowHint | Qt::Dialog);//窗口置顶且不阻塞其他程序
//    systemConfigPage->setAttribute(Qt::WA_QuitOnClose,false); //接收关闭事件
//    systemConfigPage->resize(800,700);
//    systemConfigPage->m_newTitleBar->setTitleText(tr("系统设置"));
//    systemConfigPage->show();
    systemConfigMenu->setParent(this);
    systemConfigMenu->setWindowFlags(Qt::FramelessWindowHint | Qt::Dialog);
    systemConfigMenu->setAttribute(Qt::WA_QuitOnClose,false); //接收关闭事件
    systemConfigMenu->resize(800,700);
    systemConfigMenu->m_newTitleBar->setTitleText(tr("系统设置"));
    systemConfigMenu->setInitItem();
    systemConfigMenu->show();
}
