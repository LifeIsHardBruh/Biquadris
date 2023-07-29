#include "View.h"
#include "window.h"
#include "Board.h"
#include "Block.h"
#include <iomanip>
#include <iostream>
#include <string>
#include <memory>


// required board size
const int boardRows = 18;
const int totalRows = 21;
const int boardCols = 11;
const int s = 20;                               // side length of 1 single block
const float w = s - 0.01;
const int board_width = boardCols * s;          // width of a board
const int board_height = boardRows * s;         // height of a board
const int header_h = 4 * s;                     // height of header part
const int footer_h = 5 * s;                     // height of footer part
const int inner_s = 5 * s;                       // width of space between b1 and b2
const int outter_s = 2.5 * s;                     // width of outter space 
const int win_width = 2 * (board_width + outter_s) + inner_s;      // width of the entire window
const int win_height = header_h + board_height + footer_h;     // height of the entire window

const int board_l1 = outter_s;       // left border for P1
const int board_r1 = board_l1 + board_width;       // right border for P1
const int board_l2 = board_r1 + inner_s;       // left border for P2
const int board_r2 = board_l2 + board_width;       // right border for P2
const int board_top = header_h;            // top border
const int board_d = board_top + board_height;     // down border

const int bw = 5;       // border width

// Constructor
View::View(bool g): isGraphic{g} {
    if (isGraphic){
        initGraph();
    }
}

// helper 
// initializes the background of the board
void View::initGraph() {
    
    xw = std::make_shared<Xwindow>(win_width, win_height);
    xw->fillRectangle(0, 0, win_width, win_height, Xwindow::Gray90);         // filled with black
    
    // board 1 & 2
    // xw->fillRectangle(board_l1, board_top, board_width, board_height, Xwindow::White);
    // xw->fillRectangle(board_l2, board_top, board_width, board_height, Xwindow::White);

    xw->fillRectangle(board_l1 - bw, board_top - bw, board_width + bw, bw, Xwindow::Black);
    xw->fillRectangle(board_l1 - bw, board_top - bw, bw, board_height + bw, Xwindow::Black);
    xw->fillRectangle(board_l1 - bw, board_d, board_width + bw, bw, Xwindow::Black);
    xw->fillRectangle(board_r1, board_top - bw, bw, board_height + 2 * bw, Xwindow::Black);

    xw->fillRectangle(board_l2 - bw, board_top - bw, board_width + bw, bw, Xwindow::Black);
    xw->fillRectangle(board_l2 - bw, board_top - bw, bw, board_height + bw, Xwindow::Black);
    xw->fillRectangle(board_l2 - bw, board_d, board_width + bw, bw, Xwindow::Black);
    xw->fillRectangle(board_r2, board_top - bw, bw, board_height + 2 * bw, Xwindow::Black);

    // strings
    xw->drawString(board_l1 + 1, s, "LEVEL:");
    xw->drawString(board_l2 + 1, s, "LEVEL:");
    xw->drawString(board_l1 + 1, 2 * s, "SCORE:");
    xw->drawString(board_l2 + 1, 2 * s, "SCORE:");
    xw->drawString(board_l1 + 1, 3 * s, "HIGHEST SCORE:");
    xw->drawString(board_l2 + 1, 3 * s, "HIGHEST SCORE:");
    xw->drawString(board_l1 + 1, board_d + s, "NEXT:");
    xw->drawString(board_l2 + 1, board_d + s, "NEXT:");

    player1_turn();

}

// helper function
// return color based on block type
const int colortype(char type){
    switch (type)
    {
    case 'I':   
        return Xwindow::Blue;

    case 'J':
        return Xwindow::BlueViolet;

    case 'L':
        return Xwindow::Cyan;

    case 'O':
        return Xwindow::GreenYellow;

    case 'S':
        return Xwindow::Indianred1;

    case 'Z':
       return Xwindow::Orange;
    
    case 'T':
        return Xwindow::DeepPink1;
    
    case '*':
        return Xwindow::Black;
    
    case ' ':
        return Xwindow::White;
    }
    return Xwindow::White;
}


