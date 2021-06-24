#pragma once

#include <string>
#include <iostream>
#include <FL/Fl_PNG_Image.H>

#include "Graph.h"
#include "GUI.h"

#include "Constants.h"

using std::string;
using Graph_lib::Point;
using Graph_lib::Image;



class Piece {


    public:
        enum Team{ white, black};
        enum Race{ king, queen, rook, knight, bishop, pawn};
        //define moves in clockwise rotasjon, ex. RD = RightDown, DL = DownLeft etc.
        enum Direction{ U , UR, R, RD, D, DL , L , LU , currentP };

        Team getTeam() const;
        Race getRace() const;
        bool pieceIsAlive() const;

        //Set the piece as dead and decrement different counts
        void kill();



        //get the amount of dead pieces of each race
        virtual int getDeadPieces() const = 0;
        //return amount of live teamates
        int getDeadTeamates() const;

        //to get and set indeks of dead pieces
        virtual void setDeadInd(int ind) = 0;
        virtual int getDeadIndex() const = 0;

        //gets the different moves of each peiece
        virtual map<Direction, vector<Point>> getPossibleMoves(int cellIndex) const = 0 ;


        //Moves in all 8 different directions
        const Point moveUp(const Point& p, int step = 1) const { return { p.x , p.y - 1*step }; }
        const Point moveUpRight(const Point& p, int step = 1) const { return { p.x + 1*step , p.y-1*step }; }
        const Point moveRight(const Point& p, int step = 1) const { return { p.x + 1*step , p.y }; }
        const Point moveRightDown(const Point& p, int step = 1) const { return { p.x + 1*step , p.y + 1*step }; }
        const Point moveDown(const Point& p, int step = 1) const { return { p.x , p.y + 1*step }; }
        const Point moveDownLeft(const Point& p, int step = 1) const { return { p.x - 1*step , p.y + 1*step }; }
        const Point moveLeft(const Point& p, int step = 1) const { return { p.x - 1*step  , p.y }; }
        const Point moveLeftUp(const Point& p, int step = 1) const { return { p.x - 1*step  , p.y - 1*step }; }
        

        //Convert cellIndex to point
        static Point cellIndexToPoint(int cellIndex);

        //Check if the pice has been moved
        bool hasBeenMoved() const;

        //Set that piece has been moved
        void setMoved();

        void setEnPassent(bool enPassent);
        bool getEnPassent() const;


        static void resetPiecesCounts();

        //resets the amount of live and dead teamates
        static void resetTeamates();


        void draw();
        void move(int dx , int dy);
        Point getPos() const;
        
        virtual ~Piece() = default;
    protected:
        Piece(string imageName, Point p, Team t, Race r);
        bool isAlive;
        Team team;
        Race race;
        // decrement the different counts of subclasses and increment deadpieces
        virtual void AdjustLiveDeadPiece()=0;


        // if the piece has been moved at least once
        bool moved;
        bool enPassent;


    private:
        //Is the pawn still on board?
        static inline int liveTeamateWhite{0};
        static inline int liveTeamateBlack{0};
        
        static inline int deadTeamateWhite{0};
        static inline int deadTeamateBlack{0};
        
        Fl_PNG_Image image;

        Point pos;



};

//Compare two pieces - equal if same race and team
bool operator==(const Piece& lhs , const Piece& rhs );

class King : public Piece{

    //teamates alive
    static inline int livePieceWhite{0};
    static inline int livePieceBlack{0};

    //teamates dead
    static inline int deadPieceWhite{0};
    static inline int deadPieceBlack{0};


    //index of dead pieces that all same pieces have
    static inline int deadIndexWhite{-1};
    static inline int deadIndexBlack{-1};


    public:

        King(string imageName, Point p, Team t, Race r);
        void AdjustLiveDeadPiece() override;
        int getDeadPieces() const override;

        void setDeadInd(int ind) override;
        int getDeadIndex() const override;
        map<Direction, vector<Point>> getPossibleMoves(int cellIndex) const override;
        
