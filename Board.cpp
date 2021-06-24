#include "Board.h"

#include <algorithm>

#include <chrono>
#include <thread>




ChessBoard::ChessBoard(): 
Window(windowWidth, windowHeight, "CHESS"), selectedPiece{nullptr}, selectedCell{nullptr},
indDeadPiecesWhite{0}, indDeadPiecesBlack{0}, textEraser{{0,0}, pieceSeperation, pieceSeperation}, 
whiteKingChess{false}, blackKingChess{false}, gameStatus{Status::play}, gameStatusText{gameStatusTextPoint, ""},
pawnPromotion{false}, attemptedGiveUp{false}, attemptedDraw{false}, whiteAgreeDraw{false}, blackAgreeDraw{false},
turnToogle{false}, AIon{turnAIon}, HardAI{false},

optionsButton{optionsButtonPoint, buttonWidth, buttonHeight, optionsButtonName, ButtonFunctions::showOptionsMenu},
optionsMenu{optionsMenuPoint, menuSeperation ,buttonWidth, buttonHeight},
menu{MainMenuPoint, MainMenuButtonsSeperation, MainMenuButtonsWidht, MainMenuButtonsHeight, MainMenuTitle },
goToMainMenubtn{goToMainMenubtnPoint, buttonWidthreturn, buttonHeight, goToMainMenubtnName, ButtonFunctions::goToMainMenu}
{

    //---------------------------------- Buttons and widgets --------------------------

    optionsButton.attach_to(*this);

    allButtons.push_back(&optionsButton);



    optionsMenu.addButton( optionsMenuDrawName, ButtonFunctions::agreedDraw);
    optionsMenu.addButton( optionsMenuGiveUpName, ButtonFunctions::giveUp);
    optionsMenu.addButton( optionsMenuCancelName, ButtonFunctions::returnToMenu);

    optionsMenu.attach_to(*this);

    optionsMenu.add_to(&allButtons);



    menu.addButton(MainMenuNewGameName, ButtonFunctions::newGame);
    menu.addButton(MainMenuQuitName, ButtonFunctions::quit);

    menu.attach_to(*this);

    menu.add_to(&allButtons);


    goToMainMenubtn.attach_to(*this);
    allButtons.push_back(&goToMainMenubtn);

    
    
    menu.hide();
    optionsButton.show();
    goToMainMenubtn.show();
    




    // ---------------------------------------------------------------------------------
    this->color(backgroundColor);

    textEraser.set_fill_color(static_cast<Color::Color_type>(backgroundColor));
    textEraser.set_color(border_hide);

    //this->color(FL_GRAY);
    std::array<Color, 2> colors{grey, brown};
    
    //To initialize gridsize
    for( int y{0}; y < cell_amount; y++ ){

		
		get_current_grid().push_back({});

		for( int x{0}; x < cell_amount; x++ ){
            
            int xpos = x_offsett + x*cell_size;
            int ypos = y_offsett + y*cell_size;
			get_current_grid().back().emplace_back(Cell{colors[(y+x)%2], {xpos,ypos}, cell_size});
		}
		
	}  

    
    //To sett startingposition for all pieces
    for( int i{0}; i< cell_amount; i++){
        
        Point top = get_current_grid()[0][i].getPointCell();
        Point bottom = get_current_grid()[7][i].getPointCell();

        switch (i)
        {
        case 0 : case 7:
            get_current_grid()[0][i].setPiece(make_shared<Rooks>( blackConfig[i] , top, Piece::Team::black, Piece::Race::rook));
            get_current_grid()[7][i].setPiece(make_shared<Rooks>(whiteConfig[i]  ,  bottom, Piece::Team::white, Piece::Race::rook));
            
            break;
        case 1: case 6:

            get_current_grid()[0][i].setPiece(make_shared<Knight>(blackConfig[i], top , Piece::Team::black, Piece::Race::knight));
            get_current_grid()[7][i].setPiece(make_shared<Knight>(whiteConfig[i],  bottom, Piece::Team::white , Piece::Race::knight));

            break;

        case 2: case 5:
            get_current_grid()[0][i].setPiece(make_shared<Bishop>(blackConfig[i], top, Piece::Team::black, Piece::Race::bishop));
            get_current_grid()[7][i].setPiece(make_shared<Bishop>(whiteConfig[i], bottom, Piece::Team::white, Piece::Race::bishop));

            break;

        case 3:
            get_current_grid()[0][i].setPiece(make_shared<Queen>(blackConfig[i], top, Piece::Team::black, Piece::Race::queen));
            get_current_grid()[7][i].setPiece(make_shared<Queen>(whiteConfig[i], bottom, Piece::Team::white, Piece::Race::queen));

            break;

        case 4: 
            get_current_grid()[0][i].setPiece(make_shared<King>(blackConfig[i], top, Piece::Team::black, Piece::Race::king));
            get_current_grid()[7][i].setPiece(make_shared<King>(whiteConfig[i], bottom, Piece::Team::white, Piece::Race::king));

            break;
            
        default:
            break;
        }

        top = get_current_grid()[1][i].getPointCell();
        get_current_grid()[1][i].setPiece(make_shared<Pawn>(BPawnfileNamePNG, top, Piece::Team::black, Piece::Race::pawn));

        
        bottom = get_current_grid()[6][i].getPointCell();
        get_current_grid()[6][i].setPiece(make_shared<Pawn>(WPawnfileNamePNG, bottom, Piece::Team::white, Piece::Race::pawn));
        

    }

    for(int y{0}; y < cell_amount; y++){
        for( int x{0}; x < cell_amount; x++){
            Cell& cell= get_current_grid()[y][x];
            cell.attach_to(*this);

            int xPos = cell.getPointCell().x + cell_size/2 - adjustOffsett;
            if( y==0){
                textObjects.push_back(new Text( {xPos, yPosTop}, letters[x]));
            }         
            if(y==7){
                textObjects.push_back(new Text( {xPos, yPosBottom}, letters[x]));
            }
        
        
            int yPos = cell.getPointCell().y + cell_size/2 + adjustOffsett;
            switch(x){
            case 0:
                {
                    textObjects.push_back(new Text( {xPosLeft, yPos}, numbers[y]));

                }
                break;

            case 7:
                {
                    textObjects.push_back(new Text( {xPosRight, yPos}, numbers[y]));
                }

                break;
            default:
                break;
            }


        }
    }

    textObjects.push_back(new Text( gameEndingPosition,""));

    for(int i{0}; i < 6; i++ ){

        x_sWhite.push_back(new Text({killedPiecesWhite[i].x + pieceSeperation + xSeperation, killedPiecesWhite[i].y+ySeperation }, "" ));

        x_sBlack.push_back(new Text({killedPiecesBlack[i].x + pieceSeperation + xSeperation, killedPiecesBlack[i].y + ySeperation }, "" ));
        
        x_sWhite[i]->set_font_size(fontSizeX);
        x_sBlack[i]->set_font_size(fontSizeX);

        attach(*x_sWhite[i]);
        attach(*x_sBlack[i]);

        
    }



    for(auto& t : textObjects){
        t->set_font_size(fontSize);
        attach(*t);
    }
    textObjects.back().set_font_size(gameEndingFontSize);
    
    
    gameStatusText.set_font_size(gameStatusFontSize);
    gameStatusText.set_color(gameStatusColor);
    attach(gameStatusText);

   
    

    //Sett the different static pointers in cell
    get_current_grid()[0][0].setStaticPointers(&deadPieces);

	get_scratch_grid() = get_current_grid();

    get_newGame_grid() = get_current_grid();

    
    
    writeMessage("Return to meny to start game");
    
};







