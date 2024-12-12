#include"knight.cpp"

int main(){

    // Set locale to support Unicode
    locale::global(locale("en_US.UTF-8")); // Set locale for Unicode
    wcout.imbue(locale("en_US.UTF-8")); // Set wcout to use UTF-8

    //Initialize all board elements to ' '
    char board[8][8];
    for (int i=0; i<8; i++)
        for (int j=0; j<8; j++)
            board[i][j] = ' ';

    wcout<<"Hello, world!"<<endl;
    Board b;
    Game g;
    //g.draw_board(b);
    b.draw_board();

    return 0;
}