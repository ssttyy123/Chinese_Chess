#include "cell.h"

Cell* Cell::chosen = nullptr;

Cell::Cell(int x, int y) : QPushButton("+"), x(x), y(y)
{
    setFlat(true);
    setFixedSize(20, 20);
    fade();
    setAutoFillBackground(true);
    //Add your own code below
    //////////////////////////
    connect(this,&QPushButton::clicked,this,&Cell::select);
    connect(this,&QPushButton::clicked,[=](){
        emit Cell::click(x,y);
    });
    //////////////////////////
}
