#include <iostream>
using namespace std;
struct Card
{
    int type=0;
    int number=0;
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
