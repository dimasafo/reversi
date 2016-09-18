#ifndef _IDCELL_H_
#define _IDCELL_H_


class IdCell
{
public:
    IdCell(int row, int column);

    IdCell(const IdCell& src);

    IdCell& operator= (const IdCell& src);

    bool operator<(const IdCell& cell) const;

    //bool operator<(IdCell cell) const;

public:
    int row_;
    int column_;
};


#endif //_IDCELL_H_
