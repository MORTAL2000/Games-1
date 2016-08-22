#include "Tree.hpp"

Tree::Tree(){
}

void Tree::print(const std::vector<std::vector<TicTacToe::state> >& v){
    std::cout << "Size of vec = " << v.size() << std::endl;
    for(size_t i = 0; i < v.size(); i++){
        for(size_t j = 0; j < v.size(); j++){
            
            std::cout << v[i][j] << "  ";
    
        }
        std::cout << std::endl;
    } 
}

void Tree::minimax(int& x, int& y, std::vector<std::vector<TicTacToe::state> > v){

    // write exit fuction here
    // Its when we reach the end sate of the game
    // 
    // It means one of the path on the tree has came to end state
    // if X has won return -10
    // if O has won return +10    
    // if draw return 0
    bool turn  = true;
   // Node *n = new Node;
    std::shared_ptr<Node> n = std::make_shared<Node>();
    
    n->v   = v;
    n->val = 9999;
    int max   = -10000;

    create_tree(n, find_empty_vec(v), turn);         
 //   std::cout << "Done Creating Tree!!" << std::endl;
    
    depth_first_search(n, turn);

    for(auto it = n->collect_nodes.begin(); it != n->collect_nodes.end(); it++){
        if((*it)->val == 10 || (*it)->val == 0) {
            if( (*it)->val > max){ 
                max = (*it)->val; 
                x = (*it)->x;
                y = (*it)->y;              
            }
            
        }
         
    }
    // I think I can use root and latter delete root here
}

// since create_tree makes tree now write depth first search

int Tree::depth_first_search(std::shared_ptr<Node> n, bool turn){
    if(n->val == -10 || n->val == 0 || n->val == 10) return n->val;
    else if(turn){
        int max = -10000000; 
        for(auto it = n->collect_nodes.begin(); it != n->collect_nodes.end(); it++){
            if(depth_first_search(*it, false) > max) 
                max = depth_first_search(*it, false);
        }
        n->val = max;
        return max; 
    }else{
        int min = 10000000; 
        for(auto it = n->collect_nodes.begin(); it != n->collect_nodes.end(); it++){
            if(depth_first_search(*it, true) < min) 
                min = depth_first_search(*it, true);
        }
        n->val = min;
        return min;
    }
}   

void Tree::create_tree(std::shared_ptr<Node> n, std::vector<std::pair<int, int>> ev, bool turn){

    static int count = 0;
    // loss
    if(game_state(n->v) == 1){
        n->val = -10;
        return;
    }
    // win
    else if(game_state(n->v) == 2){ 
        n->val = 10;
        return;
    }
    // draw
    else if(game_state(n->v) == 3){ 
        n->val = 0;       
        return;
    }
    for(auto it = ev.begin(); it != ev.end(); it++){

        if(turn) {
            // HASO turn
            std::shared_ptr<Node> node = std::make_shared<Node>();
            node->v = n->v;
            node->val = -9999;
            node->v[it->first][it->second] = TicTacToe::HASO;
            node->x = it->first;
            node->y = it->second;
            n->collect_nodes.insert(node);
            create_tree(node, find_empty_vec(node->v), false); 
            
        }else{
            std::shared_ptr<Node> node = std::make_shared<Node>();
            node->v = n->v;
            node->val = 9999;
            node->v[it->first][it->second] = TicTacToe::HASX;  
            node->x = it->first;
            node->y = it->second;
            n->collect_nodes.insert(node);
            
            create_tree(node, find_empty_vec(node->v), true);
        }

    }
}

std::vector<std::pair<int,int>> Tree::find_empty_vec(const std::vector<std::vector<TicTacToe::state> >& v){

    std::vector<std::pair<int, int>> empty_vec;
    for(size_t i = 0; i < v.size(); i++){
        for(size_t j = 0; j < v.size(); j++){
            
            if(v[i][j] == TicTacToe::EMPTY)
                empty_vec.push_back(std::make_pair(i, j));
        }
    }
    return empty_vec;
}

