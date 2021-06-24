#include "Cell.h"
#include <cassert>



Cell::Cell(Color c, Point pos, int size, shared_ptr<Piece> p)
: color{c}, rect{std::make_shared<Rectangle>(pos, size, size)},
 mark{{pos.x + size/2, pos.y + size/2 }, size/2 - distMarkingBorderInt,{pos.x + size/2, pos.y + size/2 }, size/2 - inCellOffset,c},
 piece{p}, index{numberOfCells++}, KingInChess{false}, promotionPawn{false}, image{nullptr}, enPassantCell{false} {

    //setter bakgrunnsfargen
    rect->set_fill_color(color);

    piecePos = {pos.x + inCellOffset, pos.y + inCellOffset};


   
}

bool operator==(const Cell& lhs , const Cell& rhs ){
    return lhs.getCellIndex() == rhs.getCellIndex();
}


void Cell::attach_to(Window& win) { 
    win.attach(*rect);
    mark.attach_to(win);
    if(piece){
        //win.attach(*piece);
    }
}


Point Cell::getPointCell() const {return rect->point(0);}



void Cell::setPiece(shared_ptr<Piece> p) {

    piece.swap(p);
    
}

Piece* Cell::getPiece() const { return piece.get();}
Piece* Cell::getPiece() { return piece.get();}



void Cell::setStaticPointers(vector<shared_ptr<Piece>>* p) { 
    deadPiecesPtr = p;
}



void Cell::movePiece(Cell* c, int& indexB, int& indexW){
    if(c){
        assert(deadPiecesPtr != nullptr);

        if(this->piece){ //If there is a piece here

            this->piece->kill();
            //set the pieces as moved before moving 
            piece->setMoved();
            c->piece->setMoved();


            // int indexDeadPieceVector;
            // for( indexDeadPieceVector=0; indexDeadPieceVector < static_cast<int>(deadPiecesPtr->size())-1; indexDeadPieceVector++){
            //     if((*deadPiecesPtr)[indexDeadPieceVector]){
            //         continue;
            //     }
            //     break;
            // }
           


            bool firstPiece = true;
            for(auto& piecePtr : *deadPiecesPtr){
                if(*piecePtr == *this->piece.get()){ //if same piece
                    firstPiece = false;
                    break;
                }
                
            }

            // move image of board if it doesnt already exist
            if(firstPiece){
                this->moveOffBoard(indexB, indexW, this->piece.get());
                deadPiecesPtr->push_back(this->piece);
            }
            
            
            this->piece = nullptr;

            this->piece.swap(c->piece);
            
          

        } else{  //no piece in this cell

            c->piece->setMoved();
            this->piece.swap(c->piece);

        
        }

        this->updatePice();
        c->updatePice();
        

        
        //std::cout << "Moved pieces\n";
    }
}

void Cell::moveOffBoard(int& indexB, int& indexW, Piece* p){
    if(p){


        if(p->getTeam() == Piece::Team::black){

            // for(const auto& piece : *deadPiecesPtr){
            //     if(piece){
            //         if( *piece == *p ){
            //             firstpiece = false;
                        
            //             int dx = piece->point(0).x - p->point(0).x;
            //             int dy = piece->point(0).x - p->point(0).y;
            //             p->move(dx,dy);
            //         }
            //     }
            // }
            // if(firstpiece){
            int dx = killedPiecesBlack[indexB].x - p->getPos().x;
            int dy = killedPiecesBlack[indexB].y - p->getPos().y;
            p->move(dx,dy);
            p->setDeadInd(indexB);
            indexB++;
            // }
            
        } else{
            // for(const auto& piece : *deadPiecesPtr){
            //     if(piece){
            //         if( *piece == *p){
            //             firstpiece = false;

            //             int dx = piece->point(0).x - p->point(0).x;
            //             int dy = piece->point(0).x - p->point(0).y;
            //             p->move(dx,dy);
            //             break;
            //         }
            //     }
            // }
            // if(firstpiece){
            int dx = killedPiecesWhite[indexW].x - p->getPos().x;
            int dy = killedPiecesWhite[indexW].y - p->getPos().y;
            p->move(dx,dy);
            p->setDeadInd(indexW);
            indexW++;
            // }
            
        }
        p->draw();        
    }
}


void Cell::updatePice(){
    
    if(piece){
        int dx = rect->point(0).x + inCellOffset - piece->getPos().x ;
        int dy = rect->point(0).y + inCellOffset - piece->getPos().y;
        piece->move(dx,dy);
    }

}

void Cell::tooglePromotion(bool p){
    promotionPawn = p;
}


void Cell::updateCell(){
    if(KingInChess){
        rect->set_fill_color(KingInChessColor);
    } else if(promotionPawn){
        rect->set_fill_color(promotionColor);
    } else{
        rect->set_fill_color(color);
    }
    rect->draw();
    mark.show();
    if(image){
        image->draw(piecePos.x, piecePos.y);
    } else if(piece){
        piece->draw();
        //piece->drawPiece();  //--------------------------------------------
    }
}


void Cell::setChessMode(bool t) {
    KingInChess = t;
}


int Cell::getCellIndex() const{
    return index;
}


void Cell::setBorder(Piece* selectedPiece){

    if(piece && selectedPiece){

        switch(piece->getTeam())
        {
        case Piece::white:
            
            rect->set_color(teamWborder_show);
            break;
        
        case Piece::black:

            rect->set_color(teamBborder_show);
            
            break;

        default:
            throw runtime_error("setBorder fail!");
            break;
        }
    }  
    else{
        rect->set_color(border_hide);
    }
    
}

map<Piece::Direction, vector<Point>> Cell::getPieceMoves() const {
    if(piece){
        return piece->getPossibleMoves(index);
    }
    return map<Piece::Direction, vector<Point>>{};
}

void Cell::movePieceScratch(Cell* c){

    piece = nullptr;
    piece.swap(c->piece);

}



void Cell::movePromotionImage(Fl_PNG_Image* impTr){
    image = impTr;
   

}

void Cell::resetImagepTr(){
    //dont need to moeve of board yet
    image = nullptr;

}

Fl_PNG_Image* Cell::getImage() const{
    return image;
}

void Cell::setEnPassent(bool b){
    enPassantCell = b;
}
bool Cell::getEnPassent() const{
    return enPassantCell;
}

bool Cell::isMarkedEnemy() const {
    return mark.isEnemy();
}   
