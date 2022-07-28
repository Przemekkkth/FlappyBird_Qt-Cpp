#ifndef GAMESCENE_H
#define GAMESCENE_H

#include <QGraphicsScene>
#include <QTimer>
#include <QElapsedTimer>
#include <QGraphicsPixmapItem>

#include "../game.h"
class Bird;
class QGraphicsSimpleTextItem;
class GameScene : public QGraphicsScene
{
    Q_OBJECT
public:
    explicit GameScene(QObject *parent = nullptr);
    //Scene
    void init();
signals:
    void gameOverActivated();
private:
    //Pixmap
    void loadPixmap();
    QPixmap m_bgPixmap, m_basePixmap;

    QGraphicsPixmapItem *m_bgPixmapItem, *m_basePixmapItem;
    Bird* m_bird;
    float m_yPos;
    bool m_dir;
    //Pillar
    QTimer m_pillarTimer;
    //
    QGraphicsSimpleTextItem* m_scoreTextItem;
    QFont m_font;
private slots:
    void activeGameOver();
    void spawnPillar();
protected:
    virtual void keyPressEvent(QKeyEvent *event) override;
    virtual void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
};

#endif // GAMESCENE_H
