#include "gameoverscene.h"
#include "../game.h"

#include <QGraphicsSimpleTextItem>
#include <QFontDatabase>
#include <QDebug>
#include <QGraphicsPixmapItem>

GameOverScene::GameOverScene(QObject *parent)
    : QGraphicsScene{parent}
{
    setSceneRect(0,0, Game::RESOLUTION.width(), Game::RESOLUTION.height());
    loadPixmap();
    init();
}

void GameOverScene::updateScore()
{

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

    int id = QFontDatabase::addApplicationFont(Game::PATH_TO_FONT);
    QString fontFamilyName = QFontDatabase::applicationFontFamilies(id).at(0);
    QFont _font = QFont(fontFamilyName, Game::FONT_SIZE, 50);
    m_scoreTextItem = new QGraphicsSimpleTextItem();
    m_scoreTextItem->setFont(_font);
    m_scoreTextItem->setText("Your score: " + QString::number(Game::SCORE).left(Game::SCORE_TEXT_WIDTH));
    m_scoreTextItem->setPen(QPen(Game::FONT_COLOR));
    m_scoreTextItem->setBrush(QBrush(Game::FONT_COLOR));
    m_scoreTextItem->setPos((Game::RESOLUTION.width() - m_scoreTextItem->boundingRect().width())/2, 425);
    addItem(m_scoreTextItem);

    m_highScoreTextItem = new QGraphicsSimpleTextItem();
    m_highScoreTextItem->setFont(_font);
    m_highScoreTextItem->setText("Record: " + QString::number(Game::SCORE).left(Game::SCORE_TEXT_WIDTH));
    m_highScoreTextItem->setPen(QPen(Game::FONT_COLOR));
    m_highScoreTextItem->setBrush(QBrush(Game::FONT_COLOR));
    m_highScoreTextItem->setPos((Game::RESOLUTION.width() - m_highScoreTextItem->boundingRect().width())/2, 250);
    addItem(m_highScoreTextItem);
}
