#ifndef TESTWINDOW_H
#define TESTWINDOW_H

#include <QWidget>
#include <QTextBrowser>

using Pos = std::pair<int, int>;

class testwindow : public QWidget
{
    Q_OBJECT
public:
    explicit testwindow(QWidget *parent = nullptr);
    QTextBrowser textb;
    QString oppid;
    void addtst(Pos p,QString nob);
    void addm(QString nob);
};

#endif // TESTWINDOW_H
