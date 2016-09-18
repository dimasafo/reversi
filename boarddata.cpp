#include "boarddata.h"

BoardData::BoardData(int rows, int columns)
    : maxRows_(rows)
    , maxLineItems_(columns)
{
    TDLine emptyLine;

    for(int i = 0; i < maxLineItems_; ++i)
    {
        emptyLine[i] = nullptr;
    }

    for(int i = 0; i < maxRows_; ++i)
    {
        board_[i] = emptyLine;
    }
}

BoardData::~BoardData()
{
}

bool BoardData::isPlayer(IdCell cell, const PlayerId* const player) const
{
    auto itRow = board_.find(cell.row_);
    auto itCell = (itRow->second).find(cell.column_);

    if((itCell->second) == nullptr)
        return false;

    return player->isSame(itCell->second);
}

bool BoardData::isAnotherPlayer(IdCell cell, const PlayerId* const player) const
{
    auto itRow = board_.find(cell.row_);
    auto itCell = (itRow->second).find(cell.column_);

    if((itCell->second) == nullptr)
        return false;

    return !(player->isSame(itCell->second));
}

const PlayerId* const BoardData::getPlayer(IdCell cell) const
{
    auto itRow = board_.find(cell.row_);
    auto itCell = (itRow->second).find(cell.column_);

    return (itCell->second);
}

/*
bool BoardData::isPlayerA(IdCell cell) const
{
    auto itRow = board_.find(cell.row_);
    auto itCell = (itRow->second).find(cell.column_);

    return (itCell->second) == players_[0];
}

bool BoardData::isPlayerB(IdCell cell) const
{
    auto itRow = board_.find(cell.row_);
    auto itCell = (itRow->second).find(cell.column_);

    return (itCell->second) == players_[1];
}
*/

bool BoardData::isEmpty(IdCell cell) const
{
    auto itRow = board_.find(cell.row_);
    auto itCell = (itRow->second).find(cell.column_);

    return (itCell->second) == nullptr;
}

void BoardData::setPlayer(IdCell cell, const PlayerId* const player)
{
    PlayerId* p = const_cast<PlayerId*>(player);

    board_[cell.row_][cell.column_] = p;
}

/*
void BoardData::setPlayerA(IdCell cell)
{
    board_[cell.row_][cell.column_] = players_[0];
}

void BoardData::setPlayerB(IdCell cell)
{
    board_[cell.row_][cell.column_] = players_[1];
}
*/

void BoardData::setEmpty(IdCell cell)
{
    board_[cell.row_][cell.column_] = 0;
}

int BoardData::getColumns() const
{
    return maxLineItems_;
}

int BoardData::getRows() const
{
    return maxRows_;
}

int BoardData::allCells() const
{
    return maxLineItems_ * maxRows_;
}

int BoardData::playerCells(const PlayerId* const player) const
{
    int count = 0;

    for(auto itRow = board_.begin(); itRow != board_.end(); itRow++)
    {
        for(auto itCell = (itRow->second).begin(); itCell != (itRow->second).end(); ++itCell)
        {
            if(itCell->second == player)
                count++;
        }
    }

    return count;
}

bool BoardData::isCellInCorner(IdCell& cell) const
{
    if(
        (cell.row_ == 0 && cell.column_ == 0)
        || (cell.row_ == 0 && cell.column_ == (maxLineItems_ - 1))
        || (cell.row_ == (maxRows_ - 1) && cell.column_ == (maxLineItems_ - 1))
        || (cell.row_ == (maxRows_ - 1) && cell.column_ == 0)
        )
        return true;

    return false;
}

bool BoardData::isCellOnBorder(IdCell& cell) const
{
    if(cell.row_ == 0 || cell.row_ == (maxRows_ - 1))
        return true;

    if(cell.column_ == 0 || cell.column_ == (maxLineItems_ - 1))
        return true;

    return false;
}

