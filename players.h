#ifndef _PLAYERS_H_
#define _PLAYERS_H_


#include "playerid.h"

#include <vector>

class Players : public std::vector<PlayerId*>
{
public:
    Players();
    ~Players();

    const PlayerId* const getPlayer(size_t playerId) const;
    const PlayerId* const getCurrentPlayer() const;
    const PlayerId* const getPlayerByName(std::string name) const;
    void setNextPlayer();

private:
    size_t curPlayerId_;
};


#endif //_PLAYERS_H_
