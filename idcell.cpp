#include "idcell.h"


IdCell::IdCell(int row, int column)
        : row_(row)
        , column_(column)
{
}

IdCell::IdCell(const IdCell& src)
{
    this->operator=(src);
}

IdCell& IdCell::operator= (const IdCell& src)
{
    if(&src == this)
        return *this;

    this->column_ = src.column_;
    this->row_ = src.row_;

    return *this;
}

bool IdCell::operator<(const IdCell& cell) const
{
    if(this->row_ < cell.row_)
    {
        return true;
    }
    else
    {
        if(this->row_ == cell.row_)
        {
            if(this->column_ < cell.column_)
            {
                return true;
            }
        }
    }

    return false;
}

//bool IdCell::operator<(IdCell cell) const;
