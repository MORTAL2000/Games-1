#include "TicTacToe.hpp"
#include "Tree.hpp"

#define RED_TEXT    "\e[31;1m"
#define YELLOW_TEXT "\e[33;1m"
#define DEFAULT     "\e[0m"
#define GREEN_TEXT  "\e[32;1m"

TicTacToe::TicTacToe():gstate(RUNNING),turn(true), cur_state(size){
    for(auto &it : cur_state){
        it.resize(size, EMPTY);
    }
    my_tree = std::make_shared<Tree>();
}

void TicTacToe::reset(){

    cur_state.clear();
    cur_state.resize(size);
    for(auto &it : cur_state){
        it.resize(size, EMPTY);
    }  
    turn = true;
    gstate = RUNNING;  
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
    bool   xturn = true;
    if(s[i] == '\0') throw std::invalid_argument("Please provide some input data");
    while ( s[i] != '\0' ){
        if(s[i] == ' ' || s[i] == ',') {
            i++;
            if(!xturn && s[i] == '\0')
                throw std::invalid_argument("You forgot y : Please intput in correct format : 0 0 or 0,0");
            continue;
        }else{
            if(xturn){  
                if(s[i] == 'q') {
                    gstate = QUIT;
                    return;
                }else if(s[i] == 'r'){
                    gstate = RESTART; 
                    return;
                }
                xturn = false;    
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

void TicTacToe::welcome_message(){
    std::cout << YELLOW_TEXT;
    std::cout << "                Welcome to TicTacToe         \n";
    std::cout << "    For Single Player press 1 or  press 2 for Multi player \n\n\n";
    std::cout << DEFAULT;
    
}

int TicTacToe::select_player(){
    int choice;
    
    std::cout << "Please Enter your choice : ";
    while(true){
        std::cin >> choice;
        if(choice != 1 && choice != 2){
            std::cout << "\e[A"; 
            std::cout << "\033[0K";
            std::cout << "Please Enter your choice (1 or 2) : ";
            // To make sure wrong cin ( string or something else is handled)
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }else break;
    }
    std::cout << "\n";
    if(choice == 1){
        std::cout << "   Single Player Mode (Human Vs Machine)\n\n";
    }else if(choice == 2){
        std::cout << "   Multi Player Mode (Human Vs Human)\n\n";
    }
    return choice; 
}

void TicTacToe::run(){

    int choice;
    
    welcome_message();

    choice = select_player();
    
    play_game(choice);
}

void TicTacToe::play_game(int choice){
    int step; 
    std::string input_string;
    bool turn = true; 
    int x;
    int y;

    // This will ignore the newline that was there after consumtion from cin above  
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
 
    while(gstate == RUNNING){
    
        step = print();
        std::cout << "\n";
        std::cout << "Please enter co-ordinate seperated by space for ";
        
        if(turn){
            std::cout << " X : ";
            // google : wiki ANSI escape code for more detail
            // zero (or missing), clear from cursor to the end of the line.
            std::cout << "\033[0K"; 
            std::getline(std::cin, input_string);
            try{
                parse_value(input_string, x, y);
                if(gstate == RESTART){
                    reset();
                    roll_back(step+2);
                    continue;
                }
                set_state(x, y, HASX);
            }catch (std::invalid_argument &e){
                step += 3;
                std::cout << RED_TEXT;
                std::cout << e.what() << std::endl;
                std::cout << DEFAULT;
                roll_back(step);
                continue;
            }
            turn = false;
        }else{
            std::cout << " O : ";
            if(choice == 2){
                std::cout << "\033[0K"; 
                std::getline(std::cin, input_string);
            }       
            try{
                if(choice == 1){
                    std::cout << std::endl;
                    my_tree->minimax(x, y, cur_state);
                }
                else if(choice == 2){ 
                    parse_value(input_string, x, y);
                    if(gstate == RESTART) {
                        reset();
                        roll_back(step+2);
                        continue;
                    }
                }
                set_state(x, y, HASO);
             }catch (std::invalid_argument &e){
                step += 3;
                std::cout << RED_TEXT;
                std::cout << e.what() << std::endl;
                std::cout << DEFAULT;
                roll_back(step);
                continue;
            }
            turn = true;
        }
        step += 2;      
        roll_back(step);
        gstate = game_state();
    }
    print();
    std::cout << std::endl;
    std::cout << RED_TEXT;
    if ( gstate == XWON) std::cout << "HUMAN WON: Congratulaton Your Sneaky Baster                  " << std::endl;
    else if ( gstate == OWON) std::cout << "Computer WON .. Now I head for world domination         "<< std::endl;
    else if ( gstate == DRAW) std::cout << "There was a DRAW                                        " << std::endl;
    else if ( gstate == QUIT) std::cout << "You Quit the game                                       " << std::endl;
    std::cout << DEFAULT;
}

TicTacToe::gs TicTacToe::game_state(){
 
    // use for loop here 
    int mcount = 0;    
    // if x win return 1 
    if( (cur_state[0][0] == HASX) && (cur_state[0][1] == HASX) && (cur_state[0][2] == HASX))
        return XWON;
    else if( (cur_state[1][0] == HASX) && (cur_state[1][1] == HASX) && (cur_state[1][2] == HASX))
        return XWON;
    else if( (cur_state[2][0] == HASX) && (cur_state[2][1] == HASX) && (cur_state[2][2] == HASX))
        return XWON;
    else if( (cur_state[0][0] == HASX) && (cur_state[1][1] == HASX) && (cur_state[2][2] == HASX))
        return XWON;
    else if( (cur_state[2][0] == HASX) && (cur_state[1][1] == HASX) && (cur_state[0][2] == HASX))
        return XWON;
    else if( (cur_state[0][0] == HASX) && (cur_state[1][0] == HASX) && (cur_state[2][0] == HASX))
        return XWON;
    else if( (cur_state[0][1] == HASX) && (cur_state[1][1] == HASX) && (cur_state[2][1] == HASX))
        return XWON;
    else if( (cur_state[0][2] == HASX) && (cur_state[1][2] == HASX) && (cur_state[2][2] == HASX))
        return XWON;
 
  //  if o win return 2   
    else if( (cur_state[0][0]  == HASO) && (cur_state[0][1]  == HASO) && (cur_state[0][2]  == HASO))
        return OWON;
    else if( (cur_state[1][0]  == HASO) && (cur_state[1][1]  == HASO) && (cur_state[1][2]  == HASO))
        return OWON;
    else if( (cur_state[2][0]  == HASO) && (cur_state[2][1]  == HASO) && (cur_state[2][2]  == HASO))
        return OWON;
    else if( (cur_state[0][0]  == HASO) && (cur_state[1][1]  == HASO) && (cur_state[2][2]  == HASO))
        return OWON;
    else if( (cur_state[2][0]  == HASO) && (cur_state[1][1]  == HASO) && (cur_state[0][2]  == HASO))
        return OWON;
    else if( (cur_state[0][0] == HASO) && (cur_state[1][0] == HASO) && (cur_state[2][0] == HASO))
        return OWON;
    else if( (cur_state[0][1] == HASO) && (cur_state[1][1] == HASO) && (cur_state[2][1] == HASO))
        return OWON;
    else if( (cur_state[0][2] == HASO) && (cur_state[1][2] == HASO) && (cur_state[2][2] == HASO))
        return OWON;
 
    for(size_t i = 0; i < size; i++){
        for(size_t j = 0; j < size; j++){
            if( (cur_state[i][j] == HASO) || (cur_state[i][j] == HASX))
                mcount++;
        }
    }
    if (mcount == (size*size)) return DRAW;

    else return RUNNING;
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
