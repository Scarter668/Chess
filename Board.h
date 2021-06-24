#pragma once


#include "Cell.h"
#include "Constants.h"
#include "Button.h"
#include "Menu.h"
#include "MainMenu.h"

#include "GUI.h"
#include "FL/fl_ask.H"


#include <vector>
#include <array>

#include <FL/Fl_PNG_Image.H>


using std::vector;
using std::array;
using Graph_lib::Text;
using Graph_lib::Vector_ref;
using Graph_lib::Shape;
using Graph_lib::Image;







class ChessBoard : public Graph_lib::Window{
    
    public:
    
    // Grid is an alias for a 2D vector containing unnamed Cell-objects.
    using Grid = vector<vector<Cell>>;
    
    ChessBoard();
    
    //Destructor of window
     ~ChessBoard() {
            for(unsigned int i{0}; i < x_sWhite.size(); i++){
                delete x_sWhite[i];
                delete x_sBlack[i];
            }
        }
    
   

    private:
        
        Fl_PNG_Image BBBishop{"PiecesJPEG\\PNG\\BlackBishop.png"};

        //Names for the visual representation of pieces when promotion is available
        Fl_PNG_Image BQueenImage{ BQueenfileNamePNG.c_str()};
        Fl_PNG_Image BBishopImage{ BBishopfileNamePNG.c_str()};
        Fl_PNG_Image BRookImage{BRookfileNamePNG.c_str()};
        Fl_PNG_Image BKnightImage{BKnightfileNamePNG.c_str()};
        
        Fl_PNG_Image WQueenImage{ WQueenfileNamePNG.c_str()};
        Fl_PNG_Image WBishopImage{WBishopfileNamePNG.c_str()};
        Fl_PNG_Image WRookImage{WRookfileNamePNG.c_str()};
        Fl_PNG_Image WKnightImage{WKnightfileNamePNG.c_str()};
        
        //holding all the images
        std::array<Fl_PNG_Image*, 8> BlackWhiteImages = {&BQueenImage, &BRookImage, &BBishopImage, &BKnightImage, &WQueenImage, &WRookImage, &WBishopImage, &WKnightImage};
        //assigning an int value to all images so it can be compared;
        const map<Fl_PNG_Image*, int> imageToIntValue{
                {&BQueenImage, 0},
                {&BRookImage, 1},
                {&BBishopImage, 2},
                {&BKnightImage, 3},
                {&WQueenImage, 4},
                {&WRookImage, 5},
                {&WBishopImage, 6},
                {&WKnightImage,7}

        };
        

        int current_grid = 0, scratch_grid = 1, newGame_grid = 2;
        std::array<Grid, 3> grid;

        // These four member functions gives the caller a reference
        // to the current and scratch grids.
        Grid& get_current_grid();
        Grid& get_scratch_grid();
        const Grid& get_current_grid() const;
        const Grid& get_scratch_grid() const;

        //grid to store the set for the new game
        Grid& get_newGame_grid();

        //The selected piece and cell chosen with mouse
        Piece* selectedPiece; 
        Cell* selectedCell;


        // Holds all the numbers and letters displayed on board 
        Vector_ref<Text> textObjects;
        

        //Holds all the valid moves a player can hold 
        vector<Cell*> allValidMoves;

        //Holds all the cells that has been afected by promotion
        vector<Cell*> promotionCells;

        //Holds all the pieces that has been moved off the board (Dead peices)
        vector<shared_ptr<Piece>> deadPieces;


        //index of killed pieces to get their positions
        int indDeadPiecesWhite;
        int indDeadPiecesBlack;

        //The nameless x'es for dead pieces
        vector<Text*> x_sWhite;
        vector<Text*> x_sBlack;

        //rectangles acts as an eraser to remove/hide x'es (text).
        Rectangle textEraser;

        //Keeps controll of the kings, and if they are in chess
        bool whiteKingChess;
        bool blackKingChess;


        //the status of the game, if it is ongoing or not  
        Status gameStatus;
        
        //text to display the gameStatus after win or draw
        Text gameStatusText;

        //if promotion of pawn is the next move
        bool pawnPromotion;

        //check if give up button was pressed without a selected piece
        bool attemptedGiveUp;

        //If both white and black agree to draw
        bool attemptedDraw;
        bool whiteAgreeDraw;
        bool blackAgreeDraw;


        bool turnToogle;

        bool AIon;
        bool HardAI;
        
        //vector<Piece*> pieces;
        bool newGame = true;
        
// array too handle the turns
const std::array<Piece::Team, 2> teamArray{Piece::Team::white , Piece::Team::black};

const map<Piece::Team, string> teamToString{ {Piece::Team::white, "White"}, {Piece::Team::black, "Black"}  };

        //----------------------------- Buttons and widgets ----------------------------------------------------------
        

        vector<OwnButton*> allButtons;

