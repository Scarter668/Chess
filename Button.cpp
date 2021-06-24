#include "Button.h"


OwnButton::OwnButton(Point pos , int w, int h, string name, ButtonFunctions func)
:name{name}, box{pos, w, h }, text{ {pos.x + inButtonTextOffset_x, pos.y + inButtonTextOffset_y} , name},
shown{false}, function{func}, position{pos}
{   
    box.set_color(buttonColorBorder);
    box.set_fill_color(buttonColor);

    text.set_font_size(inButtonTextFont);
    hide();
}


void OwnButton::attach_to(Window& win){

    win.attach(box);
    win.attach(text);
}

void OwnButton::drawIfShown(){
    if(shown){
        box.set_color(buttonColorBorder);
        box.set_fill_color(buttonColor);
        box.move(position.x - box.point(0).x, position.y - box.point(0).y);
        box.draw();
        text.set_label(name);
        text.draw();
        
    } else{
        box.set_color(backgroundColor);
        box.set_fill_color(backgroundColor);
        text.set_label("");
        box.draw();
        
        box.move(windowWidth-position.x, windowHeight-position.y);
        box.draw();
    }
}

void OwnButton::show(){
    shown = true;
    drawIfShown();
}

void OwnButton::hide(){
    shown = false;
    drawIfShown();
}

bool OwnButton::isShown() const{
    return shown;
}

int OwnButton::widht() const{
    return box.width();
}
int OwnButton::hight() const{
    return box.height();
}
Point OwnButton::pos() const{
    return position;
}

ButtonFunctions OwnButton::getfunction() const{
    return function;
}


void OwnButton::move(int dx, int dy){
    box.move(dx, dy);
    text.move(dx, dy);
    position.x += dx;
    position.y += dy;

}


void OwnButton::setName(string s){
    name = s;
}

