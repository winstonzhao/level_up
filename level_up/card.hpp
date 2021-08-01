#pragma once

#include <memory>
#include <vector>
#include <functional>

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
        static int const BIG_JOKER = 15;
        static int const SMALL_JOKER = 14;

        Card(Suite suite, int value);
        std::string ToString();
        bool operator==(const Card &other) const;
        bool operator!=(const Card &other) const;
        Card operator=(const Card &other) const;

        Suite mSuite;
        // 1 = 1, 13 = King etc.
        int mValue;
    };
}

namespace std
{
    template <>
    struct hash<LevelUp::Card>
    {
        size_t operator()(const LevelUp::Card &x) const
        {
            return std::hash<int>()(x.mValue) ^ std::hash<int>()(static_cast<int>(x.mSuite));
        }
    };
}