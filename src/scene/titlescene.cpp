#include "titlescene.h"
#include "../game.h"
#include <QGraphicsPixmapItem>
#include <QGraphicsSimpleTextItem>
#include <QFontDatabase>

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

    int id = QFontDatabase::addApplicationFont(Game::PATH_TO_FONT);
    QString fontFamilyName = QFontDatabase::applicationFontFamilies(id).at(0);
    QFont _font = QFont(fontFamilyName, Game::FONT_SIZE, 50);
    QGraphicsSimpleTextItem *textItem = new QGraphicsSimpleTextItem();
    textItem->setFont(_font);
    textItem->setText("   Press any \nkey or button...");
    textItem->setPen(QPen(Game::FONT_COLOR));
    textItem->setBrush(QBrush(Game::FONT_COLOR));
    textItem->setPos((Game::RESOLUTION.width() - textItem->boundingRect().width())/2, 125);
    addItem(textItem);

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
