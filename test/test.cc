#include <gtest/gtest.h>
#include <level_up/card.hpp>
#include <unordered_map>

using namespace LevelUp;

TEST(TestShuffle, GenerateShuffledDecks) {
  constexpr std::array<Suite, 5> CARD_SUITES{Suite::HEART, Suite::DIAMOND, Suite::SPADE, Suite::CLUBS, Suite::JOKER};
  constexpr std::array<int, 15> CARD_VALUES{1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15};

  auto decks = GenerateShuffledDecks();
  std::unordered_map<Suite, int> suites;
  std::unordered_map<int, int> numbers;

  for (auto suite : CARD_SUITES)
  {
    suites.insert({suite, 0});
  }

  for (auto val : CARD_VALUES)
  {
    numbers.insert({val, 0});
  }

  for (auto card : decks)
  {
    suites[card.mSuite]++;
    numbers[card.mValue]++;
  }
  
  for (auto suite : {Suite::HEART, Suite::DIAMOND, Suite::SPADE, Suite::CLUBS})
  {
    EXPECT_EQ(suites[suite], 26);
  }

  for (int i = 1; i <= 13; ++i)
  {
    EXPECT_EQ(numbers[i], 8);
  }
  
  EXPECT_EQ(suites[Suite::JOKER], 4);
  EXPECT_EQ(numbers[14], 2);
  EXPECT_EQ(numbers[15], 2);
}