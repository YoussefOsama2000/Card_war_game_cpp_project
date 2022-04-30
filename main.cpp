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
                Out_Card = data[front++];
            
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

class Node
{
    public:
        Card card;
        Node *next;


        void listAppend(Node **head_ref,Card new_card)
            {
                Node *tmp = *head_ref;
                Node *new_node = new Node();
                new_node->card = new_card;
                new_node->next = NULL;
                if (!tmp)
                {
                    *head_ref = new_node;
                    return;
                }
                while (tmp)
                {
                    if (!tmp->next)
                    {
                        tmp->next = new_node;
                        return;     //this line prevents inf loop
                    }
                    tmp = tmp->next;
                }
            }

        void deleteList(Node** head_ref)
            {

                /* deref head_ref to get the real head */
                Node* current = *head_ref;
                Node* next = NULL;

                while (current != NULL)
                {
                    next = current->next;
                    delete current;
                    current = next;
                }
                *head_ref = NULL;
            }

        Card getnth(Node *head_ref, int pos)
            {
                for (int i=1; i < pos; i++)
                {
                    if (head_ref)
                    {
                        head_ref = head_ref->next;
                    }
                    else
                    {
                        cout << "Out of range\n";
                        return head_ref->card;
                    }
                }
                return head_ref->card;
            }

        int size(Node *head_ref)
            {
                int i = 0;
                while (head_ref)
                {
                    i++;
                    head_ref = head_ref->next;
                }
                return i;
            }
};





class CardWarGame{
    //Queues that represent what in players hands
    Queue queue1;
    Queue queue2;
    // variables that represents the cards that will be used in the war
    Node* deckCards1= new Node(); 
    Node* deckCards2= new Node();
    //Variables that represent how many cards to draw for each player in the current card war
    int cardsToBid1[52]={0}; 
    int cardsToBid2[52]={0};
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
        int warCounter=-1;
        Card warCard1,warCard2,cardDraw1,cardDraw2;

        cardDraw1=queue1.dequeue();
        cardDraw2=queue2.dequeue();
        deckCards1->listAppend(&deckCards1,cardDraw1);
        deckCards2->listAppend(&deckCards2,cardDraw2);

        while(1)
        {   
            print();

            if(cardDraw1.number>cardDraw2.number)    //player 1 wins this round
                {
                    for(int i=1; i<=deckCards1->size(deckCards1);i++)
                        queue1.enqueue(deckCards1->getnth(deckCards1,i));

                    deckCards1->deleteList(&deckCards1);

                    for(int i=1; i<=deckCards2->size(deckCards2);i++)
                        queue1.enqueue(deckCards2->getnth(deckCards2,i));

                    deckCards2->deleteList(&deckCards2);
                }
            else if (cardDraw1.number<cardDraw2.number)     //player 2 wins this round
                {
                    for(int i=1; i<=deckCards1->size(deckCards1);i++)
                        queue2.enqueue(deckCards1->getnth(deckCards1,i));

                    deckCards1->deleteList(&deckCards1);

                    for(int i=1; i<=deckCards2->size(deckCards2);i++)
                        queue2.enqueue(deckCards2->getnth(deckCards2,i));

                    deckCards2->deleteList(&deckCards2);
                }
            else
                {   
                    warCounter++;
                    askForWar();
                    cardDraw1=deckCards1->getnth(deckCards1,cardsToBid1[warCounter]);
                    cardDraw2=deckCards1->getnth(deckCards2,cardsToBid2[warCounter]);
                    continue;   //we enter the loop again but we compare different cards according to the bids 
                }

            if (queue2.isEmpty())
            {
                cout<<"!!! Player 1 wins !!! \n";
                return;
            }
            else if (queue1.isEmpty())
            {
                cout<<"!!! Player 2 wins !!! \n";
                return;
            }

        }
   }
};
int main() {
     Card cards[5];
    // Queue new_queue;
    // Card current;

     cards[0]={3,5};
     cards[1]={2,3};
     cards[2]={1,7};
     cards[3]={4,6};
     cards[4]={3,J};

    // for(int i=0;i<5;i++)
    //     new_queue.enqueue(cards[i]);

    //   cout<<new_queue.size()<<endl<<endl;

    // for(int i=0;i<5;i++)
    // {
    //     current=new_queue.dequeue();
    //     cout<<current.type<<current.number<<endl;
    // }
    
    Node *head=NULL;
    for(int i=0;i<5;i++)
    head->listAppend(&head,cards[i]);
    // node *tmp=head;
    // for(int i=0;i<5;i++){
    // Card new_card=tmp->card;
    // cout<<new_card.type<<"\n";
    // cout<<new_card.number<<"\n";
    // tmp=tmp->next;
    // }
    //head->deleteList(&head);
    //Card test_card=head->card;
    //cout<<test_card.type<<"\n";
    // cout<<test_card.number<<"\n";
    //new_card=deckCards1->getnth(deckCards1,5);
    return 0;
}
