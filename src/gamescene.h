#ifndef GAMESCENE_H
#define GAMESCENE_H

#include <QGraphicsScene>
#include <QTimer>
#include <QElapsedTimer>
#include <QGraphicsPixmapItem>

#include "game.h"
class Bird;
class GameScene : public QGraphicsScene
{
    Q_OBJECT
public:
    explicit GameScene(QObject *parent = nullptr);

signals:

private slots:
    void loop();
private:
    //FPS
    float m_deltaTime, m_loopTime;
    const float m_loopSpeed;
    QElapsedTimer m_elapsedTimer;
    QTimer m_timer;
    //Pixmap
    void loadPixmap();
    QPixmap m_bgPixmap, m_basePixmap;
    //Scene
    void init();
    QGraphicsPixmapItem *m_bgPixmapItem, *m_basePixmapItem;
    Bird* m_bird;
    float m_birdMovement;
    float m_yPos;
    bool m_dir;

    // QGraphicsScene interface
protected:
    virtual void keyPressEvent(QKeyEvent *event) override;
};

#endif // GAMESCENE_H
