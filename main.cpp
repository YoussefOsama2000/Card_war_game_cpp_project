/******************************************************************************
 *
 * Team name: Anubis
 *
 * Team Names: Youssef Osama , Omar Sayed , Omar Ashraf
 *
 * Description: A Card war game
 *
 * GitHub repository link : https://github.com/YoussefOsama2000/cardWarGame.git
 *
 * IMPORTANT NOTE : This game was not our first, we attempted to make a connect four
 *                  but it was scrapped as minimax was considered an algorithm not
 *                  data structure. However the game is fully playable but not tested enough.
 *                  A link to the connect four repo is provided down
 *                  below just to show our effort.
 * GitHub repository link (Scrapped game - connect4): https://github.com/YoussefOsama2000/connect4.git
 *******************************************************************************/
#include <ctime>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <iostream>
#include <chrono>
#include<windows.h>
#include <bits/stdc++.h>
using namespace std;
using namespace std::chrono;
#define J 11
#define Q 12
#define K 13
#define Club 1
#define Heart 2
#define Spade 3
#define Diamond 4
std::chrono::time_point<std::chrono::system_clock> start_war, end_war;
struct Card
{
    int type = 0;
    int number = 0;
};
class Queue
{
private:
    struct Card data[52];
    int front;
    int back;
    int itemCount;

public:
    Queue()
    {
        front = 0;
        back = -1;
        itemCount = 0;
    }

    bool isEmpty()
    {
        return itemCount == 0;
    }
    bool isFull()
    {
        return itemCount == 52;
    }

    int size()
    {
        return itemCount;
    }
    void enqueue(struct Card New_Card)
    {

        if (!isFull())
        {
            if (back == 51)
            {
                back = -1;
            }
            data[++back] = New_Card;
            itemCount++;
        }
        else
        {
        }
    }
    Card dequeue()
    {
        Card Out_Card;

        if (!isEmpty())
        {
            Out_Card = data[front++];
            if (front == 52)
            {
                front = 0;
            }
            itemCount--;
        }
        else
        {
        }
        return Out_Card;
    }
};
class Stack
{
private:
    Card data[52];
    int top;

public:
    Stack()
    {
        top = -1;
    }

    Card peekStack()
    {
        return data[top];
    }

    bool isEmptyStack()
    {
        return top == -1;
    }

    bool isFullStack()
    {
        return top == 51;
    }

    void push(Card card)
    {
        if (!isFullStack())
        {
            data[++top] = card;
        }
        else
            ;
    }

    Card pop()
    {
        Card card;

        if (!isEmptyStack())
        {
            card = data[top];
            top--;
            return card;
        }
        return card;
    }

