#pragma once
#include "card.hpp"

namespace LevelUp
{
    struct IPlayer
    {
        virtual void SetId(int id) = 0;
        virtual void DealCard(Card) = 0;
        virtual std::vector<Card>& GetHand() = 0;
        virtual bool GetTeam() = 0;
        virtual int GetId() = 0;
        virtual std::vector<std::pair<Card, int>> GetThrowableCards() = 0;
        virtual ~IPlayer() {}
    };

    struct IPlayerHandler
    {
        virtual void OnCardDealt(IPlayer* player, Card card) = 0;
        virtual ~IPlayerHandler() {}
    };

    struct IGameManager
    {
        virtual ~IGameManager() {}
    };

    struct IGameInfo
    {
        virtual int GetCurrentLevel() = 0;
        virtual Suite GetMainSuite() = 0;
        // returns (isThrown, isOverride)
        virtual std::pair<bool, bool> IsMainSuiteThrown() = 0;
        virtual IPlayer* GetMainSuiteThrownBy() = 0;
        virtual bool ThrowMainCard(IPlayer*, Card card, bool isOverride) = 0;
        virtual bool CanThrowMainCard(IPlayer*, Card card, bool isOverride) = 0;
        virtual ~IGameInfo() {}
    };

    struct IGameListener
    {
        virtual void OnMainSuiteThrown(IPlayer* p, Suite suite, bool isOverride) = 0;
        virtual ~IGameListener() {}
    };
}