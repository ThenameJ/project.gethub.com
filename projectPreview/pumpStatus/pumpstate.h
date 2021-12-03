#ifndef PUMPSTATE_H
#define PUMPSTATE_H

#include <QWidget>
#include <QTimer>
#include <QTime>
#include <math.h>

class PumpState : public QWidget
{
    Q_OBJECT

    Q_PROPERTY(QColor color READ getColor WRITE setColor)

public:
    PumpState(int pumpTime, QWidget *parent = 0);
    ~PumpState();

private:
    QTimer *timer;
    int h;
    int w;
    int rangeW;
    int rangeY;
    int value;
    double unit;
    int randn;
    QColor color;

private slots:
    void onTimeOut();

protected:
    void paintEvent(QPaintEvent *);

private:
    void drawBody(QPainter *painter, const QRect &rect);
    void drawRect(QPainter *painter, const QRect &rect);
    void drawOthers(QPainter *painter, const QRectF &rect);
    void drawCricle(QPainter *painter, const QRect &rect);
    void drawTriangle(QPainter *painter,const QPolygonF &polygon);
    void drawScale(QPainter *painter , QPointF &p);
    void drawWhiteFrame(QPainter *painter, const QRect &rect);
    void drawChangeBody(QPainter *painter,const QRect &rect);
    void drawWorld(QPainter *painter, const QString &world, const QRect &rect);
    void drawBedInfo(QPainter *painter, const QRect &rect, const QString &world);
    void drawTimeInfo(QPainter *painter, const QString &world, const QRect &rect);

    QColor getColor() const;

public slots:
    void setColor(const QColor &color);


};

#endif // PUMPSTATE_H
