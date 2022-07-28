#ifndef GAMEOVERSCENE_H
#define GAMEOVERSCENE_H

#include <QGraphicsScene>
class QGraphicsSimpleTextItem;
class GameOverScene : public QGraphicsScene
{
    Q_OBJECT
public:
    explicit GameOverScene(QObject *parent = nullptr);
    void updateScore();
signals:
    void gameActivated();
protected:
    virtual void keyPressEvent(QKeyEvent *event) override;
    virtual void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
private:
    void loadPixmap();
    void init();
    QPixmap m_bgPixmap, m_gameOverTitlePixmap;
    QGraphicsSimpleTextItem *m_scoreTextItem, *m_highScoreTextItem;
};

#endif // GAMEOVERSCENE_H
