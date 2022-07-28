#include "game.h"
bool Game::GAME_ACTIVE = true;
unsigned int Game::SCORE = 0;
unsigned int Game::HIGH_SCORE = 0;


const QString Game::FLOOR_ENTITY_TYPE = "FLOOR";

const QString Game::PATH_TO_BG_PIXMAP = ":/res/sprite/background-day.png";
const QString Game::PATH_TO_BASE_PIXMAP = ":/res/sprite/base.png";
const QString Game::PATH_TO_BIRD_PIXMAP = ":/res/sprite/bird.png";
const QString Game::PATH_TO_PILLAR_PIXMAP = ":/res/sprite/pipe-red.png";
const QString Game::PATH_TO_TITLE_PIXMAP = ":/res/sprite/message.png";
const QString Game::PATH_TO_GAME_OVER_PIXMAP = ":/res/sprite/gameOver_bg.png";

const QString Game::PATH_TO_FONT = ":/res/font/04B_19.ttf";

const QUrl Game::PATH_TO_HIT_SFX = QUrl("qrc:/res/sfx/sfx_hit.wav");
const QUrl Game::PATH_TO_POINT_SFX = QUrl("qrc:/res/sfx/sfx_point.wav");;
const QUrl Game::PATH_TO_WING_SFX = QUrl("qrc:/res/sfx/sfx_wing.wav");;

Game::Game()
{

}
