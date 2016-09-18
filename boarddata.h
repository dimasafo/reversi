#ifndef _BOARDDATA_H_
#define _BOARDDATA_H_


#include "err.h"
#include "idcell.h"
#include "playerid.h"

#include <map>
#include <vector>

class BoardData
{
public:
    typedef std::map<int, PlayerId*> TDLine;
    typedef std::map<int, TDLine> TDBoard;

    BoardData(int rows, int columns);
    ~BoardData();

    bool isPlayer(IdCell cell, const PlayerId* const player) const;

    bool isAnotherPlayer(IdCell cell, const PlayerId* const player) const;

    const PlayerId* const getPlayer(IdCell cell) const;

    bool isEmpty(IdCell cell) const;

    void setPlayer(IdCell cell, const PlayerId* const player);

    void setEmpty(IdCell cell);

    int getColumns() const;

    int getRows() const;

    bool isCellInCorner(IdCell& cell) const;

    bool isCellOnBorder(IdCell& cell) const;

    bool isCellNearCorner(IdCell& cell) const;

    bool isCellNearBorder(IdCell& cell) const;

    int allCells() const;

    int playerCells(const PlayerId* const player) const;

    //////////////////////////////////////////////////////////////////////////////////////////

    enum Direction
    {
        TOP,
        BOTTOM,
        LEFT,
        RIGHT,
        TOP_RIGHT,
        TOP_LEFT,
        BOTTOM_RIGHT,
        BOTTOM_LEFT
    };

    /*
    struct Direction_base
    {
        virtual IdCell incCell(IdCell cell) = 0;
        Direction type;
    };

    struct Direction2
    {


        struct Top : Direction_base
        {
            virtual IdCell incCell(IdCell cell)
            {
                //TODO!
                return cell;
            }
        };

        struct Bottom : Direction_base
        {
            virtual IdCell incCell(IdCell cell)
            {
                //TODO!
                return cell;
            }
        };

        struct Left : Direction_base
        {
            virtual IdCell incCell(IdCell cell)
            {
                //TODO!
                return cell;
            }
        };

        struct Right : Direction_base
        {
            virtual IdCell incCell(IdCell cell)
            {
                //TODO!
                return cell;
            }
        };

        struct TopRight : Direction_base
        {
            virtual IdCell incCell(IdCell cell)
            {
                //TODO!
                return cell;
            }
        };

        struct TopLeft : Direction_base
        {
            virtual IdCell incCell(IdCell cell)
            {
                //TODO!
                return cell;
            }
        };

        struct BottomRight : Direction_base
        {
            virtual IdCell incCell(IdCell cell)
            {
                //TODO!
                return cell;
            }
        };

        struct BottomLeft : Direction_base
        {
            virtual IdCell incCell(IdCell cell)
            {
                //TODO!
                return cell;
            }
        };
    };
    */


    //////////////////////////////////////////////////////////////////////////////////////////

    class BoardDataIterator
    {
    public:
        BoardDataIterator(Direction direction, IdCell cellStart, const BoardData& board);

        BoardDataIterator(const BoardDataIterator& src);

        bool canInc();

        BoardDataIterator& operator++(); //preffix

        BoardDataIterator operator++(int); //postfix

        IdCell operator*();

        const IdCell& startCell();

        const BoardData& board_;
        const Direction direction_;
        const IdCell cellStart_;
        IdCell currentCell_;

    private:
        IdCell inc();
    };

    BoardDataIterator dataIt(Direction direction, IdCell cellStart);

private:
    TDBoard board_;

    int maxLineItems_;
    int maxRows_;
};


#endif //_BOARDDATA_H_
