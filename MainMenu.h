#pragma once

#include "Button.h"
#include "Menu.h"



class MainMenu{

    string titleName;
    Rectangle frame;
    Text titleText;

    OwnMenu menu;

    Point position;

    bool shown;

    OwnButton resume;
    bool resumeShow;

    OwnButton toogleAI;
    bool AIon;

    public:

        MainMenu(Point pos, int seperation, int width, int height, string title);

        void attach_to(Window& win);

        void drawIfShown();

        void show();

        void hide();

        bool isShown() const;

        void addButton(string name, ButtonFunctions func);

        void add_to(vector<OwnButton *>* vecPtr);

        void toogleResume(bool t);

        void toogleAIon(bool t);

};