#ifndef TITLESCENE_H
#define TITLESCENE_H

#include <QGraphicsScene>

class TitleScene : public QGraphicsScene
{
    Q_OBJECT
public:
    explicit TitleScene(QObject *parent = nullptr);
    void init();
signals:
    void gameActivated();
protected:
    virtual void keyPressEvent(QKeyEvent *event) override;
    virtual void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
private:
    void loadPixmap();
    QPixmap m_bgPixmap;
    QPixmap m_titlePixmap;
};

#endif // TITLESCENE_H
