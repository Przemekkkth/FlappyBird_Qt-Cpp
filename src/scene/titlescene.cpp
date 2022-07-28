#include "titlescene.h"
#include "../game.h"
#include <QGraphicsPixmapItem>
TitleScene::TitleScene(QObject *parent)
    : QGraphicsScene{parent}
{
    setSceneRect(0,0, Game::RESOLUTION.width(), Game::RESOLUTION.height());
    loadPixmap();
    init();
}

void TitleScene::init()
{
    QGraphicsPixmapItem *bgItem = new QGraphicsPixmapItem(m_bgPixmap);
    addItem(bgItem);

    QGraphicsPixmapItem *titleItem = new QGraphicsPixmapItem(m_titlePixmap.scaled(Game::RESOLUTION.width(), Game::RESOLUTION.height()));
    addItem(titleItem);
}

void TitleScene::keyPressEvent(QKeyEvent *event)
{
    emit gameActivated();
    QGraphicsScene::keyPressEvent(event);
}

void TitleScene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    emit gameActivated();
    QGraphicsScene::mousePressEvent(event);
}

void TitleScene::loadPixmap()
{
    if(m_bgPixmap.load(Game::PATH_TO_BG_PIXMAP))
    {
        qDebug() << "BG pixmap is loaded successfully";
    }
    else
    {
        qDebug() << "BG pixmap is NOT loaded successfully";
    }

    if(m_titlePixmap.load(Game::PATH_TO_TITLE_PIXMAP))
    {
        qDebug() << "Title pixmap is loaded successfully";
    }
    else
    {
        qDebug() << "Title pixmap is NOT loaded successfully";
    }
}
