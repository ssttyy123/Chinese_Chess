#include "piece.h"
#include "board.h"
#include "algorithms.h"

using Type = Piece::PieceType;

const std::map<Type, wchar_t> Piece::dict = {
    { Type::RED_SHUAI, L'帥' },
    { Type::BLACK_JIANG, L'將' },
    { Type::RED_SHI, L'仕' },
    { Type::BLACK_SHI, L'士' },
    { Type::RED_XIANG, L'相' },
    { Type::BLACK_XIANG, L'象' },
    { Type::RED_MA, L'馬' },
    { Type::BLACK_MA, L'馬' },
    { Type::RED_JU, L'車' },
    { Type::BLACK_JU, L'車' },
    { Type::RED_PAO, L'炮' },
    { Type::BLACK_PAO, L'炮' },
    { Type::RED_BING, L'兵' },
    { Type::BLACK_ZU, L'卒' }
};
//函数参数x,y为移动后参数
bool JiangShuai::isBasicMove(int x, int y) const
{
    if(getSide(type) == Board::getBoard()->side()){
        if((abs(x-this->x) + abs(y-this->y))==1 && x<=6 && x>=4 && y<=3 && y>=1){
            return true;
        }
        else{
            return false;
        }
    }
    else{
        if((abs(x-this->x) + abs(y-this->y))==1 && x<=6 && x>=4 && y<=10 && y>=8){
            return true;
        }
        else{
            return false;
        }
    }

}

bool JiangShuai::isValidMove(int x, int y) const
{
    if(Piece::isValidMove(x,y)){
        //吃子
        if(Board::getBoard()->find(x,y).front().second != PieceType::NONE){
            if((Board::getBoard()->find(x,y).front().second > PieceType::NONE && type > PieceType::NONE) || (Board::getBoard()->find(x,y).front().second < PieceType::NONE && type < PieceType::NONE)){
                //不能吃本方子
                return false;
            }
            else{
                return true;
            }
        }
        //移动
        else if(Board::getBoard()->find(x,y).front().second == PieceType::NONE){
            return true;
        }
    }
}

const std::list<Pos> JiangShuai::getPossibleMoves(const std::list<std::pair<Pos, Piece::PieceType>>& pieces) const
{
    std::list<Pos> r;
    int pec[4][2]={{1,0},{-1,0},{0,1},{0,-1}};
    for(int i=0;i<4;i++){
        if(Piece::isValidMove(this->x+pec[i][0],this->y+pec[i][1])){
            std::pair<Pos, Piece::PieceType> poit=Algorithms::find(pieces,std::pair(this->x+pec[i][0],this->y+pec[i][1]));
            if(poit.second != PieceType::NONE){
                if((poit.second > PieceType::NONE && type > PieceType::NONE) || (poit.second < PieceType::NONE && type < PieceType::NONE)){
                    //不能吃本方子
                    continue;
                }
                else{
                    r.push_back(poit.first);
                }
            }
            //移动
            else if(poit.second == PieceType::NONE){
                r.push_back(poit.first);
            }
        }
    }
    return r;
}

bool Shi::isBasicMove(int x, int y) const
{
    if(getSide(type) == Board::getBoard()->side()){
        if(abs(x-this->x)==1 && abs(y-this->y)==1 && x<=6 && x>=4 && y<=3 && y>=1){
            return true;
        }
        else{
            return false;
        }
    }
    else{
        if(abs(x-this->x)==1 && abs(y-this->y)==1 && x<=6 && x>=4 && y<=10 && y>=8){
            return true;
        }
        else{
            return false;
        }
    }
}

bool Shi::isValidMove(int x, int y) const
{
    if(Piece::isValidMove(x,y)){
        //吃子
        if(Board::getBoard()->find(x,y).front().second != PieceType::NONE){
            if((Board::getBoard()->find(x,y).front().second > PieceType::NONE && type > PieceType::NONE) || (Board::getBoard()->find(x,y).front().second < PieceType::NONE && type < PieceType::NONE)){
                //不能吃本方子
                return false;
            }
            else{
                return true;
            }
        }
        else if(Board::getBoard()->find(x,y).front().second == PieceType::NONE){
            return true;
        }
    }
}

