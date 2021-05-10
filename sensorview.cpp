#include "sensorview.h"
#include "ui_sensorview.h"

QColor SensorView::GradColors::DarkBlue(32, 57, 110, 255);
QColor SensorView::GradColors::Blue(109, 118, 183, 255);

QColor SensorView::GradColors::DarkGreen(176, 203, 31, 255);
QColor SensorView::GradColors::Green(Qt::white);

QColor SensorView::GradColors::DarkYellow(255, 237, 0, 255);
QColor SensorView::GradColors::Yellow(Qt::white);

QColor SensorView::GradColors::DarkOrange(239, 127, 26, 255);
QColor SensorView::GradColors::Orange(Qt::white);

QColor SensorView::GradColors::DarkRed(227, 30, 36, 255);
QColor SensorView::GradColors::Red(Qt::white);

SensorView::SensorView(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::SensorView)
{
    ui->setupUi(this);

}

SensorView::~SensorView()
{
    delete ui;
}

void SensorView::paintEvent(QPaintEvent *event)
{

    //QRect rec(550,120,200,100);
    QRect rec2(X_START,Y_START,X_WIDTH,Y_HEIGHT);
    QRect rec3(X_START+X_WIDTH+50,Y_START,X_WIDTH,Y_HEIGHT);
    QRect rec4(X_START+2*X_WIDTH+100,Y_START,X_WIDTH,Y_HEIGHT);
    QRect rec5(X_START+3*X_WIDTH+150,Y_START,X_WIDTH,Y_HEIGHT);
    QRect rec6(X_START+4*X_WIDTH+200,Y_START,X_WIDTH,Y_HEIGHT);

    QPainter painter(this);

    //
    //GradientTMP.setColorAt(0.5, Qt::yellow);

    QPointF center2(X_CENTER, Y_CENTER+Y_HEIGHT/2+10);
    QPointF center3(X_CENTER+X_WIDTH+50, Y_CENTER+Y_HEIGHT/2+5);
    QPointF center4(X_CENTER+2*X_WIDTH+100, Y_CENTER+Y_HEIGHT/2+5);
    QPointF center5(X_CENTER+3*X_WIDTH+150, Y_CENTER+Y_HEIGHT/2+5);
    QPointF center6(X_CENTER+4*X_WIDTH+200, Y_CENTER+Y_HEIGHT/2+5);

    //QLinearGradient gradient(rec.topLeft(), rec.bottomRight()); // diagonal gradient from top-left to bottom-right
    QRadialGradient grad2(center2, 30);
    QRadialGradient grad3(center3, 30);
    QRadialGradient grad4(center4, 30);
    QRadialGradient grad5(center5, 30);
    QRadialGradient grad6(center6, 30);

    //gradient.setColorAt(0, Qt::white);
    //gradient.setColorAt(1, Qt::red);

    grad2.setColorAt(0, GradColors::Blue);
    grad2.setColorAt(1, GradColors::DarkBlue);

    grad3.setColorAt(0, GradColors::Green);
    grad3.setColorAt(1, GradColors::DarkGreen);

    grad4.setColorAt(0, GradColors::Yellow);
    grad4.setColorAt(1, GradColors::DarkYellow);

    grad5.setColorAt(0, GradColors::Orange);
    grad5.setColorAt(1, GradColors::DarkOrange);

    grad6.setColorAt(0, GradColors::Red);
    grad6.setColorAt(1, GradColors::DarkRed);


    //painter.fillRect(rec, gradient);
    painter.fillRect(rec2, grad2);
    painter.fillRect(rec3, grad3);
    painter.fillRect(rec4, grad4);
    painter.fillRect(rec5, grad5);
    painter.fillRect(rec6, grad6);

    //painter.setBrush(Qt::RadialGradientPattern);
    //painter.setBrush(Qt::LinearGradientPattern);
    //painter.setBrush(GradientTMP);
    //painter.setBrush(Qt::SolidPattern);



    //pen.setColor(Qt::black);
    //pen.setWidth(5);

    //painter.setPen(pen);
    //painter.drawRect(rec);
    //QLinearGradient myGradient;
    QPen myPen;
    myPen.setStyle(Qt::NoPen);
    //myPen.setColor(QColor(79, 106, 25)
    //myPen.set 0, Qt::SolidLine, Qt::FlatCap, Qt::MiterJoin);

    QPointF center, startPoint;


    QRect Rect1(200, 200, 300, 300);
    QRect Rect2(150, 150, 400, 400);
    QPointF Rcenter(350, 350);

    QPainterPath myPath;
    myPath.moveTo(Rcenter);

    myPath.arcTo(Rect1, 315, 45);

    myPath.lineTo(Rcenter);
    myPath.arcTo(Rect2, 315, 45);
    myPath.closeSubpath();

    QPainter painter2(this);

    painter2.setPen(myPen);
    painter2.setBrush(QColor(122, 163, 39));

    painter2.drawPath(myPath);
}
