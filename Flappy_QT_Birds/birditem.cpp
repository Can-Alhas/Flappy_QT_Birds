#include "birditem.h"
#include <QTimer>
#include <QGraphicsScene>

BirdItem::BirdItem(QPixmap pixmap) : wingPosition(WingPosition::Up), wingDirection(0)
{
    setPixmap(pixmap);
    QTimer *birdWingsTimer = new QTimer(this);
    connect(birdWingsTimer, &QTimer::timeout,[=]()
    {
        updatePixmap();

    });



    birdWingsTimer->start(80);

    groundPosition = scenePos().y() + 290;


    yAnimation = new QPropertyAnimation(this,"y",this);
    yAnimation->setStartValue(scenePos().y());
    yAnimation->setEndValue(groundPosition);
    yAnimation->setEasingCurve(QEasingCurve::InQuad);
    yAnimation->setDuration(1000);

    yAnimation->start();

    rotationAnimation = new QPropertyAnimation(this, "rotation",this);
    rotateTo(90, 1200, QEasingCurve::InQuad);

}



qreal BirdItem::rotation() const
{
    return m_rotation;
}

void BirdItem::setRotation(qreal rotation)
{
    m_rotation = rotation;

    QPointF c = boundingRect().center();
    QTransform t;
    t.translate(c.x(), c.y());
    t.rotate(rotation);
    t.translate(-c.x(), -c.y());
    setTransform(t);
}

qreal BirdItem::y() const
{
    return m_y;
}

void BirdItem::shootUp()
{
    yAnimation->stop();
    rotationAnimation->stop();

    qreal curPosY = y();

    yAnimation->setStartValue(curPosY);
    yAnimation->setEndValue(curPosY - scene()->sceneRect().height()/8);
    yAnimation->setEasingCurve(QEasingCurve::OutCurve);
    yAnimation->setDuration(285);

    connect(yAnimation, &QPropertyAnimation::finished, [=]()
    {
            fallToGroundIfNeccessary();
    });

    yAnimation->start();

    rotateTo(-20, 200, QEasingCurve::OutCubic);
}

void BirdItem::setY(qreal newY)
{
    moveBy(0, newY-m_y);
    m_y = newY;
}

void BirdItem::rotateTo(const qreal &end, const int &duration, const QEasingCurve &curve)
{
    rotationAnimation->setStartValue(rotation());
    rotationAnimation->setEndValue(end);
    rotationAnimation->setEasingCurve(curve);
    rotationAnimation->setDuration(duration);

    rotationAnimation->start();
}

void BirdItem::fallToGroundIfNeccessary()
{
    if(y() < groundPosition){
        rotationAnimation->stop();
        //yAnimation->stop();

        yAnimation->setStartValue(y());
        yAnimation->setEasingCurve(QEasingCurve::InQuad);
        yAnimation->setEndValue(groundPosition);
        yAnimation->setDuration(1200);


        yAnimation->start();

        rotateTo(90, 1100, QEasingCurve::InCubic);

    }
}

void BirdItem::updatePixmap()
{
    if(wingPosition == WingPosition::Middle){

         if(wingDirection){
            //UP
            setPixmap(QPixmap(":/images/yellow_bird_up.png"));
            wingPosition = WingPosition::Up;
            wingDirection = 0;
         }else{
            //DOWN
            setPixmap(QPixmap(":/images/yellow_bird_down.png"));
            wingPosition = WingPosition::Down;
            wingDirection = 1;
         }
    }else{
        setPixmap(QPixmap(":/images/yellow_bird_middle.png"));
        wingPosition = WingPosition::Middle;
    }
}
