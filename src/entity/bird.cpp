#include "bird.h"
#include <QDebug>
#include <QKeyEvent>
#include <QGraphicsScene>
#include "pillar.h"

Bird::Bird(QString pathToPixmap)
    : m_pixmapSize(QSize(34, 24)), m_startPos(QPoint(5, 256)), m_index(0), m_loopTime(120)
{
    if(m_birdPixmap.load(pathToPixmap))
    {
        qDebug() << "Bird pixmap is loaded successfully";
    }
    else
    {
        qDebug() << "Bird pixmap is NOT loaded successfully";
    }
    connect(&m_timer, &QTimer::timeout, this, &Bird::updatePixmap);
    //setTransformOriginPoint(m_pixmapSize.width()/2, m_pixmapSize.height()/2);

    m_timer.start(m_loopTime);
    setPixmap(m_birdPixmap.copy(m_index*m_pixmapSize.width(), 0, m_pixmapSize.width(), m_pixmapSize.height()));

    m_yAnimation = new QPropertyAnimation(this,"y",this);
    m_yAnimation->setStartValue(scenePos().y());
    m_yAnimation->setEndValue(Game::RESOLUTION.height());
    m_yAnimation->setEasingCurve(QEasingCurve::InQuad);
    m_yAnimation->setDuration(2500);
    m_yAnimation->start();

    m_rotationAnimation = new QPropertyAnimation(this,"rotation",this);
}

const QPoint Bird::startPosition() const
{
    return m_startPos;
}

void Bird::updatePixmap()
{
    if(m_index < 2)
    {
        m_index += 1;
    }
    else
    {
        m_index = 0;
    }

    setPixmap(m_birdPixmap.copy(m_index*m_pixmapSize.width(), 0, m_pixmapSize.width(), m_pixmapSize.height()));
}

void Bird::rotateTo(const qreal &end, const int &duration, const QEasingCurve &curve)
{
    m_rotationAnimation->setStartValue(rotation());
    m_rotationAnimation->setEndValue(end);
    m_rotationAnimation->setEasingCurve(curve);
    m_rotationAnimation->setDuration(duration);

    m_rotationAnimation->start();
}

void Bird::fall()
{
    m_rotationAnimation->stop();

    m_yAnimation->setStartValue(y());
    m_yAnimation->setEasingCurve(QEasingCurve::InQuad);
    m_yAnimation->setEndValue(scene()->sceneRect().height());
    m_yAnimation->setDuration(1200);
    m_yAnimation->start();

    rotateTo(90,750,QEasingCurve::InCubic);
}

void Bird::jump()
{
    m_yAnimation->stop();


    qreal curPosY = y();

    m_yAnimation->setStartValue(curPosY);
    m_yAnimation->setEndValue(curPosY - scene()->sceneRect().height()/8);
    m_yAnimation->setEasingCurve(QEasingCurve::OutQuad);
    m_yAnimation->setDuration(285);

    connect(m_yAnimation,&QPropertyAnimation::finished,[=](){
       fall();
    });


    m_yAnimation->start();
    rotateTo(-20,200,QEasingCurve::OutCubic);
}

qreal Bird::rotation() const
{
    return m_rotation;
}

qreal Bird::y() const
{
    return m_y;
}

void Bird::setRotation(qreal rotation)
{
    m_rotation = rotation;

    QPointF c = boundingRect().center();

    QTransform t;
    t.translate(c.x(), c.y());
    t.rotate(rotation);
    t.translate(-c.x(), -c.y());
    setTransform(t);
}

void Bird::checkCollideWithGround()
{
    QList<QGraphicsItem*> collidedWithBird = collidingItems();
    foreach(QGraphicsItem* item, collidedWithBird)
    {
        if(item->data(QGraphicsItem::UserType+1).toString() == Game::FLOOR_ENTITY_TYPE )
        {
            emit collidedWithGround();
        }
    }
}

void Bird::setY(qreal y)
{
    moveBy(0,y-m_y);
    m_y = y;
    checkCollideWithGround();
}



void Bird::keyPressEvent(QKeyEvent *event)
{
    if(event->isAutoRepeat())
    {
        return;
    }
    switch (event->key()) {
        case Qt::Key_Space:
            jump();
            return;

        return;
    }
    QGraphicsPixmapItem::keyPressEvent(event);
}
