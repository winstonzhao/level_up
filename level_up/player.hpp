#pragma once
#include "interfaces.hpp"

namespace LevelUp
{
    class Player : public IPlayer
    {
    public:
        Player(int id, IPlayerHandler*, bool team, IGameInfo*);

        // IPlayer
        void SetId(int id) override;
        void DealCard(Card) override;
        std::vector<Card>& GetHand() override;
        bool GetTeam() override { return mTeam; }
        int GetId() override {return mId; }
        std::vector<std::pair<Card, int>> GetThrowableCards() override;
        

    private:
        int mId = -1;
        IPlayerHandler* mHandler;
        IGameInfo* mGame;
        std::vector<Card> mHand;
        bool mTeam;
    };
}