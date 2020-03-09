#include "graphics.hpp"
#include <vector>
#include <iostream>
#include <sstream>
#include <time.h>

using namespace std;
using namespace genv;

const int width = 600;
const int height = 600;

void hatter()
{
    gout << color(0,0,0) << move_to(0,0) << box(width,height);
}

struct Cimke
{
protected:
    int x;
    int y;
    int w;
    int h;
    bool kijelolt = false;
    int num = 0;
public:
    bool valtoztam = false;
    Cimke()
    {
        w = rand()% 50 + 30;
        h = rand()% 50 + 30;
        x = (rand()%(width - w));
        y = (rand()%(height - h));
    }

    void draw()
    {
        int keret = 2;
        if(kijelolt)
        {
            keret = 4;
        }
        gout << color(0, 255, 0) << move_to(x, y) << box(w, h);
        gout << color(0, 0, 211) << move_to(x+keret, y+keret) << box(w-2*keret, h-2*keret);
        stringstream ss;
        ss << num;
        gout << color(255,255,255) << move_to(x+w/2-5,y+h/2+5) << text(ss.str());
        valtoztam = false;
    }

    void mozgat(int pos_x, int pos_y)
    {
        int x_off = w/2;
        int y_off = h/2;
        x = pos_x - x_off;
        y = pos_y - y_off;
        valtoztam = true;
    }

    void kijelol()
    {
        kijelolt = true;
        valtoztam = true;
    }
    void elenged()
    {
        kijelolt = false;
        valtoztam = true;
    }
    bool kijelolte()
    {
        return kijelolt;
    }

    bool folotte(int ex, int ey)
    {
        return (x < ex && ex < x + w &&
                y < ey && ey < y + h);
    }

    void setNum(int x)
    {
        num+=x;
        valtoztam = true;
    }
};

struct Gomb : public Cimke
{
private:
public:
    Gomb() : Cimke()
    {

    }
    void draw()
    {
        int keret = 2;
        if(kijelolt)
        {
            keret = 4;
        }
        gout << color(255, 0, 0) << move_to(x, y) << box(w, h);
        gout << color(255, 211, 0) << move_to(x+keret, y+keret) << box(w-2*keret, h-2*keret);
        stringstream ss;
        ss << num;
        gout << color(255,255,255) << move_to(x+w/2-5,y+h/2+5) << text(ss.str());
        valtoztam = false;
    }

    void setNum2(int x)
    {
        num+=10*x;
        valtoztam = true;
    }
};

int main()
{
    srand(time(0));
    gout.open(width, height);

    vector<Cimke*> cimkek;
    vector<Gomb*> gombok;
    Cimke* elkapott = nullptr;
    Gomb* kapott = nullptr;

    for(size_t i = 0; i<10; i++)
    {
        cimkek.push_back(new Cimke());
    }

    for(size_t i = 0; i<10; i++)
    {
        gombok.push_back(new Gomb());
    }

    for(Cimke* cimke: cimkek)
    {
        cimke->draw();
    }

    for(Gomb* gomb: gombok)
    {
        gomb->draw();
    }

    bool lenyomva = false;

    gout << refresh;

    event ev;
    while(gin >> ev)
    {
        if(ev.type == ev_mouse)
        {
            if(ev.button == btn_left)
            {
                lenyomva = true;
                elkapott = nullptr;
                kapott = nullptr;
                for(Cimke* cimke : cimkek)
                {
                    cimke->elenged();
                    if(cimke->folotte(ev.pos_x, ev.pos_y))
                    {
                        elkapott = cimke;
                    }
                }
                for(Gomb* gomb : gombok)
                {
                    gomb->elenged();
                    if(gomb->folotte(ev.pos_x, ev.pos_y))
                    {
                        kapott = gomb;
                    }
                }
                if (elkapott != nullptr && kapott == nullptr)
                {
                    elkapott->kijelol();
                }
                if (kapott != nullptr)
                {
                    kapott->kijelol();
                    elkapott = nullptr;
                }
            }
            else if(ev.button == -btn_left)
            {
                lenyomva = false;
            }
            else if(ev.button == 0 && lenyomva)
            {
                if (elkapott != nullptr)
                {
                    elkapott->mozgat(ev.pos_x, ev.pos_y);
                }

                if (kapott != nullptr)
                {
                    kapott->mozgat(ev.pos_x, ev.pos_y);
                }
            }

            if(ev.button ==  btn_wheelup)
            {
                if(elkapott!=nullptr)
                {
                    elkapott->setNum(1);
                }

                if(kapott!=nullptr)
                {
                    kapott->setNum2(1);
                }
            }

            if(ev.button ==  btn_wheeldown)
            {
                if(elkapott!=nullptr)
                {
                    elkapott->setNum(-1);
                }
                if(kapott!=nullptr)
                {
                    kapott->setNum2(-1);
                }
            }
            bool kell_frissiteni = false;
            if(ev.button ==  btn_right)
            {
                Cimke* c = new Cimke();
                cimkek.push_back(c);
                kell_frissiteni = true;
            }

            for (Cimke* cimke : cimkek)
            {
                if (cimke->valtoztam)
                {
                    kell_frissiteni = true;
                }
            }
            for (Gomb* gomb : gombok)
            {
                if (gomb->valtoztam)
                {
                    kell_frissiteni = true;
                }
            }
            if (kell_frissiteni)
            {
                hatter();
                for (Cimke* cimke : cimkek)
                {
                    cimke->draw();
                }
                for (Gomb* gomb : gombok)
                {
                    gomb->draw();
                }
                gout << refresh;
            }
        }
    }
    return 0;
}