        // button for geting the menu open
        OwnButton optionsButton;
        //OwnButton test;
        
        // Menu optionsMenu;
        OwnMenu optionsMenu;

        //The main menu
        MainMenu menu;

        OwnButton goToMainMenubtn;






        void showOptionsMenu();
        void giveUp();
        void agreedDraw();
        void returnToMenu();
      
        void startNewGame();
        void quitGame();
        void resumeGame();
        void toogleAI();


        void goToMainMenu();


        //------------------------------------------------------------------------------------------------------

        //hides the previous drawn text
        void eraseText(const std::array<Point, 6>& arr, int index);

        //change the x-Text, to whatever the input is (label)
        void toggleText(bool set, vector<Text*>* x_s, int index, string label="");
        void updateDeadPiecesText();

        //Handle inputs
        int handle(int event) override;


        // Handle the mouse-button clicks captured by handler(int).
	    int click_handler(Point pos);

        // Return a pointer to the Cell at point pos. If there's no cell at pos,
	    // return nullptr.
	    Cell* cell_at_pos(Point pos);

        // return the function that the pressed button should do if pressed
        ButtonFunctions get_ownButton_Pressed(Point pos);


        //process the result and do the function of the pressed butn
        bool dealWithPressedButn(ButtonFunctions func);


        // // Selects or unselects a piece if pressed on it
        // void selectPieceToggle(Cell* p);

        //Find corresponding cell of selected piece
        Cell* findCell(Piece* selectedPiece) ;

        //redraw the board
        void updateBoard();
        
        //reset hide all the marks
        void resetMarkers();


        // Checks that point is within board
        static inline bool isWithinChessBoard(Point p) { return (0 <= p.x && p.x < cell_amount && 0 <= p.y && p.y < cell_amount); }
        
        bool isInsidebox(Point pos, Point pBox, int w, int h) { return (pBox.x < pos.x && pos.x < pBox.x + w) && (pBox.y < pos.y && pos.y < pBox.y + h); }

        template< typename T>
        bool isInVector(const vector<T>& v, T c) const;
        

        

        //Validated each points
        vector<Cell*> processMoves(map<Piece::Direction, std::vector<Graph_lib::Point>>& moves, Grid& get_grid, bool display = display_results);

        //Check if castling is an option
        bool canCastling(Cell* selCell, Piece::Direction direction, Grid& get_grid) const;

        //Checks if a cell is empty
        bool isEmptyCellind(int cellInd, Grid& get_grid) const;
        
        //gets the piece at the cell index
        Piece* getPieceAtCellInd(int cellInd, Grid& get_grid) const;
        
        //returns the cellpointer corresponding to the cellindex
        Cell* getCellAtCellInd(int cellInd, Grid& get_grid) const;
        
        //perform the casling move
        void castilingMove(Cell* cellpTr, Cell* selectedCell, Grid& get_grid);


        //Check if the king is in check
        bool kingInCheck(Piece::Team team, Grid& get_grid);

        //Check if the king is in checkmate
        bool kingInCheckMate(Piece::Team team);
        
        //Find the posistion of the king
        Cell* findKing(Piece::Team team, Grid& get_grid) const;


        //testing if chess for all valid moves;
        void testChessForAllValidMoves(vector<Cell*>& allMoves, Piece* selPiece , Cell* selCell, bool display = true);

        //wait a certain time before returning to main menu
        void waitForReturn();

        //take care of writeing returning sequence to window
        void writeReturningString(int num);

        //write a message to the screen
        void writeMessage(string message);

        //check if selected cell is available for promotion
        void checkForPromotion( Cell* cellpTr);

        //checks for stalemate
        bool checkForStalemate();

        //check for draw by dead positions (two kings left)
        bool checkForDeadPosition();

        //displays the different pieces you can select
        void displayPromotionOption(Cell* selCell, Piece* selPiece);

        //create a new piece, given the cellpTr
        void createNewPiece(Cell* cpTr, Cell* selCell);
        
        //Compare if two images are the same
        bool isEqual(Fl_PNG_Image* lhs, Fl_PNG_Image* rhs);

        //checks if enPassent is enabled
        void checkForEnPassent(Cell* cellpTr, Piece* selPiece, Cell* selCell);

        //check is a double jumb was made
        bool checkPassentMove(int to, int from);


        //checks if a pawn is aible to do a passant in that position
        bool checkForPassentPawn(Point currP, Piece::Direction dir, Grid& get_grid);

        //reset all cells an piece's enPassent
        void resetAllEnPassant();

        //correct move the pawn back to this cell so that it can be taken.
        void correctForEnPassent(Cell* cellpTr);

        //updates the gamestatus
        void updateGameStatus();

        //make the AI move a piece
        void AImovePiece();


        //get move from a selscted cell
        std::vector<Cell *> getMoves(Cell* selCel , Grid& get_grid, bool display = true);

};
