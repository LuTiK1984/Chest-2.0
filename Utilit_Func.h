#pragma once

struct Card {
    int Suit;
    int Rank;
};

void DeckShuffle(Card Deck[], int size);

void DeckGeneration(Card Deck[]);

void sortDeck(Card handPlayer[], int& size);

void FillHandPlayer(Card handPlayer[], Card Choice, int& size);

Card getCardFromMas(Card mas[], Card handPlayer[], int& size, int& sizePlayer, int index);

Card GetCardFromTheEnd(Card handPlayer[], int& size);

void ReturnAllCardsByRank(Card handPlayer[], Card handBot[], int Choice, int& size, int& sizePlayer);

int searchRequestedCard(Card handPlayer[], int Choice, int& size);

void CardDistribution(Card handPlayer[], Card Deck[], int& size, int& handSize, int n);

void PrintCardName(Card card);

void PrintHand(Card hand[], int size);

void Clear();

void Continue();

void Menu();

bool RandPlayer();

void PrintRankName(int card);

void CardDelAndMove(Card handPlayer[], int& sizePlayer, int choice);

void CheckPlayerChests(Card handPlayer[], int &ChestCountPlayer, int &sizePlayer);