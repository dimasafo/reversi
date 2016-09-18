#include "game.h"


Game::Game(int rows, int columns)
    : boardData_(rows, columns)
    , gameFinished_(false)
{
    players_.push_back(new PlayerA(PlayerId::Color(43, 0, 85), true));
    players_.push_back(new PlayerB(PlayerId::Color(187, 0, 4), false));

    boardData_.setPlayer(IdCell(3,3), players_[Player_A]);
    boardData_.setPlayer(IdCell(3,4), players_[Player_B]);
    boardData_.setPlayer(IdCell(4,4), players_[Player_A]);
    boardData_.setPlayer(IdCell(4,3), players_[Player_B]);

    /*
    boardData_.setPlayer(IdCell(0,0), players_[Player_B]);
    boardData_.setPlayer(IdCell(1,0), players_[Player_B]);
    boardData_.setPlayer(IdCell(0,1), players_[Player_B]);

    boardData_.setPlayer(IdCell(1,2), players_[Player_A]);
    boardData_.setPlayer(IdCell(0,2), players_[Player_A]);
    */
}

Game::~Game()
{
}

////////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////////

int Game::canGoOneDirection(IdCell start, BoardData::Direction direction, const PlayerId* const player)
{
    if(!boardData_.isEmpty(start))
        return 0;

    BoardData::BoardDataIterator it = boardData_.dataIt(direction, start);

    bool checkNear = true; //проверить ближайшую ячейку

    int cellsWalked = 0; //сколько вражеских ячеек можно сьесть

    while(true)
    {
        if(!it.canInc())
            return 0;

        it++;

        IdCell next = *it;

        //если следующая ячейка пустая - нельзя походить
        if(boardData_.isEmpty(next))
            return 0;

        if(checkNear)
        {
            checkNear = false;

            //вторая (соседняя) ячейка обязательно должна принадлежать другому игроку
            if(!boardData_.isAnotherPlayer(next, player))
                return 0;
        }
        else
        {
            //если следующая ячейка такая же как и первая - МОЖНО моходить
            if(boardData_.isPlayer(next, player))
                return cellsWalked;
        }

        ++cellsWalked;
    };
}

////////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////////

GoChoice Game::getGoChoice(IdCell cell, const PlayerId* const player)
{
    //можно походить, если хотя бы по одному из восьми направлений можно походить
    int maxCellsWalked = 0;

    int walked = 0;

    walked = canGoOneDirection(cell, BoardData::Direction::TOP, player);
    maxCellsWalked += walked;

    walked = canGoOneDirection(cell, BoardData::Direction::BOTTOM, player);
    maxCellsWalked += walked;

    walked = canGoOneDirection(cell, BoardData::Direction::RIGHT, player);
    maxCellsWalked += walked;

    walked = canGoOneDirection(cell, BoardData::Direction::LEFT, player);
    maxCellsWalked += walked;

    walked = canGoOneDirection(cell, BoardData::Direction::TOP_RIGHT, player);
    maxCellsWalked += walked;

    walked = canGoOneDirection(cell, BoardData::Direction::TOP_LEFT, player);
    maxCellsWalked += walked;

    walked = canGoOneDirection(cell, BoardData::Direction::BOTTOM_RIGHT, player);
    maxCellsWalked += walked;

    walked = canGoOneDirection(cell, BoardData::Direction::BOTTOM_LEFT, player);
    maxCellsWalked += walked;

    GoChoice choice(cell, maxCellsWalked, boardData_);

    return choice;
}

////////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////////

bool Game::canGo(IdCell cell, const PlayerId* const player)
{
    return !(getGoChoice(cell, player).isEmpty());
}

////////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////////

/*
bool Game::canGoAnywhere(const PlayerId* const player, int& maxCellsWalked, IdCell& cellToGo)
{
    for(int row = 0; row < boardData_.getRows(); row++)
    {
        for(int column = 0; column  < boardData_.getColumns(); column ++)
        {
            //если ячейка непустая - не можем сюда ходить, пропускаем
            if(!boardData_.isEmpty(IdCell(row, column)))
                continue;

            int maxLocalCellsWalked = getGoChoice(IdCell(row, column), player).getCellsChenged();

            if(maxLocalCellsWalked > maxCellsWalked)
            {
                maxCellsWalked = maxLocalCellsWalked;
                cellToGo = IdCell(row, column);
            }
        }
    }

    return (maxCellsWalked > 0);
}
*/

void Game::getAllChoices(const PlayerId* const player, std::set<GoChoice>& res)
{
    res.clear();

    for(int row = 0; row < boardData_.getRows(); row++)
    {
        for(int column = 0; column  < boardData_.getColumns(); column ++)
        {
            GoChoice choice(getGoChoice(IdCell(row, column), player));

            if(!choice.isEmpty())
                res.insert(choice);
        }
    }
}

////////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////////

bool Game::canGoAnywhere(const PlayerId* const player)
{
    std::set<GoChoice> res;

    getAllChoices(player, res);

    return !res.empty();
}

////////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////////

