#pragma once

#include "Constants.h"
#include "Button.h"

class OwnMenu{
    
    vector<OwnButton*> menuButtons;

    Point currentPoint;

    int verticalSeperation;
    int widhtButton;
    int heightButton;

    bool shown;

    public:

        OwnMenu(Point start, int seperation, int width, int height);

        void attach_to(Window& win);

        void drawIfShown();

        void show();

        void hide();

        bool isShown() const;

        void addButton(string name, ButtonFunctions func);

        void add_to(vector<OwnButton *>* vecPtr);

        void move(int dx, int dy);


};