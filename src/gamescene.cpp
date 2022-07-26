#include "gamescene.h"

GameScene::GameScene(QObject *parent)
    : QGraphicsScene{parent}, m_deltaTime(0.0f), m_loopTime(0.0f), m_loopSpeed(1.0f/float(Game::FPS))
{
    setSceneRect(0,0, Game::RESOLUTION.width(), Game::RESOLUTION.height());

    connect(&m_timer, &QTimer::timeout, this, &GameScene::loop);
    m_timer.start(int(m_loopSpeed));
    m_elapsedTimer.start();
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
