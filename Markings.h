#pragma once

#include "Constants.h"


using Graph_lib::Circle;
using Graph_lib::Window;

class Markings
{
    
    shared_ptr<Circle> C1;
    shared_ptr<Circle> C2;

    //if a cell is marked white or red.
    bool isMarkedW;
    bool isMarkedEnemy;
    bool isMarkedChess;


    public:

        Markings(Point p1, int rad1, Point p2, int rad2, Color cellColor):
        C1{std::make_shared<Circle>(p1,rad1)}, C2{std::make_shared<Circle>(p2,rad2)}, isMarkedW{false}, isMarkedEnemy{false}, isMarkedChess{false}
        {
            C1->set_color(border_hide);
            C2->set_color(border_hide);

            C2->set_fill_color(cellColor);

        }
        void attach_to(Window& win){
            win.attach(*C1);
            win.attach(*C2);
        }

        void draw() {
            C1->draw();
            C2->draw();
        }

        void show(){
            if(isMarkedW){
                C1->set_fill_color(markedWhiteCol);
            } else if(isMarkedEnemy){
                C1->set_fill_color(markedEnemyCol);
            } else if(isMarkedChess){
                C1->set_fill_color(KingInChessColor);
            } else{
                C1->set_fill_color(C2->color());
            }
            draw();
        }
        void setWhite() {
            isMarkedW = true;
            isMarkedEnemy = false;
            isMarkedChess = false; 
        }
        void setEnemy() { 
            isMarkedW = false;
            isMarkedEnemy = true;
            isMarkedChess = false; 
        }
        void setChess() { 
            isMarkedW = false;
            isMarkedEnemy = false;
            isMarkedChess = true; 
        }
        void removeMark()  {
            isMarkedW = false;
            isMarkedEnemy = false;
            isMarkedChess = false; 
        }

};
