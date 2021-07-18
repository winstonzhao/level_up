#include "card.hpp"
#include <cassert>

namespace LevelUp
{
    namespace
    {
        int RandomNumber(int max, int min = 0)
        {
            assert(max > min);
            return (rand() % (max - min)) + min;
        }
    }

    // Card Method Definitions
    Card::Card(Suite suite, int value) : mSuite(suite), mValue(value)
    {
        assert(value > 0);
        assert(value <= 13 || suite == Suite::JOKER);
        assert(value <= 15);
    }

    std::string Card::ToString()
    {
        return GetSuiteString(mSuite) + GetCardValueString(mValue);
    }

    // Util Definitions
    std::string GetSuiteString(Suite s)
    {
        switch (s)
        {
        case Suite::HEART:
            return "♥";
        case Suite::DIAMOND:
            return "♦";
        case Suite::SPADE:
            return "♠";
        case Suite::CLUBS:
            return "♣";
        case Suite::JOKER:
            return "🤡";
        }
        throw std::runtime_error("unknown suite");
    }

    std::vector<Card> GenerateShuffledDecks()
    {
        // CARD_SUITES and CARD_VALUES does not include Jokers
        constexpr std::array<Suite, 4> CARD_SUITES{Suite::HEART, Suite::DIAMOND, Suite::SPADE, Suite::CLUBS};
        constexpr std::array<int, 13> CARD_VALUES{1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13};
        constexpr auto SHUFFLE_AMOUNT = 10000;

        std::vector<Card> ret;

        // Generate 2 decks
        for (int i = 1; i <= 13; ++i)
        {
            for (auto suite : CARD_SUITES)
            {
                // Two of each card
                ret.emplace_back(Card(suite, i));
                ret.emplace_back(Card(suite, i));
            }
        }

        // Jokers
        ret.emplace_back(Card(Suite::JOKER, Card::SMALL_JOKER));
        ret.emplace_back(Card(Suite::JOKER, Card::SMALL_JOKER));
        ret.emplace_back(Card(Suite::JOKER, Card::BIG_JOKER));
        ret.emplace_back(Card(Suite::JOKER, Card::BIG_JOKER));

        // Shuffle
        for (int i = 0; i < SHUFFLE_AMOUNT; ++i)
        {
            // Could be the same number but whatever
            auto rand1 = RandomNumber(ret.size());
            auto rand2 = RandomNumber(ret.size());

            auto tmp = ret[rand1];
            ret[rand1] = ret[rand2];
            ret[rand2] = tmp;
        }

        return ret;
    }

    std::string GetCardValueString(int val)
    {
        assert(val > 0);
        assert(val <= 15);

        if (val <= 10)
        {
            return std::to_string(val);
        }
        else if (val == 11)
        {
            return "J";
        }
        else if (val == 12)
        {
            return "Q";
        }
        else if (val == 13)
        {
            return "K";
        }
        else if (val == Card::SMALL_JOKER)
        {
            return "S";
        }
        else if (val == Card::BIG_JOKER)
        {
            return "B";
        }

        throw std::runtime_error("unexpected card value: " + std::to_string(val));
    }
}