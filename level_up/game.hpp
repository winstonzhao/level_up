#pragma once
#include <vector>
#include <memory>
#include <array>

#include "card.hpp"
#include "player.hpp"
#include "interfaces.hpp"

namespace LevelUp
{
    class Game : public IGameInfo, public IGameManager
    {
    public:
        IPlayer *AddPlayer(IPlayer *, IPlayerHandler *);
        bool IsReady() { return mPlayers.size() == 4; }
        std::pair<bool, std::string> StartGame();
        void SetListener(IGameListener *listener) { mGameListener = listener; }
        bool DealNextCard();

        // IGameInfo
        int GetCurrentLevel() override;
        Suite GetMainSuite() override { return mMainSuite; }
        std::pair<bool, bool> IsMainSuiteThrown() override { return std::make_pair(mMainSuiteThrown, mMainSuiteIsOverrided); }
        IPlayer *GetMainSuiteThrownBy() override { return mMainSuiteThrownBy; };
        bool ThrowMainCard(IPlayer *, Card card, bool isOverride) override;
        bool CanThrowMainCard(IPlayer *, Card card, bool isOverride) override;

        bool GetTeamLevel(IPlayer *player) { return GetTeamLevel(player->GetTeam()); }
        bool GetTeamLevel(bool team) { return team ? mTeam1Level : mTeam2Level; }

        std::vector<Card> GetDeck() { return mDeck; }

    private:
        IGameListener *mGameListener = nullptr;

        std::vector<IPlayer *> mPlayers;
        std::vector<IPlayer *> mTeam1;
        std::vector<IPlayer *> mTeam2;
        std::vector<IPlayer *> mPlayersByTurn;
        int mId = 0;

        std::vector<Card> mDeck = GenerateShuffledDecks();
        int mDeckIndex = 0;

        Suite mMainSuite;
        bool mMainSuiteThrown = false;
        bool mMainSuiteCanOverride = true;
        bool mMainSuiteIsOverrided = false;
        IPlayer *mMainSuiteThrownBy = nullptr;

        bool mFirstRound = true;
        int mTeam1Level = 2;
        int mTeam2Level = 2;
        int mPlayerTurn = 0;
        bool mAttackingTeam; // true => team1, false => team2
    };
}