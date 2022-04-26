#include <iostream>
using namespace std;

#define J 11
#define Q 12
#define K 13
#define Club 1
#define Heart 2
#define Spade 3
#define Diamond 4

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
   Card *deckCards1= new Card[26]; //declar arrays in heap to prevent stack overflow
   Card *deckCards2= new Card[26];
};
int main() {
   cout << "Hello, World!" << endl;
   cout << "New line" << endl;
    return 0;

}
