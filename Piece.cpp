#include "Piece.h"



Piece::Piece(string imageName, Point p, Team t, Race r )
:/*Image({p.x+inCellOffset,p.y+inCellOffset},BKingfileName),*/
isAlive{1}, team{t}, race{r}, moved{false}, enPassent{false}, image{imageName.c_str()},
pos{p.x+inCellOffset,p.y+inCellOffset}
{

    if(team == Team::black){
        liveTeamateBlack++;
    } else{
        liveTeamateWhite++;
    }
    //image.draw(this->point(0).x, this->point(0).y);
    
}   

Piece::Team Piece::getTeam() const {return team;};

Piece::Race Piece::getRace() const {return race;};
bool Piece::pieceIsAlive() const {return isAlive;};


int Piece::getDeadTeamates() const{
    if(team == Team::black){
        return deadTeamateBlack;
    }
    return deadTeamateWhite;
}

void Piece::kill(){ 
    isAlive = false;
    if(team == Team::black){
        liveTeamateBlack--;
        deadTeamateBlack++;
    } else{
        liveTeamateWhite--;
        deadTeamateBlack++;
    }
    AdjustLiveDeadPiece();
}



bool operator==(const Piece& lhs , const Piece& rhs ){

    return (lhs.getTeam() == rhs.getTeam() && lhs.getRace() == rhs.getRace());
}


Point Piece::cellIndexToPoint(int cellIndex) {
    return {cellIndex % cell_amount, cellIndex / cell_amount };
}

bool Piece::hasBeenMoved() const { return moved;}

void Piece::setMoved() { moved = true;}
void Piece::setEnPassent(bool enPassent) {this->enPassent = enPassent; }
bool Piece::getEnPassent() const { return enPassent; }




void Piece::resetPiecesCounts(){
    resetTeamates();
    King::resetSubs();
    Queen::resetSubs();
    Rooks::resetSubs();
    Knight::resetSubs();
    Bishop::resetSubs();
    Pawn::resetSubs();


}

void Piece::resetTeamates(){
    liveTeamateWhite = 16;
    liveTeamateBlack = 16;

    deadTeamateWhite = 0;
    deadTeamateBlack = 0;
}


void Piece::draw(){
    
    image.draw(pos.x, pos.y); 

}

void Piece::move(int dx , int dy){
    pos.x += dx;
    pos.y += dy;

}

Point Piece::getPos() const{
    return pos;
}


//------------------------------------------ KING------------------------------------------------------
King::King(string imageName, Point p, Team t, Race r): Piece(imageName, p, t, r) {
    if(team == Team::black){
        livePieceBlack++;
    } else{
        livePieceWhite++;
    }
}

void King::AdjustLiveDeadPiece(){
    if(team == Team::black){
        livePieceBlack--;
        deadPieceBlack++;
    } else{
        livePieceWhite--;
        deadPieceWhite++;
    }
}

int King::getDeadPieces() const { 
    if(team == Team::black){
        return deadPieceBlack; 
    } else{
        return deadPieceWhite; 
    }
}

void King::setDeadInd(int ind){
    if(team == Team::black){
        deadIndexBlack = ind; 
    } else{
        deadIndexWhite = ind; 
    }
}
int King::getDeadIndex() const{
    return (team == Team::black) ? deadIndexBlack : deadIndexWhite; 
}

map<Piece::Direction, vector<Point>> King::getPossibleMoves(int cellIndex) const{
    
    Point point = cellIndexToPoint(cellIndex);

    map<Piece::Direction, vector<Point>> possibleMoves;
    
    possibleMoves[U].push_back( moveUp( point) );
    possibleMoves[UR].push_back( moveUpRight( point) );
    possibleMoves[R].push_back( moveRight( point) );
    possibleMoves[RD].push_back( moveRightDown( point) );
    possibleMoves[D].push_back( moveDown( point) );
    possibleMoves[DL].push_back( moveDownLeft( point) );
    possibleMoves[L].push_back( moveLeft( point) );
    possibleMoves[LU].push_back( moveLeftUp( point) );
    possibleMoves[currentP].push_back( point);

    if(!moved){
        possibleMoves[L].push_back(moveLeft(point,2));
        possibleMoves[R].push_back(moveRight(point,2));
    }

    return possibleMoves;
}


void King::resetSubs(){
    livePieceWhite = 1;
    livePieceBlack = 1;

    deadPieceWhite = 0;
    deadPieceBlack = 0;

    deadIndexWhite = -1;
    deadIndexBlack = -1;
}

//------------------------------------------ QUEEN------------------------------------------------------

Queen::Queen(string imageName, Point p, Team t, Race r): Piece(imageName, p, t, r) {
    if(team == Team::black){
        livePieceBlack++;
    } else{
        livePieceWhite++;
    }
}

void Queen::AdjustLiveDeadPiece(){
    if(team == Team::black){
        livePieceBlack--;
        deadPieceBlack++;
    } else{
        livePieceWhite--;
        deadPieceWhite++;
    }
}



