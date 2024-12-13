#include"knight.h"

//------------------------------------
//Class Board function implementations
//------------------------------------

//Board class constructor for initializing a board with blank elements
Board::Board(){
    //Initialize a dynamically allocated board as a matrix of elements
    board = new char*[8];

    for (int i=0; i<8; i++){
        board[i] = new char[8];
    }

    //Set initial knight and flag positions
    initial_knight_x = generate_random_number_1_8();
    initial_knight_y = generate_random_number_1_8();
    do{
        target_flag_x = generate_random_number_1_8();
        target_flag_y = generate_random_number_1_8();
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
}

//draw_board function
void Board::draw_board(){
    wcout << "\033[2J\033[H\n";
    wcout<<" ___ ___ ___ ___ ___ ___ ___ ___\n";
    int count_rows{8};
    for (int i=0; i<8; i++){
        wcout<<"| ";
        for (int j=0; j<8; j++){
            if (board[i][j] == 'H'){
                wcout << L'\u265E'; //♞
                //wcout<<L"\U0001F4A9"; //💩
                wcout<<" | ";
            }
            else if(board[i][j] == 'X'){
                wcout<<L"\U0001F6A9"; //🚩
                //wcout<<L"\U0001F6BD"; //🚽
                //wcout << L'\u274C'; //❌
                wcout<<"| ";
            }

            else if(board[i][j] == '*'){
                wcout<<L'\U0001F4A3'; //💣
                //wcout << L'\u1F4A'; //alt bomb
                wcout<<"| ";
            }
            else{
                //wcout<<board[i][j]<< "  | ";
                wcout<<L'\u200B';
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
//Function that removes a number of mines based on game mode
void Board::remove_mines(/*int& remove_mines_num, char& mine_position*/){
    int x{}, y{};
    for (int i=0; i<remove_mines_num; i++){
        do{
            x = generate_random_number_1_8();
            y = generate_random_number_1_8();
        }
        while (board[x-1][y-1] == mine_position);
        board[x-1][y-1] = ' '; 
    }
}
//Function that update figure position after a successfull move
void Board::update_figure_position(int next_x, int next_y){
    board[initial_knight_x-1][initial_knight_y-1] = ' ';
    initial_knight_x = next_x;
    initial_knight_y = next_y;
    board[next_x-1][next_y-1] = current_position;
}


//-------------------------------------
//Class Figure function implementations
//-------------------------------------


//-----------------------------------
//Class Game function implementations
//-----------------------------------
//function that draws the board
void Game::draw_board(Board& b){
    b.draw_board();
}
//Function that sets the game mode
void Game::set_game_mode(){
    wcout << "\033[2J\033[H\n";
    wcout<<"Select game mode: \n\n\n0 - Tutorial\t 1 - Easy\t 2 - Medium\t 3 - Survival\n\n\n";
    do {
        cin>>game_mode;
    }
    while (game_mode<0 || game_mode>3);
    wcout<<"\n\n\n";
}
//Function that sets up the variables
void Game::setup_variables(/*int& game_mode, */Board& b){
    switch (game_mode){
        case 0: // TUTORIAL GAME MODE
            b.initial_mines   = 5;
            //b.mine_increment_per_move = 1;
            b.mine_increment_per_flag = 1;
            b.remove_mines_num = 1;
            max_moves_allowed = 1000;
            number_of_rounds  = 1;
            break;
        case 1: // EASY GAME MODE
            b.initial_mines   = 8;
            //b.mine_increment_per_move = 2;
            b.mine_increment_per_flag = 2;
            b.remove_mines_num = 2;
            max_moves_allowed = 1000;
            number_of_rounds  = 3;
            break;
        case 2: // MEDIUM GAME MODE
            b.initial_mines   = 12;
            //b.mine_increment_per_move = 2;
            b.mine_increment_per_flag = 3;
            b.remove_mines_num = 3;
            max_moves_allowed = 1000;
            number_of_rounds  = 10;
            break;
        case 3: // SURVIVAL GAME MODE
            b.initial_mines   = 5;
            //b.mine_increment_per_move = 1;
            b.mine_increment_per_flag = 3;
            b.remove_mines_num = 5;
            max_moves_allowed = 10000;
            number_of_rounds  = 100;
            break;  
    }
}
//Function that is in charge of making a move
void Game::make_move(Board& b){
    int next_x, next_y;
    do{
        //successive_illegal_move_counter++;
        cin.clear();  // Clear the error flags caused by impropper coordinates
        cin.ignore(numeric_limits<std::streamsize>::max(), '\n'); //ignoring previous things found in cin
        wcout<<"Enter next valid move: ";
        cin>>b.user_input_y >> b.user_input_x; //Entering new values that are treated like strings

        successive_illegal_move_counter++; 

        next_x = letter_to_int_conversion_x(b, next_x); //Local variables have taken new coordinates
        next_y = letter_to_int_conversion_y(b, next_y);
    }
    while (!(b.check_move_legality_A_to_B(b.initial_knight_x, b.initial_knight_y, next_x, next_y)) || ((b.user_input_y<'a' || b.user_input_y>'z') && (b.user_input_y<'A' || b.user_input_y>'Z')) || (b.user_input_x<'1' || b.user_input_x>'9'));

    //Resseting invalid move counter
    successive_illegal_move_counter = 0;

    //Update knight coordinates;
    //b.board[b.initial_knight_x-1][b.initial_knight_y-1] = ' ';
    b.update_figure_position(next_x, next_y);
}

//--------------------------------
//Generic function implementations
//--------------------------------
// Function to generate a random number between 1 and 8
int generate_random_number_1_8() {
    //Seeding random number generator with the current time
    srand(static_cast<unsigned>(time(0)));
    return rand() % 8 + 1;
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