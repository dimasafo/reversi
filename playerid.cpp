#include "playerid.h"


PlayerId::PlayerId(std::string name, Color color, bool userPlayer)
    : name_(name)
    , color_(color)
    , userPlayer_(userPlayer)
{
}

PlayerId::PlayerId(const PlayerId& src)
    : name_(src.name_)
    , color_(src.color_)
{
}

bool PlayerId::isSame(const PlayerId* const player) const
{
    if(player->name_ == name_)
        return true;

    return false;
}

bool PlayerId::isUser() const
{
    return userPlayer_;
}

std::string PlayerId::name() const
{
    return name_;
}

const PlayerId::Color PlayerId::color() const
{
    return color_;
}

//////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////

PlayerA::PlayerA(PlayerId::Color color, bool userPlayer)
    : PlayerId("AAAAAA", color, userPlayer)
{
}

PlayerA::PlayerA(const PlayerA& src)
    : PlayerId(src)
{
}

//////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////

PlayerB::PlayerB(PlayerId::Color color, bool userPlayer)
    : PlayerId("BBBBBB", color, userPlayer)
{
}

PlayerB::PlayerB(const PlayerB& src)
    : PlayerId(src)
{
}
