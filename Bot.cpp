#include <iostream>


struct Card {
    int Suit;
    int Rank;
};



int ReturnBenefitValues(Card handBot[], int sizeBot)
{
    srand(time(0));
    int countCards[9] = { 0 };
    
    for (int i = 0; i < sizeBot; i++)
        if (handBot[i].Rank > 5 && handBot[i].Rank < 15)
            countCards[handBot[i].Rank - 6]++;

    int maxNum = 0, secondMaxNum = 0;
    int maxIndex = -1, secondMaxindex = -1;
    
    for (int i = 0; i < 9; i++)
    {
        if (countCards[i] > maxNum)
        {
            secondMaxNum = maxNum;
            maxNum = countCards[i];
            secondMaxindex = maxIndex;
            maxIndex = i;
        }
        else if (countCards[i] > secondMaxNum && countCards[i] <= maxNum)
        {
            secondMaxNum = countCards[i];
            secondMaxindex = i;
        }
    }
    
    if (rand() % 2)
        return maxIndex + 6;
    else 
        return secondMaxindex + 6;


}