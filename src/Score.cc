#include "Score.h"

int Score::getScore() {return score;}

int Score::getHscore() {return highestScore;}

int Score::getLevel() {return level->getCurlevel();}

void Score::setLevel(std::shared_ptr<Level> newLevel) {
    level = newLevel;
} 

void Score::cleanRow(int numRow) {
    if (numRow == 0) {return;}
    score += (getLevel() + numRow) * (getLevel() + numRow);
    if (score > highestScore) {
        highestScore = score;
    }
}

void Score::addscore(int num) {
    score += num;
    if (score > highestScore) {
        highestScore = score;
    }
}

void Score::restart() {score = 0;}
