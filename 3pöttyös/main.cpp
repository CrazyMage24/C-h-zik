#include "graphics.hpp"
#include <cstdlib>
#include <time.h>
#include <vector>
using namespace genv;
using namespace std;

void kor(int x, int y, int r)
{
    for(int i = x-r; i<x+r; i++)
    {
        for(int j = y-r; j<y+r; j++)
        {
            if((i-x)*(i-x) + (j-y)*(j-y) <= r*r)
            {
                gout << move_to(i,j) << dot;
            }
        }
    }
}

struct Particle
{
    int pos_x;
    int pos_y;
    int vel_x;
    int vel_y;
    int acc_x;
    int acc_y;

    vector<int> history_x;
    vector<int> history_y;

    Particle(int x, int y)
    {
        pos_x=x;
        pos_y=y;
        vel_x = 5;
        vel_y = 5;
        acc_x=0;
        acc_y=0;
    }

    void show()
    {
        gout << color(255,255,0);
        kor(pos_x,pos_y,5);
    }

    void showHistory()
    {
        for(int i = 0; i < history_x.size(); i++)
        {
            gout <<move_to(history_x[i],history_y[i]) << color(255,0,0) << dot;
        }
    }

    void update()
    {

        history_x.push_back(pos_x);
        history_y.push_back(pos_y);
        vel_x = (int)vel_x / 10;
        vel_y = (int)vel_y / 10;
        vel_x+=acc_x;
        vel_y+=acc_y;

        pos_x+=vel_x;
        pos_y+=vel_y;

        acc_x=0;
        acc_y=0;

    }

    void applyForce(int x, int y)
    {
        acc_x+=x;
        acc_y+=y;
    }

    void seek(Particle p)
    {
        int des_x = p.pos_x - pos_x;
        int des_y = p.pos_y - pos_y;

        int steer_x =(int) (des_x - vel_x) / 10;
        int steer_y =(int) (des_y - vel_y) / 10;



        applyForce(steer_x,steer_y);
    }
};

int main()
{
    int w = 400;
    int h = 400;
    gout.open(w,h);
    gin.timer(30);

    Particle a = Particle(200,100);
    Particle b = Particle(100,300);
    Particle c = Particle(300,300);

    event ev;
    while(gin >> ev)
    {
        if(ev.type == ev_timer)
        {
            //background
            gout << move_to(0,0) << color(0,0,0) << box(w,h);
            // kockák
            a.show();
            a.update();
            b.show();
            b.update();
            c.show();
            c.update();

            a.seek(b);
            b.seek(c);
            c.seek(a);

            a.showHistory();

            b.showHistory();

            c.showHistory();

            gout << refresh;
        }
    }
    return 0;
}
