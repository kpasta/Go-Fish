#include <iostream>
#include <cmath>
using namespace std;


    const char HEART = '\3';
    const char DIAMOND = '\4';
    const char CLUB = '\5';
    const char SPADE = '\6';
    const char ACE = 'A';
    const char* TWEENCARDS = "  ";

int main()
{
    int cardctr = 52;
    int xCards = 4;
    int hand[52];

    for( int i = 0; i < 52; i++ )
    {
    hand[i] = i+1;
    }
    for( int i = 0; i < xCards; i++ )
    { cout << hand[i] << " "; }
    cout << endl;

for( int ctr = 0; ctr < 13; ctr++ )
{
    
    for( int i = 0; i < xCards; i++ )
    {   cout << " ---- " << TWEENCARDS;   }
    cout << endl;
    for( int i = 0; i < xCards; i++ )
    {   cout << "|    |" << TWEENCARDS;  }
    cout << endl;
    for( int i = 0; i < xCards; i++ )
    {   cout << "| ";
        printf( "%2i", hand[ctr] );
        cout << " |" << TWEENCARDS;  
    }
    cout << endl;
    for( int i = 0; i < xCards; i++ )
    {   cout << "| ";
        printf( "\%2c", i+3 );
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

cout << endl;
    system("PAUSE");
    return 0;
}