//get functions for each grid 
ChessBoard::Grid& ChessBoard::get_current_grid() { return grid[current_grid]; }
ChessBoard::Grid& ChessBoard::get_scratch_grid() { return grid[scratch_grid]; }
ChessBoard::Grid& ChessBoard::get_newGame_grid() { return grid[newGame_grid]; }
const ChessBoard::Grid& ChessBoard::get_current_grid() const
{
	return grid[current_grid];
}
const ChessBoard::Grid& ChessBoard::get_scratch_grid() const
{
	return grid[scratch_grid];
}





int ChessBoard::handle(int event)
{
    if(newGame){
        updateBoard();
        newGame =false;
    }
	if (int handled = Fl_Group::handle(event) > 0) {
		// Event has been passed on to a child widget
		return handled;
	} else if (event == FL_PUSH) {
		// Handle mouse button clicks outside the widgets
		return click_handler(Point{Fl::event_x(), Fl::event_y()});
	} else {
		return Fl_Widget::handle(event);
	}
}


int ChessBoard::click_handler(Point pos){
    
    ButtonFunctions func = get_ownButton_Pressed(pos);
    
    bool keepPlay = true;
    auto cellpTr = cell_at_pos(pos);

    if(dealWithPressedButn(func)){
        keepPlay = false;
    } else{

        if( cellpTr == nullptr){
            return false;
        }
    }


    if(gameStatus == Status::play && keepPlay){ // if the game is set to keep playing
        
        if(!pawnPromotion){

            if(selectedPiece == nullptr){ //selcts a piece if no piece was selected
                selectedPiece = cellpTr->getPiece();

                if(!selectedPiece){
                    return false;
                }

                if(selectedPiece->getTeam() != teamArray[turnToogle]){
                    
                    selectedPiece = nullptr;
                    writeMessage( teamToString.at(teamArray[turnToogle]) + "'s turn!" );
                    updateBoard();
                    return false;
                }
                
                selectedCell = cellpTr; //findCell(selectedPiece);


                selectedCell->setBorder(selectedPiece);

                allValidMoves = getMoves(selectedCell, get_current_grid());

                testChessForAllValidMoves(allValidMoves,selectedPiece , selectedCell);
                
                checkForPromotion(cellpTr);
                if(pawnPromotion){
                    selectedCell = cellpTr;
                }
                

            } 
            else{ // A piece has already been selected
                
                if(selectedPiece == cellpTr->getPiece()){ // if the selected piece is the same as before
                    selectedPiece = nullptr; //unselect a piece
                    selectedCell->setBorder(selectedPiece);

                    //reset everything
                    resetMarkers();
                    allValidMoves.clear();
                    

                

                } else if( isInVector(allValidMoves, cellpTr)){ // selected piece is one of the valid cells 

                    if( selectedPiece->getRace() == Piece::Race::king && !selectedPiece->hasBeenMoved() && isInVector(CastlingIndexVec, cellpTr->getCellIndex()) ){
                        
                        //perform the casling move
                        castilingMove(cellpTr, selectedCell, get_current_grid());
                    
                    } else{

                        if(cellpTr->getEnPassent()){

                            correctForEnPassent(cellpTr);

                        }

                        cellpTr->movePiece(selectedCell, indDeadPiecesBlack, indDeadPiecesWhite); //Kan ikke være nullPTr

                        checkForPromotion(cellpTr);
                         
                    }
                    
                    turnToogle = !turnToogle;
                    

                    resetAllEnPassant();

                    checkForEnPassent(cellpTr, selectedPiece, selectedCell);

                    

                    if(!pawnPromotion){
                        selectedPiece = nullptr;
                    }    

                    //shows the border if the selected piece is still valid, else hides it
                    selectedCell->setBorder(selectedPiece); 
                    selectedCell = nullptr;

                    // //reset everything
                    // resetMarkers();
                    // allValidMoves.clear();
                    
                    if(pawnPromotion){
                        selectedCell = cellpTr;
                    
                    } else{
                        updateGameStatus();                  
                    }

                    //reset everything
                    resetMarkers();
                    allValidMoves.clear();
                    

                    updateDeadPiecesText();
                }
            } 
        
        }else { //pawnPromotion is true
            

            if( isInVector(promotionCells, cellpTr)){

                createNewPiece(cellpTr, selectedCell);
                pawnPromotion = false;
                selectedCell->tooglePromotion(pawnPromotion);
                
                selectedPiece = nullptr;
                selectedCell->setBorder(selectedPiece); 
                selectedCell = nullptr;
                writeMessage("");

            }

        }
        if(pawnPromotion){
            displayPromotionOption( selectedCell, selectedPiece);
            writeMessage("Choose a promotion-piece for pawn!");

        } 
    
        
        updateBoard();

        if(AIon && turnToogle && gameStatus == Status::play && !pawnPromotion){
            // for(int i{30}; i > 0 ;  i--){
            //     writeMessage("Turn left: " + to_string(i));
            // }
            AImovePiece();
            turnToogle = !turnToogle;
        }

    }

    if( gameStatus != Status::gameEnded){

        if(attemptedGiveUp){
            writeMessage("Choose a piece to give up first");

        } else if( (whiteAgreeDraw || blackAgreeDraw) && whiteAgreeDraw != blackAgreeDraw ){
            //one of them, but not both
            if(whiteAgreeDraw){
                writeMessage("Black must agree to draw too");
            }else{
                writeMessage("White must agree to draw too");
            }
        } else  if(attemptedDraw){
            writeMessage("Both must agree to draw first");

        } else{
            writeMessage("");
        }
        gameStatusText.set_label(statusToString.at(gameStatus));
        gameStatusText.draw();
        if(gameStatus != Status::play){
            waitForReturn();
            goToMainMenu();
        }
    }

    return 1;

}


