#include"knight.h"

//------------------------------------------------------------------------------------------
//Class Board function implementations
//------------------------------------------------------------------------------------------

//Board class constructor for initializing a board with blank elements
Board::Board(){
    //Initialize a dynamically allocated board as a matrix of elements
    board = new char*[8];

    for (int i=0; i<8; i++){
        board[i] = new char[8];
    }

    //Set initial knight and flag positions
    initial_knight_x = generate_random_number(BOARD_SIZE);
    initial_knight_y = generate_random_number(BOARD_SIZE);
    do{
        target_flag_x = generate_random_number(BOARD_SIZE);
        target_flag_y = generate_random_number(BOARD_SIZE);
    }
    while ((target_flag_x == initial_knight_x && target_flag_y == initial_knight_y) ||
           check_move_legality_A_to_B(initial_knight_x, initial_knight_y, target_flag_x, target_flag_y)); 

    //Set initial knight and flag positions by setting 'H' and 'X' on the board
    board[initial_knight_x-1][initial_knight_y-1] = current_position; // 'H'
    board[target_flag_x-1][target_flag_y-1]       = flag_position;    // 'X'
}

//Board class destructor
Board::~Board(){
    for (int i=0; i<8; i++){
        delete[] board[i];
    }
    delete[] board;
    board = nullptr;
    wcout<<"\nDestructor called from the actual destructor!!!!\n";
}

//draw_board function
void Board::draw_board(Figure& f){
    wcout << "\033[2J\033[H\n";
    wcout<<" ___ ___ ___ ___ ___ ___ ___ ___\n";
    int count_rows{8};
    for (int i=0; i<8; i++){
        wcout<<"| ";
        for (int j=0; j<8; j++){
            if (board[i][j] == current_position){
                wcout << L'\u265E'; //♞
                //wcout<<L"\U0001F4A9"; //💩
                wcout<<" | ";
            }
            else if(board[i][j] == flag_position){
                wcout<<L"\U0001F6A9"; //🚩
                //wcout<<L"\U0001F6BD"; //🚽
                //wcout << L'\u274C'; //❌
                wcout<<"| ";
            }

            else if(board[i][j] == mine_position){
                wcout<<L'\U0001F4A3'; //💣
                wcout<<"| ";
            }
            //New case where a square could be an enemy
            else if (board[i][j] == enemy_position){
                switch (f.current_enemy){
                    case KNIGHT:
                        wcout<<L'\u2658'; //♘
                        wcout<<" | ";
                        break;
                    case ROOK:
                        wcout<<L'\u2656'; //♖
                        wcout<<" | ";
                        break;
                    case BISHOP:
                        wcout<<L'\u2657'; //♗
                        wcout<<" | ";
                        break;
                    case QUEEN:
                        wcout<<L'\u2655'; //♕
                        wcout<<" | ";
                        break;
                    case KING:
                        wcout<<L'\u2654'; //♔
                        wcout<<" | ";
                        break;
                }
            }
            else{
                //wcout<<board[i][j]<< "  | ";
                wcout<<L'\u200B'; //unicode for an empty square
                wcout<<"  | ";
            }
        }
        wcout<<"  "<<count_rows;
        count_rows --;
        wcout<<"\n|___|___|___|___|___|___|___|___|\n";
    }
        wcout << "  A   B   C   D   E   F   G   H\n";
}

