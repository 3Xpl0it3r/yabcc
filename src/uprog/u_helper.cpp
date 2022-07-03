#include <u_helper.hpp>
#include <iostream>


// 格式化打印
// /*
/*
void print_aligned(Position pos, string s, int length, bool is_end)
{
    int spaces = 0;
    switch (pos) {
        case CENTER: spaces = (length - s.size()) / 2; break;
        case RIGHT:  spaces = length - s.size(); break;
        default: break;
    }

    if (spaces > 0)  cout << string(spaces, ' '); 
    cout << s;
    if (is_end) cout << endl;
}

*/
