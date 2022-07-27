#include "bird.h"
#include <QDebug>
#include <QKeyEvent>

Bird::Bird(QString pathToPixmap)
    : m_pixmapSize(QSize(34, 24)), m_index(0), m_loopTime(120)
{
    if(m_birdPixmap.load(pathToPixmap))
    {
        qDebug() << "Bird pixmap is loaded successfully";
    }
    else
    {
        qDebug() << "Bird pixmap is NOT loaded successfully";
    }
    connect(&m_timer, &QTimer::timeout, this, &Bird::loop);
    setTransformOriginPoint(m_pixmapSize.width()/2, m_pixmapSize.height()/2);

    m_timer.start(m_loopTime);
    setPixmap(m_birdPixmap.copy(m_index*m_pixmapSize.width(), 0, m_pixmapSize.width(), m_pixmapSize.height()));

}

void Bird::loop()
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

void Bird::fall()
{
    if(y() > Game::RESOLUTION.height())
    {
        setY( 0);
    }
    setY( y() + Game::GRAVITY/8);
}

void Bird::jump()
{
    if(y() < 0)
    {
        setY( Game::RESOLUTION.height());
    }
    setY( y() - Game::GRAVITY/8);
}

void Bird::keyPressEvent(QKeyEvent *event)
{
    qDebug() << "Bird key: " << event->key();
    QGraphicsPixmapItem::keyPressEvent(event);
}
