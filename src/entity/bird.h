#ifndef BIRD_H
#define BIRD_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QTimer>
#include "../game.h"

class Bird : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    explicit Bird(QString pathToPixmap = Game::PATH_TO_BIRD_PIXMAP);
    const QPoint startPosition() const;
    void updateBird();
signals:
private slots:
    void loop();
private:
    void fall();
    void jump();
    QTimer m_timer;
    QPixmap m_birdPixmap;
    const QSize m_pixmapSize;
    const QPoint m_startPos;
    int m_index;
    const int m_loopTime;
    bool m_isJump;
    // QGraphicsItem interface
    unsigned int m_strongOfJump;
protected:
    virtual void keyPressEvent(QKeyEvent *event) override;
};

#endif // BIRD_H
