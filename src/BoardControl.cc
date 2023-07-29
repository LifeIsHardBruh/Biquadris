#include "BoardControl.h"
#include "View.h"
#include "Board.h"
#include <iostream>


void BoardControl::restart() {
    round = 1;
    Board1->reset();
    Board2->reset();
}


void BoardControl::rotateCW(int times) {
    if (round == 1) {
        for (int i = 0; i < times; i++) {
            Board1->rotateCW();
        }
        if (Board1->heavydown() == false) {
            changeRound();
            return;
        }
        return;
    }
    for (int i = 0; i < times; i++) {
        Board2->rotateCW();
    }
    if (Board2->heavydown() == false) {
        changeRound();
    }
}

void BoardControl::rotateAW(int times) {
    if (round == 1) {
        for (int i = 0; i < times; i++) {
            Board1->rotateAW();
        }
        if (Board1->heavydown() == false) {
            changeRound();
            return;
        }
        return;
    }
    for (int i = 0; i < times; i++) {
        Board2->rotateAW();
    }
    if (Board2->heavydown() == false) {
        changeRound();
    }
}

void BoardControl::left(int times) {
    if (round == 1) {
        for (int i = 0; i < times; i++) {
            //只有是heavy的情况下board::right可能会return false
            Board1->left();
        }
        if (Board1->heavydown() == false) {
            changeRound();
            return;
        }
        return;
    }
    for (int i = 0; i < times; i++) {
        Board2->left();
    }
    if (Board2->heavydown() == false) {
        changeRound();
    }
}

void BoardControl::right(int times) {
    if (round == 1) {
        for (int i = 0; i < times; i++) {
            //只有是heavy的情况下board::right可能会return false
            Board1->right();
        }
        if (Board1->heavydown() == false) {
            changeRound();
            return;
        }
        return;
    }
    for (int i = 0; i < times; i++) {
        Board2->right(); 
    }
    if (Board2->heavydown() == false) {
        changeRound();
    }
}

void BoardControl::drop(int times) {
    if (round == 1) {
        for (int i = 0; i < times; i++) {
            Board1->drop();
            changeRound();
            bool ifblind = false;
            if (Board2->getBlind()) {ifblind = true;}
            changeRound();
            if (ifblind) {Board2->setBlind();}
        }
        changeRound();
        return;
    }
    for (int i = 0; i < times; i++) {
        Board2->drop();
        changeRound();
        bool ifblind = false;
        if (Board1->getBlind()) {ifblind = true;}
        changeRound();
        if (ifblind) {Board1->setBlind();}
    }
    changeRound();
}

void BoardControl::down(int times) {
    if (round == 1) {
        for (int i = 0; i < times; i++) {
            if ((Board1->down() == 2)) {
                changeRound();
                return;
            }
        }
        return;
    }
    for (int i = 0; i < times; i++) {
        if ((Board2->down() == 2)) {
            changeRound();
            return;
        }
    }
}

void BoardControl::heavy() {
    if (round == 1) {
        Board2->heavy();
        return;
    }
    Board1->heavy(); 
}

void BoardControl::force(char block) {
    if (round == 1) {
        Board2->force(block);
        return;
    }
    Board1->force(block);
}

void BoardControl::forceMe(char block) {
    if (round == 1) {
        Board1->force(block);
        return;
    }
    Board2->force(block);
}

void BoardControl::levelup(int num) {
    if (round == 1) {
        int curLevel = Board1->getLevel()->getCurlevel();
        if (curLevel == 4) {return;}
        if (curLevel + num == 1) {
            Board1->setLevel(std::make_shared<Level1>(Board1->getLevel()->getFilename()));
        } else if (curLevel + num == 2) {
            Board1->setLevel(std::make_shared<Level2>(Board1->getLevel()->getFilename()));
        } else if (curLevel + num == 3) {
            Board1->setLevel(std::make_shared<Level3>(Board1->getLevel()->getFilename()));
            Board1->getCurBlock()->setHeavyLevel(Board1->getCurBlock()->getHeavyLevel() + 1);
            Board1->getNextBlock()->setHeavyLevel(Board1->getNextBlock()->getHeavyLevel() + 1);
        } else if (curLevel + num >= 4) {
            Board1->setLevel(std::make_shared<Level4>(Board1->getLevel()->getFilename()));
            if (curLevel < 3) {
                Board1->getCurBlock()->setHeavyLevel(Board1->getCurBlock()->getHeavyLevel() + 1);
                Board1->getNextBlock()->setHeavyLevel(Board1->getNextBlock()->getHeavyLevel() + 1);
            }
        }
        Board1->getNextBlock()->setGenerateLevel(Board1->getLevel()->getCurlevel());
        Board1->getScore()->setLevel(Board1->getLevel());
        return;
    }
    int curLevel = Board2->getLevel()->getCurlevel();
    if (curLevel == 4) {return;}
    if (curLevel + num == 1) {
        Board2->setLevel(std::make_shared<Level1>(Board2->getLevel()->getFilename()));
    } else if (curLevel + num == 2) {
        Board2->setLevel(std::make_shared<Level2>(Board2->getLevel()->getFilename()));
    } else if (curLevel + num == 3) {
        Board2->setLevel(std::make_shared<Level3>(Board2->getLevel()->getFilename()));
        Board2->getCurBlock()->setHeavyLevel(Board2->getCurBlock()->getHeavyLevel() + 1);
        Board2->getNextBlock()->setHeavyLevel(Board2->getNextBlock()->getHeavyLevel() + 1);
    } else if (curLevel + num >= 4) {
        Board2->setLevel(std::make_shared<Level4>(Board2->getLevel()->getFilename()));
        if (curLevel < 3) {
            Board2->getCurBlock()->setHeavyLevel(Board2->getCurBlock()->getHeavyLevel() + 1);
            Board2->getNextBlock()->setHeavyLevel(Board2->getNextBlock()->getHeavyLevel() + 1);
        }
    }
    Board2->getNextBlock()->setGenerateLevel(Board2->getLevel()->getCurlevel());
    Board2->getScore()->setLevel(Board2->getLevel());
    //Board2->getLevel()->setSeed(seed);
}

