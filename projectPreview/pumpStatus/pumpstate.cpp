#include "pumpstate.h"
#include "qpainter.h"
#include <QDebug>
//输注颜色
//绿色 0,128,0
//蓝色 50,100,200
//红色 255,114,86
PumpState::PumpState(int pumpTime, QWidget *parent)
    : QWidget(parent)
{
    setWindowFlags(Qt::WindowCloseButtonHint | Qt::MSWindowsFixedSizeDialogHint);
    setMinimumSize(280,170);
    //setMaximumSize();
    unit = 0;
    color = QColor(255,114,86);
    randn = pumpTime;
    timer = new QTimer(this);
    timer->stop();
    timer->setTimerType(Qt::PreciseTimer);//高精度定时器 占用CPU资源
    timer->setInterval(1000);//每一秒触发一个timeout()信号
    connect(timer,SIGNAL(timeout()),this,SLOT(onTimeOut()));
    timer->start();
}


PumpState::~PumpState()
{

}

void PumpState::onTimeOut()
{
    unit += 1;
    //qDebug() << unit;
    if((randn*60-unit)/60 <= 3)
    {
        color = QColor(220,0,27);
    }
    else if((randn*60-unit)/60 > 3 && (randn*60-unit)/60 <= 7 )
    {
        color = QColor(255,114,86);
    }
    else if((randn*60-unit)/60 > 7 && (randn*60-unit)/60 <= 15)
    {
        color = QColor(50,100,200);
    }
    else
    {
        color = QColor(0,128,0);
    }
    if(unit >= randn*60)
    {
        timer->stop();
        qDebug() << "I am Quit " << timer->isActive();
    }
    this->update();
}


void PumpState::paintEvent(QPaintEvent *)
{


    h = rect().height();
    w = rect().width();
    //int side = qMin(w, h);
    qDebug()<< h << w;
    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing);//启动反锯齿
    painter.setBrush(QBrush(QColor(40,40,40)));
    painter.setPen(Qt::NoPen);
    painter.drawRoundedRect(rect(),5,5);

    rangeW = w/3;
    if(rangeW >= 150)
    {
        rangeW = 150;
    }
    else if(rangeW <= 120)
    {
        rangeW = 120;
    }
    rangeY = h/6;
    if(rangeY >= 50)
    {
        rangeY = 50;
    }
    else if(rangeY <= 38)
    {
        rangeY = 38;
    }

    double p = rangeW/rangeY;

    QRect bodyRect = QRect(0,0,rangeW,rangeY);
    bodyRect.moveCenter(QPoint(w/2,h/2));
    QRect changeRect = QRect(bodyRect.left(),bodyRect.top(),rangeW-unit*rangeW/randn/60,rangeY);
    QRect twoRect = QRect(bodyRect.right(),bodyRect.top()-rangeY/6,rangeW/20,rangeY*4/3);
    QRect threeRect = QRect(twoRect.right(),bodyRect.top()+bodyRect.height()/4,bodyRect.height()/2,bodyRect.height()/2);
    QRect fourRect = QRect(threeRect.right(),bodyRect.top()+rangeY/6,rangeW/20,bodyRect.height()-rangeY/3);
    QRectF arcRect = QRectF(0,0,rangeW/p*3/2,rangeY*3/2);
    arcRect.moveCenter(QPoint(w/2,h/2));
    arcRect.setLeft(bodyRect.left()-rangeW/12);
    arcRect.setRight(bodyRect.left()+arcRect.height());
    QRect oneRect = QRect(0,0,bodyRect.height()/3,bodyRect.height()/3);
    oneRect.moveCenter(QPoint(w/2,h/2));
    oneRect.setRight(arcRect.left());
    oneRect.setLeft(arcRect.left()-bodyRect.height()/4);

    QRect oneCricleRect = QRect(bodyRect.right(),twoRect.top()-rangeW/40,rangeW/20,rangeY*p/20);
    QRect secondCricleRect = QRect(bodyRect.right(),twoRect.bottom()-rangeW/40,rangeW/20,rangeY*p/20);
    QRect thirdCricleRect = QRect(threeRect.right(),fourRect.top()-rangeW/40,rangeW/20,rangeY*p/20);
    QRect fourCricleRect = QRect(threeRect.right(),fourRect.bottom()-rangeW/40,rangeW/20,rangeY*p/20);
    QPolygonF polygon;
    polygon << QPointF(oneRect.left()*2/3,h/2) << QPointF(oneRect.left(),h/2-bodyRect.height()/16)
            << QPointF(oneRect.left(),h/2+bodyRect.height()/16);

    QPointF scalePoint(bodyRect.left()+rangeW/26,bodyRect.bottom());
    QRect widgetRect = QRect(rect().left(),rect().top(),rect().width(),rect().height());
    QRect worldRect(bodyRect.left(),bodyRect.bottom()*5/4,rangeW,rangeY/2);
    QRect bedInfoRect = QRect(3,3,rangeW*7/8,rangeY*2/3);


    painter.save();
    //qDebug() << w << h;
    drawWhiteFrame(&painter,widgetRect);
    drawBody(&painter,bodyRect);
    drawRect(&painter,changeRect);
    drawRect(&painter,twoRect);

    drawRect(&painter,threeRect);
    drawRect(&painter,fourRect);
    drawOthers(&painter,arcRect);
    drawRect(&painter,oneRect);
    drawCricle(&painter,oneCricleRect);
    drawCricle(&painter,secondCricleRect);
    drawCricle(&painter,thirdCricleRect);
    drawCricle(&painter,fourCricleRect);
    drawTriangle(&painter,polygon);
    drawScale(&painter,scalePoint);
    drawWorld(&painter,"Nitroglycerin",worldRect);
    drawBedInfo(&painter,bedInfoRect,"Room88-99");
    int x = randn-unit/60;
    int y = -(unit - (randn - x) * 60);
    if(x>0)
    {
        drawTimeInfo(&painter,QString::number(x)+ "Min" +QString::number(y) + "s", bodyRect);
    }
    else
    {
        int m = randn*60-unit;
        drawTimeInfo(&painter,QString::number(m)+"s",bodyRect);
    }
    painter.restore();
}