void ChessBoard::castilingMove(Cell* cellpTr, Cell* selectedCell, Grid& get_grid){
    cellpTr->movePiece(selectedCell, indDeadPiecesBlack, indDeadPiecesWhite); 
    switch (cellpTr->getCellIndex())
    {
    case LUCastlingIndx:
        {
        Point toCell = Piece::cellIndexToPoint(cellpTr->getCellIndex() + 1);
        get_grid[toCell.y][toCell.x].movePiece(&get_grid[0][0], indDeadPiecesBlack, indDeadPiecesWhite );
        }
        break;
    
    case RUCastlingIndx:
        {
        Point toCell = Piece::cellIndexToPoint(cellpTr->getCellIndex() - 1);
        get_grid[toCell.y][toCell.x].movePiece(&get_grid[0][7], indDeadPiecesBlack, indDeadPiecesWhite );
        }
        break;
    
    case LDCastlingIndx:
        {
        Point toCell = Piece::cellIndexToPoint(cellpTr->getCellIndex() + 1);
        get_grid[toCell.y][toCell.x].movePiece(&get_grid[7][0], indDeadPiecesBlack, indDeadPiecesWhite );
        }
        break;
    
    case RDCastlingIndx:
        {
        Point toCell = Piece::cellIndexToPoint(cellpTr->getCellIndex() - 1);
        get_grid[toCell.y][toCell.x].movePiece(&get_grid[7][7], indDeadPiecesBlack, indDeadPiecesWhite );
        }
        break;
    
    default:
        break;
    }

}



Cell* ChessBoard::cell_at_pos(Point pos){

    cout << pos.x << " " << pos.y << endl;
    

    int xInd = floor((pos.x-x_offsett)/static_cast<double>(cell_size));
    int yInd = floor((pos.y-y_offsett)/static_cast<double>(cell_size));

    if(!isWithinChessBoard({xInd, yInd})){
        return nullptr;
    }

    return &get_current_grid()[yInd][xInd];
    
}

ButtonFunctions ChessBoard::get_ownButton_Pressed(Point pos){

    for(auto& butn : allButtons){
       
       if(butn->isShown() && isInsidebox(pos, butn->pos(), butn->widht(), butn->hight() ) ){
           return butn->getfunction();
       }
    }
    return ButtonFunctions::none;
}


    



Cell* ChessBoard::findCell(Piece* selectedPiece){
    
    if( selectedPiece){
        
        for(auto& y : get_current_grid()){
            for( auto& cell : y){
                if( cell.getPiece() == selectedPiece){
                    return &cell;
                }
            }
        }

    }

    return nullptr;

}

void ChessBoard::updateBoard(){

    if(!pawnPromotion && promotionCells.size()!=0){
        for(auto& cellpTr : promotionCells ){
            cellpTr->tooglePromotion(pawnPromotion);
            cellpTr->resetImagepTr();
        }
        promotionCells.clear();
    }
   
    blackKingChess = kingInCheck(Piece::Team::black, get_current_grid());
    Cell* blackKingCellpTr = findKing(Piece::Team::black, get_current_grid());
    
   
    whiteKingChess = kingInCheck(Piece::Team::white, get_current_grid());
    Cell* whiteKingCellpTr = findKing(Piece::Team::white, get_current_grid());
    
    if(!blackKingCellpTr){
        gameStatus = Status::whiteWon;    
    }

    if(!whiteKingCellpTr){
        gameStatus = Status::blackWon;
    } 
    for(auto& y : get_current_grid()){
        for(auto& cell : y){

        
            if(blackKingCellpTr && cell == *blackKingCellpTr){
                blackKingCellpTr->setChessMode(blackKingChess);
            } else if(whiteKingCellpTr && cell == *whiteKingCellpTr){
                whiteKingCellpTr->setChessMode(whiteKingChess);
            } else{
                cell.setChessMode(false); //There is no king here so the cant be any chessmode here
            }   
            cell.updateCell();
        }
    }
    
}
void ChessBoard::eraseText(const std::array<Point, 6>& arr, int index){

    textEraser.move(arr[index].x + pieceSeperation - textEraser.point(0).x, arr[index].y - textEraser.point(0).y);
    textEraser.draw();
} 

