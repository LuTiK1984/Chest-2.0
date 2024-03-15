#include <iostream>
#include <Utilit_Func.h>
#include <Bot.h>


//���������� ������
Card Deck[36];
Card handPlayer[36];
Card handBot[36];

bool IsGame = true;
bool MyTurn = RandPlayer();

int sizeMain = 36;
int sizePlayer = 0;
int sizeBot = 0;
int ChestCountPlayer = 0;
int ChestCountBot = 0;

//����� ��������� � �������

bool GameOver()
{
    if (sizeMain <= 0)
        return true;
    else
        return false;
}

//������� ����
void Game()
{
    DeckShuffle(Deck, sizeMain);
    printf("\n���������� ������� ���� ��� � ���������� (������� Enter)");

    Continue();

    Clear();

    CardDistribution(handPlayer, Deck, sizeMain, sizePlayer, 4);
    CardDistribution(handBot, Deck, sizeMain, sizeBot, 4);

    while (IsGame)
    {

        sortDeck(handPlayer, sizePlayer);
        sortDeck(handBot, sizeBot);

        CheckPlayerChests(handPlayer, ChestCountPlayer, sizePlayer);
        CheckPlayerChests(handBot, ChestCountBot, sizeBot);
        
        printf("���������� ����� ���������: %i", ChestCountPlayer);
        printf("\n���������� ��������� ����������: %i\n", ChestCountBot);



        printf("\n���������� ���� � ������ - %i", sizeMain);
        printf("\n\n���� �����: \n\n");
        PrintHand(handPlayer, sizePlayer);
        printf("\n");

        int choice;
        int turnindex;

        if (MyTurn)
        {
            printf("\n\n��� ���! �������� ����� �� 6 �� 10 ��� 11 - �����, 12 - ����, 13 - ������, 14 - ���: ");
            do
            {
                scanf_s("%i", &choice);
                if (choice < 6 || choice>14)
                    printf("\n�� ����� ������������ ��������!\n");
            } while (choice < 6 || choice>14);

            turnindex = searchRequestedCard(handBot, choice, sizeBot);

            if (turnindex >= 0)
            {
                printf("\n�� ������� � ��������� � ���������� �����(�)!\n");
                ReturnAllCardsByRank(handPlayer, handBot, choice, sizeBot, sizePlayer);
                sortDeck(handPlayer, sizePlayer);
                
                printf("\n\n��� ����������� ������� Enter...");
                system("pause");
                Continue();
                Clear();
            }

            else
            {
                printf("\n�� �� ������� � ������ ����� �� ������. ��� ��������� ����������!\n");
                printf("�� ����� ����� �� ������: ");
                PrintCardName(Deck[sizeMain - 1]);
                CardDistribution(handPlayer, Deck, sizeMain, sizePlayer, 1);

                printf("��������� �������� ����� �� ������ ��� �������������.\n");
                if (sizeBot < 4)
                {
                    for (int i = sizeBot; i < 4; i++)
                    {
                        CardDistribution(handBot, Deck, sizeMain, sizeBot, 1);
                    }
                }
                MyTurn = 0;
                
                printf("\n\n��� ����������� ������� Enter...");
                Continue();
                Clear();
            }
        }

        else
        {
            printf("\n\n��� ����������! \n\n��������� �������� �����! ");
            choice = ReturnBenefitValues(handBot, sizeBot);
            printf("��������� ������ ����� ��������� ");
            PrintRankName(choice);

            turnindex = searchRequestedCard(handPlayer, choice, sizePlayer);

            if (turnindex >= 0)
            {
                printf("��������� ������ � �������� � ��� �����(�)!\n");
                ReturnAllCardsByRank(handBot, handPlayer, choice, sizePlayer, sizeBot);
                sortDeck(handBot, sizeBot);
                printf("\n\n��� ����������� ������� Enter...");
                Continue();
                Clear();
            }
            else
            {
                printf("��������� �� ������ � ����� ����� �� ������. ��� ��������� � ���!\n");
                CardDistribution(handBot, Deck, sizeMain, sizeBot, 1);

                printf("�� ��������� ����� �� ������ ��� �������������.\n\n");
                if (sizePlayer < 4)
                {
                    for (int i = sizePlayer; i < 4; i++)
                    {
                        PrintCardName(Deck[sizeMain - 1]);
                        CardDistribution(handPlayer, Deck, sizeMain, sizePlayer, 1);
                    }
                }
                printf("\n\n��� ����������� ������� Enter...");
                Continue();
                Clear();
                MyTurn = 1;
            } 
        }
            
        if (GameOver())
            {
                Clear();
                printf("\n\n\n                                            ���� ��������!\n\n\n");
                if (ChestCountPlayer > ChestCountBot)
                {
                    printf("�� ��������, �����������!!!\n");

                }
                if (ChestCountPlayer == ChestCountBot)
                {
                    printf("�����, ������� �������!!!\n");
                }
                if (ChestCountPlayer < ChestCountBot)
                {
                    printf("�� ���������! � ��������� ��� ����� ���������!\n");
                }
                Continue();
            }

    }

}


int main()
{
    srand(time(NULL));
    system("chcp 1251");

    Clear();
    Menu();
    Clear();

    DeckGeneration(Deck); //�������� ������
    Game(); //����

    return 0;
}