void BoardControl::leveldown(int num) {
    if (round == 1) {
        int curLevel = Board1->getLevel()->getCurlevel();
        if (curLevel - num <= 0) {
            Board1->setLevel(std::make_shared<Level0>(Board1->getLevel()->getFilename()));
            if (curLevel > 2) {
                Board1->getCurBlock()->setHeavyLevel(Board1->getCurBlock()->getHeavyLevel() - 1);
                Board1->getNextBlock()->setHeavyLevel(Board1->getNextBlock()->getHeavyLevel() - 1);
            }
        } else if (curLevel - num == 1) {
            Board1->setLevel(std::make_shared<Level1>(Board1->getLevel()->getFilename()));
            if (curLevel > 2) {
                Board1->getCurBlock()->setHeavyLevel(Board1->getCurBlock()->getHeavyLevel() - 1);
                Board1->getNextBlock()->setHeavyLevel(Board1->getNextBlock()->getHeavyLevel() - 1);
            }
        } else if (curLevel - num == 2) {
            Board1->setLevel(std::make_shared<Level2>(Board1->getLevel()->getFilename()));
            if (curLevel > 2) {
                Board1->getCurBlock()->setHeavyLevel(Board1->getCurBlock()->getHeavyLevel() - 1);
                Board1->getNextBlock()->setHeavyLevel(Board1->getNextBlock()->getHeavyLevel() - 1);
            }
        } else if (curLevel - num == 3) {
            Board1->setLevel(std::make_shared<Level3>(Board1->getLevel()->getFilename()));
        }
        Board1->getNextBlock()->setGenerateLevel(Board1->getLevel()->getCurlevel());
        Board1->getScore()->setLevel(Board1->getLevel());
        //Board1->getLevel()->setSeed(seed);
        return;
    }
    int curLevel = Board2->getLevel()->getCurlevel();
    if (curLevel - num <= 0) {
        Board2->setLevel(std::make_shared<Level0>(Board2->getLevel()->getFilename()));
        if (curLevel > 2) {
            Board2->getCurBlock()->setHeavyLevel(Board2->getCurBlock()->getHeavyLevel() - 1);
            Board2->getNextBlock()->setHeavyLevel(Board2->getNextBlock()->getHeavyLevel() - 1);
        }
    } else if (curLevel - num == 1) {
        Board2->setLevel(std::make_shared<Level1>(Board2->getLevel()->getFilename()));
        if (curLevel > 2) {
            Board2->getCurBlock()->setHeavyLevel(Board2->getCurBlock()->getHeavyLevel() - 1);
            Board2->getNextBlock()->setHeavyLevel(Board2->getNextBlock()->getHeavyLevel() - 1);
        }
    } else if (curLevel - num == 2) {
        Board2->setLevel(std::make_shared<Level2>(Board2->getLevel()->getFilename()));
        if (curLevel > 2) {
            Board2->getCurBlock()->setHeavyLevel(Board2->getCurBlock()->getHeavyLevel() - 1);
            Board2->getNextBlock()->setHeavyLevel(Board2->getNextBlock()->getHeavyLevel() - 1);
        }
    } else if (curLevel - num == 3) {
        Board2->setLevel(std::make_shared<Level3>(Board2->getLevel()->getFilename()));
    }
    Board2->getNextBlock()->setGenerateLevel(Board2->getLevel()->getCurlevel());
    Board2->getScore()->setLevel(Board2->getLevel());
    //Board2->getLevel()->setSeed(seed);
}

void BoardControl::norandom(std::string file) {
    if (round == 1) {
        Board1->getLevel()->norandom();
        Board1->getLevel()->setFilename(file);
        Board1->getLevel()->resetVector();
        Board1->getLevel()->readFile();
        Board1->getLevel()->resetCurIndex();
        return;
    }
    Board2->getLevel()->norandom();
    Board2->getLevel()->setFilename(file);
    Board2->getLevel()->resetVector();
    Board2->getLevel()->readFile();
    Board2->getLevel()->resetCurIndex();
}

