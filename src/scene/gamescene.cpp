#include "gamescene.h"
#include <QDebug>
#include <QKeyEvent>
#include <QFontDatabase>
#include <QGraphicsSimpleTextItem>

#include "../entity/bird.h"
#include "../entity/pillar.h"

GameScene::GameScene(QObject *parent)
    : QGraphicsScene{parent}, m_yPos(Game::RESOLUTION.height()/2)
{
    setSceneRect(0,0, Game::RESOLUTION.width(), Game::RESOLUTION.height());

    loadPixmap();
    loadSFX();

    connect(&m_pillarTimer, &QTimer::timeout, this, &GameScene::spawnPillar);

    int id = QFontDatabase::addApplicationFont(Game::PATH_TO_FONT);
    QString fontFamilyName = QFontDatabase::applicationFontFamilies(id).at(0);
    m_font = QFont(fontFamilyName, Game::FONT_SIZE, 50);
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

void GameScene::loadSFX()
{
    m_dieSFX.setSource(Game::PATH_TO_HIT_SFX);
    m_pointSFX.setSource(Game::PATH_TO_POINT_SFX);
    m_wingSFX.setSource(Game::PATH_TO_WING_SFX);
}

void GameScene::init()
{
    m_bgPixmapItem = new QGraphicsPixmapItem(m_bgPixmap);
    m_bgPixmapItem->setPos(0,0);
    addItem(m_bgPixmapItem);

    m_basePixmapItem = new QGraphicsPixmapItem(m_basePixmap.scaled(Game::RESOLUTION.width(), m_basePixmap.height()));
    m_basePixmapItem->setPos(0, Game::RESOLUTION.height() - m_basePixmap.height());
    m_basePixmapItem->setData(QGraphicsItem::UserType+1, Game::FLOOR_ENTITY_TYPE);
    addItem(m_basePixmapItem);

    m_bird = new Bird();
    m_bird->setPos(m_bird->startPosition());
    m_bird->setFlag(QGraphicsItem::ItemIsFocusable);
    m_bird->setFocus();
    connect(m_bird, &Bird::collidedWithGround, this, &GameScene::activeGameOver);
    addItem(m_bird);

    m_pillarTimer.start(1000);

    Game::SCORE = 0;
    m_scoreTextItem = new QGraphicsSimpleTextItem(QString::number(Game::SCORE).left(Game::SCORE_TEXT_WIDTH));
    m_scoreTextItem->setFont(m_font);
    m_scoreTextItem->setPen(QPen(Game::FONT_COLOR));
    m_scoreTextItem->setBrush(QBrush(Game::FONT_COLOR));

    m_scoreTextItem->setPos(Game::RESOLUTION.width()/2 - m_scoreTextItem->boundingRect().width()/2, Game::FONT_SIZE);
    m_scoreTextItem->setZValue(1);
    addItem(m_scoreTextItem);
}

void GameScene::activeGameOver()
{
    m_dieSFX.play();
    clear();
    m_pillarTimer.stop();
    emit gameOverActivated();
}

void GameScene::spawnPillar()
{
    Pillar * pillarItem = new Pillar();
    connect(pillarItem, &Pillar::collidedWithBird, this, &GameScene::activeGameOver);

    connect(pillarItem, &Pillar::scoreChanged, [this](){
        Game::SCORE++;
        m_scoreTextItem->setText(QString::number(Game::SCORE).left(Game::SCORE_TEXT_WIDTH));
        m_pointSFX.play();
    });
    addItem(pillarItem);
}

void GameScene::keyPressEvent(QKeyEvent *event)
{

    switch (event->key()) {
    case Qt::Key_Space:
        m_wingSFX.play();
        break;
    }
    QGraphicsScene::keyPressEvent(event);
}

void GameScene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    m_wingSFX.play();
    m_bird->jump();
    QGraphicsScene::mousePressEvent(event);
}