void View::displayGraph(std::shared_ptr<Board> b1, std::shared_ptr<Board> b2, int round) {
    // header 
    xw->fillRectangle(0, 0, board_width - outter_s, header_h - bw, Xwindow::Gray90);
    xw->fillRectangle(board_l2, 0, board_width - outter_s, header_h - bw, Xwindow::Gray90);

    xw->drawString(board_l1 + 1, s, "LEVEL:  " + std::to_string(b1.get()->getLevel().get()->getCurlevel()));
    xw->drawString(board_l2 + 1, s, "LEVEL:  " + std::to_string(b2.get()->getLevel().get()->getCurlevel()));

    xw->drawString(board_l1 + 1, 2 * s, "SCORE:  " + std::to_string( b1.get()->getScore().get()->getScore()));
    xw->drawString(board_l2 + 1, 2 * s, "SCORE:  " + std::to_string( b2.get()->getScore().get()->getScore()));

    xw->drawString(board_l1 + 1, 3 * s, "HIGHEST SCORE:  " + std::to_string( b1.get()->getScore()->getHscore()));
    xw->drawString(board_l2 + 1, 3 * s, "HIGHEST SCORE:  " + std::to_string( b2.get()->getScore()->getHscore()));

    // round
    if (round == 1) {
        player1_turn();
    }
    else {
        player2_turn();
    }


    // board
    for (int i = 0; i < boardRows; i++){
        int color = 0;
        // board 1
        for (int j = 0; j < boardCols; j++){
            // blind && in the range -> black
            if ((b1->getBlind()) && ((i >= 5) && (i < 15)) && ((j >= 2) && (j < 9))){
                xw->fillRectangle(board_l1 + (j * s), board_top + (i * s), w, w, Xwindow::Gray75);
            }
            else {
                color = colortype(b1.get()->findType(j, i));
                xw->fillRectangle(board_l1 + (j * s), board_top + (i * s), w, w, color);
            }  
        }
        // board 2
        for (int j = 0; j < boardCols; j++){
            if ((b2->getBlind()) && ((i >= 5) && (i < 15)) && ((j >= 2) && (j < 9))){
                xw->fillRectangle(board_l2 + (j * s), board_top + (i * s), w, w, Xwindow::Gray75);
            }
            else {
                color = colortype(b2.get()->findType(j, i));
                xw->fillRectangle(board_l2 + (j * s), board_top + (i * s), w, w, color);
            } 
        }
    }

    // Next Block:
    for (int i = 2; i < 4; i++){
        int color;
        for (int j = 0; j < 4; j++){
        // board 1 next block
            if (b1.get()->getNextBlock().get()->findPos(j, i)){
                    color = colortype(b1->getNextBlock().get()->blockType());
                    xw->fillRectangle(board_l1 + 5 * s + (j * s), board_d + (i * s), w, w, color);
            }
            else {
                xw->fillRectangle(board_l1 + 5 * s + (j * s), board_d  + (i * s), w, w, Xwindow::Gray90);
            }
            // board 2
            if (b2.get()->getNextBlock().get()->findPos(j, i)){
                    color = colortype(b2->getNextBlock().get()->blockType());
                    xw->fillRectangle(board_l2 + 5 * s + (j * s), board_d + (i * s), w, w, color);
            }
            else {
                xw->fillRectangle(board_l2 + 5 * s + (j * s), board_d + (i * s), w, w, Xwindow::Gray90);
            }
       } 
    }
}


