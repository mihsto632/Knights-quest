//-------------------------------------------------------------
// KNIGHT.H FILE FOR INITIALIZING CLASSES AND GENERIC FUNCTIONS
//-------------------------------------------------------------
#include"enums_consts.cpp"
#ifndef KNIGHT_H
#define KNIGHT_H

#include<iostream>
#include<cstring>
#include<cstdlib> //need it for abs function
//Libraries that allow the use of unicode
#include<locale>
#include<codecvt>
////Libraries that allow exception handling methods outOfRangeExcetion and invalid_argumet
#include<stdexcept>
#include<limits>
#include <thread>   // for std::this_thread::sleep_for
#include <chrono>   // for std::chrono::seconds

using namespace std;

class Board;
class Figure;
class Game;

//----------------------------
//Initializing the board class
//----------------------------
class Board{
    private:
        char** board; //Pointer to a pointer for the purpose of dynamic allocation 
        int initial_mines, max_mines_allowed{25}, mine_increment, current_mine_counter, remove_mines_num;
        int initial_knight_x, initial_knight_y;
        int target_flag_x, target_flag_y;
        char current_position = 'H', flag_position = 'X', mine_position = '*';
    public:
        bool finish_game_function_called = false;
        char user_input_x;
        char user_input_y; //Used as parameters for converting numbers into actual
                                 //coordinates
        void draw_board(Figure& f);
        void update_figure_position(int next_x, int next_y);
        void generate_additional_mines(int& mine_increment); //still not implemented
        void remove_mines();
        void generate_flag();
        bool check_move_legality_A_to_B(int initial_knight_x, int initial_knight_y, int target_flag_x, int target_flag_y);
        Board();
        ~Board();
        bool move_not_blocked(int target_flag_x, int target_flag_y);
        friend class Game;
        friend int letter_to_int_conversion_y(const Board& b, int next_y);
        friend int letter_to_int_conversion_x(const Board& b, int next_x);
};


//-----------------------------
//Initializing the Figure class
//-----------------------------
class Figure{
    private:
        int enemy_coordinate_x;
        int enemy_coordinate_y;
    public:
        enemy current_enemy;
        void update_enemy_position(int next_x, int next_y);
        friend class Game;
        friend class Board;
};


//---------------------------
//Initializing the Game class
//---------------------------
class Game{
    private:
        //const char* filename; still not implemented
        int flag_counter{0}, move_counter{0}, successive_illegal_move_counter{0};
        int max_moves_allowed;
        int number_of_rounds;
    public:
        int number_of_boards;
        int game_mode;
        void set_game_mode(); //ex: tutorial, easy, survival, custom
                             //should take initial_mines from the board object
        void draw_board(Board& b, Figure& f);
        void make_enemy_figure(Board& b, Figure& f);
        void draw_multiboard(Board& b1, Board& b2, Figure& f1, Figure& f2);
        void check_endgame_conditions(Board& b, Figure& f, int next_x, int next_y); 
        void setup_variables(Board& b); //based on game mode, sets initial number of mines, mines increment, and mine generation/removal
        //void enter_name(); // still not implemented
        void make_move(Board& b, Figure& f); //calls check_board_state from Board class object
        //void show_scoreboard(); //still not implemented
        void generate_initial_mines(Board& b);
        void check_mode_tutorial(Board& b, Figure& f, int next_x, int next_y);
        void check_mode_competitive(Board& b, Figure& f, int next_x, int next_y);
        void finish_game(Board& b);
        void generate_remove_mines(Board& b);
        void remove_enemy(Board& b, Figure& f);
        bool does_enemy_attack_player(Figure& f, Board& b);

};  

//------------------------------
//Initializing generic functions
//------------------------------
static int finish_game_counter{0};
int generate_random_number(int x); //generates random number up the number x (usually 8)
void read_from_file(); //still not implemented
void write_to_file(); //still not implemented

#endif