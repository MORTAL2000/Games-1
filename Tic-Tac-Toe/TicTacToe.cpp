#include "TicTacToe.hpp"
#include "Tree.hpp"

#define RED_TEXT    "\e[31;1m"
#define YELLOW_TEXT "\e[33;1m"
#define DEFAULT     "\e[0m"
#define GREEN_TEXT  "\e[32;1m"

TicTacToe::TicTacToe():turn(true),cur_state(size){
    for(auto &it : cur_state){
        it.resize(size,EMPTY);
    }
    //my_tree = new Tree;
    my_tree = std::make_shared<Tree>();
}

int TicTacToe::print(){
    
    // this is keep track for rolling back 
    size_t endl_count = 0;
    size_t x = 0;
    size_t y = 0;

    while(x < size){
        for(size_t i = 0; i < length; i++){
            if((i+1)%(sqSize+1) == 0 && (i+1) != length) std::cout <<"|"; 
            else std::cout << " ";
        }
        std::cout << std::endl;

        while( y < size){
            for(size_t j = 0; j < sqSize; j++){
                if(cur_state[x][y] == EMPTY){
                    if((sqSize-1)/2 == j){
                        std::cout << ",";
                    }
                    else if(((sqSize-1)/2 - 1) == j) std::cout << x; 
                    else if(((sqSize-1)/2 + 1) == j) std::cout << y;
                    else std::cout << " ";
                }else if(cur_state[x][y] == HASO){
                    if((sqSize-1)/2 == j){
                        std::cout << RED_TEXT;
                        std::cout << "O";
                        std::cout << DEFAULT;
                    }else std::cout << " ";
                }else if(cur_state[x][y] == HASX){
                    if((sqSize-1)/2 == j){
                        std::cout << GREEN_TEXT;
                        std::cout << "X";
                        std::cout << DEFAULT;
                    }else std::cout << " ";
                }
            }
            if(y<(size-1)) std::cout << "|";
            y++;
        }
        std::cout << std::endl;

        for(size_t k = 0; k < length; k++){
            if((k+1)%(sqSize+1) == 0 && (k+1) != length) std::cout <<"|"; 
            else if(x < (size-1)) std::cout << "_";
            else std::cout << " ";
        }
        std::cout << std::endl;
        x++;   
        y = 0;
        endl_count += 3;
    }
    return endl_count;
}

void TicTacToe::parse_value(std::string s, int& x, int& y){
    size_t i = 0;
    size_t count = 0;
    if(s[i] == '\0') throw std::invalid_argument("Please provide some input data");
    while ( s[i] != '\0' ){
        if(s[i] == ' ' || s[i] == ',') {
            i++;
            continue;
        }else{
            if(count == 0){  
                count++;    
                if(s[i+1] != ' ' && s[i+1] != ',')
                    throw std::invalid_argument("Please Enter intput in correct format : 0 0 or 0,0");
                x = s[i] - '0';
                if((x > 2) || (x < 0)) 
                    throw std::invalid_argument(" Please Enter x in range of 0-2                        ");
            }else{
                y = s[i] - '0';
                if((y > 2) || (y < 0)) 
                    throw std::invalid_argument(" Please Enter y in range of 0-2                        ");
                break;
            }   
        }
        i++;
    }
}

// This function sets the state of the i j index. 
// If the i and j  already contains state other then empty throw exception prompting to 
// enter different index 
    
void TicTacToe::set_state(int i, int j, state s){
    
    if( cur_state[i][j] != EMPTY) 
        throw std::invalid_argument("The index you entered already taken                               ");
    cur_state[i][j] = s;
}

void TicTacToe::run(){
    int x;
    int y;
    int step  = 0;//size*size + 1;
    int state = 0;
    std::string my_string;

    std::cout << YELLOW_TEXT;
    std::cout << "                     Welcom to TicTacToe           \n";
    std::cout << "        Please enter input in form of X and Y cordinate:   " << std::endl;
    std::cout << "eg: If you enter 1 2 or 1,2 then 1 resemble as X co-ordinate and 2 as  Y co-ordinate" << std::endl;
    std::cout << DEFAULT;
    std::cout << std::endl;
    while(state == 0){
        step = print();
       // print_state();
        //std::cout << "Please enter co-ordinates seperated by space            \n";
        if(turn){ 
            step++;
            std::cout << "Its X turn >>  "  << " : ";
            // google : wiki ANSI escape code for more detail
            // zero (or missing), clear from cursor to the end of the line.
            std::cout << "\033[0K";
            std::getline(std::cin,my_string);
        }    
        else{ 
            //std::cout << "Its O turn >> ";
            // google : wiki ANSI escape code for more detail
            // zero (or missing), clear from cursor to the end of the line.
            std::cout << "\033[0K";
        }
        try{
            parse_value(my_string,x,y);
            if(turn){
                try{
                    set_state(x,y, HASX);
                    turn = give_turn(); // This is nor proper place for this
                    std::cout << "\033[2k";
                } catch(std::invalid_argument& e){
                    std::cout << e.what() << std::endl;
                    step++;
                }
            }
            else{
                try{
                //set_state(x, y, HASO);
                // This is machine turn now
                machine_set_state(HASO);
                turn = give_turn(); // This is nor proper place for this
                std::cout << "\033[2k";
                } catch(std::invalid_argument& e){
                    std::cout << e.what() << std::endl;
                    step++;
                }
            }
            //std::cout << " You Entered  " << x << " , " <<  y <<"                  "<< std::endl;
        } catch( std::invalid_argument& e){
            std::cout << e.what() << std::endl;
            step++;
        }
        roll_back(step);
        state = game_state();
    }
    step = print();
    std::cout << std::endl;
    std::cout << RED_TEXT;
    if ( state == 1) std::cout << "HUMAN WON: Congratulaton Your Sneaky Baster " << std::endl;
    else if ( state == 2) std::cout << "Computer WON .. Now I head for world domination "<< std::endl;
    else if ( state == 3) std::cout << "There was a DRAW!!  " << std::endl;
    std::cout << DEFAULT;

}

