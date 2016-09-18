#include "gochoice.h"


GoChoice::GoChoice(IdCell cell, int cellsChanged, const BoardData& board)
    : cell_(cell)
    , cellsChanged_(cellsChanged)
{
    if(cellsChanged_)
    {
        corner_ = board.isCellInCorner(cell);
        onBorder_ = board.isCellOnBorder(cell);

        //nearBorder_ = board.isCellNearBorder(cell);
        nearBorder_ = false;
        nearCorner_ = board.isCellNearCorner(cell);
    }
}

GoChoice::GoChoice(const GoChoice& src)
    : cell_(src.cell_)
{
    this->operator=(src);
}

GoChoice& GoChoice::operator=(const GoChoice& src)
{
    if(&src == this)
        return *this;

    this->cell_ = src.cell_;
    this->cellsChanged_ = src.cellsChanged_;
    this->corner_ = src.corner_;
    this->onBorder_ = src.onBorder_;
    this->nearBorder_ = src.nearBorder_;
    this->nearCorner_ = src.nearCorner_;
}

bool GoChoice::isEmpty() const
{
    return cellsChanged_ <= 0;
}

int GoChoice::getCellsChenged() const
{
    return cellsChanged_;
}

bool GoChoice::operator<(const GoChoice& choice) const
{
    if(!this->corner_ && choice.corner_)
    {
        return true;
    }
    else
    {
        if(this->corner_ == choice.corner_)
        {
            if(this->nearCorner_ && !choice.nearCorner_)
            {
                return true;
            }
            else
            {
                if(this->nearCorner_ == choice.nearCorner_)
                {
                    if(!this->onBorder_ && choice.onBorder_)
                    {
                        return true;
                    }
                    else
                    {
                        if(this->onBorder_ == choice.onBorder_)
                        {
                            if(this->nearBorder_ && !choice.nearBorder_)
                            {
                                return true;
                            }
                            else
                            {
                                if(this->nearBorder_ == choice.nearBorder_)
                                {
                                    if(this->cellsChanged_ < choice.cellsChanged_)
                                    {
                                        return true;
                                    }
                                    else
                                    {
                                        if(this->cellsChanged_ == choice.cellsChanged_)
                                        {
                                            if(this->cell_ < choice.cell_)
                                            {
                                                return true;
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    return false;
}

IdCell GoChoice::getCell() const
{
    return cell_;
}
