#ifndef GAME_H
#define GAME_H
#include <QSize>
#include <QString>
#include <QPoint>

class Game
{
public:
    Game();
    static constexpr QSize RESOLUTION = QSize(288, 512);
    static constexpr float GRAVITY = 0.25f;
    static bool GAME_ACTIVE;
    static unsigned int SCORE;
    static unsigned int HIGH_SCORE;

    static const QString PATH_TO_BG_PIXMAP;
    static const QString PATH_TO_BASE_PIXMAP;
    static const QString PATH_TO_BIRD_PIXMAP;
    static const QString PATH_TO_PILLAR_PIXMAP;

    static constexpr int FPS = 60;
    static constexpr int GAP_SIZE = 100;
    static constexpr QPoint RANGE_OF_Y_FOR_PILLARS = QPoint(-125, 25);
    static constexpr int DURATION_OF_PILLAR_ANIMATION = 1500;
};

#endif // GAME_H
