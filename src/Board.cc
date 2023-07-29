#include "Board.h"
#include <algorithm>
#include <iostream>

Board::Board(std::string filename) {
    cur_block = nullptr;
    next_block = nullptr;
    level = std::make_shared<Level0>(filename);
    score = std::make_shared<Score>(level);
}


void Board::setCurBlock(std::shared_ptr<Block> block) {cur_block = block;}
void Board::setNextBlock(std::shared_ptr<Block> block) {next_block = block;}
void Board::setLevel(std::shared_ptr<Level> l) {level = l;}
void Board::setScore(std::shared_ptr<Score> s) {score = s;}

std::shared_ptr<Block> Board::getCurBlock() {return cur_block;}
std::shared_ptr<Block> Board::getNextBlock() {return next_block;}
std::shared_ptr<Level> Board::getLevel() {return level;}
std::shared_ptr<Score> Board::getScore() {return score;}

//int Board::totalBlock() const {return num_block;}

void Board::createBlock() {
    std::string endmsg;
    for (int i = 0; i < 11; i++) {
        if (findPos(i, 3)) {throw endmsg;}
    }
    if (cur_block == nullptr) {
        cur_block = level->createBlock();
        // record the level block generated in
        cur_block->setGenerateLevel(level->getCurlevel());
        cells.push_back(cur_block);
        next_block = level->createBlock();
        next_block->setGenerateLevel(level->getCurlevel());
        return;
    } 
    cur_block = next_block;
    next_block = level->createBlock();
    next_block->setGenerateLevel(level->getCurlevel());
    cells.push_back(cur_block);
}

void Board::setBlind() {
    isBlind = true;
}

void Board::unsetBlind() {
    isBlind = false;
}

bool Board::getBlind() const {
    return isBlind;
}


bool Board::findPos(int x, int y) {
    for (auto& b: cells) {
        if (b->findPos(x, y)) {
            return true;
        }
    }
    return false;
}

char Board::findType(int x, int y) {
    for (auto& b: cells) {
        if (b->findPos(x, y)) {
            return b->blockType();
        }
    }
    return ' ';
}

bool Board::left() {
    cur_block->left();
    // if out of index;
    for (int i = 0; i < 4; i++) {
        if (cur_block->getVectorPosn()[cur_block->findIndex()][i].x < 0) {
            cur_block->right();
            return true;
        }
    }

    // 这里要判断是否有重合的pos 如果有重合就right 下面几个method同理
    //traverse every block stored in cells
    //把cur_block里的每一个posn去和存的cell里的一个block里curr_state的4个posn去做比较(std::count)
    for (int i = 0; i < 4; i++) {
        int count = 0;
        for (auto& selectedblock : cells) {
            if (selectedblock->findPos(cur_block->getVectorPosn()[cur_block->findIndex()][i].x, 
                                       cur_block->getVectorPosn()[cur_block->findIndex()][i].y)) {
                count += 1;
            }          
        }
        if (count >= 2) {
            cur_block->right();
            return true;
        }
    }
    //如果有heavy的情况下，trigger down，如果down不下去了就return false，createblock
    /*for (int i = 0; i < cur_block->getHeavyLevel(); i++) {
        if (this->down() == 2) {
            return false;
        }
    }*/
    return true;  
}

bool Board::heavydown() {
    for (int i = 0; i < cur_block->getHeavyLevel(); i++) {
        if (this->down() == 2) {
            return false;
        }
    }
    return true;
}

bool Board::right() {
    cur_block->right();
    for (int i = 0; i < 4; i++) {
        if (cur_block->getVectorPosn()[cur_block->findIndex()][i].x > 10) {
            cur_block->left();
            return true;
        }
    }
    for (int i = 0; i < 4; i++) {
        int count = 0;
        for (auto& selectedblock : cells) {
            if (selectedblock->findPos(cur_block->getVectorPosn()[cur_block->findIndex()][i].x, 
                                       cur_block->getVectorPosn()[cur_block->findIndex()][i].y)) {
                count += 1;
            }          
        }
        if (count >= 2) {
            cur_block->left();
            return true;
        }
    }
    //如果有heavy的情况下，trigger down，如果down不下去了就return false，createblock
    /*for (int i = 0; i < cur_block->getHeavyLevel(); i++) {
        if (this->down() == 2) {
            return false;
        }
    }*/
    return true;
}

void Board::drop() {
    while (true) {
        int status = -1;
        status = down();
        if (status == 0) {
            createBlock();
            break;
        } else if (status == 2) {
            break;
        }
    }  
}

int Board::down() {
    cur_block->down();

    //检查有没有out of range
    for (int i = 0; i < 4; i++) {
        if (cur_block->getVectorPosn()[cur_block->findIndex()][i].y > 17) {
            cur_block->up();
            // end current turn
            //createBlock();
            if (cur_block->getHeavyLevel() > 0) {
                if (block_before_starblock == true) {
                    return 2;
                } else {
                    createBlock();
                    return 2;
                }
            }            
            return 0;
        }
    }
    //检查有没有做出一个成功的down
    for (int i = 0; i < 4; i++) {
        int count = 0;
        for (auto& selectedblock : cells) {
            if (selectedblock->findPos(cur_block->getVectorPosn()[cur_block->findIndex()][i].x, 
                                       cur_block->getVectorPosn()[cur_block->findIndex()][i].y)) {
                count += 1;
            }          
        }
        if (count >= 2) {
            cur_block->up();
            //如果是有heavy的情况下如果down不下去了,自动createblock
            if (cur_block->getHeavyLevel() > 0) {
                if (block_before_starblock == true){
                    //do nothing
                } else {
                    createBlock();
                }
                //在heavy的情况下如果当底下有block
                return 2;
            }
            //在不是heavy的情况下如果当底下有block
            return 0;
        }
    }   
    //如果底下没block
    return 1;
}

