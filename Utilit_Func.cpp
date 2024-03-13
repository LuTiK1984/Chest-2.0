#include <iostream>

struct Card {
    int Suit;
    int Rank;
};

// Перемешивание карт
void DeckShuffle(Card Deck[], int size) {
    for (int i = size - 1; i > 0; i--)
    {
        int j = rand() % (i + 1);
        Card temp = Deck[i];
        Deck[i] = Deck[j];
        Deck[j] = temp;
    }
}
//Генерация карт
void DeckGeneration(Card Deck[]) {
    int i = 0;//Выбор индекса карты
    for (int Suit = 1; Suit <= 4; Suit++) {
        for (int Value = 6; Value <= 14; Value++) {
            Deck[i].Suit = Suit;
            Deck[i].Rank = Value;
            i++;
        }
    }
}
//сортирует карты в руке по номиналу
void sortDeck(Card Hand[], int& size) {
    for (int i = 0; i < size - 1; ++i)
        for (int j = 0; j < size - i - 1; ++j)
            if (Hand[j].Rank > Hand[j + 1].Rank)
            {
                Card temp = Hand[j];
                Hand[j] = Hand[j + 1];
                Hand[j + 1] = temp;
            }
}

//добавляет карту в конец массива руки
void FillHandPlayer(Card handPlayer[], Card Choice, int& size)
{
    size++;
    handPlayer[size - 1] = Choice;
}

void getCardFromMas(Card handBot[], Card handPlayer[], int& sizeBot, int& sizePlayer, int choice)
{
    Card Choice = handBot[choice];
    handBot[choice].Rank = 0;
    handBot[choice].Suit = 0;
    for (int i = choice; i < sizeBot - 1; i++)
    {
        handBot[i] = handBot[i + 1];
    }
    sizeBot--;

    FillHandPlayer(handPlayer, Choice, sizePlayer);
}



Card GetCardFromTheEnd(Card handPlayer[], int& size)
{
    Card temp = handPlayer[size - 1];
    size--;
    return temp;
}

void ReturnAllCardsByRank(Card handPlayer[], Card handBot[], int Choice, int& sizeBot, int& sizePlayer)
{
    for (int i = 0; i < sizeBot; i++)
        if (handBot[i].Rank == Choice) {
            getCardFromMas(handBot, handPlayer, sizeBot, sizePlayer, i);
            i--;
        }
}

int searchRequestedCard(Card handPlayer[], int Choice, int& size)
{
    for (int i = 0; i < size; i++)
    {
        if (handPlayer[i].Rank == Choice)
            return i;
    }
    return -1;
}

void CardDistribution(Card handPlayer[], Card Deck[], int& size, int& handSize, int n)
{
    for (int i = 0; i < n; i++)
    {
        handPlayer[handSize] = Deck[size - 1];
        size--;
        handSize++;
    }
}

void PrintCardName(Card card)
{

    switch (card.Suit)
    {
    case 1: printf("Пики "); break;
    case 2: printf("Черви "); break;
    case 3: printf("Крести "); break;
    case 4: printf("Буби "); break;
    }
    if (card.Rank >= 6 && card.Rank <= 10)
        printf("%i\n", card.Rank);
    else {
        switch (card.Rank)
        {
        case 11: printf("Валет\n"); break;
        case 12: printf("Дама\n"); break;
        case 13: printf("Король\n"); break;
        case 14: printf("Туз\n"); break;
        }
    }
}

void PrintHand(Card hand[], int size)
{
    for (int i = 0; i < size; i++)
    {
        PrintCardName(hand[i]);
    }
}
void Clear()
{
    system("cls");
}

void Continue()
{
    char ch;
    while ((ch = getchar()) != '\n');
}

void Menu()
{
    char ch;
    printf("\n\n\n                                                   Сундучок 2.0\n\n");
    printf("                                         Чтобы начать игру нажмите Enter\n");
    while ((ch = getchar()) != '\n');
}

bool RandPlayer()
{
    srand(time(NULL));
    int player = rand() % 2;
    if (player == 1)
        return true;
    else
        return false;
}

void PrintRankName(int card)
{
    if (card >= 6 && card <= 10)
        printf("%i\n", card);
    else {
        switch (card)
        {
        case 11: printf("Валет\n"); break;
        case 12: printf("Дама\n"); break;
        case 13: printf("Король\n"); break;
        case 14: printf("Туз\n"); break;
        }
    }
}

void CardDelAndMove(Card handPlayer[], int& sizePlayer, int choice)
{
    for (int i = choice; i < sizePlayer - 1; i++)
        handPlayer[i] = handPlayer[i + 1];
    sizePlayer--;
}

void CheckPlayerChests(Card handPlayer[], int &ChestCountPlayer, int& sizePlayer)
{

    for (int i = 0; i < sizePlayer; i++)
    {
        int count = 0;
        for (int j = 0; j < sizePlayer; j++)
        {
            if (handPlayer[i].Rank == handPlayer[j].Rank)
                count++;

        }
        if (count == 4)
        {
            int index = handPlayer[i].Rank;
            ChestCountPlayer++;

            for (int k = 0; k < sizePlayer; k++)
            {
                if (index == handPlayer[k].Rank)
                {
                    CardDelAndMove(handPlayer, sizePlayer, k);
                    k--;
                }
            }
        }
    }

}

