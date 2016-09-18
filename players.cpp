#include "players.h"
#include "err.h"

Players::Players()
    : std::vector<PlayerId*>()
    , curPlayerId_(0)
{
}

Players::~Players()
{
    for(auto it = this->begin(); it != this->end(); ++it)
    {
        delete (*it);
    }
}

const PlayerId* const Players::getPlayer(size_t playerId) const
{
    if(playerId >= this->size())
        throw Err();

    return this->operator[](playerId);
}

const PlayerId* const Players::getCurrentPlayer() const
{
    return getPlayer(curPlayerId_);
}

const PlayerId* const Players::getPlayerByName(std::string name) const
{
    for(auto it = this->begin(); it != this->end(); ++it)
    {
        if((*it)->name() == name)
            return *it;
    }

    return nullptr;
}

void Players::setNextPlayer()
{
    curPlayerId_++;

    if(curPlayerId_ == this->size())
        curPlayerId_ = 0;
}