int Queen::getDeadPieces() const { 
    if(team == Team::black){
        return deadPieceBlack; 
    } else{
        return deadPieceWhite; 
    }
}

void Queen::setDeadInd(int ind){
    if(team == Team::black){
        deadIndexBlack = ind; 
    } else{
        deadIndexWhite = ind; 
    }
}
int Queen::getDeadIndex() const{
    return (team == Team::black) ? deadIndexBlack : deadIndexWhite; 
}

map<Piece::Direction, vector<Point>> Queen::getPossibleMoves(int cellIndex) const{
    
    Point point = cellIndexToPoint(cellIndex);

    map<Piece::Direction, vector<Point>> possibleMoves;
    
    for(int i{1}; i <= cell_amount ; i++){ //loop 8 times
        possibleMoves[U].push_back(moveUp(point,i));
        possibleMoves[UR].push_back(moveUpRight(point,i));
        possibleMoves[R].push_back(moveRight(point,i));
        possibleMoves[RD].push_back(moveRightDown(point,i));
        possibleMoves[D].push_back(moveDown(point,i));
        possibleMoves[DL].push_back(moveDownLeft(point,i));
        possibleMoves[L].push_back(moveLeft(point,i));
        possibleMoves[LU].push_back(moveLeftUp(point,i));
    }
    possibleMoves[currentP].push_back( point);



    return possibleMoves;
}

void Queen::resetSubs(){
    livePieceWhite = 1;
    livePieceBlack = 1;

    deadPieceWhite = 0;
    deadPieceBlack = 0;

    deadIndexWhite = -1;
    deadIndexBlack = -1;
}
//------------------------------------------ ROOKS------------------------------------------------------

Rooks::Rooks(string imageName, Point p, Team t, Race r): Piece(imageName, p, t, r) {

    if(team == Team::black){
        livePieceBlack++;
    } else{
        livePieceWhite++;
    }
}


void Rooks::AdjustLiveDeadPiece(){
    if(team == Team::black){
        livePieceBlack--;
        deadPieceBlack++;
    } else{
        livePieceWhite--;
        deadPieceWhite++;
    }
}


int Rooks::getDeadPieces() const { 
    if(team == Team::black){
        return deadPieceBlack; 
    } else{
        return deadPieceWhite; 
    }
}
void Rooks::setDeadInd(int ind){
    if(team == Team::black){
        deadIndexBlack = ind; 
    } else{
        deadIndexWhite = ind; 
    }
}
int Rooks::getDeadIndex() const{
    return (team == Team::black) ? deadIndexBlack : deadIndexWhite; 
}

map<Piece::Direction, vector<Point>> Rooks::getPossibleMoves(int cellIndex) const{
    
    Point point = cellIndexToPoint(cellIndex);

    map<Piece::Direction, vector<Point>> possibleMoves;
    
    for(int i{1}; i <= cell_amount ; i++){ //loop 8 times
        possibleMoves[U].push_back(moveUp(point,i));
        possibleMoves[R].push_back(moveRight(point,i));
        possibleMoves[D].push_back(moveDown(point,i));
        possibleMoves[L].push_back(moveLeft(point,i));

    }
    possibleMoves[currentP].push_back( point);



    return possibleMoves;
}

void Rooks::resetSubs(){
    livePieceWhite = 2;
    livePieceBlack = 2;

    deadPieceWhite = 0;
    deadPieceBlack = 0;

    deadIndexWhite = -1;
    deadIndexBlack = -1;
}
//------------------------------------------ KNIGHT------------------------------------------------------

Knight::Knight(string imageName, Point p, Team t, Race r): Piece(imageName, p, t, r) {
    if(team == Team::black){
        livePieceBlack++;
    } else{
        livePieceWhite++;
    }
}

void Knight::AdjustLiveDeadPiece(){
    if(team == Team::black){
        livePieceBlack--;
        deadPieceBlack++;
    } else{
        livePieceWhite--;
        deadPieceWhite++;
    }
}

int Knight::getDeadPieces() const { 
    if(team == Team::black){
        return deadPieceBlack; 
    } else{
        return deadPieceWhite; 
    }
}
void Knight::setDeadInd(int ind){
    if(team == Team::black){
        deadIndexBlack = ind; 
    } else{
        deadIndexWhite = ind; 
    }
}
int Knight::getDeadIndex() const{
    return (team == Team::black) ? deadIndexBlack : deadIndexWhite; 
}