bool BoardData::isCellNearCorner(IdCell& cell) const
{
    if(
        (cell.row_ == 1 && cell.column_ == 1)
        ||(cell.row_ == 0 && cell.column_ == 1)
        ||(cell.row_ == 1 && cell.column_ == 0)

        || (cell.row_ == 1 && cell.column_ == (maxLineItems_ - 2))
        || (cell.row_ == 0 && cell.column_ == (maxLineItems_ - 2))
        || (cell.row_ == 1 && cell.column_ == (maxLineItems_ - 1))

        || (cell.row_ == (maxRows_ - 2) && cell.column_ == (maxLineItems_ - 2))
        || (cell.row_ == (maxRows_ - 1) && cell.column_ == (maxLineItems_ - 2))
        || (cell.row_ == (maxRows_ - 1) && cell.column_ == (maxLineItems_ - 1))

        || (cell.row_ == (maxRows_ - 2) && cell.column_ == 1)
        || (cell.row_ == (maxRows_ - 1) && cell.column_ == 1)
        || (cell.row_ == (maxRows_ - 2) && cell.column_ == 0)
        )
        return true;

    return false;
}

bool BoardData::isCellNearBorder(IdCell& cell) const
{
    if(cell.row_ == 1 || cell.row_ == (maxRows_ - 2))
        return true;

    if(cell.column_ == 1 || cell.column_ == (maxLineItems_ - 2))
        return true;

    return false;
}

BoardData::BoardDataIterator BoardData::dataIt(Direction direction, IdCell cellStart)
{
    return BoardDataIterator(direction, cellStart, *this);
}

//////////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////////

BoardData::BoardDataIterator::BoardDataIterator(Direction direction, IdCell cellStart, const BoardData& board)
    : board_(board)
    , direction_(direction)
    , cellStart_(cellStart)
    , currentCell_(cellStart)
{
}

BoardData::BoardDataIterator::BoardDataIterator(const BoardDataIterator& src)
    : board_(src.board_)
    , direction_(src.direction_)
    , cellStart_(src.cellStart_)
    , currentCell_(src.cellStart_)
{
}

bool BoardData::BoardDataIterator::canInc()
{
    IdCell newCell = inc();

    if(newCell.column_ >= board_.getColumns()
        || newCell.row_ >= board_.getRows()
        || newCell.column_ < 0
        || newCell.row_ < 0)
        return false;

    return true;
}

BoardData::BoardDataIterator& BoardData::BoardDataIterator::operator++() //preffix
{
    if(!canInc())
        throw Err();

    currentCell_ = inc();
    return *this;
}

BoardData::BoardDataIterator BoardData::BoardDataIterator::operator++(int) //postfix
{
    if(!canInc())
        throw Err();

    BoardDataIterator copy(*this);
    currentCell_ = inc();
    return copy;
}

IdCell BoardData::BoardDataIterator::operator*()
{
    return currentCell_;
}

const IdCell& BoardData::BoardDataIterator::startCell()
{
    return cellStart_;
}

IdCell BoardData::BoardDataIterator::inc()
{
    IdCell newCell(currentCell_);

    switch (direction_)
    {
        case TOP:
        {
            newCell.row_++;
            break;
        }
        case BOTTOM:
        {
            newCell.row_--;
            break;
        }
        case LEFT:
        {
            newCell.column_--;
            break;
        }
        case RIGHT:
        {
            newCell.column_++;
            break;
        }
        case TOP_RIGHT:
        {
            newCell.row_++;
            newCell.column_++;
            break;
        }
        case TOP_LEFT:
        {
            newCell.row_++;
            newCell.column_--;
            break;
        }
        case BOTTOM_RIGHT:
        {
            newCell.row_--;
            newCell.column_++;
            break;
        }
        case BOTTOM_LEFT:
        {
            newCell.row_--;
            newCell.column_--;
            break;
        }
    };

return newCell;
}