void BoardControl::random() {
    if (round == 1) {
        Board1->getLevel()->random();
        return;
    }
    Board2->getLevel()->random();
}

std::shared_ptr<Board> BoardControl::getBoard1() {return Board1;}

std::shared_ptr<Board> BoardControl::getBoard2() {return Board2;}

void BoardControl::changeRound() {
    if (round == 1) {
        Board1->unsetBlind();
        // special action
        int row = Board1->cleanRow();
        if (row != 0 && Board1->getLevel()->getCurlevel() == 4) {Board1->getLevel()->resetRound();}
        if (Board1->getLevel()->ifstar() && Board1->getLevel()->getCurlevel() == 4) {
            std::shared_ptr<Block> star = std::make_shared<Star_block>();
            star->setHeavyLevel(1);
            //store the new created normal block
            std::shared_ptr<Block> last_block = Board1->getCurBlock();
            //pop-back that normal block
            Board1->popbackCells();
            Board1->setblock_before_starblock(true);
            Board1->addCells(star);
            Board1->setCurBlock(star);
            Board1->drop();
            Board1->setblock_before_starblock(false);
            Board1->addCells(last_block);
            Board1->setCurBlock(last_block);
            Board1->getLevel()->resetRound();
            std::string endmsg;
            int count = 0;
            for (int i = 0; i < 11; i++) {
                for (int j = 0; j < 4; j++) {
                    if (Board1->findPos(i, j)) {count += 1;}
                }
            }
            if (count > 4) {throw endmsg;}
        }
        if (row >= 2) {
            display();
            std::cout << "You have a chance to select special actions!" << std::endl;
            std::cout << "Choose one of blind, heavy, or force to your opponent!" << std::endl;
            std::string command;
            std::cin >> command;
            if (command[0] == 'b') {
                applyBlind();
            } else if (command[0] == 'h') {
                heavy();
            } else if (command[0] == 'f') {
                std::cout << "Please type the block you want to force" << std::endl;
                std::cout << "I J L O S Z T" << std::endl;
                char b;
                std::cin >> b;
                force(b);
            } else {
                std::cout << "Oh! You are kind! You lose this chance XDDD" <<std::endl;
                std::cout << "Press any to continue" << std::endl;
                std::string temp;
                std::cin >> temp;
            }
        }
        round = 2;
        return;
    }
    Board2->unsetBlind();
    int row = Board2->cleanRow();
    if (row != 0 && Board2->getLevel()->getCurlevel() == 4) {Board2->getLevel()->resetRound();}
    if (Board2->getLevel()->ifstar() && Board2->getLevel()->getCurlevel() == 4) {
        std::shared_ptr<Block> star = std::make_shared<Star_block>();

        star->setHeavyLevel(1);
        //store the new created normal block
        std::shared_ptr<Block> last_block = Board2->getCurBlock();
        //pop-back that normal block
        Board2->popbackCells();
        Board2->setblock_before_starblock(true);
        Board2->addCells(star);
        Board2->setCurBlock(star);
        // this drop has problem
        Board2->drop();
        Board2->setblock_before_starblock(false);
        Board2->addCells(last_block);
        Board2->setCurBlock(last_block);
        Board2->getLevel()->resetRound();
        std::string endmsg;
        int count = 0;
        for (int i = 0; i < 11; i++) {
            for (int j = 0; j < 4; j++) {
                if (Board2->findPos(i, j)) {count += 1;}
            }
        }
        if (count > 4) {throw endmsg;}
    }
    if (row >= 2) {
        display();
        std::cout << "You have a chance to select special actions!" << std::endl;
        std::cout << "Choose one of blind, heavy, or force to your opponent!" << std::endl;
        std::string command;
        std::cin >> command;
        if (command[0] == 'b') {
            applyBlind();
        } else if (command[0] == 'h') {
            heavy();
        } else if (command[0] == 'f') {
            std::cout << "Please type the block you want to force" << std::endl;
            std::cout << "I J L O S Z T" << std::endl;
            char b;
            std::cin >> b;
            force(b);
        } else {
            std::cout << "Oh! You are kind! You lose this chance XDDD" <<std::endl;
            std::cout << "Press any to continue" << std::endl;
            std::string temp;
            std::cin >> temp;
        }
    }
    round = 1;
}

void BoardControl::display() {
    if (graphic) {
        view->displayGraph(Board1, Board2, round);
    }
    view->displayText(Board1, Board2);
}

void BoardControl::applyBlind() {
    if (round == 1){
        Board2->setBlind();
    }
    else {
        Board1->setBlind();
    } 
}

void BoardControl::removeBlind() {
    if (round == 1) {
        Board2->unsetBlind();
    }
    else {
        Board1->unsetBlind();
    }    
}


void BoardControl::needGraph() {
    graphic = true;
    view->graphic_version();
    view->initGraph(); 
}

void BoardControl::endgame() {
    view->endGame(Board1, Board2);
}
