#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <level_up/interfaces.hpp>

using namespace LevelUp;

struct MockGameListener : public IGameListener 
{
    MOCK_METHOD(void, OnMainSuiteThrown, (IPlayer* p, Suite suite, bool isOverride));
    ~MockGameListener() {}
};

struct MockPlayer: public IPlayer
{
    MOCK_METHOD(void, SetId, (int));
    MOCK_METHOD(void, DealCard, (Card));
    MOCK_METHOD(std::vector<Card>&, GetHand, ());
    MOCK_METHOD(bool, GetTeam, ());
    MOCK_METHOD(int, GetId, ());
    // https://github.com/google/googletest/issues/2490
    MOCK_METHOD0(GetThrowableCards, std::vector<std::pair<Card, int>>());
    virtual  ~MockPlayer() {}
};

struct MockPlayerHandler : public IPlayerHandler
{
    MOCK_METHOD(void, OnCardDealt, (IPlayer* player, Card card));
    virtual ~MockPlayerHandler() {}
};