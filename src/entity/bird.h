#ifndef BIRD_H
#define BIRD_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QTimer>
#include <QPropertyAnimation>

#include "../game.h"

class Bird : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
    Q_PROPERTY(qreal rotation READ rotation WRITE setRotation)
    Q_PROPERTY(qreal y READ y WRITE setY )
public:
    explicit Bird(QString pathToPixmap = Game::PATH_TO_BIRD_PIXMAP);
    const QPoint startPosition() const;
    void updateBird();
    void jump();

    qreal rotation() const;
    qreal y() const;
public slots:
    void setRotation(qreal rotation);
    void setY(qreal y);
private slots:
    void loop();
signals:

private:
    void rotateTo(const qreal& end, const int& duration, const QEasingCurve& curve);
    void fall();
    QTimer m_timer;
    QPixmap m_birdPixmap;
    const QSize m_pixmapSize;
    const QPoint m_startPos;
    int m_index;
    const int m_loopTime;

    qreal m_rotation, m_y;
    QPropertyAnimation *m_yAnimation, *m_rotationAnimation;
    // QGraphicsItem interface
protected:
    virtual void keyPressEvent(QKeyEvent *event) override;
};

#endif // BIRD_H
