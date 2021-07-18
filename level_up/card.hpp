#pragma once

#include <memory>
#include <vector>

namespace LevelUp
{
    enum class Suite;
    struct Card;

    std::string GetSuiteString(Suite s);
    std::string GetCardValueString(int val);
    std::vector<Card> GenerateShuffledDecks();

    enum class Suite
    {
        HEART,
        DIAMOND,
        SPADE,
        CLUBS,
        JOKER
    };

    struct Card
    {
        static int const  BIG_JOKER = 15;
        static int const  SMALL_JOKER = 14;

        Card(Suite suite, int value);
        std::string ToString();

        Suite mSuite;
        // 1 = 1, 13 = King etc.
        int mValue;
    };
}