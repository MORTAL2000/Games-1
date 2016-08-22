
#ifndef MY_CLASS_TREE
#define MY_CLASS_TREE


#include "TicTacToe.hpp"
#include <iostream>
#include <set>

#define SIZE 5

struct Node{
    // basically collection of empty Nodes
    std::set<std::shared_ptr<Node>> collect_nodes;
    // stores current game state with each index 
    // containing either EMPTY, HASX or HASO
    std::vector<std::vector<TicTacToe::state> > v;
    int val;
    int x;  
    int y;
    
};

class Tree{

    
    
public:
    Tree();     
    void print(const std::vector<std::vector<TicTacToe::state> >&);
    void minimax(int&, int&, std::vector<std::vector<TicTacToe::state> > v );
    int game_state(const std::vector<std::vector<TicTacToe::state> >& v);
    void create_tree(std::shared_ptr<Node>, std::vector<std::pair<int,int>>, bool);
    std::vector<std::pair<int,int>> find_empty_vec(const std::vector<std::vector<TicTacToe::state> >&);
    int depth_first_search( std::shared_ptr<Node>, bool);
    
    
};

#endif
