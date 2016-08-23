
#ifndef _MY_CLASS_TIC_TAC_TOE
#define _MY_CLASS_TIC_TAC_TOE

//#include "Tree.hpp"

#include <iostream>
#include <stdexcept>
#include <vector>
#include <tuple>
#include <memory>


class Tree;

class TicTacToe{
    // logical size of tictactoe 
    const size_t size   = 3;
    // this is the total size of tictactoe board in terminal
    const size_t length = 16;
    // size of each square of board 
    // a size of 3 contains 3*3 = 9 squares
    const size_t sqSize = 5;
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
    int game_state();
    //void game_logic();
    void set_state(int i, int j, state s);
    void machine_set_state(state);
    void run();  
    void parse_value(std::string s, int& x, int& y);
    void roll_back(int step);
    bool give_turn();
    void minimax(int& x, int& y);
    void print_state();
    
};

#endif