void ChessBoard::toggleText(bool set, vector<Text*>* x_s, int index, string label){
    
    auto* arr = &killedPiecesWhite;
    if(x_s == &x_sBlack){
        arr = &killedPiecesBlack;
    }

    auto& x_s1 = *x_s;
    if(set){
        x_s1[index]->set_label(label);
        x_s1[index]->draw();
    }
    else{
        x_s1[index]->set_label(label);
        x_s1[index]->draw();
        eraseText(*arr, index);
    }

}

void ChessBoard::updateDeadPiecesText(){

    for( auto& piece : deadPieces){
        if(piece){

            int index = piece->getDeadIndex();
            if(piece->getTeam() == Piece::Team::black){
                
                toggleText(0, &x_sBlack, index);
                toggleText(1, &x_sBlack, index, "x "+ to_string(piece->getDeadPieces()));


            } else{
                
                toggleText(0, &x_sWhite, index);
                toggleText(1, &x_sWhite, index, "x "+ to_string(piece->getDeadPieces()));

            }

        }
        
    }



}

void ChessBoard::resetMarkers(){
    for(auto& y : get_current_grid()){
        for( auto& cell : y){
            cell.resetMarker();
        }
    }
}

vector<Cell*> ChessBoard::processMoves(map<Piece::Direction, std::vector<Graph_lib::Point>>& moves, Grid& get_grid, bool display){
    
    vector<Cell*> cellPtrCollect;
    if(moves.size() != 0){
        
        Point currentPoint = moves[Piece::Direction::currentP].front();
        Piece* pieceAtPos = get_grid[currentPoint.y][currentPoint.x].getPiece();
        Piece::Team currentTeam = pieceAtPos->getTeam();
        
        //Check if it is possible to cast to the left or right 
        if( moves[Piece::Direction::R].size() == 2 && !canCastling(&get_grid[currentPoint.y][currentPoint.x], Piece::Direction::R, get_grid) ){
            moves[Piece::Direction::R].pop_back();
        }
        if( moves[Piece::Direction::L].size() == 2 && !canCastling(&get_grid[currentPoint.y][currentPoint.x], Piece::Direction::L, get_grid) ){
            moves[Piece::Direction::L].pop_back();
        }
       

        for(auto [direction, container] : moves){

            std::vector<Graph_lib::Point> move;
            
            //filter the posistions
            for(const auto& p : container ){
                if(!isWithinChessBoard(p)){
                    break;
                }
                move.push_back(p);
            }

            
            for(const auto& point : move){
                Cell* cell = &get_grid[point.y][point.x];
                Piece* piece = cell->getPiece();

                if(piece){          //if there is a piece in this cellposition
                    if(piece->getTeam()!=currentTeam){ //if not same team
                       
                        //As long as it is not a pawn taking an enemy from 2 distances
                        if(!((direction == Piece::Direction::U || direction == Piece::Direction::D) && pieceAtPos->getRace()==Piece::Race::pawn)){
                            
                            if(display){
                                cell->setMarkerEnemy();
                            }
                            cellPtrCollect.push_back(cell);
                            
                        }
                    }
                    break;
                }
                //No piece in this cellposition


                vector<Piece::Direction> dir{Piece::Direction::UR, Piece::Direction::RD, Piece::Direction::DL, Piece::Direction::LU};
                //ignore position if its a pawn with no enemy in these directions
                if( !(isInVector(dir,direction) && container.size() !=0 && pieceAtPos->getRace() == Piece::Race::pawn)){ 
                    if(display){
                        cell->setMarkerWhite();
                    }
                    cellPtrCollect.push_back(cell);
                }

                //if enpassent is available
                if( isInVector(dir, direction) && checkForPassentPawn(currentPoint, direction, get_grid) ){
                    if(display){
                        cell->setMarkerEnemy();
                    }
                    cell->setEnPassent(true);
                    cellPtrCollect.push_back(cell);
                }
                

            }
            
        }



    }
    return cellPtrCollect;

}


template<typename T>
bool ChessBoard::isInVector(const vector<T>& v, T c) const{ 
    for(auto& cell : v){
        if(cell == c){
            return true;
        }
    }
    return false;
}




bool ChessBoard::canCastling(Cell* selCell, Piece::Direction direction, Grid& get_grid) const{

    Piece* piece =  selCell->getPiece();
    int cellIndex = selCell->getCellIndex();


    // if not a king, or it has been moved
    if( piece->getRace() != Piece::Race::king || piece->hasBeenMoved()  ){
        return false;
    }


    switch (direction)
    {
    case Piece::Direction::R:
        
        //not empty cells to the right
        if( !isEmptyCellind(++cellIndex, get_grid) || !isEmptyCellind(++cellIndex, get_grid)){ return false; }

        // empty cell at rook position, or no rook here
        if( isEmptyCellind(++cellIndex, get_grid) || getPieceAtCellInd(cellIndex, get_grid)->getRace() != Piece::Race::rook){ return false; }
        
        //rook has been moved
        if( getPieceAtCellInd(cellIndex, get_grid)->hasBeenMoved()) { return false; }


        break;
    
    case Piece::Direction::L:

        if( !isEmptyCellind(--cellIndex, get_grid) || !isEmptyCellind(--cellIndex, get_grid) || !isEmptyCellind(--cellIndex, get_grid)) { return false; }
        
        if( isEmptyCellind(--cellIndex, get_grid) || getPieceAtCellInd(cellIndex, get_grid)->getRace() != Piece::Race::rook){ return false; }

        if( getPieceAtCellInd(cellIndex, get_grid)->hasBeenMoved()) { return false; }

        break;
    

    default:
        break;
    }

    return true;
    
    
 



}


