#include <iostream>
using namespace std;
<<<<<<< HEAD

#define J 11
#define Q 12
#define K 13
#define Club 1
#define Heart 2
#define Spade 3
#define Diamond 4

=======
class Queue{
    //TODO::will implement the queue here
};
>>>>>>> 42c6ead28c8d9dcb3a0c91f0efa4304c69eb8726
struct Card
{
    int type=0;
    int number=0;
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

            if(!isFull()) 
            {
                
                if(back == 51) 
                {
                    back = -1;            
                }       

                data[++back] = New_Card;
                itemCount++;
            } 
            else 
            {
                cout<<"----- Full Queue -----\n";
            }
        }  

        struct Card dequeue() 
        {
        
            struct Card Out_Card;

            if(!isEmpty())
            {
                struct Card Out_Card = data[front++];
            
                if(front == 52) 
                {
                    front = 0;
                }
            
                itemCount--;
                
            } 
            else 
            {
                cout<<"----- Empty Queue -----\n";
            }

            return Out_Card;

        }
};
class CardWarGame{
    //Queues that represent what in players hands
    Queue queue1;
    Queue queue2;
    // variables that represents the cards that will be used in the war
   Card *deckCards1= new Card[26]; //declar arrays in heap to prevent stack overflow
   Card *deckCards2= new Card[26];
    //Variables that represent how many cards to draw for each player in the current card war
    int cardsToDraw1;
    int CardsToDraw2;
   CardWarGame(){
   //TODO:: omar ashraf will make a constructor that will prepare two queues that represent cards in each player hands and at the end of the constructor it will call Game Engine function to start the game
   }
   void print(){
   //TODO:: osama will make this function that depends on two queues
   }
   void askForWar(){
   //TODO:: osama will ask the two players how many cards they want to draw in this turn and update drawInWar1 and drawInWar2 variables
   }
   void GameEngine(){
   //TODO:: omar sayed will make the function that manage the game at all , and call print function and askForWar function when needed
   }
};
int main() {
   cout << "Hello, World!" << endl;
   cout << "New line" << endl;
    return 0;

}
