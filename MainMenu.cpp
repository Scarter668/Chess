#include "MainMenu.h"


MainMenu::MainMenu(Point pos, int seperation, int width, int height, string title)
:titleName{title}, frame{pos, MainMenuWidht, MainMenuHeiht}, titleText{pos, MainMenuTitle},
 menu{pos,seperation, width, height }, position{pos}, shown{false},
 resume{{pos.x + frame.width() - width - 20, pos.y + frame.height()/2}, width, height, MainMenuResumeGameName, ButtonFunctions::resumeGame },
 resumeShow{false},
 toogleAI{pos, width, height, MainMenuToogleAIOFFName, ButtonFunctions::toogleAI},
 AIon{turnAIon}
{
    frame.set_fill_color(MainMenuBackgroundColor);
    titleText.set_font_size(MainMenuTitleFontsize);
    titleText.move( MainMenuTitlePoint.x, MainMenuTitlePoint.y);
    menu.move(MainMenuOwnMenuPoint.x, MainMenuOwnMenuPoint.y);
    toogleAI.move(MainMenuToogleAIPoint.x, MainMenuToogleAIPoint.y);
    toogleAIon(AIon);
}

void MainMenu::attach_to(Window& win){
    
    win.attach(frame);
    win.attach(titleText);
    menu.attach_to(win);
    toogleAI.attach_to(win);

}

void MainMenu::drawIfShown(){
    if(shown){
        frame.set_color(Color::black);
        frame.set_fill_color(MainMenuBackgroundColor);
        frame.move(position.x-frame.point(0).x, position.y-frame.point(0).y);
        frame.draw();

        titleText.set_label(MainMenuTitle);
        titleText.draw();
        menu.show();
        toogleAI.show();
        if(resumeShow){
            resume.show();
        } else{
            resume.hide();
        }


    } else{
        menu.hide();
        toogleAI.hide();
        titleText.set_label("");
        frame.set_color(border_hide);
        frame.set_fill_color(backgroundColor);
        resume.hide();

        frame.draw(); 
        frame.move(windowWidth-position.x, windowHeight-position.y);
        frame.draw();
    }
}

void MainMenu::show(){
    shown = true;
    drawIfShown();
}

void MainMenu::hide(){
    shown = false;
    drawIfShown();
}

bool MainMenu::isShown() const{
    return shown;
}

void MainMenu::addButton(string name, ButtonFunctions func){
    menu.addButton(name, func);
}

void MainMenu::add_to(vector<OwnButton *>* vecPtr){
    menu.add_to(vecPtr);
    vecPtr->push_back(&resume);
    vecPtr->push_back(&toogleAI);
}

void MainMenu::toogleResume(bool t){
    resumeShow = t;
}

void MainMenu::toogleAIon(bool t){
    AIon = t;
    if(AIon){
        toogleAI.setName(MainMenuToogleAIOFFName);
    } else{
        toogleAI.setName(MainMenuToogleAIONName);
    }
}