    int size()
    {
        return top + 1;
    }
};
class CardWarGame
{
    //global variable to measuer time complixity
    // Queues that represent what in players hands
    Queue queue1;
    Queue queue2;
    int warCounter;
    int globalWarCounter;
    // variables that represent the cards that will be used in the war
    Stack deckCards1;
    Stack deckCards2;
    Card cardsToCompare1[52];
    Card cardsToCompare2[52];
    // Variables that represent how many cards to draw for each player in the current card war
    int *cardsToBid1 = new int[52];
    int *cardsToBid2 = new int[52];
   std::chrono::time_point<std::chrono::system_clock> start_war, end_war;

public:
    CardWarGame() // Constructor that creates a full deck in order then randomizes it and distributes them to both players
    {
        globalWarCounter = 0;
        srand(time(0));
        resettingBids();
        warCounter = -1;
        Card fullDeck[52];
        Card randomizedDeck[52];
        // Creating the full deck in order
        int type = 0;
        for (int i = 0; i <= 51; i++)
        {
            if ((i % 13) == 0)
            {
                type++;

                fullDeck[i + 1].type = type;
            }
            fullDeck[i].number = (i % 13) + 1;
            fullDeck[i].type = type;
        }
        int temp = 0;
        for (int i = 0; i < 52; i++)
        {
            temp = rand();
            temp = (temp % (51 - 0 + 1)) + 0; // (rand() % (upper - lower + 1)) + lower
            if ((fullDeck[temp].number != 0 && fullDeck[temp].type != 0) && temp < 52)
            {
                randomizedDeck[i].number = fullDeck[temp].number;
                randomizedDeck[i].type = fullDeck[temp].type;
                fullDeck[temp].number = fullDeck[temp].type = 0;
            }
            else
            {
                temp = rand();
                temp = (temp % (51 - 0 + 1)) + 0;
                while ((fullDeck[temp].number == 0 || fullDeck[temp].type == 0))
                {
                    temp++;
                    if (temp > 51)
                    {
                        temp = temp % 52;
                    }
                }
                randomizedDeck[i].number = fullDeck[temp].number;
                randomizedDeck[i].type = fullDeck[temp].type;
                fullDeck[temp].number = fullDeck[temp].type = 0;
            }
        }
        for (int i = 0; i < 26; i++)
        {
            queue1.enqueue(randomizedDeck[i]);
            queue2.enqueue(randomizedDeck[i + 25]);
        }
    }
    void print() // Prints what happens in each round
    {
        //cout<<endl;
        if (system("CLS"));

        cout << "           player 1            VS                player  2" << endl
             << "            " << queue1.size() << // tell each player how many cards he has in his hands
             " Cards"
             << "                              " << queue2.size() << " Cards" << endl
             << "____________________________________________________________________" << endl;
        Card card1 = cardsToCompare1[0], card2 = cardsToCompare2[0];
        printCards(card1, card2);
        int currentCardNumber1 = 1, currentCardNumber2 = 1;
        Card flippedCard, emptyCard;
        flippedCard.number = 0;
        emptyCard.number = -1;
        for (int i = 0; cardsToBid1[i] != 0 && cardsToBid2[i] != 0; i++)
        {
            for (int j = 1; j <= (cardsToBid1[i] > cardsToBid2[i] ? cardsToBid1[i] : cardsToBid2[i]); j++) // the loop will iterate until j becomes equal the greater between the number of cards to bid the two players choose
            {
                printCards((j < cardsToBid1[i] ? flippedCard : (j == cardsToBid1[i] ? cardsToCompare1[i + 1] : emptyCard)), (j < cardsToBid2[i] ? flippedCard : (j == cardsToBid2[i] ? cardsToCompare2[i + 1] : emptyCard)));
            }
        }
        cout << endl
             << endl;
        string continuePlaying;
        while (continuePlaying != "c")
        {

            cout << "press c to continue...\n";
            cin >> continuePlaying;
            cin.ignore(10000,'\n');

        }

    }
    void printCards(Card card1, Card card2) // print 2 cards ,on for each player, in front of each other
    {
        /*
         print cards function prints two cards , it can print one faced up card and the other is flipped
         by giving value 0 to the number of the flipped card, and it can also print one card only by giving -1
         to the number of the absent card
         */
        if (card1.number > 0 && card2.number > 0)
        {
            // print type and number of the card
            cout << "              " << (card1.number < 11 ? to_string(card1.number) : (card1.number == J ? "J" : (card1.number == K ? "K" : "Q"))) << (card1.type == Club ? '\x05' : (card1.type == Spade ? '\x06' : (card1.type == Diamond ? '\x04' : '\x03'))) << "                                   " << (card2.number < 11 ? to_string(card2.number) : (card2.number == J ? "J" : (card2.number == K ? "K" : "Q"))) << (card2.type == Club ? '\x05' : (card2.type == Spade ? '\x06' : (card2.type == Diamond ? '\x04' : '\x03'))) << endl;
        }
        else if (card1.number <= 0 && card2.number > 0)
        {
            // print type and number of the card
            cout << (card1.number == 0 ? "            Flipped                                 " : "                                                    ") << (card2.number < 11 ? to_string(card2.number) : (card2.number == J ? "J" : (card2.number == K ? "K" : "Q"))) << (card2.type == Club ? '\x05' : (card2.type == Spade ? '\x06' : (card2.type == Diamond ? '\x04' : '\x03'))) << endl;
        }
        else if (card1.number > 0 && card2.number <= 0)
        {
            // print type and number of the card
            cout << "              " << (card1.number < 11 ? to_string(card1.number) : (card1.number == J ? "J" : (card1.number == K ? "K" : "Q"))) << (card1.type == Club ? '\x05' : (card1.type == Spade ? '\x06' : (card1.type == Diamond ? '\x04' : '\x03'))) << (card2.number == 0 ? "                                 Flipped" : " ") << endl;
        }
        else if (card1.number <= 0 && card2.number <= 0)
        {
            cout << (card1.number == 0 && card2.number == 0 ? "            Flipped                              Flipped" : (card1.number == 0 && card2.number == -1 ? "            Flipped" : "                                                 Flipped")) << endl;
        }
    }