bool ChessBoard::isEmptyCellind(int cellInd, Grid& get_grid) const{
    

    Point p = Piece::cellIndexToPoint(cellInd);


    if(get_grid[p.y][p.x].getPiece()){
        return false;
    }
    return true;


}

Piece* ChessBoard::getPieceAtCellInd(int cellInd, Grid& get_grid) const{
    Point p = Piece::cellIndexToPoint(cellInd);
    return get_grid[p.y][p.x].getPiece();
}

Cell* ChessBoard::getCellAtCellInd(int cellInd, Grid& get_grid) const{
    Point p = Piece::cellIndexToPoint(cellInd);
    return &get_grid[p.y][p.x];
}


Cell* ChessBoard::findKing(Piece::Team team, Grid& get_grid) const{
    for(auto& y : get_grid){
        for(auto& cell : y){
            if(cell.getPiece() && cell.getPiece()->getTeam() == team && cell.getPiece()->getRace() == Piece::Race::king){
                return &cell;
            }
        }
    }
    return nullptr;
}


bool ChessBoard::kingInCheck(Piece::Team team, Grid& get_grid) {
  
    Cell* kingCell = findKing(team, get_grid);
    
    if(!kingCell){
        return false;
    }


    vector<Cell*> cellPtrVector;
    for(const auto& y : get_grid){
        for(const auto& cell : y){
            if(cell.getPiece() && cell.getPiece()->getTeam() != team){
                
                map<Piece::Direction, std::vector<Graph_lib::Point>> movesDirectionMap = cell.getPieceMoves();
                cellPtrVector = processMoves( movesDirectionMap , get_grid, disregard_results);

                if( isInVector(cellPtrVector, kingCell)){
                    return true;
                }

            }
            
            
        }
    }
    return false;

}


void ChessBoard::testChessForAllValidMoves(vector<Cell*>& allMoves, Piece* selPiece, Cell* selCell, bool display) {

    if( !selPiece || allMoves.size()==0 ){
        return;
    }
    //here the selected piece and cell has been chosen

    get_scratch_grid() = get_current_grid();

    Cell* cellptrScratchFrom = getCellAtCellInd(selCell->getCellIndex(), get_scratch_grid());

    Piece::Team team = selPiece->getTeam();

    Cell* cellptrScratchto;
    vector<Cell*> temporaryAllValid;
    for(auto& curGridCell : allMoves){
        cellptrScratchto = getCellAtCellInd(curGridCell->getCellIndex(), get_scratch_grid());
        cellptrScratchto->movePieceScratch(cellptrScratchFrom);
        
        
        if(kingInCheck(team, get_scratch_grid())){
            if(display){
                curGridCell->setMarkerChess();
            }

        } else{

            temporaryAllValid.push_back(curGridCell);
        }

        get_scratch_grid() = get_current_grid();
    }

    allMoves = temporaryAllValid;

}  


bool ChessBoard::kingInCheckMate(Piece::Team team){


    if(!kingInCheck(team, get_current_grid())){
        return false;
    }

    get_scratch_grid() = get_current_grid();
    vector<Cell*> tempCellpTrVec;
    for(auto& y : get_current_grid()){
        for( auto& cell : y){


            Cell* cellpTrScrath = getCellAtCellInd(cell.getCellIndex(), get_scratch_grid());
            //if there is a piece here at it is from the other team
            if(cellpTrScrath->getPiece() &&  cellpTrScrath->getPiece()->getTeam() == team ){

                map<Piece::Direction, std::vector<Graph_lib::Point>> movesDirectionMap = cellpTrScrath->getPieceMoves();
                tempCellpTrVec = processMoves(movesDirectionMap, get_scratch_grid(), disregard_results);

                for(auto& cellpTrTo : tempCellpTrVec ){

                    cellpTrTo->movePieceScratch(cellpTrScrath);

                    if(!kingInCheck(team,get_scratch_grid())){
                        return false;
                    }

                    get_scratch_grid() = get_current_grid();

                }
            }
        }
    }

    return true;
}


void ChessBoard::waitForReturn(){
    for(int i{gameEndingtime}; i >=0 ; i--){
        
        writeReturningString(i);
        
        this_thread::sleep_for(chrono::microseconds(second));
    }

}



void ChessBoard::writeReturningString(int num){
    Text& text = textObjects.back();
    int dx = text.point(0).x  - textEraser.point(0).x;
    int dy = text.point(0).y - 2*textEraser.height()/3 - textEraser.point(0).y;  
    textEraser.move( dx , dy );
    textEraser.draw();
    for(int i{0}; i<6; i++){
        textEraser.move( textEraser.width() , 0);
        textEraser.draw();
    }
    text.set_label(returningText +  to_string(num));
    text.draw();
}

void ChessBoard::writeMessage(string message){
    Text& text = textObjects.back();
    int dx = text.point(0).x  - textEraser.point(0).x;
    int dy = text.point(0).y - 2*textEraser.height()/3 - textEraser.point(0).y;  
    textEraser.move( dx , dy );
    textEraser.draw();
    for(int i{0}; i<6; i++){
        textEraser.move( textEraser.width() , 0);
        textEraser.draw();
    }
    text.set_label(message);
    text.set_font_size(fontSize);
    text.draw();
}


void ChessBoard::checkForPromotion( Cell* cellpTr){
    Point p = Piece::cellIndexToPoint(cellpTr->getCellIndex());
    if(isInVector({0,7}, p.y) && cellpTr->getPiece() && cellpTr->getPiece()->getRace() == Piece::Race::pawn){ 
        //there is a pawn in here, and condtions for promotion are met
        pawnPromotion = true;
        cellpTr->tooglePromotion(pawnPromotion);
        
    } 
                            
}



