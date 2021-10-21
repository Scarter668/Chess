#pragma once

#include "Graph.h"
#include <vector>


#include "Window.h"
using Graph_lib::Window;

#include "Piece.h"
#include "Constants.h"
#include "Markings.h"
#include <cassert>


using Graph_lib::Color;
using Graph_lib::Rectangle;
using Graph_lib::Point;
using Graph_lib::Text;
using Graph_lib::Image;




class Cell{

    //background of cell
    Color color;

    shared_ptr<Rectangle> rect;

    //To visualize that a piece can be moved to this cell
    Markings mark;
    

    shared_ptr<Piece> piece;

    //Pointer to the deadPieces-vector
    static inline vector<shared_ptr<Piece>>* deadPiecesPtr{nullptr};

    //Every cell have an unique index
    int index; 
    static inline int numberOfCells{0}; 

    // A bool to notify if a king is in chess in this cell
    bool KingInChess;
    
    //if the cell is in a promotion state
    bool promotionPawn;
    // image showing the different promotion pieces
    Fl_PNG_Image* image;

    // if the cell is in a enPassentCell
    bool enPassantCell;

    //where the piece should be
    Point piecePos;
    public:

        //set the deadPiecesPtr to the actual vector;
        void setStaticPointers(vector<shared_ptr<Piece>>* p); 

        //Backgroungcolor, position, and size of square, and piece
        Cell(Color c, Point pos, int size, shared_ptr<Piece> p = nullptr);

        // Attach the Cell's graphical representation to win
	    void attach_to(Window& win);

        //set a piece in cell
        void setPiece(shared_ptr<Piece> p);

        //Get the point of the cell
        Point getPointCell() const;

        // get the piece
        Piece* getPiece() const;
        Piece* getPiece();

        //set KingInChess varialble
        void setChessMode(bool t);

        //set promotion-bool
        void tooglePromotion(bool p);

        //get possible moves
        map<Piece::Direction, vector<Point>> getPieceMoves() const; 


        //move the piece to cell;
        void movePiece(Cell* p, int& indexB, int& indexW);
        

        //moves the piece off board
        void moveOffBoard(int& indexB, int& indexW, Piece* p);

        //return cellIndex
        int getCellIndex() const;                

        //update posistion of Piece
        void updatePice();
        //Redraw the cell with piece on top
        void updateCell();


        //Move the promotion image to this cell;
        void movePromotionImage(Fl_PNG_Image* impTr);

        //show or hide border
        void setBorder(Piece* selectedPiece);
        
        //Set the marker as follows..
        void setMarkerWhite() {mark.setWhite();}
        void setMarkerEnemy() {mark.setEnemy();}
        void setMarkerChess() {mark.setChess();}
        void resetMarker() {mark.removeMark();}
       
        //moves the piece in the scratch board;
        void movePieceScratch(Cell* c);

        
        // reset the image pointer
        void resetImagepTr();

        //return image pointer
        Fl_PNG_Image* getImage() const;

        //set and get enPassent state
        void setEnPassent(bool b);
        bool getEnPassent() const;


};

//Compare two cells - equal if same index
bool operator==(const Cell& lhs , const Cell& rhs );