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

int main()
{
    deck one;
    cout << one;

    system("PAUSE");
    return 0;
}
deck::deck()
{   
    top = NULL;
    card *temp = NULL;

    for( int i=0; i<52 ; i++ )
    {
        temp = new card();
        temp->rank = i+1;
        if( i < 13 )
        { temp->suit = '\3'; }
        else if( i >=13 && i < 26 )
        { 
            temp->suit = '\4'; 
            temp->rank -= 13;
        }
        else if( i >=26 && i < 39 )
        { 
            temp->suit = '\5'; 
            temp->rank -= 26;
        }
        else
        { 
            temp->suit = '\6'; 
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