const std::list<Pos> Shi::getPossibleMoves(const std::list<std::pair<Pos, Piece::PieceType>>& pieces) const
{
    std::list<Pos> r;
    int pec[4][2]={{1,1},{-1,-1},{-1,1},{1,-1}};
    for(int i=0;i<4;i++){
        if(Piece::isValidMove(this->x+pec[i][0],this->y+pec[i][1])){
            std::pair<Pos, Piece::PieceType> poit=Algorithms::find(pieces,std::pair(this->x+pec[i][0],this->y+pec[i][1]));
            //吃子
            if(poit.second != PieceType::NONE){
                if((poit.second > PieceType::NONE && type > PieceType::NONE) || (poit.second < PieceType::NONE && type < PieceType::NONE)){
                    //不能吃本方子
                    continue;
                }
                else{
                    r.push_back(poit.first);
                }
            }
            else if(poit.second == PieceType::NONE){
                r.push_back(poit.first);
            }
        }
    }
    return r;
}

bool Xiang::isBasicMove(int x, int y) const{
    qDebug()<<"x:"<<(int)(abs(x-this->x)==2 && abs(y-this->y)==2);
    qDebug()<<"y:"<<y-this->y;
    if(abs(x-this->x)==2 && abs(y-this->y)==2){
        if(getSide(type) == Board::getBoard()->side()){
            if(x<=9 && x>=1 && y<=5 && y>=1){
                return true;
            }
            else{
                return false;
            }
        }
        else{
            if(x<=9 && x>=1 && y<=10 && y>=6){
                return true;
            }
            else{
                return false;
            }
        }
    }
    else{
        return false;
    }
}

bool Xiang::isValidMove(int x, int y) const
{
    if(Piece::isValidMove(x,y)){
        //是否别腿
        qDebug()<<"abc"<<std::pair((x+this->x)/2,(y+this->y)/2)<<"   "<<(int)Board::getBoard()->find((x+this->x)/2,(y+this->y)/2).front().second;
        if(Board::getBoard()->find((x+this->x)/2,(y+this->y)/2).front().second == PieceType::NONE){
            //吃子
            if(Board::getBoard()->find(x,y).front().second != PieceType::NONE){
                if((Board::getBoard()->find(x,y).front().second > PieceType::NONE && type > PieceType::NONE) || (Board::getBoard()->find(x,y).front().second < PieceType::NONE && type < PieceType::NONE)){
                    //不能吃本方子
                    return false;
                }
                else{
                    return true;
                }
            }
            else if(Board::getBoard()->find(x,y).front().second == PieceType::NONE){
                return true;
            }
        }
        else{
            return false;
        }
    }
}

const std::list<Pos> Xiang::getPossibleMoves(const std::list<std::pair<Pos, Piece::PieceType>>& pieces) const
{
    std::list<Pos> r;
    int pec[4][2]={{2,2},{-2,-2},{-2,2},{2,-2}};
    for(int i=0;i<4;i++){
        if(Piece::isValidMove(this->x+pec[i][0],this->y+pec[i][1])){
            std::pair<Pos, Piece::PieceType> poit=Algorithms::find(pieces,std::pair(this->x+pec[i][0],this->y+pec[i][1]));
            //是否别腿
            if(Algorithms::find(pieces,std::pair((x+this->x)/2,(y+this->y)/2)).second == PieceType::NONE){
                //吃子
                if(poit.second != PieceType::NONE){
                    if((poit.second > PieceType::NONE && type > PieceType::NONE) || (poit.second < PieceType::NONE && type < PieceType::NONE)){
                        //不能吃本方子
                        continue;
                    }
                    else{
                        r.push_back(poit.first);
                    }
                }
                else if(poit.second == PieceType::NONE){
                    r.push_back(poit.first);
                }
            }
        }
    }
    return r;
}

bool Ma::isBasicMove(int x, int y) const
{
    if((abs(x-this->x)+abs(y-this->y))==3 && abs(x-this->x)!=3 && abs(y-this->y)!=3){
        if(x<=9 && x>=1 && y<=10 && y>=1){
            return true;
        }
        else {
            return false;
        }
    }
    else{
        return false;
    }
}

