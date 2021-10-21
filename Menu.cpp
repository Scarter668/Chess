#include "Menu.h"


OwnMenu::OwnMenu(Point start, int seperation, int width, int height)
:currentPoint{start}, verticalSeperation{seperation}, widhtButton{width},
heightButton{height}, shown{false}
{
    hide();
}


void OwnMenu::attach_to(Window& win){
    for(auto& b : menuButtons ){
        b->attach_to(win);
    }
}

void OwnMenu::drawIfShown(){

    for(auto& b : menuButtons ){
        if(shown){
            b->show();
        } else{
            b->hide();
        }
    }   
    

}

void OwnMenu::show(){
    shown = true;
    drawIfShown();
}

void OwnMenu::hide(){
    shown = false;
    drawIfShown();
}

bool OwnMenu::isShown() const{
    return shown;
}


void OwnMenu::addButton(string name, ButtonFunctions func){
    menuButtons.push_back( new OwnButton{currentPoint, widhtButton, heightButton, name, func});
    currentPoint.y += (heightButton + verticalSeperation);
}

void OwnMenu::add_to(vector<OwnButton *>* vecPtr){
    for(auto& b : menuButtons){
        vecPtr->push_back(b);
    }
}


void OwnMenu::move(int dx, int dy){
    for(auto bptr : menuButtons){
        bptr->move(dx, dy);
    }
    currentPoint.x += dx;
    currentPoint.y += dy;

}
