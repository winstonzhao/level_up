#include <cassert>
#include "game.hpp"

namespace LevelUp
{
    IPlayer *Game::AddPlayer(IPlayer *player, IPlayerHandler *handler)
    {
        if (mPlayers.size() >= 4)
        {
            throw std::runtime_error("too many players: " + mPlayers.size());
        }

        auto side = player->GetTeam();
        auto &team = side ? mTeam1 : mTeam2;
        if (team.size() >= 2)
        {
            auto teamStr = side ? "team 1" : "team 2";
            throw std::runtime_error("too many players in " + std::string(teamStr) + " team: " + std::to_string(team.size()));
        }

        player->SetId(++mId);
        mPlayers.emplace_back(player);
        team.emplace_back(player);
        return player;
    }

    std::pair<bool, std::string> Game::StartGame()
    {
        if (mPlayers.size() != 4)
        {
            return {false, "Not enough players: " + std::to_string(mPlayers.size()) + ", to start game!"};
        }

        mPlayersByTurn.emplace_back(mTeam1[0]);
        mPlayersByTurn.emplace_back(mTeam2[0]);
        mPlayersByTurn.emplace_back(mTeam1[1]);
        mPlayersByTurn.emplace_back(mTeam2[1]);

        return {true, ""};
    }

    bool Game::DealNextCard()
    {
        if (mDeck.size() - mDeckIndex  == 8)
        {
            return false;
        }

        assert(mDeck.size() - mDeckIndex > 8);

        mPlayersByTurn[mPlayerTurn]->DealCard(mDeck[mDeckIndex++]);
        mPlayerTurn = (mPlayerTurn + 1) % mPlayers.size();
        return true;
    }

    bool Game::CanThrowMainCard(IPlayer *p, Card card, bool isOverride)
    {
        // Card needs to be same as level.
        if (GetTeamLevel(p) != card.mValue)
        {
            return false;
        }

        int numCard = 0;
        for (auto &c : p->GetHand())
        {
            if (c == card)
            {
                ++numCard;
            }
        }
        assert(numCard < 3);

        // Player requires 2 of the thrown card to override
        if (isOverride && numCard != 2)
        {
            return false;
        }

        // Player cannot override himself, he can however, doubledown on the same suite
        if (isOverride && p->GetId() == mMainSuiteThrownBy->GetId() && mMainSuite != card.mSuite)
        {
            return false;
        }

        // No suite can only be achieved using 2 cards
        if (!isOverride && card.mSuite == Suite::JOKER)
        {
            return false;
        }

        // Cannot override no suite
        if (mMainSuite == Suite::JOKER && mMainSuiteIsOverrided)
        {
            return false;
        }

        return true;
    }

    bool Game::ThrowMainCard(IPlayer *p, Card card, bool isOverride)
    {
        assert(CanThrowMainCard(p, card, isOverride));

        if (mFirstRound)
        {
            mAttackingTeam = p->GetTeam();
        }

        mMainSuiteThrown = true;
        mMainSuite = card.mSuite;
        mMainSuiteThrownBy = p;

        if (isOverride)
        {
            mMainSuiteIsOverrided = true;
        }

        if (mGameListener)
        {
            mGameListener->OnMainSuiteThrown(p, card.mSuite, isOverride);
        }

        return true;
    }

    int Game::GetCurrentLevel()
    {
        // Current level = level of the defending team
        return mAttackingTeam ? mTeam2Level : mTeam1Level;
    }
}