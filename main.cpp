#include"knight.cpp"

int main(){

// Set locale to support Unicode
    locale::global(locale("en_US.UTF-8")); // Set locale for Unicode
    wcout.imbue(locale("en_US.UTF-8")); // Set wcout to use UTF-8

    Game g;
    Board b;
    g.set_game_mode(); // Player chooses between tutorial, easy, hard and survival
    g.setup_variables(b);
    while (1){
        g.draw_board(b);
        g.make_move(b);
    }
    return 0;
}