void PumpState::drawBody(QPainter *painter, const QRect &rect)
{
    painter->save();
    painter->setPen(QPen(color,2));
    painter->drawRoundedRect(rect,1,1);
    //painter->fillRect(rect,red);
    painter->restore();
}


void PumpState::drawRect(QPainter *painter, const QRect &rect)
{
    painter->save();
    painter->drawRoundedRect(rect,1,1);
    painter->fillRect(rect,color);
    painter->restore();
}


void PumpState::drawOthers(QPainter *painter, const QRectF &rect)
{
    painter->save();
    painter->setBrush(Qt::NoBrush);
    painter->drawRect(rect);
    painter->setBrush(color);
    painter->drawChord(rect,139*16,82*16);
    painter->restore();
}


void PumpState::drawCricle(QPainter *painter, const QRect &rect)
{
    painter->save();
    painter->setBrush(Qt::NoBrush);
    painter->drawRect(rect);
    painter->setBrush(color);
//    painter->drawChord(rect,140*16,80*16);
    painter->drawEllipse(rect);
    painter->restore();
}


void PumpState::drawTriangle(QPainter *painter ,const QPolygonF &polygon)
{
    painter->save();
    painter->setBrush(color);
    painter->drawPolygon(polygon, Qt::WindingFill);
    painter->drawPolyline(polygon);
    painter->restore();
}


void PumpState::drawScale(QPainter *painter , QPointF &p)
{
    painter->save();
    painter->setPen(QColor(255,255,255));
    for(int i = 0; i < 25; i++)
    {
        if((i+1) % 5 == 0)
        {
            QPointF p1(p.x()+i*rangeW*7/180,p.y());
            QPointF p2(p.x()+i*rangeW*7/180,p.y()-p.y()/20);
            painter->drawLine(p1,p2);
            continue;
        }
        QPointF p1(p.x()+i*rangeW*7/180,p.y());
        QPointF p2(p.x()+i*rangeW*7/180,p.y()-p.y()/40);
        painter->drawLine(p1,p2);
    }
    painter->restore();
}


void PumpState::drawWhiteFrame(QPainter *painter, const QRect &rect)
{
    painter->save();
    painter->setPen(QPen(QColor(255,255,255),1));
    painter->drawRoundedRect(rect,3,3);
    painter->restore();
}


void PumpState::drawChangeBody(QPainter *painter,const QRect &rect)
{
    painter->save();
    painter->drawRoundedRect(rect,5,5);
    painter->fillRect(rect,color);
    painter->restore();
}


void PumpState::drawWorld(QPainter *painter, const QString &world,const QRect &rect)
{
    painter->save();
    QPen pen;
    pen.setColor(QColor(255,255,255));
    painter->setPen(pen);
    QFont mfont = painter->font();
    mfont.setBold(true);
    mfont.setPixelSize(rangeW/8);
    painter->setPen(pen);
    painter->setFont(mfont);
    painter->drawText(rect, Qt::AlignCenter, world);
    painter->restore();
}


void PumpState::drawBedInfo(QPainter *painter, const QRect &rect, const QString &world)
{
    painter->save();
    painter->setBrush(QBrush(QColor(220,220,220)));
    painter->setPen(Qt::NoPen);
    painter->drawRoundRect(rect,5,5);

    QPen pen;
    pen.setColor(QColor(40, 40, 40));
    painter->setPen(pen);
    QFont mfont = painter->font();
    mfont.setBold(true);
    mfont.setPixelSize(rangeW/8);
    painter->setFont(mfont);
    painter->drawText(rect, Qt::AlignCenter, world);

    painter->restore();
}


void PumpState::drawTimeInfo(QPainter *painter, const QString &world, const QRect &rect)
{

    //qDebug() << world;
    painter->save();
    painter->setPen(QPen(QColor(255,255,255)));
    QFont mfont = painter->font();
    mfont.setBold(true);
    mfont.setPixelSize(rangeW/8);
    painter->setFont(mfont);
    painter->drawText(rect, Qt::AlignCenter, world);
    painter->restore();
}


QColor PumpState::getColor() const
{
    return this->color;
}

void PumpState::setColor(const QColor &color)
{
    if (this->color != color)
    {
        this->color = color;
        this->update();
    }
}
