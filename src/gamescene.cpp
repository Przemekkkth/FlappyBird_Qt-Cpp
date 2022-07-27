#include "gamescene.h"
#include <QDebug>
#include <QKeyEvent>
#include "entity/bird.h"
#include "entity/pillar.h"

GameScene::GameScene(QObject *parent)
    : QGraphicsScene{parent}, m_deltaTime(0.0f), m_loopTime(0.0f)
    , m_loopSpeed(int(1.0f/float(Game::FPS))), m_birdMovement(0.0f), m_yPos(Game::RESOLUTION.height()/2)
{
    setSceneRect(0,0, Game::RESOLUTION.width(), Game::RESOLUTION.height());

    m_timer.start(int(m_loopSpeed));
    m_elapsedTimer.start();

    loadPixmap();
    init();


    connect(&m_pillarTimer, &QTimer::timeout, [this](){
        Pillar * pillarItem = new Pillar();
        addItem(pillarItem);
    });
    m_pillarTimer.start(1000);
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
    m_basePixmapItem->setData(QGraphicsItem::UserType+1, "Floor");
    addItem(m_basePixmapItem);

    m_bird = new Bird();
    m_bird->setPos(m_bird->startPosition());
    m_bird->setFlag(QGraphicsItem::ItemIsFocusable);
    m_bird->setFocus();
    addItem(m_bird);
}

void GameScene::keyPressEvent(QKeyEvent *event)
{

    switch (event->key()) {
        case Qt::Key_W:
//            m_bird->jump();
//            m_bird->setY(m_bird->y() + 1);
        break;
    }
    qDebug() << "GameScene::keyPressEvent(QKeyEvent *event)";
    QGraphicsScene::keyPressEvent(event);
}
