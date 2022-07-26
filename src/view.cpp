#include "view.h"

View::View()
    : QGraphicsView(), m_gameScene(new GameScene())
{
    setScene(m_gameScene);
    resize(Game::RESOLUTION.width()+2, Game::RESOLUTION.height()+2);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
}
