#ifndef _PLAYERID_H_
#define _PLAYERID_H_


#include <string>

class PlayerId
{
public:
    struct Color
    {
        unsigned char r_;
        unsigned char g_;
        unsigned char b_;

        Color(unsigned char r, unsigned char g, unsigned char b)
            : r_(r)
            , g_(g)
            , b_(b)
        {}
    };

    PlayerId(std::string name, Color color, bool userPlayer);
    PlayerId(const PlayerId& src);
    virtual ~PlayerId() {}

    bool isSame(const PlayerId* const player) const;
    bool isUser() const;
    std::string name() const;
    const Color color() const;

private:
    virtual void func()=0;

    std::string name_;
    bool userPlayer_;
    Color color_;
};

//////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////

class PlayerA : public PlayerId
{
public:
    PlayerA(PlayerId::Color color, bool userPlayer);
    PlayerA(const PlayerA& src);

private:
    virtual void func() {}
};

//////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////

class PlayerB : public PlayerId
{
public:
    PlayerB(PlayerId::Color color, bool userPlayer);
    PlayerB(const PlayerB& src);

private:
    virtual void func() {}
};


#endif //_PLAYERID_H_
