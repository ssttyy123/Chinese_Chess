#ifndef PIECE_H
#define PIECE_H

#include <cmath>
#include <list>
#include <map>
#include <QDebug>

#define RED_SIDE true
#define BLACK_SIDE false

using Pos = std::pair<int, int>;

class Piece {   //请不要继承QObject
public:
    mutable int x, y;
    //正数
    enum class PieceType {
        NONE = 0,
        JIANG_SHUAI = 1,
        RED_SHUAI   = 1,    BLACK_JIANG     = -1,
        SHI = 2,
        RED_SHI     = 2,    BLACK_SHI       = -2,
        XIANG = 3,
        RED_XIANG   = 3,    BLACK_XIANG     = -3,
        MA = 4,
        RED_MA      = 4,    BLACK_MA        = -4,
        JU = 5,
        RED_JU      = 5,    BLACK_JU        = -5,
        PAO = 6,
        RED_PAO     = 6,    BLACK_PAO       = -6,
        BING_ZU = 7,
        RED_BING    = 7,    BLACK_ZU        = -7
    } type;
private:
    static const std::map<PieceType, wchar_t> dict;
public:
    static inline wchar_t convert(PieceType type) {
        return dict.at(type);
    }
    inline wchar_t text() const {
        return convert(type);
    }
    inline void move(int x, int y) const {  //请勿修改
        this->x = x;
        this->y = y;
    }
    inline bool side() const {
        return type > PieceType::NONE;
    }
    inline const Pos pos() const {
        return std::make_pair(x, y);
    }
private:
    bool noThreat(int x, int y) const;
    virtual bool isBasicMove(int x, int y) const = 0;
public:
    virtual bool isValidMove(int x, int y) const {
        return isBasicMove(x, y) && noThreat(x, y);
    }
    //参数为当前或假设移动后的棋盘
    virtual const std::list<Pos> getPossibleMoves(const std::list<std::pair<Pos, Piece::PieceType>>& pieces) const = 0;

    Piece(int x, int y, PieceType type) : x(x), y(y), type(type) {}
    virtual ~Piece() {} //虚析构
};

inline Piece::PieceType removeSide(Piece::PieceType type) {
    return (Piece::PieceType)std::abs((int)type);
}

inline bool getSide(Piece::PieceType type) {
    return type > Piece::PieceType::NONE;
}

class JiangShuai:public Piece{
private:
    bool isBasicMove(int x, int y) const;
public:
    bool isValidMove(int x, int y) const;
    const std::list<Pos> getPossibleMoves(const std::list<std::pair<Pos, Piece::PieceType>>& pieces) const;

    JiangShuai(int x,int y,PieceType type):Piece(x,y,type){};
};

class Shi:public Piece{
private:
    bool isBasicMove(int x, int y) const;
public:
    bool isValidMove(int x, int y) const;
    const std::list<Pos> getPossibleMoves(const std::list<std::pair<Pos, Piece::PieceType>>& pieces) const;

    Shi(int x,int y,PieceType type):Piece(x,y,type){};
};

class Xiang:public Piece{
private:
    bool isBasicMove(int x, int y) const;
public:
    bool isValidMove(int x, int y) const;
    const std::list<Pos> getPossibleMoves(const std::list<std::pair<Pos, Piece::PieceType>>& pieces) const;

    Xiang(int x,int y,PieceType type):Piece(x,y,type){};
};

class Ma:public Piece{
private:
    bool isBasicMove(int x, int y) const;
public:
    bool isValidMove(int x, int y) const;
    const std::list<Pos> getPossibleMoves(const std::list<std::pair<Pos, Piece::PieceType>>& pieces) const;

    Ma(int x,int y,PieceType type):Piece(x,y,type){};
};

class Ju:public Piece{
private:
    bool isBasicMove(int x, int y) const;
public:
    bool isValidMove(int x, int y) const;
    const std::list<Pos> getPossibleMoves(const std::list<std::pair<Pos, Piece::PieceType>>& pieces) const;

    Ju(int x,int y,PieceType type):Piece(x,y,type){};
};

class Pao:public Piece{
private:
    bool isBasicMove(int x, int y) const;
public:
    bool isValidMove(int x, int y) const;
    const std::list<Pos> getPossibleMoves(const std::list<std::pair<Pos, Piece::PieceType>>& pieces) const;

    Pao(int x,int y,PieceType type):Piece(x,y,type){};
};

class BingZu:public Piece{
private:
    bool isBasicMove(int x, int y) const;
public:
    bool isValidMove(int x, int y) const;
    const std::list<Pos> getPossibleMoves(const std::list<std::pair<Pos, Piece::PieceType>>& pieces) const;

    BingZu(int x,int y,PieceType type):Piece(x,y,type){};
};

#endif // PIECE_H
