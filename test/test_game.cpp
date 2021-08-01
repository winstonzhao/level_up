#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <level_up/game.hpp>
#include <unordered_map>
#include "mocks.hpp"

using namespace LevelUp;
using namespace ::testing;

struct GameFixture : public Test
{
    void SetUp() override
    {
        mGame = std::make_unique<Game>();
        mGame->SetListener(&mListener);
    }

    void StartGame()
    {
        auto team = false;

        for (auto* player : {&mPlayer1, &mPlayer2, &mPlayer3, &mPlayer4})
        {
            EXPECT_CALL(*player, GetTeam).WillOnce(Return(team = !team));
            EXPECT_CALL(*player, SetId(_));
            mGame->AddPlayer(player, &mPlayerHandler);
        }

        mGame->StartGame();
    }

    void ExpectFullDecks(std::vector<Card> decks)
    {
        std::unordered_map<Suite, int> suites;
        std::unordered_map<int, int> numbers;
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
        EXPECT_EQ(decks.size(), 108);
    }

    MockGameListener mListener;
    MockPlayerHandler mPlayerHandler;
    std::unique_ptr<Game> mGame;

    MockPlayer mPlayer1;
    MockPlayer mPlayer2;
    MockPlayer mPlayer3;
    MockPlayer mPlayer4;
};

TEST_F(GameFixture, AddPlayers_NonAlternating) {
    MockPlayer player;
    EXPECT_CALL(player, GetTeam).WillRepeatedly(Return(false));
    EXPECT_CALL(player, SetId(1));
    EXPECT_CALL(player, SetId(2));
    mGame->AddPlayer(&player, &mPlayerHandler);
    mGame->AddPlayer(&player, &mPlayerHandler);

    EXPECT_CALL(player, GetTeam).WillRepeatedly(Return(true));
    EXPECT_CALL(player, SetId(3));
    EXPECT_CALL(player, SetId(4));
    mGame->AddPlayer(&player, &mPlayerHandler);
    mGame->AddPlayer(&player, &mPlayerHandler);
}

TEST_F(GameFixture, AddPlayers_Alternating) {
    MockPlayer player;
    {
        InSequence seq;
        EXPECT_CALL(player, GetTeam).WillOnce(Return(false));
        EXPECT_CALL(player, SetId(1));
        EXPECT_CALL(player, GetTeam).WillOnce(Return(true));
        EXPECT_CALL(player, SetId(2));
        EXPECT_CALL(player, GetTeam).WillOnce(Return(false));
        EXPECT_CALL(player, SetId(3));
        EXPECT_CALL(player, GetTeam).WillOnce(Return(true));
        EXPECT_CALL(player, SetId(4));
    }
    
    mGame->AddPlayer(&player, &mPlayerHandler);
    mGame->AddPlayer(&player, &mPlayerHandler);
    mGame->AddPlayer(&player, &mPlayerHandler);
    mGame->AddPlayer(&player, &mPlayerHandler);
}

TEST_F(GameFixture, AddPlayers_TooManyPlayers) {
    MockPlayer player;

    EXPECT_CALL(player, GetTeam).WillRepeatedly(Return(false));
    EXPECT_CALL(player, SetId(1));
    EXPECT_CALL(player, SetId(2));

    mGame->AddPlayer(&player, &mPlayerHandler);
    mGame->AddPlayer(&player, &mPlayerHandler);
    EXPECT_ANY_THROW(mGame->AddPlayer(&player, &mPlayerHandler));
}

TEST_F(GameFixture, TestDealing)
{
    StartGame();
    std::vector<Card> cards;
    
    for (auto* player : {&mPlayer1, &mPlayer2, &mPlayer3, &mPlayer4})
    {
        EXPECT_CALL(*player, DealCard(_)).WillRepeatedly(Invoke([&](Card c){
            cards.emplace_back(c);
        }));
    }

    int numDealt = 0;

    while (mGame->DealNextCard()) { numDealt++; }
    EXPECT_EQ(numDealt, 100);

    EXPECT_EQ(cards.size(), 100);
    for (auto it = mGame->GetDeck().begin() + 100; it != mGame->GetDeck().end(); ++it)
    {
        cards.emplace_back(*it);
    }
    
    ExpectFullDecks(cards);
}