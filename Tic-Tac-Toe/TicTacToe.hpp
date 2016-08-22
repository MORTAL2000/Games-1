
#ifndef _MY_CLASS_TIC_TAC_TOE
#define _MY_CLASS_TIC_TAC_TOE

//#include "Tree.hpp"

#include <iostream>
#include <stdexcept>
#include <vector>
#include <tuple>


class Tree;

class TicTacToe{
    
    const int size = 3;
public:
    // this can be accessed in compile time TicTacToe::
    enum s {EMPTY, HASX, HASO};   
    // internal typedef style 
    // It is always best to limit the scope of names as much as possible
    typedef s state;    

    std::vector<std::vector<state> > cur_state;
/*    state state_array[SIZE][SIZE] = {
        {EMPTY, EMPTY, EMPTY},
        {EMPTY, EMPTY, EMPTY},
        {EMPTY, EMPTY, EMPTY},

    };
*/
    bool turn;
    Tree * my_tree;    

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