//Function that checks move legality
bool Board::check_move_legality_A_to_B(int initial_knight_x, int initial_knight_y, int target_flag_x, int target_flag_y){
    if ((target_flag_x == initial_knight_x+2 && target_flag_y == initial_knight_y+1) ||
        (target_flag_x == initial_knight_x+2 && target_flag_y == initial_knight_y-1) ||
        (target_flag_x == initial_knight_x-2 && target_flag_y == initial_knight_y+1) ||
        (target_flag_x == initial_knight_x-2 && target_flag_y == initial_knight_y-1) ||
        (target_flag_x == initial_knight_x+1 && target_flag_y == initial_knight_y+2) ||
        (target_flag_x == initial_knight_x+1 && target_flag_y == initial_knight_y-2) ||
        (target_flag_x == initial_knight_x-1 && target_flag_y == initial_knight_y+2) ||
        (target_flag_x == initial_knight_x-1 && target_flag_y == initial_knight_y-2))
        return true;
    else 
        return false;
}
//Function that update figure position after a successfull move
void Board::update_figure_position(int next_x, int next_y){
    board[initial_knight_x-1][initial_knight_y-1] = ' ';
    initial_knight_x = next_x;
    initial_knight_y = next_y;
    board[next_x-1][next_y-1] = current_position;
}
//Function that generates a flag
void Board::generate_flag(){
    int x{0}, y{0};
    do{
        x = generate_random_number(BOARD_SIZE);
        y = generate_random_number(BOARD_SIZE);
    }
    while(check_move_legality_A_to_B(target_flag_x, target_flag_y, x, y) || !move_not_blocked(target_flag_x, target_flag_y) || board[x-1][y-1] == mine_position || board[x-1][y-1] == current_position);
    target_flag_x = x;
    target_flag_y = y;
    board[x-1][y-1] = flag_position;
    }
//Checks if a possible move is blocked
bool Board::move_not_blocked(int target_flag_x, int target_flag_y){
    if((target_flag_x+1<8 && target_flag_x+1>=0) && (target_flag_y+2<8 && target_flag_y+2>=0) && board[target_flag_x+1][target_flag_y+2] != '*')
        return true;
    if((target_flag_x+1<8 && target_flag_x+1>=0) && (target_flag_y-2<8 && target_flag_y-2>=0) && board[target_flag_x+1][target_flag_y-2] != '*')
        return true;
    if((target_flag_x-1<8 && target_flag_x-1>=0) && (target_flag_y+2<8 && target_flag_y+2>=0) && board[target_flag_x-1][target_flag_y+2] != '*')
        return true;
    if((target_flag_x-1<8 && target_flag_x-1>=0) && (target_flag_y-2<8 && target_flag_y-2>=0) && board[target_flag_x-1][target_flag_y-2] != '*')
        return true;
    if((target_flag_x+2<8 && target_flag_x+2>=0) && (target_flag_y+1<8 && target_flag_y+1>=0) && board[target_flag_x+2][target_flag_y+1] != '*')
        return true;
    if((target_flag_x+2<8 && target_flag_x+2>=0) && (target_flag_y-1<8 && target_flag_y-1>=0) && board[target_flag_x+2][target_flag_y-1] != '*')
        return true;
    if((target_flag_x-2<8 && target_flag_x-2>=0) && (target_flag_y+1<8 && target_flag_y+1>=0) && board[target_flag_x-2][target_flag_y+1] != '*')
        return true;
    if((target_flag_x-2<8 && target_flag_x-2>=0) && (target_flag_y-1<8 && target_flag_y-1>=0) && board[target_flag_x-2][target_flag_y-1] != '*')
        return true;

    // If no valid move is found
    return false;
}
//Function that generates additional mines after the iniital have been set up
void Board::generate_additional_mines(int& mine_increment){
    int x{0}, y{0};
    for (int i=0; i<mine_increment; i++){
        if (current_mine_counter >= max_mines_allowed)
            return;
        do{
            x = generate_random_number(BOARD_SIZE);
            y = generate_random_number(BOARD_SIZE);
        }
        while ((board[x-1][y-1] == current_position || board[x-1][y-1] == flag_position || board[x-1][y-1] == mine_position || check_move_legality_A_to_B(x, y, target_flag_x, target_flag_y)));
        board [x-1][y-1] = mine_position;
        current_mine_counter++;
    }
}


//------------------------------------------------------------------------------------------
//Class Figure function implementations
//------------------------------------------------------------------------------------------
void Figure::update_enemy_position(int next_x, int next_y){
    this->enemy_coordinate_x = next_x;
    this->enemy_coordinate_y = next_y;
}