int Tree::game_state(const std::vector<std::vector<TicTacToe::state> >& cur_state){

    int mcount = 0;    
    // if x win return 1 
    if( (cur_state[0][0] == TicTacToe::HASX) && (cur_state[0][1] == TicTacToe::HASX) && (cur_state[0][2] == TicTacToe::HASX))
        return 1;
    else if( (cur_state[1][0] == TicTacToe::HASX) && (cur_state[1][1] == TicTacToe::HASX) && (cur_state[1][2] == TicTacToe::HASX))
        return 1;
    else if( (cur_state[2][0] == TicTacToe::HASX) && (cur_state[2][1] == TicTacToe::HASX) && (cur_state[2][2] == TicTacToe::HASX))
        return 1;
    else if( (cur_state[0][0] == TicTacToe::HASX) && (cur_state[1][1] == TicTacToe::HASX) && (cur_state[2][2] == TicTacToe::HASX))
        return 1;
    else if( (cur_state[2][0] == TicTacToe::HASX) && (cur_state[1][1] == TicTacToe::HASX) && (cur_state[0][2] == TicTacToe::HASX))
        return 1;
    else if( (cur_state[0][0] == TicTacToe::HASX) && (cur_state[1][0] == TicTacToe::HASX) && (cur_state[2][0] == TicTacToe::HASX))
        return 1;
    else if( (cur_state[0][1] == TicTacToe::HASX) && (cur_state[1][1] == TicTacToe::HASX) && (cur_state[2][1] == TicTacToe::HASX))
        return 1;
    else if( (cur_state[0][2] == TicTacToe::HASX) && (cur_state[1][2] == TicTacToe::HASX) && (cur_state[2][2] == TicTacToe::HASX))
        return 1;
 
  //  if o win return 2   
    else if( (cur_state[0][0]  == TicTacToe::HASO) && (cur_state[0][1]  == TicTacToe::HASO) && (cur_state[0][2]  == TicTacToe::HASO))
        return 2;
    else if( (cur_state[1][0]  == TicTacToe::HASO) && (cur_state[1][1]  == TicTacToe::HASO) && (cur_state[1][2]  == TicTacToe::HASO))
        return 2;
    else if( (cur_state[2][0]  == TicTacToe::HASO) && (cur_state[2][1]  == TicTacToe::HASO) && (cur_state[2][2]  == TicTacToe::HASO))
        return 2;
    else if( (cur_state[0][0]  == TicTacToe::HASO) && (cur_state[1][1]  == TicTacToe::HASO) && (cur_state[2][2]  == TicTacToe::HASO))
        return 2;
    else if( (cur_state[2][0]  == TicTacToe::HASO) && (cur_state[1][1]  == TicTacToe::HASO) && (cur_state[0][2]  == TicTacToe::HASO))
        return 2;
    else if( (cur_state[0][0] == TicTacToe::HASO) && (cur_state[1][0] == TicTacToe::HASO) && (cur_state[2][0] == TicTacToe::HASO))
        return 2;
    else if( (cur_state[0][1] == TicTacToe::HASO) && (cur_state[1][1] == TicTacToe::HASO) && (cur_state[2][1] == TicTacToe::HASO))
        return 2;
    else if( (cur_state[0][2] == TicTacToe::HASO) && (cur_state[1][2] == TicTacToe::HASO) && (cur_state[2][2] == TicTacToe::HASO))
        return 2;
 
    for(size_t i = 0; i < cur_state.size(); i++){
        for(size_t j = 0; j < cur_state.size(); j++){
            if( (cur_state[i][j] == TicTacToe::HASO) || (cur_state[i][j] == TicTacToe::HASX))
                mcount++;
        }
    }
    if (mcount == (cur_state.size()*cur_state.size())) return 3;

    else return 0;




}
