#include <iostream>
#include <Utilit_Func.h>
#include <Bot.h>


//Глобальные данные
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

//Поиск сундучков у игроков

bool GameOver()
{
    if (sizeMain <= 0)
        return true;
    else
        return false;
}

//Функция игры
void Game()
{
    DeckShuffle(Deck, sizeMain);
    printf("\nПроисходит раздача карт вам и противнику (нажмите Enter)");

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
        
        printf("Количество ваших сундучков: %i", ChestCountPlayer);
        printf("\nКоличество сундучков противника: %i\n", ChestCountBot);



        printf("\nКоличество карт в колоде - %i", sizeMain);
        printf("\n\nВаши карты: \n\n");
        PrintHand(handPlayer, sizePlayer);
        printf("\n");

        int choice;
        int turnindex;

        if (MyTurn)
        {
            printf("\n\nВаш ход! Выберите карту от 6 до 10 или 11 - Валет, 12 - Дама, 13 - Король, 14 - Туз: ");
            do
            {
                scanf_s("%i", &choice);
                if (choice < 6 || choice>14)
                    printf("\nВы ввели неккоректное значение!\n");
            } while (choice < 6 || choice>14);

            turnindex = searchRequestedCard(handBot, choice, sizeBot);

            if (turnindex >= 0)
            {
                printf("\nВы угадали и забераете у противника карту(ы)!\n");
                ReturnAllCardsByRank(handPlayer, handBot, choice, sizeBot, sizePlayer);
                sortDeck(handPlayer, sizePlayer);
                
                printf("\n\nДля продолжения нажмите Enter...");
                system("pause");
                Continue();
                Clear();
            }

            else
            {
                printf("\nВы не угадали и берете карту из колоды. Ход переходит противнику!\n");
                printf("Вы взяли карту из колоды: ");
                PrintCardName(Deck[sizeMain - 1]);
                CardDistribution(handPlayer, Deck, sizeMain, sizePlayer, 1);

                printf("Противник добирает карты из колоды при необходимости.\n");
                if (sizeBot < 4)
                {
                    for (int i = sizeBot; i < 4; i++)
                    {
                        CardDistribution(handBot, Deck, sizeMain, sizeBot, 1);
                    }
                }
                MyTurn = 0;
                
                printf("\n\nДля продолжения нажмите Enter...");
                Continue();
                Clear();
            }
        }

        else
        {
            printf("\n\nХод противника! \n\nПротивник выбирает карту! ");
            choice = ReturnBenefitValues(handBot, sizeBot);
            printf("Противник выбрал карту номиналом ");
            PrintRankName(choice);

            turnindex = searchRequestedCard(handPlayer, choice, sizePlayer);

            if (turnindex >= 0)
            {
                printf("Противник угадал и заберает у вас карту(ы)!\n");
                ReturnAllCardsByRank(handBot, handPlayer, choice, sizePlayer, sizeBot);
                sortDeck(handBot, sizeBot);
                printf("\n\nДля продолжения нажмите Enter...");
                Continue();
                Clear();
            }
            else
            {
                printf("Противник не угадал и берет карту из колоды. Ход переходит к вам!\n");
                CardDistribution(handBot, Deck, sizeMain, sizeBot, 1);

                printf("Вы добираете карты из колоды при необходимости.\n\n");
                if (sizePlayer < 4)
                {
                    for (int i = sizePlayer; i < 4; i++)
                    {
                        PrintCardName(Deck[sizeMain - 1]);
                        CardDistribution(handPlayer, Deck, sizeMain, sizePlayer, 1);
                    }
                }
                printf("\n\nДля продолжения нажмите Enter...");
                Continue();
                Clear();
                MyTurn = 1;
            } 
        }
            
        if (GameOver())
            {
                Clear();
                printf("\n\n\n                                            Игра Окончена!\n\n\n");
                if (ChestCountPlayer > ChestCountBot)
                {
                    printf("Вы победили, поздравляем!!!\n");

                }
                if (ChestCountPlayer == ChestCountBot)
                {
                    printf("Ничья, неплохо сыграли!!!\n");
                }
                if (ChestCountPlayer < ChestCountBot)
                {
                    printf("Вы проиграли! В следующий раз точно получится!\n");
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

    DeckGeneration(Deck); //Создание колоды
    Game(); //Игра

    return 0;
}