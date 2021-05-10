#include "sensorsfront.h"
#include "ui_sensorsfront.h"

QColor SensorsFront::GradColors::DarkBlue(32, 57, 110, 255);
QColor SensorsFront::GradColors::Blue(109, 118, 183, 255);

QColor SensorsFront::GradColors::DarkGreen(176, 203, 31, 255);
QColor SensorsFront::GradColors::Green(Qt::white);

QColor SensorsFront::GradColors::DarkYellow(255, 237, 0, 255);
QColor SensorsFront::GradColors::Yellow(Qt::white);

QColor SensorsFront::GradColors::DarkOrange(239, 127, 26, 255);
QColor SensorsFront::GradColors::Orange(Qt::white);

QColor SensorsFront::GradColors::DarkRed(227, 30, 36, 255);
QColor SensorsFront::GradColors::Red(Qt::white);

double SensorsFront::Angles[] = {
        SENSOR_0_ANGLE,
        SENSOR_1_ANGLE,
        SENSOR_2_ANGLE,
        SENSOR_3_ANGLE,
        SENSOR_4_ANGLE
    };
int SensorsFront::BlocksRanges[] = {
        GREEN_BLOCK_TOP,
        GREEN_BLOCK_BOTTOM,
        YELLOW_BLOCK_TOP,
        YELLOW_BLOCK_BOTTOM,
        ORANGE_BLOCK_TOP,
        ORANGE_BLOCK_BOTTOM,
        RED_BLOCK_TOP,
        RED_BLOCK_BOTTOM
};


SensorsFront::SensorsFront(QWidget *parent) :
    QMainWindow(parent), ui(new Ui::SensorsFront)
{
    ui->setupUi(this);

}

SensorsFront::~SensorsFront()
{
    delete ui;
}

void SensorsFront::paintEvent(QPaintEvent *event)
{

    //QRect rec(550,120,200,100);
    /*QRect rec2(X_START,Y_START,X_WIDTH,Y_HEIGHT);
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

*/

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

///////////////////////
    //QRect RectBigger;
    //QRect RectSmaller;

    QRect Rect1(-400, -400, 800, 800);
    QRect Rect2(-365, -365, 730, 730);

    QPointF Rcenter(0, 0);

    /*for(int i = 0; i < 5; i++)
    {

        RectBigger = QRect(-400, -400, 800, 800);
        RectSmaller = QRect(-365, -365, 730, 730);
    }*/

    QPainterPath myPath;
    myPath.moveTo(Rcenter);

    myPath.arcTo(Rect1, 352.5, 15); // tworzy pierwszy wycinek kola (wysrodkowany wzgledem osi X)

    myPath.lineTo(Rcenter);
    myPath.arcTo(Rect2, 352.5, 15); // tworzy drugi wycinek kola (wysrodkowany wzgledem osi X)
    myPath.closeSubpath();

    QPainter painter2(this);

    painter2.setPen(myPen);
    painter2.setBrush(QColor(122, 163, 39)); // wstawia odpowiedni kolor
    painter2.rotate(-90); // obrót. Od teraz współrzednie są zamienione
    painter2.translate(-382.5, 0); // do pozycji (0, 0)
    painter2.translate(-300, 400); // ustawia na środek ekranu

    painter2.drawPath(myPath);
    ////////////////////////////////
}