        //reset the amout of live and dead subclasses
        static void resetSubs();
};
class Queen : public Piece{

    //teamates alive
    static inline int livePieceWhite{0};
    static inline int livePieceBlack{0};

    //teamates dead
    static inline int deadPieceWhite{0};
    static inline int deadPieceBlack{0};

    
    //index of dead pieces that all same pieces have
    static inline int deadIndexWhite{-1};
    static inline int deadIndexBlack{-1};


    public:
        Queen(string imageName, Point p, Team t, Race r);
        void AdjustLiveDeadPiece() override;
        int getDeadPieces() const override;

        void setDeadInd(int ind) override;
        int getDeadIndex() const override;
        map<Direction, vector<Point>> getPossibleMoves(int cellIndex) const override;
        
        //reset the amout of live and dead subclasses
        static void resetSubs();
};
class Rooks : public Piece{
     
    //teamates alive
    static inline int livePieceWhite{0};
    static inline int livePieceBlack{0};

    //teamates dead
    static inline int deadPieceWhite{0};
    static inline int deadPieceBlack{0};


    //index of dead pieces that all same pieces have
    static inline int deadIndexWhite{-1};
    static inline int deadIndexBlack{-1};



    public:
        Rooks(string imageName, Point p, Team t, Race r);
        void AdjustLiveDeadPiece() override;
        int getDeadPieces() const override;

        void setDeadInd(int ind) override;
        int getDeadIndex() const override;
        map<Direction, vector<Point>> getPossibleMoves(int cellIndex) const override;

        //reset the amout of live and dead subclasses
        static void resetSubs();

};
class Knight : public Piece{
     
    //teamates alive
    static inline int livePieceWhite{0};
    static inline int livePieceBlack{0};

    //teamates dead
    static inline int deadPieceWhite{0};
    static inline int deadPieceBlack{0};

    //index of dead pieces that all same pieces have
    static inline int deadIndexWhite{-1};
    static inline int deadIndexBlack{-1};


    public:
        Knight(string imageName, Point p, Team t, Race r);
        void AdjustLiveDeadPiece() override;
        int getDeadPieces() const override;

        void setDeadInd(int ind) override;
        int getDeadIndex() const override;
        map<Direction, vector<Point>> getPossibleMoves(int cellIndex) const override;

        //reset the amout of live and dead subclasses
        static void resetSubs();

};
class Bishop : public Piece{
     
    //teamates alive
    static inline int livePieceWhite{0};
    static inline int livePieceBlack{0};

    //teamates dead
    static inline int deadPieceWhite{0};
    static inline int deadPieceBlack{0};

    //index of dead pieces that all same pieces have
    static inline int deadIndexWhite{-1};
    static inline int deadIndexBlack{-1};


    public:
        Bishop(string imageName, Point p, Team t, Race r);
        void AdjustLiveDeadPiece() override;
        int getDeadPieces() const override;

        void setDeadInd(int ind) override;
        int getDeadIndex() const override;
        map<Direction, vector<Point>> getPossibleMoves(int cellIndex) const override;

        //reset the amout of live and dead subclasses
        static void resetSubs();



};

class Pawn : public Piece{
     
    //teamates alive
    static inline int livePieceWhite{0};
    static inline int livePieceBlack{0};

    //teamates dead
    static inline int deadPieceWhite{0};
    static inline int deadPieceBlack{0};

    //index of dead pieces that all same pieces have
    static inline int deadIndexWhite{-1};
    static inline int deadIndexBlack{-1};

    public:
        Pawn(string imageName, Point p, Team t, Race r);
        void AdjustLiveDeadPiece() override;
        int getDeadPieces() const override;

        void setDeadInd(int ind) override;
        int getDeadIndex() const override;
        map<Direction, vector<Point>> getPossibleMoves(int cellIndex) const override;

        //reset the amout of live and dead subclasses
        static void resetSubs();
};
    