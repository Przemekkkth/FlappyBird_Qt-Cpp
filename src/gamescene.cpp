#include "gamescene.h"
#include <QDebug>

GameScene::GameScene(QObject *parent)
    : QGraphicsScene{parent}, m_deltaTime(0.0f), m_loopTime(0.0f), m_loopSpeed(1.0f/float(Game::FPS))
{
    setSceneRect(0,0, Game::RESOLUTION.width(), Game::RESOLUTION.height());

    connect(&m_timer, &QTimer::timeout, this, &GameScene::loop);
    m_timer.start(int(m_loopSpeed));
    m_elapsedTimer.start();

    loadPixmap();
    init();
}

void GameScene::loop()
{
    m_deltaTime = m_elapsedTimer.elapsed();
    m_elapsedTimer.restart();

    m_loopTime += m_deltaTime;
    if( m_loopTime > m_loopSpeed)
    {
        m_loopTime -= m_loopSpeed;
    }
}

void GameScene::loadPixmap()
{
    if(m_bgPixmap.load(Game::PATH_TO_BG_PIXMAP))
    {
        qDebug() << "BG pixmap is loaded successfully";
    }
    else
    {
        qDebug() << "BG pixmap is NOT loaded successfully";
    }

    if(m_basePixmap.load(Game::PATH_TO_BASE_PIXMAP))
    {
        qDebug() << "Base pixmap is loaded successfully";
    }
    else
    {
        qDebug() << "Base pixmap is NOT loaded successfully";
    }

}

void GameScene::init()
{
    m_bgPixmapItem = new QGraphicsPixmapItem(m_bgPixmap);
    m_bgPixmapItem->setPos(0,0);
    addItem(m_bgPixmapItem);

    m_basePixmapItem = new QGraphicsPixmapItem(m_basePixmap);
    m_basePixmapItem->setPos(0, Game::RESOLUTION.height() - m_basePixmap.height());
    addItem(m_basePixmapItem);
}