//------------------------------------------------------------------------------------------
//Class Game function implementations
//------------------------------------------------------------------------------------------
//function that draws the board
void Game::draw_board(Board& b, Figure& f){
    wchar_t current_enemy; 
    b.draw_board(f);
}
//Function that sets the game mode
void Game::set_game_mode(){
    wcout << "\033[2J\033[H\n";
    wcout<<"Select game mode: \n\n\n0 - Tutorial\t 1 - Easy\t 2 - Medium\t 3 - Survival\t 4 - Multigame\n\n\n";
    do {
        cin>>game_mode;
    }
    while (game_mode<0 || game_mode>4);
    wcout<<"\n\n\n";
}
//Function that sets up the variables
void Game::setup_variables(Board& b){
    switch (game_mode){
        case 0: // TUTORIAL GAME MODE
            b.initial_mines   = 10;
            b.current_mine_counter = b.initial_mines;
            b.mine_increment = 1;
            b.remove_mines_num = 1;
            max_moves_allowed = 10;
            number_of_rounds  = 1;
            number_of_boards  = 1;
            break;
        case 1: // EASY GAME MODE
            b.initial_mines   = 12;
            b.current_mine_counter = b.initial_mines;
            b.mine_increment = 2;
            b.remove_mines_num = 2;
            max_moves_allowed = 20;
            number_of_rounds  = 3;
            number_of_boards  = 1;
            break;
        case 2: // MEDIUM GAME MODE
            b.initial_mines   = 12;
            b.current_mine_counter = b.initial_mines;
            b.mine_increment = 3;
            b.remove_mines_num = 3;
            max_moves_allowed = 50;
            number_of_rounds  = 10;
            break;
        case 3: // SURVIVAL GAME MODE
            b.initial_mines   = 5;
            b.current_mine_counter = b.initial_mines;
            b.mine_increment = 3; //per flag
            b.remove_mines_num = 5;
            max_moves_allowed = 10000;
            number_of_rounds  = 10000;
            number_of_boards  = 1;
            break;  

        case 4: // SURVIVAL GAME MODE
            b.initial_mines   = 5;
            b.current_mine_counter = b.initial_mines;
            b.mine_increment = 3; //per flag
            b.remove_mines_num = 5;
            max_moves_allowed = 10000;
            number_of_rounds  = 10000;
            number_of_boards  = 2;
            break;
    }
}
//Function that is in charge of making a move
void Game::make_move(Board& b, Figure& f){
    int next_x, next_y;
    successive_illegal_move_counter = 0;
    do{
        if (successive_illegal_move_counter == 3){
            wcout << "You entered 3 invalid inputs in a row. You lose.\n";
            finish_game(b);
        }
        
        if (game_mode < 3){
            wcout<<"\nMoves left: "<<max_moves_allowed - move_counter;
            wcout<<"\nFlags left: "<<number_of_rounds  - flag_counter<<'\n';
        }
        else 
            wcout<<"\nFlags captured: "<<flag_counter<<'\n';

        cin.clear();  // Clear the error flags caused by impropper coordinates
        cin.ignore(numeric_limits<std::streamsize>::max(), '\n'); //ignoring previous things found in cin
        
        wcout<<"Enter next valid move: ";

        cin>>b.user_input_y >> b.user_input_x; //Entering new values that are treated like strings
        next_x = letter_to_int_conversion_x(b, next_x); //Local variables have taken new coordinates
        next_y = letter_to_int_conversion_y(b, next_y);

        successive_illegal_move_counter++;
    }
    while (!(b.check_move_legality_A_to_B(b.initial_knight_x, b.initial_knight_y, next_x, next_y)) || ((b.user_input_y<'a' || b.user_input_y>'z') && (b.user_input_y<'A' || b.user_input_y>'Z')) || (b.user_input_x<'1' || b.user_input_x>'9'));


    //Update the move counter and resseting illegal move counter
    move_counter++;
    successive_illegal_move_counter = 0;

    //Function that checks the game state
    check_endgame_conditions(b, f, next_x, next_y);

}
//Function that generates initial mines on the board (must be written in Game class)
void Game::generate_initial_mines(Board& b){
    int x{0}, y{0};
    for (int i=0; i<b.initial_mines; i++){
        do{
            x = generate_random_number(BOARD_SIZE);
            y = generate_random_number(BOARD_SIZE);
        }
        while ((b.board[x-1][y-1] == b.current_position || b.board[x-1][y-1] == b.flag_position || b.board[x-1][y-1] == b.mine_position || b.check_move_legality_A_to_B(x, y, b.target_flag_x, b.target_flag_y)));

        b.board [x-1][y-1] = b.mine_position;
    }
}
//Function that checks if the game is over
void Game::check_endgame_conditions(Board& b, Figure& f, int next_x, int next_y){
    //PLAYER EXEEDED NUMBER OF MOVES
    if (move_counter == max_moves_allowed){
        //wcout<<"\nMoves left: "<<max_moves_allowed - move_counter<<'\n';
        wcout<<"Moves limit reached. You lose.\n\n\n\n\n\n";
        finish_game(b);
    }
    //PLAYER FOUND A FLAG
    if (b.board[next_x-1][next_y-1] == b.flag_position){
        remove_enemy(b, f);
        flag_counter++;
        b.update_figure_position(next_x, next_y);
        switch (game_mode){
            case 0: 
                check_mode_tutorial(b, f, next_x, next_y);
                break;
            case 1:
            case 2:
            case 3:
            case 4:
                check_mode_competitive(b, f, next_x, next_y);
                break;
            default: 
                //finish_game(b);
                break;
        }
    }
    //Case if player stepped on a mine
    else if (b.board[next_x-1][next_y-1] == b.mine_position){
        switch  (game_mode){
            case 0:
            case 1:
            case 2:
            case 3:
                b.update_figure_position(next_x, next_y);
                b.draw_board(f);
                wcout<<"You stepped on a mine. Game over.\n\n\n\n\n\n";
                finish_game(b);
            break;
        
            case 4: // Multigame
                b.update_figure_position(next_x, next_y);
                finish_game(b);
                break;
        }
        
    }
    
    //IMPOSSIBLE TO REACH DESTINATION
    else if (!b.move_not_blocked(b.target_flag_x-1, b.target_flag_y-1)){
        wcout<<"Impossible to reach the flag. Game over.";
        wcout<<"\nFinal score: "<<flag_counter<<"\n\n\n";
        finish_game(b);
    } 

    //Checks if player captured the enemy figure
    if(b.board[next_x-1][next_y-1] == enemy_position){
        remove_enemy(b, f);
        flag_counter++; //So far, enemies are just additional flags
        b.update_figure_position(next_x, next_y);
        b.draw_board(f);
    }
    b.update_figure_position(next_x, next_y);

    //PLAYER TAKEN BY THE ENEMY FIGURE
    if (does_enemy_attack_player(f, b) == true){
        //IF PLAYER REACHES SQUARE ATTACKED BY ENEMY, FIRST WE NEED TO DRAW THE BOARD, AND THEN SHOW THE MOVE THE ENEMY TAKES
        if (game_mode != 4) 
            b.draw_board(f);

        //this_thread::sleep_for(chrono::seconds(1));
        this_thread::sleep_for(chrono::milliseconds(500));  // 500 milliseconds = 0.5 seconds

        wcout<<"\nYou were taken by the enemy figure. Game over.";
        remove_enemy(b, f);
        b.update_figure_position(next_x, next_y);
        b.board[next_x-1][next_y-1] = enemy_position;
        finish_game(b);
        b.draw_board(f);
    }

    //PLAYER MAKES A NORMAL MOVE
    else {
        b.update_figure_position(next_x, next_y);
        }
    }
