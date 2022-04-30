/******************************************************************************
 *
 * Team name: Anubis
 *
 * Team Names: Youssef Osama , Omar Sayed , Omar Ashraf
 *
 * Description: A Card war game
 *
 *******************************************************************************/
#include <iostream>
using namespace std;

#define J 11
#define Q 12
#define K 13
#define Club 1
#define Heart 2
#define Spade 3
#define Diamond 4

struct Card {
	int type = 0;
	int number = 0;
};

class Queue {
private:
	struct Card data[52];
	int front;
	int back;
	int itemCount;

public:
	Queue() {
		front = 0;
		back = -1;
		itemCount = 0;
	}

	bool isEmpty() {
		return itemCount == 0;
	}

	bool isFull() {
		return itemCount == 52;
	}

	int size() {
		return itemCount;
	}

	void enqueue(struct Card New_Card) {

		if (!isFull()) {

			if (back == 51) {
				back = -1;
			}

			data[++back] = New_Card;
			itemCount++;
		} else {
			cout << "----- Full Queue -----\n";
		}
	}

	struct Card dequeue() {

		struct Card Out_Card;

		if (!isEmpty()) {
			Out_Card = data[front++];

			if (front == 52) {
				front = 0;
			}

			itemCount--;

		} else {
			cout << "----- Empty Queue -----\n";
		}

		return Out_Card;

	}
};
class CardWarGame {
public:
	//Queues that represent what in players hands
	Queue queue1;
	Queue queue2;
	// variables that represents the cards that will be used in the war
	Card *deckCards1 = new Card[26]; //declar arrays in heap to prevent stack overflow
	Card *deckCards2 = new Card[26];
	//Variables that represent how many cards to draw for each player in the current card war
	int cardsToDraw1;
	int CardsToDraw2;
	CardWarGame() {
		//TODO:: omar ashraf will make a constructor that will prepare two queues that represent cards in each player hands and at the end of the constructor it will call Game Engine function to start the game
		Card fullDeck[52];
		Card randomizedDeck[52];
		// Creating the full deck in order
		int type=0;
		for (int i = 0; i <= 51; i++) {
			if((i%13)==0)
				{
					type++;

				fullDeck[i+1].type=type;
				}
			fullDeck[i].number=(i%13)+1 ;
			fullDeck[i].type=type ;

		}

		int temp = 0;
		for (int i = 0; i < 52; i++) {
			temp = rand();
			temp = (temp % (51 - 0 + 1)) + 1; // (rand() % (upper – lower + 1)) + lower
			if ((fullDeck[temp].number != 0 && fullDeck[temp].type!=0) && temp < 52) {
				randomizedDeck[i].number = fullDeck[temp].number;
				randomizedDeck[i].type = fullDeck[temp].type;
				fullDeck[temp].number = fullDeck[temp].type = 0;
			} else {
				temp = rand();
				temp = (temp % (52 - 1 + 1)) + 1;
				while ((fullDeck[temp].number == 0 || fullDeck[temp].type==0)) {
					temp++;
					if (temp > 51) {
						temp = temp % 52;
					}
				}

				randomizedDeck[i].number = fullDeck[temp].number;
				randomizedDeck[i].type = fullDeck[temp].type;
				fullDeck[temp].number = fullDeck[temp].type = 0;
			}
		}
		for (int i = 0; i < 26; i++) {
			deckCards1[i] = randomizedDeck[i];
			deckCards2[i] = randomizedDeck[i + 25];
		}
	}

	void print() {
		//TODO:: osama will make this function that depends on two queues
	}
	void askForWar() {
		//TODO:: osama will ask the two players how many cards they want to draw in this turn and update drawInWar1 and drawInWar2 variables
	}
	void GameEngine() {
		//TODO:: omar sayed will make the function that manage the game at all , and call print function and askForWar function when needed
	}
};
int main() {
	Card cards[5];
	Queue new_queue;
	Card current;

	cards[0] = { 3, 5 };
	cards[1] = { 2, 3 };
	cards[2] = { 1, 7 };
	cards[3] = { 4, 6 };
	cards[4] = { 3, J };

	CardWarGame Game;
	for (int i = 0; i < 5; i++)
		new_queue.enqueue(cards[i]);

	cout << new_queue.size() << endl << endl;

	for (int i = 0; i < 5; i++) {
		current = new_queue.dequeue();
		cout << current.type << current.number << endl;
	}

	return 0;
}