bool Board::rotateCW() {
    cur_block->rotateCW();
    // if out of index
    for (int i = 0; i < 4; i++) {
        if (cur_block->getVectorPosn()[cur_block->findIndex()][i].x > 10) {
            cur_block->rotateAW();
            return true;
        }
    }
    for (int i = 0; i < 4; i++) {
        int count = 0;
        for (auto& selectedblock : cells) {
            if (selectedblock->findPos(cur_block->getVectorPosn()[cur_block->findIndex()][i].x, 
                                       cur_block->getVectorPosn()[cur_block->findIndex()][i].y)) {
                count += 1;
            }          
        }
        if (count >= 2) {
            cur_block->rotateAW();
            return true;
        }
    }
    //如果有heavy的情况下，trigger down，如果down不下去了就return false，createblock
    /*for (int i = 0; i < cur_block->getHeavyLevel(); i++) {
        if (this->down() == 2) {
            return false;
        }
    }*/
    return true;    
}

bool Board::rotateAW() {
    cur_block->rotateAW();
    for (int i = 0; i < 4; i++) {
        if (cur_block->getVectorPosn()[cur_block->findIndex()][i].x > 10) {
            cur_block->rotateCW();
            return true;
        }
    }
    for (int i = 0; i < 4; i++) {
        int count = 0;
        for (auto& selectedblock : cells) {
            if (selectedblock->findPos(cur_block->getVectorPosn()[cur_block->findIndex()][i].x, 
                                       cur_block->getVectorPosn()[cur_block->findIndex()][i].y)) {
                count += 1;
            }          
        }
        if (count >= 2) {
            cur_block->rotateCW();
            return true;
        }
    }
    //如果有heavy的情况下，trigger down，如果down不下去了就return false，createblock
    /*for (int i = 0; i < cur_block->getHeavyLevel(); i++) {
        if (this->down() == 2) {
            return false;
        }
    }*/
    return true;  
}

int Board::cleanRow() {
    int numRow = 0;
    for (int i = totalRow; i > 3; i--) {
        for (int j = 0; j <= totalCol; j++) {
            if (findPos(j, i) == false) {
                break;
            }
            if (j == totalCol && findPos(j, i)) {
                // clean row
                // let all pos in current row to be invisible
                for (auto& b: cells) {
                    for (int m = 0; m <= totalCol; m++) {
                        if (b->findPos(m, i)) {
                            b->changeVis(m, i);
                        }
                    }
                }
                // let all upper pos down one
                for (int m = i - 1; m > 3; m--) {
                    for (int n = 0; n <= totalCol; n++) {
                        for (auto& b: cells) {
                            if (b->findPos(n, m)) {
                                b->changeY(n, m, 1);
                            }
                        }
                    }
                }
                numRow += 1;
                i += 1;
            }
        }
    }
    score->cleanRow(numRow);
    // to check if there is new block totally clean
    int addScore = 0;
    for (auto b: cells) {
        if (b->ifVis() == false) {
            //std::cout << b->getGenerateLevel() << std::endl;
            addScore += (b->getGenerateLevel() + 1) * (b->getGenerateLevel() + 1);
        }
    }
    int add = addScore - oldAddscore;
    oldAddscore = addScore;
    score->addscore(add);
    return numRow;
}

void Board::heavy() {
    cur_block->setHeavyLevel(cur_block->getHeavyLevel() + 2);
}

void Board::force(char type) {
    int heavy = cur_block->getHeavyLevel();
    if (type == 'I') {cur_block = std::make_shared<I_block>();}
    else if (type == 'J') {cur_block = std::make_shared<J_block>();}
    else if (type == 'L') {cur_block = std::make_shared<L_block>();}
    else if (type == 'O') {cur_block = std::make_shared<O_block>();}
    else if (type == 'S') {cur_block = std::make_shared<S_block>();}
    else if (type == 'Z') {cur_block = std::make_shared<Z_block>();}
    else if (type == 'T') {cur_block = std::make_shared<T_block>();}
    else {
        std::cout << "Invalid Type" << std::endl;
        return;
    }
    cells.pop_back();
    cur_block->setHeavyLevel(heavy);
    cur_block->setGenerateLevel(level->getCurlevel());
    cells.push_back(cur_block);
}

void Board::reset() {
    int size = cells.size();
    for (int i = 0; i < size; i++) {
        cells.pop_back();
    }
    level->resetCurIndex();
    cur_block = level->createBlock();
    cells.push_back(cur_block);
    cur_block->setGenerateLevel(level->getCurlevel());
    next_block = level->createBlock();
    next_block->setGenerateLevel(level->getCurlevel());
    score->restart();
    level->resetRound();
    oldAddscore = 0;
}

void Board::resetBlockonly() {
    cur_block = nullptr;
    next_block = nullptr;
    int size = cells.size();
    for (int i = 0; i < size; i++) {
        cells.pop_back();
    }
}
