#include "graphics.hpp"
#include <cstdlib>
#include <time.h>
#include <vector>
#include <fstream>

using namespace genv;
using namespace std;

struct kocka
{
    int r;
    int g;
    int b;
    kocka(int r, int g, int b)
    {
        this->r=r;
        this->g=g;
        this->b=b;
    }
};

int main()
{
    int w;
    int h;
    int r;
    int g;
    int b;
    ifstream be;
    vector<kocka> kockak;
    be.open("a.kep");
    if(be.is_open())
    {
        be >> w;
        be >> h;
        while(!be.eof())
        {
            be >> r >> g >> b;
            kocka k = kocka(r,g,b);
            kockak.push_back(k);
        }
        gout.open(w, h);
    }

    event ev;
    while(gin >> ev)
    {
        if(ev.type == ev_mouse && ev.button==0)
        {
            //background
            gout << move_to(0,0) << color(0,0,0) << box(w,h);
            //kép
            int n = 0;
            for(int i = 1; i <= h; i++)
            {
                for(int j = 1; j <= w; j++)
                {
                    gout << move_to(j+ev.pos_x-w/2,i+ev.pos_y-h/2);
                    gout << color(kockak[n].r,kockak[n].g,kockak[n].b) << dot;
                    n++;
                }
            }
            gout << refresh;
        }
    }
    return 0;
}