    void askForWar() // in case of draw (equal cards), it determines the number of cards for war for each player
    {

        cout << "!!!this round ends to draw!!! \n \nwe have to play another round" << endl
             << "player 1! \nhow many cards you want to bid in this war?" << endl;
        int player1CardsToBid;
        cin >> player1CardsToBid;
<<<<<<< HEAD
        while(player1CardsToBid==0){cin.clear();cin.ignore(10000,'\n');cout<<"please enter valid input \n";cin>>player1CardsToBid;}
=======
        while(player1CardsToBid==0){cin.clear();cin.ignore();cout<<"please enter valid input \n";cin>>player1CardsToBid;}
>>>>>>> 54c84c019de0e0a06224f262c7fb011e546fc01d
        while (player1CardsToBid > queue1.size() || player1CardsToBid < globalWarCounter)
        {
            if (globalWarCounter >= queue1.size())
            {
                cout << "you are forced to bid all cards in your hand in this war \n";
                player1CardsToBid = queue1.size();
                break;
            }
            if (player1CardsToBid < globalWarCounter)
                cout << "you cannot bid less than " << globalWarCounter << " card/s in this war \n";
            else
                cout << "you don't have enough cards , you have only " << queue1.size() << " cards\n";
            cin >> player1CardsToBid;
        }
        for (int i = 1; i <= player1CardsToBid; i++)
        {
            deckCards1.push(queue1.dequeue());
        }

        cout << "player 2! \nhow many cards you want to bid in this war?" << endl;
        int player2CardsToBid;
        cin >> player2CardsToBid;
<<<<<<< HEAD
         while(player2CardsToBid==0){
             cin.clear();cin.ignore(10000,'\n');cout<<"please enter valid input \n";cin>>player2CardsToBid;}

         start_war = std::chrono::system_clock::now();
        //ios_base::sync_with_stdio(false);
=======
         while(player2CardsToBid==0){cin.clear();cin.ignore();cout<<"please enter valid input \n";cin>>player2CardsToBid;}
>>>>>>> 54c84c019de0e0a06224f262c7fb011e546fc01d
        while (player2CardsToBid > queue2.size() || player2CardsToBid < globalWarCounter)
        {
            if (globalWarCounter >= queue2.size())
            {
                cout << "you are forced to bid all cards in your hand in this war \n";
                player2CardsToBid = queue2.size();
                break;
            }
            if (player2CardsToBid < globalWarCounter)
                cout << "you cannot bid less than " << globalWarCounter << " card/s in this war \n";
            else
                cout << "you don't have enough cards , you have only " << queue2.size() << " cards\n";
            cin >> player2CardsToBid;
        }
        for (int i = 1; i <= player2CardsToBid; i++)
        {
            deckCards2.push(queue2.dequeue());
        }
        // adding the bid of each player in the array cardsToBid
        int i = 0;
        // while(cardsToBid1[i]!=0)i++;
        cardsToBid1[warCounter] = player1CardsToBid;
        cardsToBid2[warCounter] = player2CardsToBid;
        cardsToCompare1[warCounter + 1] = deckCards1.peekStack();
        cardsToCompare2[warCounter + 1] = deckCards2.peekStack();
     cout<<endl;

    }

