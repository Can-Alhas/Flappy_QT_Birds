#ifndef SCENE_H
#define SCENE_H

#include <QGraphicsScene>
#include <QTimer>
#include <pillaritem.h>
#include "birditem.h"

class Scene : public QGraphicsScene
{
    Q_OBJECT
public:
    explicit Scene(QObject *parent = nullptr);

    void addBird();
signals:

public slots:

private:
    void setUpPillarTimer();
    QTimer *pillarTimer;
    BirdItem *bird;

    // QGraphicsScene interface
protected:
    void keyPressEvent(QKeyEvent *event) override;
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
};

#endif // SCENE_H
