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
        int initial_mines, max_mines_allowed{35}, mine_increment, current_mine_counter, remove_mines_num;
        int initial_knight_x, initial_knight_y;
        int target_flag_x, target_flag_y;
        char current_position = 'H', flag_position = 'X', mine_position = '*';
    public:
        char user_input_x;
        char user_input_y; //Used as parameters for converting numbers into actual
                                 //coordinates
        void draw_board();
        void update_figure_position(int next_x, int next_y);
        void generate_additional_mines(int& mine_increment); //still not implemented
        void remove_mines(); //still not implemented
        void generate_flag();
        bool check_move_legality_A_to_B(int initial_knight_x, int initial_knight_y, int target_flag_x, int target_flag_y); //When figures other than knight are implemented, type of figure should be a function parameter
        Board();
        ~Board();
        bool move_not_blocked(int target_flag_x, int target_flag_y);
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
        void add_figure(Figure& f); //still not implemented
        void check_game_state(Board& b, int next_x, int next_y); // still not implemented
        void setup_variables(Board& b); //based on game mode, sets initial number of mines, mines increment, and mine generation/removal
        void enter_name(); // still not implemented
        void make_move(Board& b); //calls check_board_state from Board class object
        void show_scoreboard(); //still not implemented
        void set_game_mode(); //ex: tutorial, easy, survival, custom
                             //should take initial_mines from the board object
        void generate_initial_mines(Board& b);
        void check_mode_tutorial(Board& b, int next_x, int next_y);
        void check_mode_competitive(Board& b, int next_x, int next_y);
        void finish_game(Board& b);
};  

//------------------------------
//Initializing generic functions
//------------------------------
int generate_random_number_1_8();
void read_from_file(); //still not implemented
void write_to_file(); //still not implemented

#endif