bool Ma::isValidMove(int x, int y) const
{
    if(Piece::isValidMove(x,y)){
        //是否别腿
        int bx = 0,by = 0;
        if(abs(x-this->x)==2){
            bx=(x+this->x)/2;
            by=this->y;
        }
        else if(abs(y-this->y)==2){
            by=(y+this->y)/2;
            bx=this->x;
        }
        if(Board::getBoard()->find(bx,by).front().second == PieceType::NONE){
            //吃子
            if(Board::getBoard()->find(x,y).front().second != PieceType::NONE){
                if((Board::getBoard()->find(x,y).front().second > PieceType::NONE && type > PieceType::NONE) || (Board::getBoard()->find(x,y).front().second < PieceType::NONE && type < PieceType::NONE)){
                    //不能吃本方子
                    return false;
                }
                else{
                    return true;
                }
            }
            else if(Board::getBoard()->find(x,y).front().second == PieceType::NONE){
                return true;
            }
        }
        else{
            return false;
        }
    }
}

const std::list<Pos> Ma::getPossibleMoves(const std::list<std::pair<Pos, Piece::PieceType>>& pieces) const
{
    std::list<Pos> r;
    int pec[8][2]={{2,1},{2,-1},{-2,1},{-2,-1},{1,2},{1,-2},{-1,2},{-1,-2}};
    for(int i=0;i<8;i++){
        if(Piece::isValidMove(this->x+pec[i][0],this->y+pec[i][1])){
            std::pair<Pos, Piece::PieceType> poit=Algorithms::find(pieces,std::pair(this->x+pec[i][0],this->y+pec[i][1]));
            //是否别腿
            int bx = 0,by = 0;
            if(abs(x-this->x)==2){
                bx=(x+this->x)/2;
                by=this->y;
            }
            else if(abs(y-this->y)==2){
                by=(y+this->y)/2;
                bx=this->x;
            }
            if(Algorithms::find(pieces,std::pair(bx,by)).second == PieceType::NONE){
                //吃子
                if(poit.second != PieceType::NONE){
                    if((poit.second > PieceType::NONE && type > PieceType::NONE) || (poit.second < PieceType::NONE && type < PieceType::NONE)){
                        //不能吃本方子
                        continue;
                    }
                    else{
                        r.push_back(poit.first);
                    }
                }
                else if(poit.second == PieceType::NONE){
                    r.push_back(poit.first);
                }
            }
        }
    }
    return r;
}

bool Ju::isBasicMove(int x, int y) const
{
    if((x==this->x && y!=this->y) || (x!=this->x && y==this->y)){
        if(x<=9 && x>=1 && y<=10 && y>=1){
            return true;
        }
        else{
            return false;
        }
    }
    else{
        return false;
    }
}

bool Ju::isValidMove(int x, int y) const
{
    if(Piece::isValidMove(x,y)){
        //路径上是否有其他子F:有,T:无
        bool r=true;
        if(x==this->x){
            if(y>this->y){
                for(int i=this->y+1;i<y;i++){
                    if(Board::getBoard()->find(x,i).front().second != PieceType::NONE){
                        r=false;
                        break;
                    }
                }
            }
            else if(y<this->y){
                for(int i=this->y-1;i>y;i--){
                    if(Board::getBoard()->find(x,i).front().second != PieceType::NONE){
                        r=false;
                        break;
                    }
            }
            }
        }
        else if(y==this->y){
            if(x>this->x){
                for(int i=this->x+1;i<x;i++){
                    if(Board::getBoard()->find(i,y).front().second != PieceType::NONE){
                        r=false;
                        break;
                    }
                }
            }
            else if(x<this->x){
                for(int i=this->x-1;i>x;i--){
                    if(Board::getBoard()->find(i,y).front().second != PieceType::NONE){
                        r=false;
                        break;
                    }
                }
            }
        }
        if(r){
            //吃子
            if(Board::getBoard()->find(x,y).front().second != PieceType::NONE){
                if((Board::getBoard()->find(x,y).front().second > PieceType::NONE && type > PieceType::NONE) || (Board::getBoard()->find(x,y).front().second < PieceType::NONE && type < PieceType::NONE)){
                    //不能吃本方子
                    return false;
                }
                else{
                    return true;
                }
            }
            else if(Board::getBoard()->find(x,y).front().second == PieceType::NONE){
                return true;
            }
        }
        else{
            return false;
        }
    }

}

