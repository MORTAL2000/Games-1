
#ifndef _MY_CLASS_TIC_TAC_TOE
#define _MY_CLASS_TIC_TAC_TOE

//#include "Tree.hpp"

#include <iostream>
#include <stdexcept>
#include <vector>
#include <tuple>
#include <memory>
#include <limits> 

class Tree;

class TicTacToe{
    // logical size of tictactoe 
    const size_t size   = 3;
    // this is the total size of tictactoe board in terminal
    const size_t length = 16;
    // size of each square of board 
    // a size of 3 contains 3*3 = 9 squares
    const size_t sqSize = 5;
    // game state
    enum gs { RUNNING, XWON, OWON, DRAW, RESTART, QUIT };

    gs gstate;
    void welcome_message();
    
    // return 1 for single player and 2 for double player
    int select_player();
    // main engine that runs the game  
    void play_game(int);
    // method for debugging 
    void print_state();

public:
    // this can be accessed in compile time TicTacToe::
    enum s {EMPTY, HASX, HASO};   
    // internal typedef style 
    // It is always best to limit the scope of names as much as possible
    typedef s state;    

    std::vector<std::vector<state> > cur_state;
    
    bool turn;
    std::shared_ptr<Tree> my_tree;    

    TicTacToe();
    int print();
    gs game_state();
    //void game_logic();
    void set_state(int i, int j, state s);
    void run();  
    void parse_value(std::string s, int& x, int& y);
    void roll_back(int step);
    void reset();
};

#endif
