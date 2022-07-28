#include "gameoverscene.h"
#include "../game.h"
#include <QDebug>
#include <QGraphicsPixmapItem>

GameOverScene::GameOverScene(QObject *parent)
    : QGraphicsScene{parent}
{
    setSceneRect(0,0, Game::RESOLUTION.width(), Game::RESOLUTION.height());
    loadPixmap();
    init();
}

void GameOverScene::keyPressEvent(QKeyEvent *event)
{
    emit gameActivated();
    QGraphicsScene::keyPressEvent(event);
}

void GameOverScene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    emit gameActivated();
    QGraphicsScene::mousePressEvent(event);
}

void GameOverScene::loadPixmap()
{
    if(m_bgPixmap.load(Game::PATH_TO_BG_PIXMAP))
    {
        qDebug() << "BG pixmap is loaded successfully";
    }
    else
    {
        qDebug() << "BG pixmap is NOT loaded successfully";
    }

    if(m_gameOverTitlePixmap.load(Game::PATH_TO_GAME_OVER_PIXMAP))
    {
        qDebug() << "Title pixmap is loaded successfully";
    }
    else
    {
        qDebug() << "Title pixmap is NOT loaded successfully";
    }
}

void GameOverScene::init()
{
    QGraphicsPixmapItem *bgItem = new QGraphicsPixmapItem(m_bgPixmap);
    addItem(bgItem);

    QGraphicsPixmapItem *goTitleItem = new QGraphicsPixmapItem(m_gameOverTitlePixmap.scaled(Game::RESOLUTION.width(), Game::RESOLUTION.height()));
    addItem(goTitleItem);

}
