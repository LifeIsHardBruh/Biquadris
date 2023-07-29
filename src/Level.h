#ifndef _LEVEL_H_
#define _LEVEL_H_
#include <string>
#include "Block.h"
#include <vector>
#include <memory>
#include <iostream>

class Level {
    protected:
    std::string filename = "";
    std::vector<char> block; //store the blocks produced in file
    bool is_random = false;
    int cur_level;
    int curIndex = 0;
    int counter = 0;

    public:
    int getCurlevel() const;
    void readFile();
    void norandom();
    void random();
    void setFilename(std::string fname);
    std::string getFilename() const;
    void resetRound();
    void resetCurIndex();
    bool ifstar() const;
    void resetVector();
    virtual std::shared_ptr<Block> createBlock() = 0;
};

class Level0: public Level {
    public:
    Level0(std::string file) {
        filename = file;
        is_random = false;
        cur_level = 0;
        if (filename != "") {
            readFile();
        }
    }
    std::shared_ptr<Block> createBlock() override;
    void resetRound();
};

class Level1: public Level {
    public:
    Level1(std::string file) {
        filename = file;
        is_random = true;
        cur_level = 1;
    }
    std::shared_ptr<Block> createBlock() override;
};

class Level2: public Level {
    public:
    Level2(std::string file) {
        filename = file;
        is_random = true;
        cur_level = 2;
    }
    std::shared_ptr<Block> createBlock() override;
};

class Level3: public Level {
    public:
    Level3(std::string file) {
        filename = file;
        is_random = true;
        cur_level = 3;
        if (filename != "") {
            readFile();
        }
    }
    std::shared_ptr<Block> createBlock() override;
};

class Level4: public Level {
    public:
    Level4(std::string file) {
        filename = file;
        is_random = true;
        cur_level = 4;
        if (filename != "") {
            readFile();
        }
    }
    std::shared_ptr<Block> createBlock() override;
};

#endif
