#pragma once
#include "Graph.h"
#include <string>


using Graph_lib::Color;
using Graph_lib::Point;
using std::string;




//------------------------ CELL ------------------------------------------
//Constant offset inside each cell
constexpr int inCellOffset = 14;
constexpr int distMarkingBorderInt = 1;



const Color markedWhiteCol = Color::white;
const Color markedEnemyCol = Color::red;


// Colors to either show or hide a Cell border.
// Same color ground, but different visibility.
const Color teamWborder_show = Color{Color::green, Color::visible};
const Color teamBborder_show = Color{Color::red, Color::visible};

const Color border_hide = Color{Color::black, Color::invisible};


//Color when king in chess
const Color KingInChessColor = Color::magenta; 

//Set the color for when pawn should be promoted
const Color promotionColor = Color::green; 


//------------------------ CHESSBOARD ------------------------------------------
//Size of window
constexpr int windowWidth = 1400;
constexpr int windowHeight = 800;


//Color of background
const Fl_Color backgroundColor = FL_GRAY;

// How wide and tall are the cells?
constexpr int cell_size = 90;

// Amount of cell in width and lenght of board
constexpr int cell_amount = 8;

// offsett of board in x and y-axis
constexpr int x_offsett = 50;
constexpr int y_offsett = 40;




//Distance of textobject from board
constexpr int distanceFromCellLarge = 25;
constexpr int distanceFromCellSmall = 15;


// To adjust for uncentered letters/numbers
constexpr int adjustOffsett = 5;


//Position of numbers on left and right of board
const int xPosLeft = x_offsett - distanceFromCellLarge;
const int xPosRight = x_offsett + cell_size*cell_amount + distanceFromCellSmall;

//Position of numbers on top and bottom of board
const int yPosTop = y_offsett - distanceFromCellSmall;
const int yPosBottom = y_offsett + cell_size*cell_amount + distanceFromCellLarge;

//Font size of text ( letters/ numbers)
constexpr int fontSize = 25;


// arrays for each textobject indexing the board
const std::array<string, 8> letters{"a", "b", "c" , "d", "e", "f", "g", "h"};
const std::array<string, 8> numbers{"8", "7", "6" , "5", "4", "3", "2", "1"};




//different colors for each cell
const Color brown = Color{static_cast<int>(fl_rgb_color(95,72,0))};
const Color grey = Color{Color::light_gray}; 



//Points where the dead pieces should be moved
constexpr int pieceSeperation = 60;
const int x1 = xPosRight - distanceFromCellSmall + pieceSeperation;
const int x2 = x1 + 2*pieceSeperation;
const int x3 = x2 + 2*pieceSeperation;

const int y1Up =  y_offsett + inCellOffset;
const int y2Up = y1Up + cell_size;

const int y1Down = y2Up + 5*cell_size;
const int y2Down = y1Down + cell_size;

constexpr int killedPieceSize = 6;
const std::array<Point, killedPieceSize> killedPiecesWhite{ Point{x1, y1Up}, Point{x1, y2Up}, Point{x2, y1Up}, Point{x2, y2Up}, Point{x3,y1Up} , Point{x3, y2Up} };
const std::array<Point, killedPieceSize> killedPiecesBlack{ Point{x1,y2Down}, Point{x1,y1Down} ,Point{x2,y2Down} ,Point{x2,y1Down} ,  Point{x3,y2Down} ,Point{x3,y1Down} };

// Seperation (x) between killed piece and letter X
constexpr int xSeperation = 12;
// Seperation (y) between killed piece top left y and botom letter X
constexpr int ySeperation = 40;
constexpr int fontSizeX = 30;

//Cellindex for where castling is possible in upper and lower row
constexpr int LUCastlingIndx = 2;
constexpr int RUCastlingIndx = 6;
const int LDCastlingIndx = LUCastlingIndx + 7*cell_amount;
const int RDCastlingIndx = RUCastlingIndx + 7*cell_amount;

//all indexes in a vector
const vector<int> CastlingIndexVec{{ LUCastlingIndx, RUCastlingIndx, LDCastlingIndx, RDCastlingIndx }};

//names for true and false
constexpr bool display_results = true;
constexpr bool disregard_results = false;


//deals with waitingtime for mainmenu to show up
constexpr int gameEndingtime = 5;
constexpr int second = 1'000'000;
//Position of text and font size
const Point gameEndingPosition{830, 500};
constexpr int gameEndingFontSize = 30;
//The text that it should display
const string returningText = "Returning to main menu in: "; 


//Keeps track of the games status
enum Status{play, whiteWonCM, blackWonCM, whiteWon, blackWon,
 drawStalemate, drawAgreed, drawDeadPosition, giveUpWhite, giveUpBlack,
 gameEnded
 };


//text for displaying gamestatus when won/lost
const Point gameStatusTextPoint{100, 400};
constexpr int gameStatusFontSize = 100;
const Color gameStatusColor = Color::blue; 
const map<Status , string> statusToString = {
    {Status::whiteWonCM, "White Won - Check Mate"},
    {Status::blackWonCM, "Black Won - Check Mate"},
    {Status::whiteWon, "White Won"},
    {Status::blackWon, "Black Won"},
    {Status::drawStalemate, "Draw - Stalemate"},
    {Status::drawDeadPosition, "Draw - Dead Position" },
    {Status::drawAgreed, "Draw - By agreement" },
    {Status::giveUpBlack, "White Won - Black gave up"},
    {Status::giveUpWhite, "Black Won - White gave up"},
    {Status::play, ""},
    {Status::gameEnded, ""}
    };


    //----------------------------- Buttons and widgets -----------------------------------------------


constexpr int buttonWidth{100};
constexpr int buttonHeight{40};
const Color buttonColor = Color::mid_gray;
const Color buttonColorBorder = Color::black;

