#include "view.h"
#include <QKeyEvent>
#include <QApplication>

View::View()
    : QGraphicsView(), m_gameScene(new GameScene(this)), m_titleScene(new TitleScene(this))
{
    setScene(m_titleScene);
    resize(Game::RESOLUTION.width()+2, Game::RESOLUTION.height()+2);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    createConnections();
}

void View::createConnections()
{
    connect(m_titleScene, &TitleScene::gameActivated, [this](){
        setScene(m_gameScene);
        m_gameScene->init();
    });
}

void View::keyPressEvent(QKeyEvent *event)
{
    switch (event->key()) {
        case Qt::Key_Escape:
            QApplication::instance()->quit();
        break;
    }
    qDebug() << "View::keyPressEvent";
    QGraphicsView::keyPressEvent(event);
}