    void resettingBids() // Reset number of cards going for each bid after each round
    {
        delete[] cardsToBid1;
        delete[] cardsToBid2;
        cardsToBid1 = new int[52];
        cardsToBid2 = new int[52];
        warCounter = -1;
        for (int i = 0; i <= 51; i++)
        {
            cardsToBid1[i] = 0;
            cardsToBid2[i] = 0;
        }
    }
    void gameEngine() // Function that generally manages the game (e.g. who wins the game ,... etc.)
    {
        Card cardDraw1, cardDraw2;
        cardDraw1 = queue1.dequeue();
        cardDraw2 = queue2.dequeue();
        deckCards1.push(cardDraw1);
        deckCards2.push(cardDraw2);
        cardsToCompare1[0] = deckCards1.peekStack();
        cardsToCompare2[0] = deckCards2.peekStack();
        while (1)
        {

            if (cardDraw1.number > cardDraw2.number) // player 1 wins this round
            {
                print();
                int counter = deckCards1.size();
                for (int i = 1; i <= counter; i++)
                    queue1.enqueue(deckCards1.pop());

                counter = deckCards2.size();
                for (int i = 1; i <= counter; i++)
                    queue1.enqueue(deckCards2.pop());
                cardDraw1 = queue1.dequeue();
                cardDraw2 = queue2.dequeue();
                deckCards1.push(cardDraw1);
                deckCards2.push(cardDraw2);
                cardsToCompare1[0] = deckCards1.peekStack();
                cardsToCompare2[0] = deckCards2.peekStack();
                if(warCounter>-1)
                {
                     auto end_war = std::chrono::system_clock::now();
                    std::chrono::duration<double> elapsed_seconds = end_war - start_war;
                    //time_taken *= 1e-9;
                    cout << "Elapsed time in nanoseconds: "<<elapsed_seconds.count()<<setprecision(9);
                    //cout<<endl;
                    Sleep(3000);
                }
                resettingBids();
            }
            else if (cardDraw1.number < cardDraw2.number) // player 2 wins this round
            {
                print();
                int counter = deckCards1.size();
                for (int i = 1; i <= counter; i++)
                    queue2.enqueue(deckCards1.pop());
                counter = deckCards2.size();
                for (int i = 1; i <= counter; i++)
                    queue2.enqueue(deckCards2.pop());
                cardDraw1 = queue1.dequeue();
                cardDraw2 = queue2.dequeue();
                deckCards1.push(cardDraw1);
                deckCards2.push(cardDraw2);
                cardsToCompare1[0] = deckCards1.peekStack();
                cardsToCompare2[0] = deckCards2.peekStack();
                if(warCounter>-1)
                {
                    auto end_war = std::chrono::system_clock::now();
                    std::chrono::duration<double> elapsed_seconds = end_war - start_war;
                    cout << "Elapsed time in nanoseconds: "<<elapsed_seconds.count()<<setprecision(9);
                    //cout<<endl;
                    Sleep(3000);
                }
                resettingBids();
            }
            else
            {
                warCounter++;
                globalWarCounter++;
                print();
                askForWar();
                cardDraw1 = deckCards1.peekStack();
                cardDraw2 = deckCards2.peekStack();
                continue; // we enter the loop again, but we compare different cards according to the bids
            }

            if (queue2.isEmpty())
            {
                cout << "!!! Player 1 wins !!! \n";
                return;
            }
            else if (queue1.isEmpty())
            {
                cout << "!!! Player 2 wins !!! \n";
                return;
            }
        }
    }
};
int main()
{
    std::chrono::time_point<std::chrono::system_clock> start, end;
    start = std::chrono::system_clock::now();
    CardWarGame *cardWarGame = new CardWarGame();
    char playAgain;
    while (1)
    {
        cardWarGame->gameEngine();
        cout << "if you want to play again press r , if you want to end program press any button ";
        cin >> playAgain;
        if (playAgain == 'r')
        {
            delete cardWarGame;
            cardWarGame = new CardWarGame();
            continue;
        }
        else
            break;
    }
    end = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsed_seconds = end - start;
    std::cout << "elapsed time for whole game: " << elapsed_seconds.count() << "s\n";
    return 0;
}