void View::displayText(std::shared_ptr<Board> b1, std::shared_ptr<Board> b2) {
    // Header part
    std::cout << "Level:" << std::setw(5) << b1->getLevel()->getCurlevel();
    std::cout << "          " ;
    std::cout << "Level:" << std::setw(5) << b2->getLevel()->getCurlevel();
    std::cout << std::endl;
    
    std::cout << "Score:" << std::setw(5) << b1->getScore()->getScore();
    std::cout << "          " ;
    std::cout << "Score:" << std::setw(5) << b2->getScore()->getScore();
    std::cout << std::endl;

    std::cout << "HiScore:" << std::setw(3) << b1->getScore()->getHscore();
    std::cout << "          " ;
    std::cout << "HiScore:" << std::setw(3) << b2->getScore()->getHscore();
    std::cout << std::endl;

    std::cout << "-----------          -----------" << std::endl;
    
    // Board part
    for (int i = 0; i < boardRows; i++) {
        // board 1
        for (int j = 0; j < boardCols; j++){
            // blind && in the range -> cout '?'
            if ((b1->getBlind()) && ((i >= 5) && (i < 15)) && ((j >= 2) && (j < 9))){
                std::cout << '?';
            }
            else {
                std::cout << b1->findType(j, i);   
            }     
        }

        std::cout << "          ";

        // board 2
        for (int j = 0; j < boardRows; j++){
            // blind && in the range -> cout '?'
            if ((b2->getBlind()) && ((i >= 5) && (i < 15)) && ((j >= 2) && (j < 9))){
                std::cout << '?';
            }
            else {
                std::cout << b2->findType(j, i);
            } 
        }

        std::cout << std::endl;
    }
    
    // Next block
    std::cout << "-----------          -----------" << std::endl;
    std::cout << "Next:                Next:      " << std::endl;
    for (int i = 2; i < 4; i++){
        // next block for board 1
        std::cout << "      ";
        for (int j = 0; j < 4; j++){
            // there is something in this posn
            if (b1->getNextBlock().get()->findPos(j, i)){
                std::cout << b1->getNextBlock().get()->blockType();
            }
            else {
                std::cout << " ";
            }
        }   // for loop
        std::cout << "                 ";

        // next block for board 2
        for (int j = 0; j < 4; j++){
            // there is something in this posn
            if (b2->getNextBlock().get()->findPos(j, i)){
                std::cout << b2->getNextBlock().get()->blockType();
            }
            else {
                std::cout << " ";
            }
        }   // for loop
        std::cout << "         " << std::endl;
    }   // for loop
}

void View::endGame(std::shared_ptr<Board> b1, std::shared_ptr<Board> b2) {
    int score_1 = b1->getScore().get()->getHscore();
    int score_2 = b2->getScore().get()->getHscore();
    std::string win;

    if (score_1 > score_2){
        win = "Player 1 Wins!";
    }
    else if (score_1 == score_2){
        win = "Tie!";
    }
    else {
        win = "Player 2 Wins!";
    }

    // graphic version
    if (isGraphic){
        xw->fillRectangle(board_l1 + inner_s - bw, board_top + header_h - bw, board_width * 2 - inner_s + 2 * bw, bw);
        xw->fillRectangle(board_l1 + inner_s - bw, board_top + 4 * header_h, board_width * 2 - inner_s + 2 * bw, bw);
        xw->fillRectangle(board_l1 + inner_s - bw, board_top + header_h - bw, bw, 3 * header_h + 2 * bw);
        xw->fillRectangle(board_l1 + board_width * 2 , board_top + header_h - bw, bw, 3 * header_h + 2 * bw);
        

        xw->fillRectangle(board_l1 + inner_s, board_top + header_h, board_width * 2 - inner_s , 3 * header_h, Xwindow::White);
        xw->drawString(board_l1 + 2 *inner_s, board_top + header_h + 2 * s, "Player 1 Highest Score: " + std::to_string(score_1));
        xw->drawString(board_l1 + 2 *inner_s, board_top + header_h + 4 * s, "Player 2 Highest Score: " + std::to_string(score_2));
        xw->drawString(board_l1 + 2 *inner_s, board_top + header_h + 6 * s, win);
        
    }
    // text version
        std::cout << "-----------          -----------" << std::endl;
        std::cout << "HiScore:             HiScore:" << std::endl;
        std::cout << " " << score_1 << std::setw(21) << score_2 << std::endl;
        std::cout << std::endl;
        std::cout << win << std::endl;
        std::cout << "-----------          -----------" << std::endl;
}

void View::graphic_version(){
    isGraphic = true;
}

void View::player1_turn(){
    xw->fillRectangle(board_r1 - s, 3 * s, w, bw, Xwindow::GreenYellow);
    xw->fillRectangle(board_r2 - s, 3 * s, w, bw, Xwindow::Gray75);
}

void View::player2_turn() {
    xw->fillRectangle(board_r1 - s, 3 * s, w, bw, Xwindow::Gray75);
    xw->fillRectangle(board_r2 - s, 3 * s, w, bw, Xwindow::GreenYellow);
}