map<Piece::Direction, vector<Point>> Knight::getPossibleMoves(int cellIndex) const {
    
    Point point = cellIndexToPoint(cellIndex);

    map<Piece::Direction, vector<Point>> possibleMoves;
    
    possibleMoves[U].push_back( moveLeft(moveUp(point,2)) );
    possibleMoves[UR].push_back( moveRight(moveUp(point,2)) );
    possibleMoves[R].push_back( moveUp(moveRight(point,2)) );
    possibleMoves[RD].push_back( moveDown(moveRight(point,2)) );
    possibleMoves[D].push_back( moveRight(moveDown(point,2)) );
    possibleMoves[DL].push_back( moveLeft(moveDown(point,2)) );
    possibleMoves[L].push_back( moveDown(moveLeft(point,2)) );
    possibleMoves[LU].push_back( moveUp(moveLeft(point,2)) );
    possibleMoves[currentP].push_back( point);



    return possibleMoves;
}

void Knight::resetSubs(){
    livePieceWhite = 2;
    livePieceBlack = 2;

    deadPieceWhite = 0;
    deadPieceBlack = 0;

    deadIndexWhite = -1;
    deadIndexBlack = -1;
}
//------------------------------------------ BISHOP------------------------------------------------------

Bishop::Bishop(string imageName, Point p, Team t, Race r): Piece(imageName, p, t, r) {
    if(team == Team::black){
        livePieceBlack++;
    } else{
        livePieceWhite++;
    }
}

void Bishop::AdjustLiveDeadPiece(){
    if(team == Team::black){
        livePieceBlack--;
        deadPieceBlack++;
    } else{
        livePieceWhite--;
        deadPieceWhite++;
    }
}


int Bishop::getDeadPieces() const { 
    if(team == Team::black){
        return deadPieceBlack; 
    } else{
        return deadPieceWhite; 
    }
}
void Bishop::setDeadInd(int ind){
    if(team == Team::black){
        deadIndexBlack = ind; 
    } else{
        deadIndexWhite = ind; 
    }
}
int Bishop::getDeadIndex() const{
    return (team == Team::black) ? deadIndexBlack : deadIndexWhite; 
}

map<Piece::Direction, vector<Point>> Bishop::getPossibleMoves(int cellIndex) const {
    
    Point point = cellIndexToPoint(cellIndex);

    map<Piece::Direction, vector<Point>> possibleMoves;
    
    
    for(int i{1}; i <= cell_amount ; i++){ //loop 8 times

        possibleMoves[UR].push_back(moveUpRight(point,i));
        possibleMoves[RD].push_back(moveRightDown(point,i));
        possibleMoves[DL].push_back(moveDownLeft(point,i));
        possibleMoves[LU].push_back(moveLeftUp(point,i));
    }
    
    possibleMoves[currentP].push_back( point);


    return possibleMoves;
}

void Bishop::resetSubs(){
    livePieceWhite = 2;
    livePieceBlack = 2;

    deadPieceWhite = 0;
    deadPieceBlack = 0;

    deadIndexWhite = -1;
    deadIndexBlack = -1;
}



//------------------------------------------ PAWN ------------------------------------------------------

Pawn::Pawn(string imageName, Point p, Team t, Race r): Piece(imageName, p, t, r) {
    if(team == Team::black){
        livePieceBlack++;
    } else{
        livePieceWhite++;
    }
    //cout << "Pawn " << livePieceBlack << " " << livePieceWhite << endl;
}
void Pawn::AdjustLiveDeadPiece(){
    if(team == Team::black){
        livePieceBlack--;
        deadPieceBlack++;
    } else{
        livePieceWhite--;
        deadPieceWhite++;
    }
}



int Pawn::getDeadPieces() const { 
    if(team == Team::black){
        return deadPieceBlack; 
    } else{
        return deadPieceWhite; 
    }
}
void Pawn::setDeadInd(int ind){
    if(team == Team::black){
        deadIndexBlack = ind; 
    } else{
        deadIndexWhite = ind; 
    }
}
int Pawn::getDeadIndex() const{
    return (team == Team::black) ? deadIndexBlack : deadIndexWhite; 
}

map<Piece::Direction, vector<Point>> Pawn::getPossibleMoves(int cellIndex) const{
    
    Point point = cellIndexToPoint(cellIndex);

    map<Piece::Direction, vector<Point>> possibleMoves;
    

    if(team == Team::black){

        possibleMoves[D].push_back(moveDown(point));
        if(point.y == 1){
            possibleMoves[D].push_back(moveDown(point,2));
        }


        possibleMoves[RD].push_back( moveRightDown(point));
        possibleMoves[DL].push_back( moveDownLeft(point));


    } else{

        possibleMoves[U].push_back(moveUp(point));
        if(point.y == 6){
            possibleMoves[U].push_back(moveUp(point,2));
        }


        possibleMoves[UR].push_back( moveUpRight(point));
        possibleMoves[LU].push_back( moveLeftUp(point));


    }
    possibleMoves[currentP].push_back( point);



    return possibleMoves;
}

void Pawn::resetSubs(){
    livePieceWhite = 8;
    livePieceBlack = 8;

    deadPieceWhite = 0;
    deadPieceBlack = 0;

    deadIndexWhite = -1;
    deadIndexBlack = -1;
}


