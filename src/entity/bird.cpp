#include "bird.h"
#include <QDebug>
#include <QKeyEvent>

Bird::Bird(QString pathToPixmap)
    : m_pixmapSize(QSize(34, 24)), m_startPos(QPoint(50, 256)), m_index(0), m_loopTime(120), m_isJump(false)
    , m_strongOfJump(4)
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

const QPoint Bird::startPosition() const
{
    return m_startPos;
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
    qDebug() << "fall y " << y();
    if(y() > Game::RESOLUTION.height())
    {
        setY( 0);
    }
    setY( y() + Game::GRAVITY/8);
}

void Bird::jump()
{
    qDebug() << "jump y " << y();
    if(y() < 0)
    {
        setY( Game::RESOLUTION.height());
    }
    setY( y() - Game::GRAVITY/8 * m_strongOfJump);
//    m_strongOfJump--;
//    if(m_strongOfJump == 0)
//    {
//        m_strongOfJump = 4;
//        m_isJump = false;
//    }
}

void Bird::updateBird()
{
    if(m_isJump)
    {
        jump();
    }
    else
    {
        fall();
    }
}

void Bird::keyPressEvent(QKeyEvent *event)
{
//    if(event->isAutoRepeat())
//    {
//        return;
//    }
    switch (event->key()) {
        case Qt::Key_W:
            m_isJump = true;
            return;
        case Qt::Key_S:
            m_isJump = false;
        return;
    }
    QGraphicsPixmapItem::keyPressEvent(event);
}