constexpr int inButtonTextOffset_x{15};
constexpr int inButtonTextOffset_y{25};
constexpr int inButtonTextFont{20};

const Point optionsButtonPoint{windowWidth - 3*buttonWidth/2, windowHeight/2 + 50};
constexpr int menuSeperation{10};
const string optionsButtonName{"Options"}; //Delete

const Point optionsMenuPoint = optionsButtonPoint;
const string optionsMenuName{"Menu"};

const string optionsMenuDrawName{"Draw"};

const string optionsMenuGiveUpName{"Give up"};

const string optionsMenuCancelName{"Cancel"};


const int buttonWidthreturn{ buttonWidth + 120 };
const Point goToMainMenubtnPoint{windowWidth-buttonWidthreturn-20 , buttonHeight + 50};
const string goToMainMenubtnName{"Return to main menu"};

constexpr int MainMenuWidht{800};
constexpr int MainMenuHeiht{700};
constexpr Point MainMenuPoint{250,100};
const Color MainMenuBackgroundColor = Color::dark_gray;

const string MainMenuTitle{"Main menu"};
const Point MainMenuTitlePoint{MainMenuWidht/40,MainMenuHeiht/5};
constexpr int MainMenuTitleFontsize{150};

const Point MainMenuOwnMenuPoint{2*MainMenuWidht/5,MainMenuHeiht/3};
constexpr int MainMenuButtonsWidht{150};
constexpr int MainMenuButtonsHeight{40};
constexpr int MainMenuButtonsSeperation{50};

const string MainMenuNewGameName{"- New Game -"};

const string MainMenuQuitName{"- Quit Game -"};

const string MainMenuResumeGameName{"Resume game"};


const Point MainMenuToogleAIPoint{2*MainMenuWidht/5,MainMenuHeiht - 3*buttonHeight};
const string MainMenuToogleAIONName{"Turn AI ON"};
const string MainMenuToogleAIOFFName{"Turn AI OFF"};

enum class ButtonFunctions{
    showOptionsMenu,
    giveUp,
    agreedDraw,
    returnToMenu,
    goToMainMenu,

    newGame,
    quit,
    resumeGame,
    toogleAI,
    none
};



constexpr bool turnAIon{false};
const chrono::milliseconds AIwait{1 * 1'000};
const chrono::milliseconds AIwaitPromotion{500};
    //----------------------------- Buttons and widgets - End -----------------------------------------------


//------------------------ PIECE ------------------------------------------

const string BBishopfileNamePNG = "PNG\\BlackBishop.png";
const string BKingfileNamePNG = "PNG\\BlackKing.png";
const string BKnightfileNamePNG = "PNG\\BlackKnight.png";
const string BPawnfileNamePNG = "PNG\\BlackPawn.png";
const string BQueenfileNamePNG = "PNG\\BlackQueen.png";
const string BRookfileNamePNG = "PNG\\BlackRook.png";

const string WBishopfileNamePNG = "PNG\\WhiteBishop.png";
const string WKingfileNamePNG = "PNG\\WhiteKing.png";
const string WKnightfileNamePNG = "PNG\\WhiteKnight.png";
const string WPawnfileNamePNG = "PNG\\WhitePawn.png";
const string WQueenfileNamePNG = "PNG\\WhiteQueen.png";
const string WRookfileNamePNG =  "PNG\\WhiteRook.png";

const string NothingJPEG = "PiecesJPEG\\Nothing.jpg";

//different filenames for pieces
const string BBishopfileName = "";//"PiecesJPEG\\BlackBishop.jpg"; //"PiecesJPEG\\BlackBishop.jpg";
const string BKingfileName = "PiecesJPEG\\BlackKing.jpg";
const string BKnightfileName = "PiecesJPEG\\BlackKnight.jpg";
const string BPawnfileName = "PiecesJPEG\\BlackPawn.jpg";
const string BQueenfileName = "PiecesJPEG\\BlackQueen.jpg";
const string BRookfileName = "PiecesJPEG\\BlackRook.jpg";

const string WBishopfileName = "PiecesJPEG\\WhiteBishop.jpg";
const string WKingfileName = "PiecesJPEG\\WhiteKing.jpg";
const string WKnightfileName = "PiecesJPEG\\WhiteKnight.jpg";
const string WPawnfileName = "PiecesJPEG\\WhitePawn.jpg";
const string WQueenfileName = "PiecesJPEG\\WhiteQueen.jpg";
const string WRookfileName = "PiecesJPEG\\WhiteRook.jpg";

//amount of dead pieces one can choose from
constexpr int deadOptionAmount = 4;


//for configuration of startposition - names
const std::array<string, 8> blackConfig { 
    // BRookfileName,
    // BKnightfileName,
    // BBishopfileName,
    // BQueenfileName,
    // BKingfileName,
    // BBishopfileName,
    // BKnightfileName,
    // BRookfileName

    BRookfileNamePNG,
    BKnightfileNamePNG ,
    BBishopfileNamePNG,
    BQueenfileNamePNG ,
    BKingfileNamePNG ,
    BBishopfileNamePNG,
    BKnightfileNamePNG ,
    BRookfileNamePNG
    



};


//for configuration of startposition - names
const std::array<string, 8> whiteConfig { 
    // WRookfileName,
    // WKnightfileName,
    // WBishopfileName,
    // WQueenfileName,
    // WKingfileName,
    // WBishopfileName,
    // WKnightfileName,
    // WRookfileName
    WRookfileNamePNG,
    WKnightfileNamePNG ,
    WBishopfileNamePNG,
    WQueenfileNamePNG ,
    WKingfileNamePNG ,
    WBishopfileNamePNG,
    WKnightfileNamePNG ,
    WRookfileNamePNG
};







