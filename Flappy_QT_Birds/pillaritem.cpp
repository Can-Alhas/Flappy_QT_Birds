#include "pillaritem.h"
#include <QRandomGenerator>
#include <QDebug>
#include <QGraphicsScene>

PillarItem::PillarItem():
    topPillar(new QGraphicsPixmapItem(QPixmap(":/images/pillar.png"))),

    bottomPillar(new QGraphicsPixmapItem(QPixmap(":/images/pillar.png")))


{

    topPillar->setPos(QPointF(0,0) - QPointF(topPillar->boundingRect().width()/2,
                                              topPillar->boundingRect().height() + 60));
    bottomPillar->setPos(QPointF(0,0) + QPointF(-bottomPillar->boundingRect().width()/2,
                                                 80));

    addToGroup(topPillar);
    addToGroup(bottomPillar);

    yPos = QRandomGenerator::global()->bounded(150);
    int xRandomizer = QRandomGenerator::global()->bounded(200);

    setPos(QPointF(0,0) + QPointF(260 + xRandomizer,yPos));


    xAnimation = new QPropertyAnimation(this, "x", this);
    xAnimation->setStartValue(260 + xRandomizer);
    xAnimation->setEndValue(-260);
    xAnimation->setEasingCurve(QEasingCurve::Linear);
    xAnimation->setDuration(1500);

    connect(xAnimation, &QPropertyAnimation::finished, [=]()
    {
        qDebug() << "animation FINISHED";
        scene()->removeItem(this);
        delete this;
    });

    xAnimation->start();




}

PillarItem::~PillarItem()
{
    qDebug() << "Deleting Pillar";
}

qreal PillarItem::x() const
{
    return m_x;
}

void PillarItem::setX(qreal x)
{
    qDebug() << "Pillar Position: " << x;
    m_x = x;

    setPos(QPoint(0,0) + QPointF(x,yPos));
}





