#include "mainwindow.h"
#include "uimanager.h"
#include <QApplication>
#include <QDebug>
#include <QFont>
#include "server.h"
#include <QSharedMemory>
#include <keyhook.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    //程序打包后只允许运行一个单独程序
    static QSharedMemory *shareMem = new QSharedMemory("pumpSystem");
    if(!shareMem->create(1))
    {
        qApp->quit();
        return -1;
    }
    keyhook->initKeyHook();
    cmsserver->instance()->init();
    uimanager->setMessageQueue(cmsserver->instance()->getMessageQueue());
    uimanager->start();
    //
    QFont font = uimanager->getResource()->getFont(Cms::Res::Font_HarmonyOS_Sans_SC);
    font.setBold(false);
    font.setPixelSize(18);
    a.setFont(font);
    qDebug()<<"font family:" <<font.family();

    MainWindow w;
//    w.show();
    w.showFullScreen();
    return a.exec();
}
