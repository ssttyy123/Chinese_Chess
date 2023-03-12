#ifndef ALGORITHMS_H
#define ALGORITHMS_H

#include "board.h"

//工具类
class Algorithms {
public:
    //判断僵局(无子可走)
    static bool isStalemate(bool side) {
        auto pieces = Board::getBoard()->find();
        auto result = Board::getBoard()->find(-1, -1, side);

        for (const auto& [pos, type] : result) {
            auto piece = Board::getBoard()->pieces.at(pos);
            if (!piece->getPossibleMoves(pieces).empty())
                return false;
        }
        return true;
    }

    //Piece::noThreat和Algorithms::isCheck的推荐辅助函数
    static inline bool isCheck(const std::list<std::pair<Pos, Piece::PieceType>>& pieces, bool side) {
        std::list<std::pair<Pos, Piece::PieceType>>::const_iterator it=pieces.begin();
        Pos king_pos;
        for(;it!=pieces.end();it++){
            if(abs((int)it->second)==1 && (((int)it->second)>0) == side){
                king_pos=it->first;
                break;
            }
        }
        for(it=pieces.begin();it!=pieces.end();it++){
            //ma
            if(abs((int)it->second)==4 && (((int)it->second)>0) != side){
                int dx=abs(king_pos.first-it->first.first),dy=abs(king_pos.second-it->first.second);
                if(dx+dy == 3 && dx!=3 && dy!=3){
                    if(dx==2){
                        Pos barrier=std::pair((king_pos.first+it->first.first)/2,it->first.second);
                        std::list<std::pair<Pos, Piece::PieceType>>::const_iterator it2=pieces.begin();
                        for(;it2!=pieces.end();it2++){
                            if(it2->first==barrier){
                                break;
                            }
                            else{
                                return true;
                            }
                        }
                    }
                    else if(dy==2){
                        Pos barrier=std::pair(it->first.first,(king_pos.second+it->first.second)/2);
                        std::list<std::pair<Pos, Piece::PieceType>>::const_iterator it2=pieces.begin();
                        for(;it2!=pieces.end();it2++){
                            if(it2->first==barrier){
                                break;
                            }
                            else{
                                return true;
                            }
                        }
                    }
                }
            }
            //ju
            else if(abs((int)it->second)==5 && (((int)it->second)>0) != side){
                bool bet;
                if(king_pos.first==it->first.first){
                    bet=false;
                    std::list<std::pair<Pos, Piece::PieceType>>::const_iterator it2=pieces.begin();
                    int max=std::max(king_pos.second,it->first.second),min=std::min(king_pos.second,it->first.second);
                    for(;it2!=pieces.end();it2++){
                        if(it2->first.first==king_pos.first && it2->first.second<max && it2->first.second>min){
                            bet=true;
                            break;
                        }
                    }
                    if(!bet){
                        return true;
                    }
                }
                else if(king_pos.second==it->first.second){
                    bet=false;
                    std::list<std::pair<Pos, Piece::PieceType>>::const_iterator it2=pieces.begin();
                    int max=std::max(king_pos.first,it->first.first),min=std::min(king_pos.first,it->first.first);
                    for(;it2!=pieces.end();it2++){
                        if(it2->first.second==king_pos.second && it2->first.first<max && it2->first.first>min){
                            bet=true;
                            break;
                        }
                    }
                    if(!bet){
                        return true;
                    }
                }
            }
            //pao
            else if(abs((int)it->second)==6 && (((int)it->second)>0) != side){
                if(king_pos.first==it->first.first){
                    std::list<std::pair<Pos, Piece::PieceType>>::const_iterator it2=pieces.begin();
                    int max=std::max(king_pos.second,it->first.second),min=std::min(king_pos.second,it->first.second);
                    int sum=0;
                    for(;it2!=pieces.end();it2++){
                        if(it2->first.first==king_pos.first && it2->first.second<max && it2->first.second>min){
                            if(sum==0){
                                sum++;
                            }
                            else{
                                sum++;
                                break;
                            }
                        }
                    }
                    if(sum==1){
                        return true;
                    }
                }
                else if(king_pos.second==it->first.second){
                    std::list<std::pair<Pos, Piece::PieceType>>::const_iterator it2=pieces.begin();
                    int max=std::max(king_pos.first,it->first.first),min=std::min(king_pos.first,it->first.first);
                    int sum=0;
                    for(;it2!=pieces.end();it2++){
                        if(it2->first.second==king_pos.second && it2->first.first<max && it2->first.first>min){
                            if(sum==0){
                                sum++;
                            }
                            else{
                                sum++;
                                break;
                            }
                        }
                    }
                    if(sum==1){
                        return true;
                    }
                }
            }
            //bing
            else if(abs((int)it->second)==7 && (((int)it->second)>0) != side){
                int pec[3][2]={{0,1},{1,0},{-1,0}};
                Pos rangeBZ;
                for(int i=0;i<3;i++){
                    rangeBZ=std::pair(it->first.first+pec[i][0],it->first.second+pec[i][1]);
                    if(rangeBZ==king_pos){
                        return true;
                    }
                }
            }

        }
        return false;
    }

    static bool isCheck(bool side) {
        return isCheck(Board::getBoard()->find(), side);
    }

    static inline std::pair<Pos, Piece::PieceType> find(const std::list<std::pair<Pos, Piece::PieceType>>& pieces,Pos pos){
        std::list<std::pair<Pos, Piece::PieceType>>::const_iterator it=pieces.begin();
        for(;it!=pieces.end();it++){
            if(it->first==pos){
                return *it;
            }
        }
        return std::pair(pos,Piece::PieceType(0));
    };
    static inline std::pair<Pos, Piece::PieceType> find(const std::list<std::pair<Pos, Piece::PieceType>>& pieces,Piece::PieceType type){
        std::list<std::pair<Pos, Piece::PieceType>>::const_iterator it=pieces.begin();
        for(;it!=pieces.end();it++){
            if(it->second==type){
                return *it;
            }
        }
        return std::pair(std::pair(-1,-1),type);
    };
};

#endif // ALGORITHMS_H
