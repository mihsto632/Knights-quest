//-------------------------------------------------------------
// KNIGHT.H FILE FOR INITIALIZING CLASSES AND GENERIC FUNCTIONS
//-------------------------------------------------------------

#ifndef KNIGHT_H
#define KNIGHT_H

#include<iostream>
#include<cstring>
//Libraries that allow the use of unicode
#include<locale>
#include<codecvt>
////Libraries that allow exception handling methods outOfRangeExcetion and invalid_argumet
#include<stdexcept>
#include<limits>

using namespace std;

//----------------------------
//Initializing the board class
//----------------------------
class Board{
    private:
        char** board; //Pointer to a pointer for the purpose of dynamic allocation 
        int initial_mines, max_mines_allowed{35}, mine_increment_per_move, mine_increment_per_flag, current_mine_counter, remove_mines_num;
        int initial_knight_x, initial_knight_y;
        int target_flag_x, target_flag_y;
        char current_position = 'H', flag_position = 'X', mine_position = '*';
    public:
        char user_input_x;
        char user_input_y; //Used as parameters for converting numbers into actual
                                 //coordinates
        void draw_board();
        void set_initial_knight_flag_pos();
        void update_figure_position(int next_x, int next_y);
        void generate_initial_mines();
        void generate_additional_mines();
        void remove_mines(/*int& remove_mines_num, char& mine_position*/);
        void generate_flag();
        bool check_move_legality_A_to_B(int initial_knight_x, int initial_knight_y, int target_flag_x, int target_flag_y); //When figures other than knight are implemented, type of figure should be a function parameter
        Board();
        ~Board();
        friend class Game;
        friend int letter_to_int_conversion_y(const Board& b, int next_y);
        friend int letter_to_int_conversion_x(const Board& b, int next_x);
};

//-----------------------------
//Initializing the figure class
//-----------------------------
class Figure{
    private:
    public:
        bool check_player_input();
        friend class Game;
};

//---------------------------
//Initializing the Game class
//---------------------------
class Game{
    private:
        const char* filename;
        int flag_counter{0};
        int move_counter{0};
        int max_moves_allowed;
        int successive_illegal_move_counter{0};
        int number_of_rounds;
    public:
        int game_mode{0}; //default game mode set to 0, which is Tutorial mode
        void draw_board(Board& b);
        void add_figure(Figure& f); //adds an object of class figure
        bool check_game_state(); //if game is over, returns true
        void setup_variables(/*int& game_mode, */Board& b); //based on game mode, sets initial number of mines, mines increment, and mine generation/removal
        void enter_name();
        void make_move(Board& b); //calls check_board_state from Board class object
        void show_scoreboard(); //initializes the filename based on game mode
                                //performs logic based on scoreboard files
        void set_game_mode(); //ex: tutorial, easy, survival, custom
                             //should take initial_mines from the board object
};

//------------------------------
//Initializing generic functions
//------------------------------
int generate_random_number_1_8();
void read_from_file();
void write_to_file();

#endif