//Function that defines behaviour of the game in Tutorial mode
void Game::check_mode_tutorial(Board& b, Figure& f, int next_x, int next_y){
        //b.update_figure_position(next_x, next_y);
        wcout << "\033[2J\033[H\n";
        draw_board(b, f);
        wcout<<"Congratulations! You found the target within "<<move_counter<<" moves.You won!\n\n\n";
        finish_game(b);
}
//Function that defines behaviour of the game in EASY mode
void Game::check_mode_competitive(Board& b, Figure& f, int next_x, int next_y){
        //flag_counter++;
        if (flag_counter == number_of_rounds){
            //b.update_figure_position(next_x, next_y);
            wcout << "\033[2J\033[H\n";
            draw_board(b, f);
            wcout<<"Congratulations! You found "<<number_of_rounds<<" flags in "<<move_counter<<" moves. You win!\n\n\n\n\n\n";
            finish_game(b);
        }
        //b.update_figure_position(next_x, next_y);
        else if (flag_counter % 3 == 0){
            generate_remove_mines(b);
        }
        else 
            b.generate_additional_mines(b.mine_increment);
        
        //LOGIC THAT ALLOWS AN ENEMY FIGURE TO BE MADE AT DIFFERENT POINTS IN TIME, WILL BE RETURNED AFTER TESTING
        /*if (flag_counter <= 25 && flag_counter % 3 == 0)
            make_enemy_figure(b, f);
        else if (flag_counter > 25 && flag_counter <= 50 && flag_counter % 2 == 0)
            make_enemy_figure(b, f);
        else if (flag_counter > 50){
            make_enemy_figure(b, f);
        }*/

        b.generate_flag();
        //TEMPORARY LOGIC FOR TESTING PURPOSES
       make_enemy_figure(b, f);
        //draw_board(b);
}
//Function that finishes the game
void Game::finish_game(Board& b){
    b.finish_game_function_called = true;
    finish_game_counter++; // global static variable updated
    //for (int i=0; i<8; i++){
        //delete[] b.board[i];
    //}
    //delete[] b.board;
    //b.board = nullptr;
    wcout<<"\nFake destructor!!!!\n";
    //write_to_file();
    //read_from_file();
    //show_scoreboard();

    //exit(0);
}
//Function that removes a certain number of mines, and regenerates them and additional ones
//Only implemented every 3rd flag
void Game::generate_remove_mines(Board& b){//Function that removes a number of mines based on game mode
    int x{}, y{};
    for (int i=0; i<b.remove_mines_num; i++){
        do{
            x = generate_random_number(BOARD_SIZE);
            y = generate_random_number(BOARD_SIZE);
        }
        while (b.board[x-1][y-1] != b.mine_position);
        //while (b.board[x-1][y-1] == b.mine_position || b.board[x-1][y-1] == b.current_position);
        b.board[x-1][y-1] = ' '; 
        b.current_mine_counter--;
    }
    int temp = b.mine_increment + b.remove_mines_num;
    if (b.current_mine_counter + temp >= b.max_mines_allowed)
        b.generate_additional_mines(b.remove_mines_num);
    else 
        b.generate_additional_mines(temp);
}

