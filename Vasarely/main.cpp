#include "graphics.hpp"
using namespace genv;


int main()
{
    gout.open(600,600);
    int mertek = 10;
    int szin = 8;
    for(int i = 0; i < 30; i++)
    {
        gout << color(i*szin,255-i*szin,0);
        gout << line_to(300,i*mertek);
        gout << move_to(300-i*mertek,300);
    }

    for(int i = 0; i < 32; i++)
    {
        gout << color(i*szin,255-i*szin,0);
        gout << line_to(300,300 + i*mertek);
        gout << move_to(i*mertek,300);
    }

    for(int i = 0; i < 31; i++)
    {
        gout << color(i*szin,255-i*szin,0);
        gout << line_to(300,600 - i * mertek);
        gout << move_to(300 + i * mertek,300);
    }

    for(int i = 0; i < 31; i++)
    {
        gout << color(i*szin,255-i*szin,0);
        gout << line_to(600 - i*mertek,300);
        gout << move_to(300,300 - i*mertek);
    }
    gout << refresh;
    event ev;
    while(gin >> ev) {
    }
    return 0;
}
