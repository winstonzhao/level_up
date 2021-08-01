#include "player.hpp"
#include <unordered_map>
#include <cassert>
#include <algorithm>

namespace LevelUp
{
    Player::Player(int id, IPlayerHandler *handler, bool team, IGameInfo *gi) : mId(id), mHandler(mHandler), mTeam(team), mGame(gi) {}

    void Player::SetId(int id)
    {
        if (mId != -1)
        {
            throw std::runtime_error("id cannot be set twice, id is already set to: " + std::to_string(mId));
        }

        mId = id;
    }

    void Player::DealCard(Card card)
    {
        mHand.emplace_back(card);
        mHandler->OnCardDealt(this, card);
    }
    std::vector<Card> &Player::GetHand() { return mHand; }

    std::vector<std::pair<Card, int>> Player::GetThrowableCards()
    {
        auto level = mGame->GetCurrentLevel();
        std::unordered_map<Card, int> candidates;
        for (auto card : GetHand())
        {
            if (card.mValue == level || card.mValue == Card::BIG_JOKER || card.mValue == Card::SMALL_JOKER)
            {
                if (candidates.count(card))
                {
                    candidates[card]++;
                }
                else
                {
                    candidates[card] = 1;
                }
            }
        }

        std::vector<std::pair<Card, int>> ret;
        std::copy_if(candidates.begin(), candidates.end(), ret.begin(), [&](const std::pair<Card, int>& kv){ return mGame->CanThrowMainCard(this, kv.first, kv.second == 2); });
        return ret;
    }
}