void TicTacToe::minimax(int& x, int& y){
    // latter I could ask user for algorithm that they want 
    // and use switch to select the proper 
    // algorithm 
    my_tree->minimax(x, y, cur_state);

}
    
// this function calls set_state by providing 
// appropriate x and y
void TicTacToe::machine_set_state(state s){

    int x;
    int y;
    
    //std::cout << "entering machine setting for  x  = " << x << " ,  y = " << y << std::endl;
    minimax(x, y); 

    //std::cout << "got machine setting of x  = " << x << " ,  y = " << y << std::endl;
    set_state(x, y, s);
}

int TicTacToe::game_state(){
 
    // use for loop here 

    int mcount = 0;    
    // if x win return 1 
    if( (cur_state[0][0] == HASX) && (cur_state[0][1] == HASX) && (cur_state[0][2] == HASX))
        return 1;
    else if( (cur_state[1][0] == HASX) && (cur_state[1][1] == HASX) && (cur_state[1][2] == HASX))
        return 1;
    else if( (cur_state[2][0] == HASX) && (cur_state[2][1] == HASX) && (cur_state[2][2] == HASX))
        return 1;
    else if( (cur_state[0][0] == HASX) && (cur_state[1][1] == HASX) && (cur_state[2][2] == HASX))
        return 1;
    else if( (cur_state[2][0] == HASX) && (cur_state[1][1] == HASX) && (cur_state[0][2] == HASX))
        return 1;
    else if( (cur_state[0][0] == HASX) && (cur_state[1][0] == HASX) && (cur_state[2][0] == HASX))
        return 1;
    else if( (cur_state[0][1] == HASX) && (cur_state[1][1] == HASX) && (cur_state[2][1] == HASX))
        return 1;
    else if( (cur_state[0][2] == HASX) && (cur_state[1][2] == HASX) && (cur_state[2][2] == HASX))
        return 1;
 
  //  if o win return 2   
    else if( (cur_state[0][0]  == HASO) && (cur_state[0][1]  == HASO) && (cur_state[0][2]  == HASO))
        return 2;
    else if( (cur_state[1][0]  == HASO) && (cur_state[1][1]  == HASO) && (cur_state[1][2]  == HASO))
        return 2;
    else if( (cur_state[2][0]  == HASO) && (cur_state[2][1]  == HASO) && (cur_state[2][2]  == HASO))
        return 2;
    else if( (cur_state[0][0]  == HASO) && (cur_state[1][1]  == HASO) && (cur_state[2][2]  == HASO))
        return 2;
    else if( (cur_state[2][0]  == HASO) && (cur_state[1][1]  == HASO) && (cur_state[0][2]  == HASO))
        return 2;
    else if( (cur_state[0][0] == HASO) && (cur_state[1][0] == HASO) && (cur_state[2][0] == HASO))
        return 2;
    else if( (cur_state[0][1] == HASO) && (cur_state[1][1] == HASO) && (cur_state[2][1] == HASO))
        return 2;
    else if( (cur_state[0][2] == HASO) && (cur_state[1][2] == HASO) && (cur_state[2][2] == HASO))
        return 2;
 
    for(size_t i = 0; i < size; i++){
        for(size_t j = 0; j < size; j++){
            if( (cur_state[i][j] == HASO) || (cur_state[i][j] == HASX))
                mcount++;
        }
    }
    if (mcount == (size*size)) return 3;

    else return 0;
}

bool TicTacToe::give_turn(){
    // we can use bit toggle here 
    // true means turn of X
    if(turn) {
        turn = false;
        return turn;       
    }
    else {
        turn = true;
        return turn;
    }   
}


void TicTacToe::roll_back(int step){
    for(size_t i = 0; i < step; i++)std::cout << "\e[A";
}

void TicTacToe::print_state(){

    for(size_t i = 0; i < size; i++){
        for(size_t j = 0; j < size; j++){
            
            std::cout << cur_state[i][j] << "  ";
    
        }
        std::cout << std::endl;
    }

}
