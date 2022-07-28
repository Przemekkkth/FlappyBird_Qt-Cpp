#ifndef VIEW_H
#define VIEW_H

#include <QGraphicsView>
#include "scene/gamescene.h"
#include "scene/titlescene.h"
#include "scene/gameoverscene.h"

class View : public QGraphicsView
{
    Q_OBJECT
public:
    explicit View();

signals:

private:
    void createConnections();
    GameScene* m_gameScene;
    TitleScene* m_titleScene;
    GameOverScene* m_gameOverScene;
    // QWidget interface
protected:
    virtual void keyPressEvent(QKeyEvent *event) override;
};

#endif // VIEW_H