const std::list<Pos> Ju::getPossibleMoves(const std::list<std::pair<Pos, Piece::PieceType>>& pieces) const
{
    std::list<Pos> r;
    //x轴变化
    for(int i=1;this->x+i<=9;i++){
        if(Piece::isValidMove(this->x+i,this->y)){
            std::pair<Pos, Piece::PieceType> poit=Algorithms::find(pieces,std::pair(this->x+i,this->y));
            if(poit.second != PieceType::NONE){
                if((poit.second>PieceType::NONE && this->type<PieceType::NONE) || (poit.second<PieceType::NONE && this->type>PieceType::NONE)){
                    r.push_back(poit.first);
                }
                break;
            }
            else if(poit.second == PieceType::NONE){
                r.push_back(poit.first);
            }
        }
    }
    for(int i=-1;this->x+i>=1;i--){
        if(Piece::isValidMove(this->x+i,this->y)){
            std::pair<Pos, Piece::PieceType> poit=Algorithms::find(pieces,std::pair(this->x+i,this->y));
            if(poit.second != PieceType::NONE){
                if((poit.second>PieceType::NONE && this->type<PieceType::NONE) || (poit.second<PieceType::NONE && this->type>PieceType::NONE)){
                    r.push_back(poit.first);
                }
                break;
            }
            else if(poit.second == PieceType::NONE){
                r.push_back(poit.first);
            }
        }
    }
    //y轴变化
    for(int i=1;this->y+i<=10;i++){
        if(Piece::isValidMove(this->x,this->y+i)){
            std::pair<Pos, Piece::PieceType> poit=Algorithms::find(pieces,std::pair(this->x,this->y+i));
            if(poit.second != PieceType::NONE){
                if((poit.second>PieceType::NONE && this->type<PieceType::NONE) || (poit.second<PieceType::NONE && this->type>PieceType::NONE)){
                    r.push_back(poit.first);
                }
                break;
            }
            else if(poit.second == PieceType::NONE){
                r.push_back(poit.first);
            }
        }
    }
    for(int i=-1;this->y+i>=1;i--){
        if(Piece::isValidMove(this->x,this->y+i)){
            std::pair<Pos, Piece::PieceType> poit=Algorithms::find(pieces,std::pair(this->x,this->y+i));
            if(poit.second != PieceType::NONE){
                if((poit.second>PieceType::NONE && this->type<PieceType::NONE) || (poit.second<PieceType::NONE && this->type>PieceType::NONE)){
                    r.push_back(poit.first);
                }
                break;
            }
            else if(poit.second == PieceType::NONE){
                r.push_back(poit.first);
            }
        }
    }
    return r;
}

bool Pao::isBasicMove(int x, int y) const
{
    if((x==this->x && y!=this->y) || (x!=this->x && y==this->y)){
        if(x<=9 && x>=1 && y<=10 && y>=1){
            return true;
        }
        else{
            return false;
        }
    }
    else{
        return false;
    }
}

