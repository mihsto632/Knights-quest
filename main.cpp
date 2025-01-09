#include"knight.cpp"

int main(){

    //Initialize random number generator
    srand(static_cast<unsigned>(time(0)));

    // Set locale to support Unicode
    //locale::global(locale("en_US.UTF-8")); // Set locale for Unicode
    setlocale(LC_ALL, "en_US.UTF-8");
    wcout.imbue(std::locale(""));
    wcout << "\033[2J\033[H\n";

    //Creating class objects
    Game g;
    g.set_game_mode(); // Player chooses between tutorial, easy, hard and survival

    Board b1, b2;
    g.setup_variables(b1);
    g.generate_initial_mines(b1);

    if (g.game_mode == 4){//Multigame
        g.setup_variables(b2);
        g.generate_initial_mines(b2);
    } 
        
    //Infinite while loop of making moves until an ending condition has been met
    while (1){
        if (g.game_mode == 4){ //GAME MODE WITH 2 BOARDS
            if (b1.finish_game_function_called == true && b2.finish_game_function_called == true){ //BOTH OBJECTS HAVE CALLED THEIR FINISH_GAME FUNCTIONS
                 goto exit_scope; //EXIT SCOPE
            }
            else if (b1.finish_game_function_called == true){//ONLY OBJECT B1 HAS CALLED ITS FINISH_GAME FUNCTION, B2 IS STILL IN PLAY
                g.draw_board(b2);
                g.make_move(b2);
            }
            else if (b2.finish_game_function_called == true){ //ONLY OBJECT B2 HAS CALLED ITS FINISH_GAME FUNCTION, B1 IS STILL IN PLAY
                g.draw_board(b1);
                g.make_move(b1);
            }
            else { //CASE WHERE WE STILL HAVE B1 AND B2 IN PLAY
                g.draw_multiboard(b1, b2);
                g.make_move(b1);
                g.make_move(b2);
            }
        }
        else { //ALL GAME MODES WITH ONLY 1 BOARD
            g.draw_board(b1);
            g.make_move(b1);
        }
    }
    exit_scope:
    wcout<<"Out of scope message";
    return 0;
}