bool ChessBoard::checkForStalemate(){
    
    set<Cell*> setCellpTrwhite;
    set<Cell*> setCellpTrblack;

    for(auto& y : get_current_grid()){
        for(auto& selCell : y ){
            if(selCell.getPiece()){

                get_scratch_grid() = get_current_grid(); 
                map<Piece::Direction, std::vector<Graph_lib::Point>> movesDirectionMap = selCell.getPieceMoves();
                allValidMoves = processMoves(movesDirectionMap, get_scratch_grid(), disregard_results);
                testChessForAllValidMoves(allValidMoves , selCell.getPiece() , &selCell);
                

                for(auto& cell : allValidMoves){
                    if(selCell.getPiece()->getTeam() == Piece::black){
                        setCellpTrblack.insert(cell);
                    } else{
                        setCellpTrwhite.insert(cell);
                    }
                }
                allValidMoves.clear();
            }

        }
    }
    if(setCellpTrwhite.size() == 0 || setCellpTrblack.size() == 0){
        return true;
    }
    return false;


}


void ChessBoard::displayPromotionOption(Cell* selCell, Piece* selPiece){
    
    vector<int> cellsPositions;
    int cellInd = selCell->getCellIndex();
    Piece::Team team = selCell->getPiece()->getTeam();
    

    if(selPiece->getTeam()==Piece::white){
        cellsPositions.push_back(cellInd+=cell_amount);
        cellsPositions.push_back(cellInd+=cell_amount);
        cellsPositions.push_back(cellInd+=cell_amount);
    } else{
        cellsPositions.push_back(cellInd-=cell_amount);
        cellsPositions.push_back(cellInd-=cell_amount);
        cellsPositions.push_back(cellInd-=cell_amount);
    }

    promotionCells.push_back(selCell);
    for(const auto& ind : cellsPositions){
        promotionCells.push_back( getCellAtCellInd(ind, get_current_grid()) );
    }

    for(int i{0}; i < deadOptionAmount; i++){
        Cell* cell = promotionCells[i];
        cell->tooglePromotion(pawnPromotion);
        if(team == Piece::white){
            cell->movePromotionImage(BlackWhiteImages[i+deadOptionAmount]);
            
        } else{
            cell->movePromotionImage(BlackWhiteImages[i]);
        }
    }
    

}

void  ChessBoard::createNewPiece(Cell* cpTr, Cell* selCell){
    Fl_PNG_Image* im = cpTr->getImage();
    Point top = cpTr->getPointCell();
    if( isEqual( im , &BQueenImage) ){

        selCell->setPiece( make_shared<Queen>(BQueenfileNamePNG, top, Piece::Team::black, Piece::Race::queen)  );

    } else if( isEqual( im , &WQueenImage) ){

        selCell->setPiece( make_shared<Queen>(WQueenfileNamePNG, top, Piece::Team::white, Piece::Race::queen)  );
    
    } else if( isEqual( im , &BRookImage) ){

        selCell->setPiece( make_shared<Rooks>(BRookfileNamePNG, top, Piece::Team::black, Piece::Race::rook)  );
        
    } else if( isEqual( im , &WRookImage) ){

        selCell->setPiece( make_shared<Rooks>(WRookfileNamePNG, top, Piece::Team::white, Piece::Race::rook)  );
        
    } else if( isEqual( im , &BBishopImage) ){ 
        
        selCell->setPiece( make_shared<Bishop>(BBishopfileNamePNG, top, Piece::Team::black, Piece::Race::bishop)  );

    } else if( isEqual( im , &WBishopImage) ){

        selCell->setPiece( make_shared<Bishop>(WBishopfileNamePNG, top, Piece::Team::white, Piece::Race::bishop)  );
        
    } else if( isEqual( im , &BKnightImage) ){

        selCell->setPiece( make_shared<Knight>(BKnightfileNamePNG, top, Piece::Team::black, Piece::Race::knight)  );
    
    } else if( isEqual( im , &WKnightImage) ){

        selCell->setPiece( make_shared<Knight>(WKnightfileNamePNG, top, Piece::Team::white, Piece::Race::knight)  );

    }

    selCell->updatePice();
}

bool ChessBoard::isEqual(Fl_PNG_Image* lhs, Fl_PNG_Image* rhs){
    return (imageToIntValue.at(lhs) == imageToIntValue.at(rhs));
}

void ChessBoard::checkForEnPassent(Cell* cellPtr, Piece* selPiece, Cell* selCell){

    if(selPiece->getRace() == Piece::pawn ){

        if(checkPassentMove(selCell->getCellIndex() , cellPtr->getCellIndex())){
            
            selPiece->setEnPassent(true); 
        } 
    }

}

bool ChessBoard::checkPassentMove(int to, int from){
    return (abs(to-from)/cell_amount == 2);
}


bool ChessBoard::checkForPassentPawn(Point currP, Piece::Direction dir, Grid& get_grid){


    
    Piece* currPiece = (get_grid[currP.y][currP.x]).getPiece();
    Piece::Team team = currPiece->getTeam();
    
    if(currPiece->getRace() != Piece::Race::pawn){
        return false;
    }

    if( dir == Piece::Direction::LU || dir == Piece::Direction::DL ){
        
        currP.x--;
        if(isWithinChessBoard(currP)){

            Piece* pieceAtPos = get_grid[currP.y][currP.x].getPiece();
            if(pieceAtPos){
                if(pieceAtPos->getRace() == Piece::Race::pawn && pieceAtPos->getTeam() != team ){

                    if(pieceAtPos->getEnPassent()){
                        return true;
                    }


                }
            }
        }

    } else if(dir == Piece::Direction::UR || dir == Piece::Direction::RD ) {
        
        currP.x++;
        if(isWithinChessBoard(currP)){
            
            Piece* pieceAtPos = get_grid[currP.y][currP.x].getPiece();
            
            if(pieceAtPos){

                if(pieceAtPos->getRace() == Piece::Race::pawn && pieceAtPos->getTeam() != team ){

                    if(pieceAtPos->getEnPassent()){
                        return true;
                    }

                }
            }

        }
    }

    return false;

}

