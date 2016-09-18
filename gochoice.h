#ifndef _GOCHOICE_H_
#define _GOCHOICE_H_


#include "idcell.h"
#include "boarddata.h"


#include <set>



class GoChoice
{
public:
    GoChoice(IdCell cell_, int cellsChanged, const BoardData& board);
    GoChoice(const GoChoice& src);
    GoChoice& operator=(const GoChoice& src);

    bool operator<(const GoChoice& choice) const;

    bool isEmpty() const;
    int getCellsChenged() const;
    IdCell getCell() const;

private:
    IdCell cell_;
    int cellsChanged_;

    bool corner_;
    bool onBorder_;
    bool nearBorder_;
    bool nearCorner_;
};


#endif //_GOCHOICE_H_
