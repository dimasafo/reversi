

#include <QtGui>
#include <QString>


#include "chessboard.h"
#include "cell.h"
#include "err.h"

#include <string>
#include <fstream>
#include <sstream>

MyChessBoard::MyChessBoard(unsigned int xMax, unsigned int yMax, QWidget *parent)
    : QWidget(parent)
    , xMax_(xMax)
    , yMax_(yMax)
    , grid_(nullptr)
{
    resize(xMax, yMax);

    QPalette Pal(palette());
    Pal.setColor(QPalette::Background, QColor(255, 255, 255));
    this->setAutoFillBackground(true);
    this->setPalette(Pal);

    grid_ = new QGridLayout();
    setLayout(grid_);

    /*
    QGridLayout* grid = new QGridLayout();
    setLayout(grid);

    int cellWidth = 40;
    int span = 2;

    bool dark = false;

    for(int row = 0; row < rows_; row++)
    {
        for(int col = 0; col < columns_; col++)
        {
            QColor color;
            if(!dark)
                color = QColor(102, 62, 49);
            else
                color = QColor(235, 222, 218);

            dark = !dark;

            MyCell* cell = new MyCell(row, col, color, cellWidth, this);
            grid->addWidget(cell, row, col, span, span);

            connect(cell, SIGNAL(signalClicked(int, int)), this, SLOT(cellClicked(int, int)));

            connect(this, SIGNAL(signalSetEmpty(int, int)), cell, SLOT(setEmpty(int, int)));

            connect(this, SIGNAL(signalSetFilled(int, int, int, int, int)), cell, SLOT(setFilled(int, int, int, int, int)));

            emit signalSetEmpty(row, col);
        }

        dark = !dark;
    }
    */
}

MyChessBoard::~MyChessBoard()
{
}

void MyChessBoard::createCells(int rows, int columns)
{
    if(!grid_)
        throw Err();

    QLayoutItem* child;
    while ((child = grid_->takeAt(0)) != 0)
    {
        delete child;
    }

    rows_ = rows;
    columns_ = columns;

    int cellWidth = 40;
    int span = 2;

    bool dark = false;

    for(int row = 0; row < rows_; row++)
    {
        for(int col = 0; col < columns_; col++)
        {
            QColor color;
            if(!dark)
                color = QColor(102, 62, 49);
            else
                color = QColor(235, 222, 218);

            dark = !dark;

            MyCell* cell = new MyCell(row, col, color, cellWidth, this);
            grid_->addWidget(cell, row, col, span, span);

            connect(cell, SIGNAL(signalClicked(int, int)), this, SLOT(cellClicked(int, int)));

            connect(this, SIGNAL(signalSetEmpty(int, int)), cell, SLOT(setEmpty(int, int)));

            connect(this, SIGNAL(signalSetFilled(int, int, int, int, int)), cell, SLOT(setFilled(int, int, int, int, int)));

            emit signalSetEmpty(row, col);
        }

        dark = !dark;
    }
}

void MyChessBoard::paintEvent(QPaintEvent *)
{
    QPainter painter(this);

    painter.setRenderHint(QPainter::Antialiasing);
    painter.translate( 0, 0 ); //начинам с угла экрана

    QColor whiteCol(255, 255, 255);
    QBrush brush(whiteCol, Qt::SolidPattern);
    painter.fillRect(0, 0, xMax_, yMax_, brush);
}

void MyChessBoard::cellClicked(int row, int column)
{
    emit signalCellClicked(row, column);
}

void MyChessBoard::clearBoard()
{
    for(int row = 0; row <= 7; row++)
    {
        for(int col = 0; col <= 7; col++)
        {
            emit signalSetEmpty(row, col);
        }
    }
}

void MyChessBoard::setState(int row, int column, const PlayerId* const player)
{
    if(!player)
        emit signalSetEmpty(row, column);
    else
        emit signalSetFilled(row, column, player->color().r_, player->color().g_, player->color().b_);
}
