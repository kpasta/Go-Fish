#include <iostream>
#include <cmath>
using namespace std;
class card;
class deck;
    const char* TWEENCARDS = "  ";

class deck
{
    public:
        deck();
        void push( int, char );
        void print();
        void shuffle();
    friend ostream &operator<<( ostream &, const deck & );
    private:
        card *top;
};

class card
{
    private:
        card();
        int rank;
        char suit;
        card *next;
    friend class deck;
    friend ostream &operator<<( ostream &, const deck & );
};
///////////////////////////////////////////////////////////////////////////
int main()
{
    deck one;

    one.shuffle();
    cout << one;

    return 0;
}
///////////////////////////////////////////////////////////////////////////
deck::deck()
{   
    top = NULL;
    card *temp = NULL;

    for( int i=0; i<52 ; i++ )
    {
        temp = new card();
        temp->rank = i+1;
        if( i < 13 )
        { temp->suit = 'S'; }
        else if( i >=13 && i < 26 )
        { 
            temp->suit = 'H'; 
            temp->rank -= 13;
        }
        else if( i >=26 && i < 39 )
        { 
            temp->suit = 'D'; 
            temp->rank -= 26;
        }
        else
        { 
            temp->suit = 'C'; 
            temp->rank -= 39;
        }
        temp->next = top;
        top = temp;
    }
    temp = NULL;
}

void deck::push( int r, char s )
{
    card *temp = new card();
    temp->rank = r;
    temp->suit = s;
    temp->next = top;
    top = temp;
}

void deck::shuffle()
{
    card *temp1 = top;
    card *temp2 = top;
    int shuffleNum;
    int move1, move2;
    char tempSuit;
    int tempRank;

    srand( time(NULL) );

    shuffleNum = rand() % 20 + 50;
    cout << shuffleNum;

    for( int i=0; i < shuffleNum; i++ )
    {
        move1 = rand() % 51 + 1;
        move2 = rand() % 51 + 1;

        for( int i=0; i < move1; i++ )
        { temp1 = temp1->next; }
        for( int i=0; i < move2; i++ )
        { temp2 = temp2->next; }

        tempSuit = temp2->suit;
        tempRank = temp2->rank;

        temp2->rank = temp1->rank;
        temp2->suit = temp1->suit;

        temp1->rank = tempRank;
        temp1->suit = tempSuit;

        temp2 = top;
        temp1 = top;
    }
}

card::card()
{
    rank = 0;
    suit = '\0';
    next = NULL;
}

ostream &operator<<( ostream &out, const deck &rhs )
{
    card *rtemp = rhs.top;
    card *stemp = rhs.top;
    int cardCtr;
    int xCards = 7;
    for( cardCtr = 0; rtemp!=NULL; cardCtr++ )
    {   rtemp = rtemp->next; }

    rtemp = rhs.top;

    while( rtemp != NULL )
    {
        cardCtr -= xCards;
        if( cardCtr < 0 )
        { xCards += cardCtr; }
        for( int i = 0; i < xCards; i++ )
        {   cout << " ---- " << TWEENCARDS;   }
        cout << endl;
        for( int i = 0; i < xCards; i++ )
        {   cout << "|    |" << TWEENCARDS;  }
        cout << endl;
        for( int i = 0; i < xCards; i++ )
        {   cout << "| ";
            switch( rtemp->rank )
                    {
                    case 1:
                        printf( "%2c", 'A' );
                        break;
                    case 11:
                        printf( "%2c", 'J' );
                        break;
                    case 12:
                        printf( "%2c", 'Q' );
                        break;
                    case 13:
                        printf( "%2c", 'K' );
                        break;
                    default:
                        printf( "%2i", rtemp->rank );
                    }
            rtemp = rtemp->next;
            cout << " |" << TWEENCARDS;  
            }
        cout << endl;
        for( int i = 0; i < xCards; i++ )
        {   
            cout << "| ";
            printf( "\%2c", stemp->suit );
            stemp = stemp->next;
            cout << " |" << TWEENCARDS;  
        }    
        cout << endl;
        for( int i = 0; i < xCards; i++ )
        {   cout << "|    |" << TWEENCARDS;  }
        cout << endl;
        for( int i = 0; i < xCards; i++ )
        {   cout << " ---- " << TWEENCARDS;   }
        cout << endl;
    }
    return out;
}