void Game::processComputerGo(const PlayerId* const player)
{
    int maxCellsWalked = 0;
    IdCell cellToGo(0,0); //default

    //canGoAnything(player, maxCellsWalked, cellToGo);

    std::set<GoChoice> res;

    getAllChoices(player, res);

    if(!res.empty())
    {
        Go(res.rbegin()->getCell(), player);
    }
}

////////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////////

void Game::Go(IdCell cell, const PlayerId* const player)
{
    if(!canGo(cell, player))
        throw Err();

    int walked = 0;

    walked = canGoOneDirection(cell, BoardData::Direction::TOP, player);
    if(walked > 0)
    {
        BoardData::BoardDataIterator it = boardData_.dataIt(BoardData::Direction::TOP, cell);

        for(int i = 1; i <= walked; i++)
        {
            ++it;
            IdCell next = *it;
            boardData_.setPlayer(next, player);
        }
    }

    walked = canGoOneDirection(cell, BoardData::Direction::BOTTOM, player);
    if(walked > 0)
    {
        BoardData::BoardDataIterator it = boardData_.dataIt(BoardData::Direction::BOTTOM, cell);

        for(int i = 1; i <= walked; i++)
        {
            ++it;
            IdCell next = *it;
            boardData_.setPlayer(next, player);
        }
    }

    walked = canGoOneDirection(cell, BoardData::Direction::RIGHT, player);
    if(walked > 0)
    {
        BoardData::BoardDataIterator it = boardData_.dataIt(BoardData::Direction::RIGHT, cell);

        for(int i = 1; i <= walked; i++)
        {
            ++it;
            IdCell next = *it;
            boardData_.setPlayer(next, player);
        }
    }

    walked = canGoOneDirection(cell, BoardData::Direction::LEFT, player);
    if(walked > 0)
    {
        BoardData::BoardDataIterator it = boardData_.dataIt(BoardData::Direction::LEFT, cell);

        for(int i = 1; i <= walked; i++)
        {
            ++it;
            IdCell next = *it;
            boardData_.setPlayer(next, player);
        }
    }

    walked = canGoOneDirection(cell, BoardData::Direction::TOP_RIGHT, player);
    if(walked > 0)
    {
        BoardData::BoardDataIterator it = boardData_.dataIt(BoardData::Direction::TOP_RIGHT, cell);

        for(int i = 1; i <= walked; i++)
        {
            ++it;
            IdCell next = *it;
            boardData_.setPlayer(next, player);
        }
    }

    walked = canGoOneDirection(cell, BoardData::Direction::TOP_LEFT, player);
    if(walked > 0)
    {
        BoardData::BoardDataIterator it = boardData_.dataIt(BoardData::Direction::TOP_LEFT, cell);

        for(int i = 1; i <= walked; i++)
        {
            ++it;
            IdCell next = *it;
            boardData_.setPlayer(next, player);
        }
    }

    walked = canGoOneDirection(cell, BoardData::Direction::BOTTOM_RIGHT, player);
    if(walked > 0)
    {
        BoardData::BoardDataIterator it = boardData_.dataIt(BoardData::Direction::BOTTOM_RIGHT, cell);

        for(int i = 1; i <= walked; i++)
        {
            ++it;
            IdCell next = *it;
            boardData_.setPlayer(next, player);
        }
    }

    walked = canGoOneDirection(cell, BoardData::Direction::BOTTOM_LEFT, player);
    if(walked > 0)
    {
        BoardData::BoardDataIterator it = boardData_.dataIt(BoardData::Direction::BOTTOM_LEFT, cell);

        for(int i = 1; i <= walked; i++)
        {
            ++it;
            IdCell next = *it;
            boardData_.setPlayer(next, player);
        }
    }

    boardData_.setPlayer(cell, player);


    jumpToNextPlayer();
}

////////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////////
void Game::jumpToNextPlayer()
{
    const PlayerId* const player = players_.getCurrentPlayer();

    while(true)
    {
        players_.setNextPlayer();

        if(players_.getCurrentPlayer() == player)
            break;

        if(this->canGoAnywhere(getCurrentPlayer()))
            break;
    }

    if(players_.getCurrentPlayer() == player)
    {
        if(!this->canGoAnywhere(getCurrentPlayer()))
            gameFinished_ = true;
    }
}

////////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////////

const BoardData* const Game::boardData() const
{
    return &boardData_;
}

////////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////////
const Players* const Game::players() const
{
    return &players_;
}

////////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////////
/*
const PlayerId* const Game::getPlayer(Pls playerNum) const
{
    return players_[playerNum];
}
*/

////////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////////
/*
Game::Pls Game::whoMustGo() const
{
    return playerMustGo_;
}
*/

////////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////////
bool Game::currentMustGoComp() const
{
    return !((players_.getCurrentPlayer())->isUser());
}

////////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////////
const PlayerId* const Game::getCurrentPlayer() const
{
    return players_.getCurrentPlayer();
}

////////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////////
bool Game::isGameFinished() const
{
    return gameFinished_;
}

////////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////////
void Game::finishGame()
{
    gameFinished_ = true;
}

////////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////////
const PlayerId* const Game::getPlayerByName(std::string name) const
{
    return players_.getPlayerByName(name);
}