//Function that draws multiple boards
void Game::draw_multiboard(Board& b1, Board& b2, Figure& f1, Figure& f2){
    wcout << "\033[2J\033[H\n";
    for (int i=0; i<number_of_boards; i++){
        wcout<<" ___ ___ ___ ___ ___ ___ ___ ___\t"; //upper most lines of the board 
    }
    int count_rows{8};
    //for (int k=0; k<number_of_boards; k++){
        for (int i=0; i<8; i++){
        wcout<<"\n| ";
        for (int k=0; k<number_of_boards; k++){
            Board& current_board = (k==0) ? b1:b2;
            Figure& current_figure = (k==0) ? f1:f2;
            for (int j=0; j<8; j++){
                //Declaring a reference to an object of class Board
                
                if (current_board.board[i][j] == current_position){
                    wcout << L'\u265E'; //♞
                    //wcout<<L"\U0001F4A9"; //💩
                    wcout<<" | ";
                }
                else if(current_board.board[i][j] == flag_position){
                    wcout<<L"\U0001F6A9"; //🚩
                    //wcout<<L"\U0001F6BD"; //🚽
                    //wcout << L'\u274C'; //❌
                    wcout<<"| ";
                }

                else if(current_board.board[i][j] == mine_position){
                    wcout<<L'\U0001F4A3'; //💣
                    //wcout << L'\u1F4A'; //alt bomb
                    wcout<<"| ";
                }
                //New case where a square could be an enemy
                else if (current_board.board[i][j] == enemy_position){
                switch (current_figure.current_enemy){
                    case KNIGHT:
                        wcout<<L'\u2658'; //♘
                        wcout<<" | ";
                        break;
                    case ROOK:
                        wcout<<L'\u2656'; //♖
                        wcout<<" | ";
                        break;
                    case BISHOP:
                        wcout<<L'\u2657'; //♗
                        wcout<<" | ";
                        break;
                    case QUEEN:
                        wcout<<L'\u2655'; //♕
                        wcout<<" | ";
                        break;
                    case KING:
                        wcout<<L'\u2654'; //♔
                        wcout<<" | ";
                        break;
                }
            }
                else{
                    //wcout<<board[i][j]<< "  | ";
                    wcout<<L'\u200B';
                    wcout<<"  | ";
                }
            }
            if (k<number_of_boards-1)
                wcout<<"\t| ";
        }
            
        wcout<<"  "<<count_rows; //Number at the end of each line
        count_rows --;
        wcout<<'\n';
        for (int k=0; k<number_of_boards; k++){
            wcout<<"|___|___|___|___|___|___|___|___|\t";
        }
        //wcout<<'\n';
    }
    wcout<<'\n';
    for (int k=0; k<number_of_boards; k++)
        wcout << "  A   B   C   D   E   F   G   H\t\t";
    //}
    
}
//Function that makes a random enemy figure
void Game::make_enemy_figure(Board& b, Figure& f){
    int randomized_enemy_figure = generate_random_number(5); //for the purpose of randomizing which figure will be created
    switch(randomized_enemy_figure){
        case 1:
            f.current_enemy = KNIGHT;
            break;
        case 2:
            f.current_enemy = ROOK;
            break;
        case 3: 
            f.current_enemy = BISHOP;
            break;
        case 4:
            f.current_enemy = QUEEN;
            break;
        case 5: 
            f.current_enemy = KING;
            break;
    }
    int x, y;
    do{
        x = generate_random_number(BOARD_SIZE);
        y = generate_random_number(BOARD_SIZE);
        f.enemy_coordinate_x = x;
        f.enemy_coordinate_y = y;
    }
    while (b.board[f.enemy_coordinate_x-1][f.enemy_coordinate_y-1] == current_position || b.board[f.enemy_coordinate_x-1][f.enemy_coordinate_y-1] == mine_position || b.board[f.enemy_coordinate_x-1][f.enemy_coordinate_y-1] == flag_position || b.check_move_legality_A_to_B(b.initial_knight_x, b.initial_knight_y, f.enemy_coordinate_x, f.enemy_coordinate_y) || does_enemy_attack_player(f, b) == true);
    b.board[x-1][y-1] = enemy_position;
}

