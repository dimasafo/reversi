#ifndef _MY_CHESS_BOARD_H_
#define _MY_CHESS_BOARD_H_

#include <vector>

#include <QWidget>
#include <QMap>
#include <QPair>
#include <QVector>

#include <qdialog.h>
#include <qlabel.h>
#include <QGridLayout>


#include "playerid.h"


#include <map>

////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////

class MyChessBoard : public QWidget
{
    Q_OBJECT

public:
    MyChessBoard(unsigned int xMax, unsigned int yMax, QWidget *parent = 0);
    virtual ~MyChessBoard();

    void clearBoard();

    void setState(int row, int column, const PlayerId* const player);

    void createCells(int rows, int columns);

signals:
    void signalSetEmpty(int, int);
    void signalSetFilled(int, int, int, int, int);

    void signalCellClicked(int, int);

public slots:
    void cellClicked(int, int);

protected:
    void paintEvent(QPaintEvent *event);

private:
    unsigned int xMax_;
    unsigned int yMax_;

    int rows_;
    int columns_;

    QGridLayout* grid_;
};

#endif //_MY_CHESS_BOARD_H_
