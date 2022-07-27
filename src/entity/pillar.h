#ifndef PILLAR_H
#define PILLAR_H

#include <QObject>
#include <QGraphicsItemGroup>
#include <QGraphicsPixmapItem>
#include <QPropertyAnimation>

class Pillar : public QObject, public QGraphicsItemGroup
{
    Q_OBJECT
    Q_PROPERTY(qreal x READ x WRITE setX)
public:
    explicit Pillar();
    ~Pillar();

    qreal x() const;
signals:
    void collideWithBird();
public slots:
    void setX(qreal x);
private:
    QPropertyAnimation *m_xAnimation;
    QGraphicsPixmapItem *m_topPillar, *m_bottomPillar;
    int m_yPos;
    qreal m_x;
    bool m_pastBird;
    const int MARGINAL_VALUE;
};

#endif // PILLAR_H