//Function that removes an enemy
void Game::remove_enemy(Board& b, Figure& f){
    //b.board[f.enemy_coordinate_x-1][f.enemy_coordinate_y-1] = ' ';
    f.enemy_coordinate_x = -1;
    f.enemy_coordinate_y = -1;
    for (int i=0; i<BOARD_SIZE; i++){
        for (int j=0; j<BOARD_SIZE; j++){
            if (b.board[i][j] == enemy_position)
                b.board[i][j] = ' ';
        }
    }

}
//Function that checks wether the player is being attacked by an enemy figure
bool Game::does_enemy_attack_player(Figure& f, Board& b){
    if (b.initial_knight_x == f.enemy_coordinate_x && b.initial_knight_y == f.enemy_coordinate_y)
        return false;
    if (f.enemy_coordinate_x == -1 && f.enemy_coordinate_y == -1) {
    return false; // No enemy present
}
    switch (f.current_enemy){

        case KNIGHT:
            if (b.check_move_legality_A_to_B(b.initial_knight_x, b.initial_knight_y, f.enemy_coordinate_x, f.enemy_coordinate_y))
                return true;
        break;

        case ROOK:
            if (b.initial_knight_x == f.enemy_coordinate_x || b.initial_knight_y == f.enemy_coordinate_y)
                return true;
            break;

        case BISHOP:
            if (b.initial_knight_x - b.initial_knight_y == f.enemy_coordinate_x - f.enemy_coordinate_y || 
                b.initial_knight_x + b.initial_knight_y == f.enemy_coordinate_x + f.enemy_coordinate_y)
                return true;
            break;
        
        case QUEEN: //combines logic for ROOK AND BISHOP
            if (b.initial_knight_x == f.enemy_coordinate_x || 
                b.initial_knight_y == f.enemy_coordinate_y || 
                b.initial_knight_x - b.initial_knight_y == f.enemy_coordinate_x - f.enemy_coordinate_y || 
                b.initial_knight_x + b.initial_knight_y == f.enemy_coordinate_x + f.enemy_coordinate_y)
                return true;
        break;
        
        case KING:
            if (abs(b.initial_knight_x - f.enemy_coordinate_x) <= 1 && 
                abs(b.initial_knight_y - f.enemy_coordinate_y) <= 1)
                return true;
            break;
        break;
        default: 
            return false;
        break;
    }
    return false;
}