void ChessBoard::resetAllEnPassant(){
    for(auto& y : get_current_grid()){
        for(auto& cell : y ){
            cell.setEnPassent(false);
            if(cell.getPiece()){
                cell.getPiece()->setEnPassent(false);
            }
        }
    }
}


void ChessBoard::correctForEnPassent(Cell* cellpTr){
    
    if(selectedPiece->getTeam() == Piece::Team::black){

        Cell* pawnCell = getCellAtCellInd( cellpTr->getCellIndex() - cell_amount , get_current_grid() );

        cellpTr->movePiece(pawnCell, indDeadPiecesBlack, indDeadPiecesWhite );

    } else{

        Cell* pawnCell = getCellAtCellInd( cellpTr->getCellIndex() + cell_amount, get_current_grid() );
        
        cellpTr->movePiece(pawnCell, indDeadPiecesBlack, indDeadPiecesWhite );


    }
}


bool ChessBoard::checkForDeadPosition(){
    int white{0};
    int black{0};

    for(auto& y : get_current_grid()){
        for(auto& cell : y){
            if(cell.getPiece()){
                if(cell.getPiece()->getTeam() == Piece::black){
                    black++;
                } else{
                    white++;
                }
                if( black > 1 || white > 1){ return false; }
            }
        }
    }
    return true;
}

void ChessBoard::updateGameStatus(){
    blackKingChess = kingInCheck(Piece::Team::black, get_current_grid());
    Cell* blackKingCellpTr = findKing(Piece::Team::black, get_current_grid());
    
   
    whiteKingChess = kingInCheck(Piece::Team::white, get_current_grid());
    Cell* whiteKingCellpTr = findKing(Piece::Team::white, get_current_grid());
    
    if(!blackKingCellpTr){
        gameStatus = Status::whiteWon;    
    } else if(!whiteKingCellpTr){
        gameStatus = Status::blackWon;
    } else if(kingInCheckMate(Piece::white)){
        gameStatus = Status::blackWonCM;

    } else if(kingInCheckMate(Piece::black)){
        gameStatus = Status::whiteWonCM;

    } else if(checkForStalemate()){
        gameStatus = Status::drawStalemate;
    } else if(checkForDeadPosition()){
        gameStatus = Status::drawDeadPosition;
    }
}


bool ChessBoard::dealWithPressedButn(ButtonFunctions func){
    switch (func)
    {
    case ButtonFunctions::showOptionsMenu :
        showOptionsMenu();
        return true;
    
    case ButtonFunctions::giveUp :
        giveUp();
        return true;
    
    case ButtonFunctions::agreedDraw :
        agreedDraw();
        return true;
    
    case ButtonFunctions::returnToMenu :
        returnToMenu();
        return true;

    case ButtonFunctions::goToMainMenu :
        menu.toogleResume(true);
        goToMainMenu();
        return true;
    
    case ButtonFunctions::newGame :
        startNewGame();

        return false;
    
    case ButtonFunctions::quit :

        quitGame();
        return false;
        
    case ButtonFunctions::resumeGame :

        resumeGame();
        return false;

    case ButtonFunctions::toogleAI :

        toogleAI();
        return false;

    case ButtonFunctions::none :
        return false;
    
    default:
        return false;
    }
}




void ChessBoard::AImovePiece(){

    this_thread::sleep_for(AIwait);
    vector<Cell*> availableCells;
    for(auto& y : get_current_grid()){
        for(auto& cell : y){
            if(cell.getPiece()  && cell.getPiece()->getTeam() == Piece::black){
                
                allValidMoves = getMoves(&cell, get_current_grid(), false);
                testChessForAllValidMoves(allValidMoves, cell.getPiece(), &cell, disregard_results);
                if(allValidMoves.size() != 0){
                    availableCells.push_back(&cell);
                }  
            }
        }
    }

    if(availableCells.size() !=0){
        
        if(HardAI){

            
            vector<Cell*> currentCellsAvail; 
            for(auto& cptr : availableCells){

                vector<Cell*> vec  = getMoves(cptr, get_current_grid(), disregard_results);
                testChessForAllValidMoves( vec , cptr->getPiece(), cptr, disregard_results);

                for(auto& c : vec ){
                    if(c->getPiece()){
                        currentCellsAvail.push_back(cptr);
                    }
                }
            }
                
            if(currentCellsAvail.size() != 0){
                availableCells = currentCellsAvail;
            }

        }

        int ind = rand() % (availableCells.size());
        Cell* selCell = availableCells[ind]; 

        allValidMoves = getMoves( availableCells[ind], get_current_grid(), disregard_results);
        testChessForAllValidMoves( allValidMoves , selCell->getPiece(), selCell, disregard_results);
        

        while( allValidMoves.size() == 0){
            ind = rand() % (availableCells.size());

            Cell* selCell = availableCells[ind]; 

            allValidMoves = getMoves( availableCells[ind], get_current_grid(), disregard_results);
            testChessForAllValidMoves(allValidMoves, selCell->getPiece(), selCell, disregard_results);

        }


        ind = rand() % (allValidMoves.size());
        Cell* cellto = allValidMoves[ind];
        
        if(HardAI){
            
        

            while( !cellto->getPiece() && allValidMoves.size() > 1){
                vector<Cell*> v;
                for(auto& c : allValidMoves){
                    if(!(*c == *cellto)){
                        v.push_back(c);
                    }
                }
                allValidMoves = v;

                ind = rand() % (allValidMoves.size());
                cellto = allValidMoves[ind];
            }
            


        }





        Piece* selPiece = selCell->getPiece();

        if( selPiece->getRace() == Piece::Race::king && !selPiece->hasBeenMoved() && isInVector(CastlingIndexVec, cellto->getCellIndex()) ){
                            
            //perform the casling move
            castilingMove(cellto, selCell, get_current_grid());
        
        } else{

            if(cellto->getEnPassent()){

                correctForEnPassent(cellto);

            }

            cellto->movePiece(selCell, indDeadPiecesBlack, indDeadPiecesWhite); //Kan ikke være nullPTr

            checkForPromotion(cellto);
                
        }
        resetAllEnPassant();

        checkForEnPassent(cellto, selPiece, selCell);
        
        updateBoard();
        

        if(pawnPromotion){
            
            
            displayPromotionOption(cellto, selPiece);
            updateBoard();

            this_thread::sleep_for(AIwaitPromotion);
            Cell* cellPromo =  promotionCells[rand() % promotionCells.size()];
            
            createNewPiece(cellPromo, cellto);
            pawnPromotion = false;
            cellto->tooglePromotion(pawnPromotion);
            cellto->setBorder(nullptr); 
            
            writeMessage("");

            
            updateBoard();
        }

        //resetMarkers();
        allValidMoves.clear();
        updateDeadPiecesText();


    } else{
        gameStatus = Status::whiteWonCM;
    }
    updateGameStatus();                  
    
}


