#include "board.h"
#include "algorithms.h"

using Type = Piece::PieceType;

Board::Board() {
    //Add your own code below
    //////////////////////////


    //////////////////////////
}

void Board::judgeStatus() {
    if (Algorithms::isStalemate(side()))
        return emit win(!side());
    if (Algorithms::isStalemate(!side()))
        return emit win(side());
    //Add your own code below
    //////////////////////////


    //////////////////////////
}

void Board::onSetup(Cell** cells) {
    move_sound->setSource(QUrl::fromLocalFile(":/sound/move.wav"));
    move_sound->setVolume(1.0);
    victory_sound->setSource((QUrl::fromLocalFile(":/sound/victory.wav")));
    victory_sound->setVolume(1.0);
    for (int i = 0; i < 10 * 9; i++) {
        auto& cell = cells[i];
        this->cells.emplace(std::piecewise_construct, std::tuple(cell->x, cell->y), std::tuple(cell));
        connect(cell,&Cell::click,this,&Board::onClick);
    }
    std::map<Type, Constructor> factory = {
        //请将nullptr替换为'new ClassName(x, y, side)'，请正确设置派生类构造函数参数
        { Type::JIANG_SHUAI, [](int x, int y, bool side)->const Piece* {
                if(!side)
                    return new JiangShuai(x,y,Type::BLACK_JIANG);
                else{
                    return new JiangShuai(x,y,Type::RED_SHUAI);
              }
          } },
        { Type::SHI, [](int x, int y, bool side)->const Piece* {
              if(!side)
                  return new Shi(x,y,Type::BLACK_SHI);
              else{
                  return new Shi(x,y,Type::RED_SHI);
            }
          } },
        { Type::XIANG, [](int x, int y, bool side)->const Piece* {
              if(!side)
                  return new Xiang(x,y,Type::BLACK_XIANG);
              else{
                  return new Xiang(x,y,Type::RED_XIANG);
            }
          } },
        { Type::MA, [](int x, int y, bool side)->const Piece* {
              if(!side)
                  return new Ma(x,y,Type::BLACK_MA);
              else{
                  return new Ma(x,y,Type::RED_MA);
            }
          } },
        { Type::JU, [](int x, int y, bool side)->const Piece* {
              if(!side)
                  return new Ju(x,y,Type::BLACK_JU);
              else{
                  return new Ju(x,y,Type::RED_JU);
            }
          } },
        { Type::PAO, [](int x, int y, bool side)->const Piece* {
              if(!side)
                  return new Pao(x,y,Type::BLACK_PAO);
              else{
                  return new Pao(x,y,Type::RED_PAO);
            }
          } },
        { Type::BING_ZU, [](int x, int y, bool side)->const Piece* {
                if(!side)
                    return new BingZu(x,y,Type::BLACK_ZU);
                else{
                    return new BingZu(x,y,Type::RED_BING);
              }
          } }
    };
    setPieces(factory);
    for (const auto& [pos, piece] : pieces){
        this->cells[pos]->change(piece);
    }
    if (side()) 
        your_turn = true;

    //Add your own code below
    //////////////////////////

    //////////////////////////
}

void Board::setPieces(const std::map<Type, Constructor> & factory) {
    static std::list<std::pair<Pos, Type>> piece_list = {
        { { 1, 1 }, Type::RED_JU },
        { { 2, 1 }, Type::RED_MA },
        { { 3, 1 }, Type::RED_XIANG },
        { { 4, 1 }, Type::RED_SHI },
        { { 5, 1 }, Type::RED_SHUAI },
        { { 6, 1 }, Type::RED_SHI },
        { { 7, 1 }, Type::RED_XIANG },
        { { 8, 1 }, Type::RED_MA },
        { { 9, 1 }, Type::RED_JU },
        { { 2, 3 }, Type::RED_PAO },
        { { 8, 3 }, Type::RED_PAO },
        { { 1, 4 }, Type::RED_BING },
        { { 3, 4 }, Type::RED_BING },
        { { 5, 4 }, Type::RED_BING },
        { { 7, 4 }, Type::RED_BING },
        { { 9, 4 }, Type::RED_BING },
        { { 1, 10 }, Type::BLACK_JU },
        { { 2, 10 }, Type::BLACK_MA },
        { { 3, 10 }, Type::BLACK_XIANG },
        { { 4, 10 }, Type::BLACK_SHI },
        { { 5, 10 }, Type::BLACK_JIANG },
        { { 6, 10 }, Type::BLACK_SHI },
        { { 7, 10 }, Type::BLACK_XIANG },
        { { 8, 10 }, Type::BLACK_MA },
        { { 9, 10 }, Type::BLACK_JU },
        { { 2, 8 }, Type::BLACK_PAO },
        { { 8, 8 }, Type::BLACK_PAO },
        { { 1, 7 }, Type::BLACK_ZU },
        { { 3, 7 }, Type::BLACK_ZU },
        { { 5, 7 }, Type::BLACK_ZU },
        { { 7, 7 }, Type::BLACK_ZU },
        { { 9, 7 }, Type::BLACK_ZU }
    };

    for (const auto& [pos, type] : piece_list){
        pieces.emplace(pos, factory.at(removeSide(type))(pos.first, pos.second,side() == getSide(type)));
    }
}