//------------------------------------------------------------------------------------------
//Generic functions implementation
//------------------------------------------------------------------------------------------
// Function to generate a random number between 1 and 8
int generate_random_number(int x) {
    //Seeding random number generator with the current time
    //srand(static_cast<unsigned>(time(0)));
    return rand() % x + 1;
}
//Function that converts user input coordinate letter into a number that board can recognize
int letter_to_int_conversion_y(const Board& b, int next_y){
    int actual_coordinate_y;
    switch(b.user_input_y){
        case 'A':
        case 'a':
            actual_coordinate_y = 1;
            break;
        case 'B':
        case 'b':
            actual_coordinate_y = 2;
            break;
        case 'C':
        case 'c':
            actual_coordinate_y = 3;
            break;
        case 'D':
        case 'd':
            actual_coordinate_y = 4;
            break;
        case 'E':
        case 'e':
            actual_coordinate_y = 5; 
            break;
        case 'F':
        case 'f':
            actual_coordinate_y = 6;
            break;
        case 'G':
        case 'g':
            actual_coordinate_y = 7;
            break;
        case 'H':
        case 'h':
            actual_coordinate_y = 8;
            break;
        default:
            actual_coordinate_y = 0;
            break;
    }
    return actual_coordinate_y;
}
//Function that converts user input coordinate letter into a number that board can recognize
int letter_to_int_conversion_x(const Board& b, int next_x){
    int actual_coordinate_x;
    switch (b.user_input_x){
        case '1':
            actual_coordinate_x = 8;
            break;
        case '2':
            actual_coordinate_x = 7;
            break;
        case '3':
            actual_coordinate_x = 6;
            break;
        case '4':
            actual_coordinate_x = 5;
            break;
        case '5':
            actual_coordinate_x = 4;
            break;
        case '6':
            actual_coordinate_x = 3;
            break;
        case '7':
            actual_coordinate_x = 2;
            break;
        case '8':
            actual_coordinate_x = 1;
            break;
        default:
            actual_coordinate_x = 0;
            break;
    }
    return actual_coordinate_x;
}