std::vector<Cell *> ChessBoard::getMoves(Cell* selCell , Grid& get_grid, bool display){

    map<Piece::Direction, std::vector<Graph_lib::Point>> movesDirectionMap = selCell->getPieceMoves();
    return processMoves(movesDirectionMap, get_grid, display);
}






//--------------------------------------- Buttons and widgets -------------------------------------------




void ChessBoard::showOptionsMenu(){
    optionsButton.hide();
    optionsMenu.show();
    goToMainMenubtn.show();

}
void ChessBoard::giveUp(){
    if(selectedPiece){
        if(selectedPiece->getTeam() == Piece::white){
            gameStatus = giveUpWhite;
        } else{
            gameStatus = giveUpBlack;
        }
    } else{
        attemptedGiveUp = true;
    }
}
void ChessBoard::agreedDraw(){
    if(selectedPiece){
        if(selectedPiece->getTeam() == Piece::white){
            whiteAgreeDraw = true;
        } else{
            blackAgreeDraw = true;
        }
    } else{
        attemptedDraw = true;
    }
    if(whiteAgreeDraw && blackAgreeDraw){
        gameStatus = Status::drawAgreed;
    }
}

void ChessBoard::returnToMenu(){

    optionsMenu.hide();
    goToMainMenubtn.hide();
    optionsButton.show();
    attemptedGiveUp = false;
    attemptedDraw = false;
    whiteAgreeDraw = false;
    blackAgreeDraw = false;
}



void ChessBoard::startNewGame(){
    get_current_grid() = get_newGame_grid();
    gameStatus = Status::play;
    
    selectedPiece = nullptr;
    if(selectedCell){
        selectedCell->setBorder(selectedPiece);
    }
    selectedCell = nullptr;
    
    for(auto& txtptr : x_sWhite){
        txtptr->set_label("");
    }
    
    for(auto& txtptr : x_sBlack){
        txtptr->set_label("");
    }

    allValidMoves.clear();
    promotionCells.clear();
    deadPieces.clear();
    
    indDeadPiecesWhite = 0;
    indDeadPiecesBlack = 0;

    whiteKingChess = false;
    blackKingChess = false;

    gameStatusText.set_label("");
    writeMessage("");

    pawnPromotion = false;

    attemptedDraw = false;
    attemptedGiveUp = false;
    whiteAgreeDraw = false;
    blackAgreeDraw = false;

    turnToogle = false;

    for(auto& imptr : BlackWhiteImages){
        imptr->draw(windowWidth, windowHeight);
    }

    redraw();
    menu.toogleResume(false);
    menu.hide();


    Piece::resetPiecesCounts();

    optionsButton.show();



    for(auto& y : get_current_grid()){
        for(auto& c : y){
            c.updatePice();
        }
    }
    updateBoard();
    
    for(auto& t : textObjects){
        t->draw();
    }

    if(AIon){
        writeMessage("White starts - AI is ON");
    } else{
        writeMessage("White starts - AI is OFF");
    }
     
    newGame = true;
    // for(auto& p : pieces ){
    //     p->draw();
    // }
}


void ChessBoard::quitGame(){
    hide();
}


void ChessBoard::goToMainMenu(){
    gameStatus = Status::gameEnded;
    optionsMenu.hide();
    optionsButton.hide();
    goToMainMenubtn.hide();
    menu.show();
}

void ChessBoard::resumeGame(){
    gameStatus = Status::play;
    menu.toogleResume(false);
    menu.hide();
    optionsButton.show();
    updateBoard();
    updateDeadPiecesText();
    for(auto& p : deadPieces){
        p->draw();
    }
    if(AIon){
        writeMessage("AI is on!");
    } else{
        writeMessage("AI is off!");
    }
    for(auto& t : textObjects){
        t->draw();
    }
    if(AIon && turnToogle){
        AImovePiece();
        turnToogle = !turnToogle;
    }

}

void ChessBoard::toogleAI(){
    AIon = !AIon;
    //HardAI = !HardAI;
    menu.toogleAIon(AIon);
    menu.show();
}