bool Pao::isValidMove(int x, int y) const
{
    if(Piece::isValidMove(x,y)){
        int sum=0;
        //移动
        if(Board::getBoard()->find(x,y).front().second == PieceType::NONE){
            qDebug()<<"t1";
            if(x==this->x){
                qDebug()<<"t2";
                if(y>this->y){
                    for(int i=this->y+1;i<y;i++){
                        if(Board::getBoard()->find(x,i).front().second != PieceType::NONE){
                            return false;
                        }
                    }
                }
                else if(y<this->y){
                    qDebug()<<"t3";
                    for(int i=this->y-1;i>y;i--){
                        if(Board::getBoard()->find(x,i).front().second != PieceType::NONE){
                            return false;
                        }
                }
                }
            }
            else if(y==this->y){
                if(x>this->x){
                    qDebug()<<"t4";
                    for(int i=this->x+1;i<x;i++){
                        if(Board::getBoard()->find(i,y).front().second != PieceType::NONE){
                            return false;
                        }
                    }
                }
                else if(x<this->x){
                    qDebug()<<"t5";
                    for(int i=this->x-1;i>x;i--){
                        if(Board::getBoard()->find(i,y).front().second != PieceType::NONE){
                            qDebug()<<"abc"<<std::pair(i,y)<<"   "<<(int)Board::getBoard()->find(i,y).front().second;
                            return false;
                        }
                    }
                }
            }
        }
        //吃子
        else if(Board::getBoard()->find(x,y).front().second != PieceType::NONE){
            if((Board::getBoard()->find(x,y).front().second > PieceType::NONE && type > PieceType::NONE) || (Board::getBoard()->find(x,y).front().second < PieceType::NONE && type < PieceType::NONE)){
                //不能吃本方子
                return false;
            }
            else{
                if(x==this->x){
                    if(y>this->y){
                        for(int i=this->y+1;i<y;i++){
                            if(Board::getBoard()->find(x,i).front().second != PieceType::NONE){
                                sum++;
                                if(sum>1){
                                    return false;
                                }
                            }
                        }
                    }
                    else if(y<this->y){
                        for(int i=this->y-1;i>y;i--){
                            if(Board::getBoard()->find(x,i).front().second != PieceType::NONE){
                                sum++;
                                if(sum>1){
                                    return false;
                                }
                            }
                        }
                    }
                }
                else if(y==this->y){
                    if(x>this->x){
                        for(int i=this->x+1;i<x;i++){
                            if(Board::getBoard()->find(i,y).front().second != PieceType::NONE){
                                sum++;
                                if(sum>1){
                                    return false;
                                }
                            }
                        }
                    }
                    else if(x<this->x){
                        for(int i=this->x-1;i>x;i--){
                            if(Board::getBoard()->find(i,y).front().second != PieceType::NONE){
                                sum++;
                                if(sum>1){
                                    return false;
                                }
                            }
                        }
                    }
                }
                if(sum==1){
                    return true;
                }
                else{
                    return false;
                }
            }
        }
    }

}

const std::list<Pos> Pao::getPossibleMoves(const std::list<std::pair<Pos, Piece::PieceType>>& pieces) const
{
    std::list<Pos> r;
    bool mid=true;//无炮架状态
    //x轴变化
    for(int i=1;this->x+i<=9;i++){
        if(Piece::isValidMove(this->x+i,this->y)){
            std::pair<Pos, Piece::PieceType> poit=Algorithms::find(pieces,std::pair(this->x+i,this->y));
            if(poit.second != PieceType::NONE){
                if(mid){
                    mid=false;
                }
                else{
                    if((poit.second>PieceType::NONE && this->type<PieceType::NONE) || (poit.second<PieceType::NONE && this->type>PieceType::NONE)){
                        r.push_back(poit.first);
                    }
                    break;
                }
            }
            else if(poit.second == PieceType::NONE && mid==true){
                r.push_back(poit.first);
            }
        }
    }
    mid=true;
    for(int i=-1;this->x+i>=1;i--){
        if(Piece::isValidMove(this->x+i,this->y)){
            std::pair<Pos, Piece::PieceType> poit=Algorithms::find(pieces,std::pair(this->x+i,this->y));
            if(poit.second != PieceType::NONE){
                if(mid){
                    mid=false;
                }
                else{
                    if((poit.second>PieceType::NONE && this->type<PieceType::NONE) || (poit.second<PieceType::NONE && this->type>PieceType::NONE)){
                        r.push_back(poit.first);
                    }
                    break;
                }
            }
            else if(poit.second == PieceType::NONE && mid==true){
                r.push_back(poit.first);
            }
        }
    }
    mid=true;
    //y轴变化
    for(int i=1;this->y+i<=10;i++){
        if(Piece::isValidMove(this->x,this->y+i)){
            std::pair<Pos, Piece::PieceType> poit=Algorithms::find(pieces,std::pair(this->x,this->y+i));
            if(poit.second != PieceType::NONE){
                if(mid){
                    mid=false;
                }
                else{
                    if((poit.second>PieceType::NONE && this->type<PieceType::NONE) || (poit.second<PieceType::NONE && this->type>PieceType::NONE)){
                        r.push_back(poit.first);
                    }
                    break;
                }
            }
            else if(poit.second == PieceType::NONE && mid==true){
                r.push_back(poit.first);
            }
        }
    }
    mid=true;
    for(int i=-1;this->y+i>=1;i--){
        if(Piece::isValidMove(this->x,this->y+i)){
            std::pair<Pos, Piece::PieceType> poit=Algorithms::find(pieces,std::pair(this->x,this->y+i));
            if(poit.second != PieceType::NONE){
                if(mid){
                    mid=false;
                }
                else{
                    if((poit.second>PieceType::NONE && this->type<PieceType::NONE) || (poit.second<PieceType::NONE && this->type>PieceType::NONE)){
                        r.push_back(poit.first);
                    }
                    break;
                }
            }
            else if(poit.second == PieceType::NONE && mid==true){
                r.push_back(poit.first);
            }
        }
    }
    return r;
}

