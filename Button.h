#pragma once

#include "Constants.h"


using Graph_lib::Rectangle;
using Graph_lib::Text;

#include "Window.h"
using Graph_lib::Window;


class OwnButton{

    string name;
    Rectangle box;
    Text text;
    bool shown;

    ButtonFunctions function;

    Point position;



    public:

        OwnButton(Point pos , int w, int h, string name, ButtonFunctions func );

        void attach_to(Window& win);

        void drawIfShown();

        void show();

        void hide();

        bool isShown() const; 

        int widht() const;
        int hight() const;
        Point pos() const;

        ButtonFunctions getfunction() const;

        void move(int dx, int dy);

        void setName(string s);



};