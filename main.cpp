#include <iostream>
using namespace std;
//SPADE   "\x06"
//CLUB    "\x05"
//HEART   "\x03"
//DIAMOND "\x04"
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

    // variables that represent the cards that will be used in the war
   Node* deckCards1= new Node;
   Node* deckCards2= new Node;
    //Variables that represent how many cards to draw for each player in the current card war
    int cardsToBid1[52]={0}; 
    int cardsToBid2[52]={0};
public:

   CardWarGame(){
   //TODO:: omar ashraf will make a constructor that will prepare two queues that represent cards in each player hands and at the end of the constructor it will call Game Engine function to start the game
   }
   void print(){
       cout << "           player 1            VS                player  2" <<
            endl <<
            "            " <<
            queue1.size() <<                     //tell each player how many cards he has in his hands
            " Cards" <<
            "                              " <<
            queue2.size() <<
            " Cards" <<
            endl<<"____________________________________________________________________"<<endl;
       Card card1 =deckCards1->getnth(deckCards1,1), card2=deckCards2->getnth(deckCards2,1);
       printCards(card1,card2);
       int currentCardNumber1=1,currentCardNumber2=1;
       Card flippedCard,emptyCard;
       flippedCard.number=0;
       emptyCard.number=-1;
       for (int i=0;cardsToBid1[i]!=0&&cardsToBid2[i];i++)
       {
           for(int j=1;j<=(cardsToBid1[i]>cardsToBid2[i]?cardsToBid1[i]:cardsToBid2[i]);j++) //the loop will iterate until j becomes equal the greater between the number of cards to bid the two players choose
           {
               printCards((j<cardsToBid1[i]?flippedCard:(j==cardsToBid1[i]?deckCards1->getnth(deckCards1,currentCardNumber1):emptyCard)),
                          (j<cardsToBid2[i]?flippedCard:(j==cardsToBid2[i]?deckCards2->getnth(deckCards1,currentCardNumber2):emptyCard)));
               if(j<=cardsToBid1[i])
                   currentCardNumber1++;
               if(j<=cardsToBid2[i])
                   currentCardNumber2++;
           }
       }
       cout<<"                         comparing between"<<endl;
       printCards(deckCards1->getnth(deckCards1,currentCardNumber1),deckCards2->getnth(deckCards2,currentCardNumber2));
   }
   void printCards(Card card1,Card card2){
       /*
        print cards function prints two cards , it can print one faced up card and the other is flipped
        by giving value 0 to the number of the flipped card, and it can also print one card only by giving -1
        to the number of the absent card
        */
       if (card1.number>0&&card2.number>0) {
           //print type and number of the card
           cout << "              " <<
                (card1.number < 11 ? to_string(card1.number) : (card1.number == J ? "J" : (card1.number == K ? "K"
                                                                                                             : "Q"))) <<
                (card1.type == Club ? '\x05' : (card1.type == Spade ? '\x06' : (card1.type == Diamond ? '\x04'
                                                                                                      : '\x03'))) <<
                "                                   " <<
                (card2.number < 11 ? to_string(card2.number) : (card2.number == J ? "J" : (card2.number == K ? "K"
                                                                                                             : "Q"))) <<
                (card2.type == Club ? '\x05' : (card2.type == Spade ? '\x06' : (card2.type == Diamond ? '\x04'
                                                                                                      : '\x03'))) <<
                endl;
       } else if (card1.number<=0&&card2.number>0){
           //print type and number of the card
           cout << (card1.number==0?"            Flipped                                 ":"                                                    " )<<
                (card2.number < 11 ? to_string(card2.number) : (card2.number == J ? "J" : (card2.number == K ? "K": "Q"))) <<
                (card2.type == Club ? '\x05' : (card2.type == Spade ? '\x06' : (card2.type == Diamond ? '\x04': '\x03'))) <<
                endl;
       } else if (card1.number>0&&card2.number<=0){
           //print type and number of the card
           cout << "              " <<
                (card1.number < 11 ? to_string(card1.number) : (card1.number == J ? "J" : (card1.number == K ? "K"
                                                                                                             : "Q"))) <<
                (card1.type == Club ? '\x05' : (card1.type == Spade ? '\x06' : (card1.type == Diamond ? '\x04': '\x03'))) <<
                (card2.number==0?"                                 Flipped":" ")<<endl;
       }
   }
   void askForWar(){
   cout<<"!!!this round ends to draw!!! \n \nwe have to play another round"<<endl<<"player 1! \nhow many cards you want to bid in this war?"<<endl;
   int player1CardsToBid;
   cin>>player1CardsToBid;
   while(player1CardsToBid>queue1.size())
   {cout<<"you don't have enough cards , you have only "<<queue1.size()<<" cards\n";
   cin>>player1CardsToBid;
   }
   cout<<"player 2! \nhow many cards you want to bid in this war?"<<endl;
   int player2CardsToBid;
   cin>>player2CardsToBid;
   while(player2CardsToBid>queue2.size())
   {
    cout<<"you don't have enough cards , you have only "<<queue1.size()<<" cards\n";
    cin>>player2CardsToBid;
    }
    //adding the bid of each player in the array cardsToBid
    int i=0;
    while(cardsToBid1[i]!=0)i++;
    cardsToBid1[i]=player1CardsToBid;
    i=0;
    while(cardsToBid2[i]!=0)i++;
    cardsToBid2[i]=player1CardsToBid;
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
     cards[0]={3,5};
     cards[1]={2,3};
     cards[2]={1,7};
     cards[3]={4,6};
     cards[4]={3,J};
    Node *head=NULL;
    for(int i=0;i<5;i++)
    head->listAppend(&head,cards[i]);
    return 0;
}