void Board::move(const Pos from, const Pos to) {
    //emit addtext(from,"move(from)");
    //emit addtext(to,"move(to)");
    if(getSide(pieces[from]->type)==side()){
        emit myMove(from,to);
    }
    const auto piece = pieces.at(from);
    piece->move(to.first, to.second);
    auto cell_from = cells.at(from);
    cell_from->change(nullptr);
    auto cell_to = cells.at(to);
    cell_to->change(piece);
    pieces.erase(from);
    /*显而易见的胜利条件，但是象棋规则一般是以对方无棋可走为胜利条件
    if (pieces.count(to) && removeSide(pieces.at(to)->type) == Type::JIANG_SHUAI)
        emit win(your_turn ? side() : !side());
    */
    pieces[to] = piece;
    move_sound->play();
    judgeStatus();
}

void Board::onClick(int x, int y) {
    std::lock_guard guard(lock);
    static std::shared_ptr<const Piece> selected = nullptr;
    if (!isYourTurn() || isMoved())
        return;
    const auto pos = std::make_pair(x, y);
    if (pieces.count(pos)) {
        const auto& piece = pieces.at(pos);
        if (piece->side() == side()) {
            selected = piece;
            cells.at(pos)->select();
            return;
        }
    }
    if (!selected)
        return;
    if (selected->isValidMove(x, y)) {
        //cells.at(pos)->fineMove();
        move(selected->pos(), pos);
        moved = true;
        your_turn = false;
        selected = nullptr;
    } else
        cells.at(pos)->wrongMove();
}

void Board::onMove(const Pos from, const Pos to) {
    std::lock_guard guard(lock);
    move(from, to);
    your_turn = true;
    moved = false;
}

const std::list<std::pair<Pos, Piece::PieceType>> Board::find(int x, int y, int side) const {
    if(x==-1 && y==-1){
        std::list<std::pair<Pos, Piece::PieceType>> rt;
        for(const auto& [pos, piece] : pieces){
            if(((int)piece->type>0 && side==1) || side==-1){
                rt.push_back(std::pair(pos, piece->type));
            }
            else if((int)piece->type<0 && side==0){
                rt.push_back(std::pair(pos, piece->type));
            }
        }
        if(rt.empty()){
            rt.push_back(std::pair(std::pair(-1,-1),Piece::PieceType::NONE));
        }
        return rt;
    }
    else if(x==-1 && y!=-1){
        std::list<std::pair<Pos, Piece::PieceType>> rt;
        for(int i=1;i<=9;i++){
            Pos res=std::pair(i,y);
            if(side==1 && (int)(*pieces.find(res)->second).type>0){
                rt.push_back(std::pair(res, (*pieces.find(res)->second).type));
            }
            else if(side==0 && (int)(*pieces.find(res)->second).type<0){
                rt.push_back(std::pair(res, (*pieces.find(res)->second).type));
            }
            else if(side==-1){
                rt.push_back(std::pair(res, (*pieces.find(res)->second).type));
            }
        }
        if(rt.empty()){
            rt.push_back(std::pair(std::pair(-1,-1),Piece::PieceType::NONE));
        }
        return rt;
    }
    else if(x!=-1 && y==-1){
        std::list<std::pair<Pos, Piece::PieceType>> rt;
        for(int i=1;i<=12;i++){
            Pos res=std::pair(x,i);
            if(side==1 && (int)(*pieces.find(res)->second).type>0){
                rt.push_back(std::pair(res, (*pieces.find(res)->second).type));
            }
            else if(side==0 && (int)(*pieces.find(res)->second).type<0){
                rt.push_back(std::pair(res, (*pieces.find(res)->second).type));
            }
            else if(side==-1){
                rt.push_back(std::pair(res, (*pieces.find(res)->second).type));
            }
        }
        if(rt.empty()){
            rt.push_back(std::pair(std::pair(-1,-1),Piece::PieceType::NONE));
        }
        return rt;
    }
    else if(x!=-1 && y!=-1){
        Pos res = std::pair(x,y);
        std::list<std::pair<Pos, Piece::PieceType>> rt;
        if(pieces.find(res) == pieces.end()){
            rt.push_back(std::pair(std::pair(-1,-1),Piece::PieceType::NONE));
            return rt;
        }
        else{
            Piece::PieceType type = (*pieces.find(res)->second).type;
            rt.push_back(std::pair(res,type));
            if((int)side==-1){
                return rt;
            }
            else if((int)type>0 && side==1){
                return rt;
            }
            else if((int)type<0 && side==0){
                return rt;
            }
        }
    }
}
