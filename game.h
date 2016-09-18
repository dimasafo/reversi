#ifndef _GAME_H_
#define _GAME_H_


#include "idcell.h"
#include "boarddata.h"
#include "playerid.h"
#include "players.h"
#include "gochoice.h"


class Game
{
public:
    enum Pls
    {
        Player_A = 0,
        Player_B = 1
    };

    Game(int rows, int columns);
    ~Game();

    int canGoOneDirection(IdCell start, BoardData::Direction direction, const PlayerId* const player);

    GoChoice getGoChoice(IdCell cell, const PlayerId* const player);

    bool canGo(IdCell cell, const PlayerId* const player);

    void processComputerGo(const PlayerId* const player);

    void Go(IdCell cell, const PlayerId* const player);

    const BoardData* const boardData() const;

    const Players* const players() const;

    bool isWaitForUser() const;

    void setWaitForUser(bool waitForUser);

    bool canGoAnywhere(const PlayerId* const player, int& maxCellsWalked, IdCell& cellToGo);

    void getAllChoices(const PlayerId* const player, std::set<GoChoice>& res);

    bool canGoAnywhere(const PlayerId* const player);

    void jumpToNextPlayer();

    //const PlayerId* const getPlayer(Pls playerNum) const;
    //Pls whoMustGo() const;
    bool currentMustGoComp() const;

    const PlayerId* const getCurrentPlayer() const;

    const PlayerId* const getPlayerByName(std::string name) const;

    bool isGameFinished() const;

    void finishGame();

private:
    BoardData boardData_;

    Players players_;
    bool gameFinished_;
};


#endif //_GAME_H_
