#ifndef _SCORE_H_
#define _SCORE_H_
#include "Level.h"
#include <memory>

class Score {
    int score;
    int highestScore;
    std::shared_ptr<Level> level;

    public:
    Score(std::shared_ptr<Level> level): score{0}, highestScore{0}, level{level} {}
    // return score in class Score
    int getScore();

    // return hignestScore in class Score
    int getHscore();
    int getLevel();
    void setLevel(std::shared_ptr<Level> newLevel);

    void cleanRow(int numRow);
    void addscore(int num);
    void restart();
};

#endif
