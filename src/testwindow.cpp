#include "testwindow.h"
#include "board.h"
#include "network.h"

testwindow::testwindow(QWidget *parent)
    : QWidget{parent}
{
    this->setWindowTitle("Chat");
    this->setFixedSize(260,200);
    textb.setParent(this);
    connect(Board::getBoard(),&Board::addtext,this,&testwindow::addtst);
    connect(Network::getInstance(),&Network::message,this,&testwindow::addm);
}

void testwindow::addtst(Pos p,QString nob)
{
    QString t=nob+": "+QString::number(p.first)+","+QString::number(p.second);
    this->textb.append(t);
}

void testwindow::addm(QString nob)
{
    this->textb.append(nob);
}

