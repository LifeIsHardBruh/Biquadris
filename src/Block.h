#ifndef _BLOCK_H_
#define _BLOCK_H_
#include <vector>
#include <memory>

const int totalRow = 17;
const int totalCol = 10;

struct Posn {
    int x, y;
    bool visible = true;
    bool operator==(const Posn& other) {
        return (x == other.x && y == other.y && visible == other.visible);
    }
};

class Block {
    protected:
    char type = ' ';
    std::vector<std::vector<Posn>> pos;
    int rotateTimes = 0;
    int posIndex = 0;
    int heavyLevel = 0;
    int generateLevel = 0; //to record the level of this block generated in

    public:
    virtual void rotateCW() = 0;
    virtual void rotateAW() = 0;
    std::vector<std::vector<Posn>> getVectorPosn() const;
    int findIndex() const;
    void left();
    void right();
    void up();
    void down();
    char blockType() const;
    int getHeavyLevel() const;
    void setHeavyLevel(int heavy);
    bool findPos(int& x, int& y);
    void changeVis(int& x, int& y); // x and y must be valid or it will error
    // return true if there is at least one posn vis
    bool ifVis() const;
    void changeY(int& x, int& y, int num); // add num to y to Posn(x, y)
    int getGenerateLevel() const;
    void setGenerateLevel(int num);
    virtual ~Block() {}
};

class I_block: public Block {
    public:
    void rotateCW() override;
    void rotateAW() override;
    I_block() {
        type = 'I';
        // 2 rotate situations
        pos.push_back(std::vector<Posn>{Posn{0, 3}, Posn{1, 3}, Posn{2, 3}, Posn{3, 3}});
        pos.push_back(std::vector<Posn>{Posn{0, 0}, Posn{0, 1}, Posn{0, 2}, Posn{0, 3}});
    }
};

class J_block: public Block {
    public:
    void rotateCW() override;
    void rotateAW() override;
    J_block() {
        type = 'J';
        // 4 rotate situations
        pos.push_back(std::vector<Posn>{Posn{0, 2}, Posn{0, 3}, Posn{1, 3}, Posn{2, 3}});
        pos.push_back(std::vector<Posn>{Posn{0, 1}, Posn{0, 2}, Posn{0, 3}, Posn{1, 1}});
        pos.push_back(std::vector<Posn>{Posn{0, 2}, Posn{1, 2}, Posn{2, 2}, Posn{2, 3}});
        pos.push_back(std::vector<Posn>{Posn{0, 3}, Posn{1, 1}, Posn{1, 2}, Posn{1, 3}});
    }
};

class L_block: public Block {
    public:
    void rotateCW() override;
    void rotateAW() override;
    L_block() {
        type = 'L';
        // 4 rotate situations
        pos.push_back(std::vector<Posn>{Posn{0, 3}, Posn{1, 3}, Posn{2, 3}, Posn{2, 2}});
        pos.push_back(std::vector<Posn>{Posn{0, 1}, Posn{0, 2}, Posn{0, 3}, Posn{1, 3}});
        pos.push_back(std::vector<Posn>{Posn{0, 2}, Posn{0, 3}, Posn{1, 2}, Posn{2, 2}});
        pos.push_back(std::vector<Posn>{Posn{0, 1}, Posn{1, 1}, Posn{1, 2}, Posn{1, 3}});
    }
};

class O_block: public Block {
    public:
    void rotateCW() override {};
    void rotateAW() override {};
    O_block() {
        type = 'O';
        // only 1 rotate situation
        pos.push_back(std::vector<Posn>{Posn{0, 2}, Posn{0, 3}, Posn{1, 2}, Posn{1, 3}});
    }
};

class S_block: public Block {
    public:
    void rotateCW() override;
    void rotateAW() override;
    S_block() {
        type = 'S';
        // 2 rotate situations
        pos.push_back(std::vector<Posn>{Posn{0, 3}, Posn{1, 3}, Posn{1, 2}, Posn{2, 2}});
        pos.push_back(std::vector<Posn>{Posn{0, 1}, Posn{0, 2}, Posn{1, 2}, Posn{1, 3}});
    }
};

class Z_block: public Block {
    public:
    void rotateCW() override;
    void rotateAW() override;
    Z_block() {
        type = 'Z';
        // 2 rotate situations
        pos.push_back(std::vector<Posn>{Posn{0, 2}, Posn{1, 2}, Posn{1, 3}, Posn{2, 3}});
        pos.push_back(std::vector<Posn>{Posn{0, 2}, Posn{0, 3}, Posn{1, 1}, Posn{1, 2}});
    }
};

class T_block: public Block {
    public:
    void rotateCW() override;
    void rotateAW() override;
    T_block() {
        type = 'T';
        // 4 rotate situations
        pos.push_back(std::vector<Posn>{Posn{0, 2}, Posn{1, 2}, Posn{1, 3}, Posn{2, 2}});
        pos.push_back(std::vector<Posn>{Posn{0, 2}, Posn{1, 1}, Posn{1, 2}, Posn{1, 3}});
        pos.push_back(std::vector<Posn>{Posn{0, 3}, Posn{1, 2}, Posn{1, 3}, Posn{2, 3}});
        pos.push_back(std::vector<Posn>{Posn{0, 1}, Posn{0, 2}, Posn{0, 3}, Posn{1, 2}});
    }
};

class Star_block: public Block {
    public:
    void rotateCW() override {};
    void rotateAW() override {};
    Star_block() {
        type = '*';
        generateLevel = 4;
        // first appear in the mid col
        pos.push_back(std::vector<Posn>{Posn{5, 3}, Posn{5, 3, false}, Posn{5, 3, false}, Posn{5, 3, false}});
    }
};

#endif
