#include "pillar.h"
#include <QRandomGenerator>
#include <QGraphicsScene>
#include "../game.h"
#include "bird.h"

Pillar::Pillar()
    : m_topPillar(new QGraphicsPixmapItem(Game::PATH_TO_PILLAR_PIXMAP)),
      m_bottomPillar(new QGraphicsPixmapItem(Game::PATH_TO_PILLAR_PIXMAP)),
      m_pastBird(false), MARGINAL_VALUE(260)
{
    m_topPillar->setPos(QPointF(0,0) - QPointF(m_topPillar->boundingRect().width()/2, Game::GAP_SIZE));
    m_topPillar->setTransformOriginPoint(QPointF(m_topPillar->boundingRect().width()/2, m_topPillar->boundingRect().height()/2));
    m_topPillar->setRotation(180);

    m_bottomPillar->setPos(QPointF(0,0) + QPointF(-m_bottomPillar->boundingRect().width()/2, m_topPillar->boundingRect().height()));

    addToGroup(m_topPillar);
    addToGroup(m_bottomPillar);

    m_yPos = QRandomGenerator::global()->bounded(Game::RANGE_OF_Y_FOR_PILLARS.x(), Game::RANGE_OF_Y_FOR_PILLARS.y());

    int xRandomizer = QRandomGenerator::global()->bounded(200);

    setPos(QPoint(0,0) + QPoint(MARGINAL_VALUE + xRandomizer, m_yPos));

    m_xAnimation = new QPropertyAnimation(this,"x",this);
    m_xAnimation->setStartValue(MARGINAL_VALUE + xRandomizer);
    m_xAnimation->setEndValue(-MARGINAL_VALUE);
    m_xAnimation->setEasingCurve(QEasingCurve::Linear);
    m_xAnimation->setDuration(Game::DURATION_OF_PILLAR_ANIMATION);

    connect(m_xAnimation,&QPropertyAnimation::finished,[=](){
        scene()->removeItem(this);
        delete this;
    });

    m_xAnimation->start();
}

Pillar::~Pillar()
{
    delete m_topPillar;
    delete m_bottomPillar;
}

qreal Pillar::x() const
{
    return m_x;
}

void Pillar::setX(qreal x)
{
    m_x = x;
    setPos(QPointF(0,0) + QPointF(x, m_yPos));
    if(x < 0 && !m_pastBird)
    {
        m_pastBird = true;
        emit scoreChanged();
    }

    if(collidesWithBird())
    {
        emit collidedWithBird();
    }
}

bool Pillar::collidesWithBird()
{
    QList<QGraphicsItem*> collidingItems = m_topPillar->collidingItems();
    collidingItems.append(m_bottomPillar->collidingItems());

    foreach (QGraphicsItem * item, collidingItems) {
        Bird * birdItem = dynamic_cast<Bird*>(item);
        if(birdItem){
            return true;
        }
    }
    return false;
}
