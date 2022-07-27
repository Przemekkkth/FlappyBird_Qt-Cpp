#include "game.h"
bool Game::GAME_ACTIVE = true;
unsigned int Game::SCORE = 0;
unsigned int Game::HIGH_SCORE = 0;

const QString Game::PATH_TO_BG_PIXMAP = ":/res/sprite/background-day.png";
const QString Game::PATH_TO_BASE_PIXMAP = ":/res/sprite/base.png";
const QString Game::PATH_TO_BIRD_PIXMAP = ":/res/sprite/bird.png";
const QString Game::PATH_TO_PILLAR_PIXMAP = ":/res/sprite/pipe-red.png";


Game::Game()
{

}