bool BingZu::isBasicMove(int x, int y) const
{
    if(getSide(type) == Board::getBoard()->side()){
       if(this->y<=5){
           //未过河
           if(x==this->x && y-this->y==1){
               return true;
           }
           else{
               return false;
           }
       }
       else if(this->y>=6){
           //过河
           if((x==this->x && y-this->y==1) || (abs(x-this->x)==1 && y==this->y)){
               if(x>=1 && x<=9 && y<=10 && y>=6){
                   return true;
               }
               else{
                   return false;
               }
           }
           else{
               return false;
           }
       }
    }
    else{
        if(this->y>=6){
            //未过河
            if(x==this->x && y-this->y==-1){
                return true;
            }
            else{
                return false;
            }
        }
        else if(this->y<=5){
            //过河
            if((x==this->x && y-this->y==-1) || (abs(x-this->x)==1 && y==this->y)){
                if(x>=1 && x<=9 && y<=5 && y>=1){
                    return true;
                }
                else{
                    return false;
                }
            }
            else{
                return false;
            }
        }
    }
}

bool BingZu::isValidMove(int x, int y) const
{
    if(Piece::isValidMove(x,y)){
        //吃子
        if(!Board::getBoard()->find(x,y).empty()){
            if(((int)Board::getBoard()->find(x,y).front().second > 0 && (int)type > 0) || ((int)Board::getBoard()->find(x,y).front().second < 0 && (int)type < 0)){
                //不能吃本方子
                return false;
            }
            else{
                return true;
            }
        }
        //移动
        else{
            return true;
        }
    }
}

const std::list<Pos> BingZu::getPossibleMoves(const std::list<std::pair<Pos, Piece::PieceType>>& pieces) const
{
    std::list<Pos> r;
    int pec[4][2]={{1,0},{-1,0},{0,1},{0,-1}};
    for(int i=0;i<4;i++){
        if(Piece::isValidMove(this->x+pec[i][0],this->y+pec[i][1])){
            std::pair<Pos, Piece::PieceType> poit=Algorithms::find(pieces,std::pair(this->x+pec[i][0],this->y+pec[i][1]));
            if(poit.second != PieceType::NONE){
                if((poit.second > PieceType::NONE && type > PieceType::NONE) || (poit.second < PieceType::NONE && type < PieceType::NONE)){
                    //不能吃本方子
                    continue;
                }
                else{
                    r.push_back(poit.first);
                }
            }
            //移动
            else if(poit.second == PieceType::NONE){
                r.push_back(poit.first);
            }
        }
    }
    return r;
}

bool Piece::noThreat(int x, int y) const
{
    std::list<std::pair<Pos, Piece::PieceType>> boardbuffer = Board::getBoard()->find(-1,-1);
    std::list<std::pair<Pos, Piece::PieceType>>::iterator it=boardbuffer.begin();
    for(;it!=boardbuffer.end();it++){
        if(it->first==std::pair(std::pair(x,y))){
            boardbuffer.erase(it);
            break;
        }
    }
    it=boardbuffer.begin();
    for(;it!=boardbuffer.end();it++){
        if(it->second==this->type){
            boardbuffer.erase(it);
            boardbuffer.push_back(std::pair(std::pair(x,y),this->type));
            break;
        }
    }
    return !Algorithms::isCheck(boardbuffer,side());
}
