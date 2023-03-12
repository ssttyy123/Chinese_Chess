#ifndef CELL_H
#define CELL_H

#include "piece.h"

#include <QPushButton>
#include <QTimer>

class Cell : public QPushButton {
    Q_OBJECT

    static Cell *chosen;
private:
    inline void delayedFade() {
        QTimer::singleShot(500, this, &Cell::fade);
    }
    inline void setBackground(const QColor& color) {
        QPalette style(palette());
        style.setColor(QPalette::Button, color);
        setPalette(style);
    }
    inline void setTextColor(const QColor& color) {
        QPalette style(palette());
        style.setColor(QPalette::ButtonText, color);
        setPalette(style);
    }
    QString qssQstring;
    QString qssSelect;
private slots:
    void fade() {
        if (text() == "+"){
            setFlat(true);
            this->setStyleSheet(QString("QPushButton{background-color:transparent"));
            setTextColor(Qt::black);
        }
        else
            this->setStyleSheet(qssQstring);
    }
public:
    const int x, y;
    Cell(int x, int y);

    inline void change(std::shared_ptr<const Piece> piece = nullptr) {
        if (!piece) {
            setText("+");
            setFlat(true);
            fade();
            return;
        }
        setText(QString(piece->text()));
        if (piece->side()){
            setFlat(false);
            qssQstring="QPushButton{color:red;border-style:solid;border-width:2;border-color:rgb(255,0,0);border-radius:10px;background-color:rgb(255,255,255);}";
            qssSelect="QPushButton{color:red;border-style:solid;border-width:2;border-color:rgb(255,0,0);border-radius:10px;background-color:rgb(0,0,200);}";
            this->setStyleSheet(qssQstring);
            setTextColor(Qt::red);
        }
        else{
            setFlat(false);
            qssQstring="QPushButton{color:black;border-style:solid;border-width:2;border-color:rgb(0,0,0);border-radius:10px;background-color:rgb(255,255,255);}";
            qssSelect="QPushButton{color:white;border-style:solid;border-width:2;border-color:rgb(0,0,0);border-radius:10px;background-color:rgb(0,0,200);}";
            this->setStyleSheet(qssQstring);
            setTextColor(Qt::black);
        }
    }
    inline void select() {
        if (chosen)
            chosen->fade();
        this->setStyleSheet(qssSelect);
        chosen = this;
    }
    inline void wrongMove() {
        setFlat(false);
        this->setStyleSheet(QString("QPushButton{color:black;background-color:rgb(200,0,0);}"));
        delayedFade();
    }
    inline void fineMove() {
        setBackground(Qt::green);
        delayedFade();
        chosen->fade();
        chosen = nullptr;
    }
signals:
    void click(int x, int y);
};

#endif // CELL_H
