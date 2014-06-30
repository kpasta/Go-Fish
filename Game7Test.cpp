#include <iostream>
#include <cmath>
using namespace std;
class card;
class deck;
class player;
class hand;
class turn;
class game;
    const char* TWEENCARDS = "  ";

    const char HEART = '\3';
    const char DIAMOND = '\4';
    const char CLUB = '\5';
    const char SPADE = '\6';

class deck
{
    public:
        deck();
        ~deck();
        void shuffle();
        bool isEmpty();
        void clear();
        void push( int, char );
        card* pop();
    private:
        card *top;
};

class hand
{
    public:
        hand();
        ~hand();
        void insert( card* );
        bool search( int );
        bool goToPrior();
        bool findBook();
        bool isEmpty();
        card* remove( );
        void clear();
    friend ostream &operator<<( ostream &, const hand & );
    friend class player;
    private:
        card *head, *cursor;
};

class player
{
    public:
        player();
        //~player();
        void deal( deck &, int );
        void displayHand();
        bool getCard( int, player );
        bool goFish( deck & );
        void findBook();
        player *choosePlayer( turn );
        int chooseRank();
        void nameYourself();
        int length( char * );
        void copy( char *, char * );
        bool compare( char *, char * );
        player &operator=( const player & );
        int countCards();
    friend ostream &operator<<( ostream &, const player & );
    friend class turn;
    friend class game;
    private:
        int book;
        hand *myHand;
        bool nowTurn;
        char *name;
    
};      

class card
{
    private:
        card();
        int rank;
        char suit;
        card *next;
    friend class deck;
    friend class hand;
    friend class player;
    friend ostream &operator<<( ostream &, const card & );
    friend ostream &operator<<( ostream &, const hand & );
};

class turn
{
    public:
        turn();
        turn( int );
        ~turn();
        player deQueue();
        bool enQueue( player );
        bool isEmpty();
        bool isFull();
    friend ostream &operator<<( ostream &, const game & );
    friend class game;
    friend class player;
    private:
        int front, rear, max;
        player *data;
};

class game
{
    public:
        game();
        game( int );
        ~game();
        void play( int );
        int numPlayers();
        bool findWinner();
        void displayOthers( int );
        bool quitGame();
        bool saveGame();
        player findMostBooks();
    friend ostream &operator<<( ostream &, const game & );
    private:
        deck *deckPtr;
        turn *turnPtr;
        player *playerPtr;
        
};
///////////////////////////////////////////////////////////////////////////
int main()
{
    game temp;
    int playerCount = temp.numPlayers();
    game one( playerCount ); 
    one.play( playerCount );
    system("PAUSE");
    return 0;
}
///////////////////////////////////////////////////////////////////////////
void game::play( int playerCount )
{
    player temp;
    player *opponent = NULL;
    bool toQuit = false;
    int tempRank = 0;
    // first will name all the players
    for( int i=0; i<playerCount; i++ )
    {
        temp = turnPtr->deQueue();
        temp.deal( *deckPtr, playerCount );        
        printf( "Player %i, ", i+1 );
        temp.nameYourself();
        temp.nowTurn = false;
        cout << temp << endl;
        turnPtr->enQueue( temp ); 
        cout << "Press a key to continue... ";
        cin.get();
        cin.ignore();
        cout << endl << endl << endl << endl << endl << endl
             << endl << endl << endl << endl << endl << endl
             << endl << endl << endl << endl << endl << endl
             << endl << endl << endl
             << "--------------------------------------" << endl;       
    }  

    while( toQuit == false )
    {
        cout << endl;
        cout << "--------------------------------------" << endl;
        temp = turnPtr->deQueue();
        while( temp.nowTurn == true )
        {            
               cout << temp << endl;
               displayOthers( playerCount );
               if( playerCount != 2 )
               {   opponent = temp.choosePlayer( *turnPtr ); }
               else
               { opponent = turnPtr->data; }
               tempRank = temp.chooseRank();
               if( !temp.getCard( tempRank, *opponent ) )
               { 
                 cout << "Opponent says: 'GO FISH!!' ";
                 temp.goFish( *deckPtr ); 
               }
               temp.findBook();
               if( findWinner() )
               { toQuit = true; }
               else if( quitGame() )
               { toQuit = true; }
        }
        turnPtr->enQueue( temp ); 
        cout << "Your turn is done" << endl 
             << "Press a key to continue... ";
        cin.get();
        cin.ignore();
        cout << endl << endl << endl << endl << endl << endl
             << endl << endl << endl << endl << endl << endl
             << endl << endl << endl << endl << endl << endl
             << endl << endl << endl
             << "--------------------------------------" << endl;  
    }
    cout << "END GAME!!" << endl;
}
bool game::quitGame()
{
     char response;
     cout << "Quit game (Y/N): ";
     cin >> response;
     if( response == 'N' || response == 'n' )
     {   return false;   }
     return true;
}
bool game::saveGame()
{
     char response;
     cout << "Save game (Y/N): ";
     cin >> response;
     if( response == 'N' || response == 'n' )
     { return false; }
     return true;    
}
bool game::findWinner()
{
     player temp;
     bool handEmpty = false;
     int totalBooks = 0;
     for( int i=0; i <= turnPtr->rear; i++ )
     {
            temp = turnPtr->deQueue();
            totalBooks += temp.book;            
            if( temp.myHand->isEmpty() )
            { handEmpty = true; }
            temp.nowTurn = false;
            turnPtr->enQueue( temp );      
     }
     if( totalBooks == 13 || deckPtr->isEmpty() || handEmpty == true  )
     {
          temp = findMostBooks();
          printf( "%s won with %i books.", temp.name, temp.book );
          return true;
     }
     return false;
}
player game::findMostBooks()
{
       player temp;
       int maxBooks = 0, tempBook = 0;
       
       temp = turnPtr->deQueue();
       maxBooks = temp.book;
       temp.nowTurn = false;
       turnPtr->enQueue( temp );
     for( int i=0; i <= turnPtr->rear; i++ )
     {
            temp = turnPtr->deQueue();
            tempBook = temp.book;
            if( tempBook > maxBooks )
            { maxBooks = tempBook; }
            temp.nowTurn = false;
            turnPtr->enQueue( temp );      
     }
     
     for( int i=0; i <= turnPtr->rear; i++ )
     {
            temp = turnPtr->deQueue();
            tempBook = temp.book;
            if( tempBook == maxBooks )
            { return temp; }
            temp.nowTurn = false;
            turnPtr->enQueue( temp );      
     }
     return temp;
}
void game::displayOthers( int playerCount )
{
     player temp;
     int ctr = 0;
     for( int i=0; i <= turnPtr->rear; i++ )
     {
            temp = turnPtr->deQueue();
            ctr = temp.countCards();
            printf( "%s has %i cards", temp.name, ctr );
            if( i <= turnPtr->rear )
            { cout << "  |  "; }                
            temp.nowTurn = false;
            turnPtr->enQueue( temp );        
     }     
     cout << endl;
}
game::game( )
{
    deckPtr = new deck;
    turnPtr = new turn;

    playerPtr = turnPtr->data;

    deckPtr->shuffle();
}
game::game( int players )
{
    deckPtr = new deck;
    turnPtr = new turn( players );

    playerPtr = turnPtr->data;

    deckPtr->shuffle();

}
game::~game()
{
    delete []deckPtr;
    delete []turnPtr;
    
    deckPtr = NULL;
    turnPtr = NULL;
    playerPtr = NULL;
}
int game::numPlayers()
{   
    int count = 2;
    cout << "Enter number of players: ";
    cin >> count;
    return count;
}

ostream &operator<<( ostream &out, const game &rhs )
{
    player *temp = rhs.turnPtr->data;
    for( int i=0; i < rhs.turnPtr->max; i++ )
    {   out << temp[i]; }
    return out;
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
        { temp->suit = SPADE; }
        else if( i >=13 && i < 26 )
        { 
            temp->suit = HEART; 
            temp->rank -= 13;
        }
        else if( i >=26 && i < 39 )
        { 
            temp->suit = DIAMOND; 
            temp->rank -= 26;
        }
        else
        { 
            temp->suit = CLUB; 
            temp->rank -= 39;
        }
        temp->next = top;
        top = temp;
    }
    temp = NULL;
}
bool deck::isEmpty()
{   
    if( top == NULL )
    { return true;  }
    return false;
}
deck::~deck()
{
    clear();   
}
void deck::clear()
{
    card *temp = top;
    while( top != NULL )
    {
        top = top->next;
        delete temp;
        temp = top;
    }
}
/////////////////////////////////////////////////////////////////////////////
void deck::push( int r, char s )
{
    card *temp = new card();
    temp->rank = r;
    temp->suit = s;
    temp->next = top;
    top = temp;
}

card* deck::pop()
{
    card* temp = top;
    top = top->next;
    temp->next = NULL;
    return temp;
}
/////////////////////////////////////////////////////////////////////////////
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

    for( int i=0; i < shuffleNum; i++ )
    {
        move1 = rand() % 51 + 0;
        move2 = rand() % 51 + 0;

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
/////////////////////////////////////////////////////////////////////////
hand::hand()
{
    head = NULL;
    cursor = NULL;
}
hand::~hand()
{
    clear();   
}
void hand::clear()
{
    cursor = head;
    while( head != NULL )
    {
        head = head->next;
        delete cursor;
        cursor = head;
    }
}
bool hand::goToPrior()
{
    card *temp = cursor;

    if( cursor == head )
    {   return false;   }

    cursor = head;
    while( cursor->next != temp )
    { cursor = cursor->next; }
    temp = NULL;
    return true;
}
void hand::insert( card *one )
{
    cursor = one;
    cursor->next = head;
    head = cursor;
}
card* hand::remove()
{
    card *temp = cursor; // temp will point to the card being removed
    if( !goToPrior() ) // if the cursor is already at top
    {   
        // then head and cursor will move down one
        head = head->next;
        cursor = head; 
        // if it's the only node, they will both equal NULL;
        // temp->next will already be NULL then
    }
    // if the cursor is not at the top, cursor will move to prior card
    else
    {
        //  cursor's next will now skip temp's card to temp's next
        cursor->next = temp->next;
        //  temp->next will now be set to null;
        temp->next = NULL;
    }
    // function will return the pointer pointing to the removed card;
    return temp;
    
}
bool hand::search( int searchRank )
{   
    // search will always start at head of list
    cursor = head;
    while( cursor != NULL )
    {
        if( searchRank == cursor->rank )
        {
            return true;
        }
        cursor = cursor->next;
    }
    cursor = head;
    return false;
}
bool hand::isEmpty()
{
     if( head == NULL )
     { return true; }
     return false;
}
bool hand::findBook()
{
    card *temp = head;
    int removeRank = 0;
    card *removeTemp = NULL;
    int makeBook;
    
    //FIrst Loop starts temp at start of hand;
    while( temp != NULL )
    { 
        makeBook = 0;

    //Loops the test from the start of the hand.
        cursor = head;
        while( cursor != NULL )
        {
        // compare each card with temp
            if( temp->rank == cursor->rank )
            {   makeBook++; }
            cursor = cursor->next;
            // if there are four cards of the same rank
            if( makeBook == 4 )
            {   
                removeRank = temp->rank;
                // go through and remove the cards
                for( int i=0;i<4;i++ )
                {
                    // move cursor to where the rank is found
                    search( removeRank );
                    // remove card
                    removeTemp = remove();
                    delete removeTemp;
                }
                // will exit out of loop and return true;                
                return true;  
            }
        }
        // temp will go to next card
        temp = temp->next;
    }
    return false;
}
/////////////////////////////////////////////////////////////////////////
card::card()
{
    rank = 0;
    suit = '\0';
    next = NULL;
}
ostream &operator<<( ostream &out, const card &rhs )
{
    cout << " ---- " << TWEENCARDS << endl;
    cout << "|    |" << TWEENCARDS << endl;
    cout << "| ";
    switch( rhs.rank )
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
         printf( "%2i", rhs.rank );
    }
    cout << " |" << TWEENCARDS << endl;
    cout << "| ";
    printf( "\%2c", rhs.suit );
    cout << " |" << TWEENCARDS << endl;  
    cout << "|    |" << TWEENCARDS << endl;
    cout << " ---- " << TWEENCARDS << endl;    

    return out;
}
//////////////////////////////////////////////////////////////////////////
ostream &operator<<( ostream &out, const hand &rhs )
{
    card *rtemp = rhs.head;
    card *stemp = rhs.head;
    int cardCtr;
    int xCards = 7;
    for( cardCtr = 0; rtemp!=NULL; cardCtr++ )
    {   rtemp = rtemp->next; }

    rtemp = rhs.head;
    if( rtemp == NULL )
    {   cout << "Player Has No Cards" << endl; }
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
    stemp = NULL;
    rtemp = NULL;
    return out;
}

//////////////////////////////////////////////////////////
player::player()
{
    book = 0;
    myHand = new hand();
    nowTurn = false;
    name = new char[15];
    *name = '\0';
}
void player::deal( deck &one, int players )
{
    if( players == 4 || players == 5 )
    {
        for( int i=0; i<5; i++ )
        { myHand->insert( one.pop() ); }
    }
    else
    {
        for( int i=0; i<7; i++ )
        { myHand->insert( one.pop() ); }
    }
}
int player::countCards()
{
    card *temp = myHand->head;
    int ctr = 0;
    while( temp != NULL )
    { 
         temp = temp->next;
         ctr++; 
    }
    return ctr;    
}
ostream &operator<<( ostream &out, const player &rhs )
{
    out << rhs.name << endl;
    out << *(rhs.myHand);
    out << "Books: " << rhs.book << endl;
    return out;
}

bool player::getCard( int cardRank, player chosenPlayers )
{
    card *temp;
    // if rank is not in player's hand return false, 
        // if search is false
    if( !myHand->search( cardRank ) )
    {   
        cout << "You Don't have this Rank" << endl;
        return false;   
    }
    // if it is, then function will continue
    // will find if in opponenet's hand
    // if it isn't will return false
    if( !chosenPlayers.myHand->search( cardRank ) )
    {   
        cout << "They don't have this card" << endl;
        return false;   
    }
   
    // if it is then the function will continue
    // will loop until no more cards are found in opponent's hand
        // while search is true, cursor is moved
    while( chosenPlayers.myHand->search( cardRank ) ) 
    {   
        // point temp to removed card
        temp = chosenPlayers.myHand->remove();
        cout << "You got this card: " << endl << *temp;
        // card is inserted into player's hand
        myHand->insert( temp );
    }
    temp = NULL;
    return true;
}
bool player::goFish( deck &one )
{
    card *temp;
    // if deck is empty return false
    if( one.isEmpty() )
    {   return false;   }
    // else pop card from top and insert in hand
    temp = one.pop();
    
    cout << "You picked up this card: " << endl << *temp;
    myHand->insert( temp );
    
    temp = NULL;
    // their turn will now equal false;
    nowTurn = false;
    return true;
}
int player::chooseRank()
{
    char test[3];       
    int rank;
    cout << "Choose the card's rank: ";
    cin >> test;

    switch( test[0] )
    {
        case 'A': return 1;
        case 'J': return 11;
        case 'Q': return 12;
        case 'K': return 13;
        case '1': 
            if( test[1] == '0' )
            {   rank = 10;  }
            else if( test[1] == '1' )
            {   rank = 11;  }
            else if( test[1] == '2' )
            {   rank = 12;  }
            else if( test[1] == '3' )
            {   rank = 13;  }
            else
            {   rank = 1;   }
            break;
        case '2': case '3': case '4': case '5': case '6': case '7': 
        case '8': case '9': 
            return test[0] - '0';
        default:
            rank = 0;
    }
    return rank;
}

player* player::choosePlayer( turn one )
{
    player *temp = NULL;
    player *findOpponent = NULL;
    char *tempName = new char[15];
    do
    {
        findOpponent = one.data;
        cout << "Who will you ask a card from? ";
        cin >> tempName;

        for( int i=0; i <= one.rear; i++ )
        {
             if( compare( tempName, findOpponent->name ) )
             {   temp = findOpponent; }
             else
             { 
               temp = NULL; 
               findOpponent++;
             }
        }
        if( temp == NULL )
        { cout << "opponent not found" << endl; }
    }
    while( temp == NULL );

    return temp;
}

void player::nameYourself()
{
    delete []name;
    char *temp = new char[15];
    int len = 0;
    cout << "What is your name? ";
    cin >> temp;
    
    len = length(temp);
    name = new char[len + 1];
    copy( name, temp );  
    delete temp;  
}

bool player::compare( char *a, char *b )
{
    int aLen, bLen;
    aLen = length( a );
    bLen = length( b );
    if( aLen != bLen )
    { return false; }

    for( int i=0; i<aLen; i++ )
    {
         if( a[i] != b[i] )
         { return false; }
    }
    return true;
}
int player::length( char *cptr )
{
    int len = 0;

    while( *cptr != '\0' )
    {
        len++;
        cptr++;
    }
    return len;
}
void player::copy( char *a, char *b )
{
	while( *b != '\0' )
	{
	*a = *b;
	a++;
	b++;
	}
	*a = '\0';
}

void player::findBook()
{
    if( myHand->findBook() )
    { 
        cout << "You Made A Book!!" << endl;
        book++; 
    }
}
player &player::operator=( const player &rhs )
{
        book = rhs.book;
        myHand = rhs.myHand;
        name = rhs.name;
        nowTurn = rhs.nowTurn;
    	return *this;
}
////////////////////////////////////////////////////////////////////////////

turn::turn()
{
    max = 2;
    data = new player[max]; // default 2 players
    front = 0;
    rear = max-1;
}

turn::turn( int numOfPlayers )
{
    max = numOfPlayers;
    data = new player[max]; 
    front = 0;
    rear = max-1;  
}
bool turn::enQueue( player turnDone )
{
    rear++;
    if( rear == max )
    {   return false; }
    data[rear] = turnDone;
    return true;
}
player turn::deQueue()
{
    player hisTurn; // temp
    if( isEmpty() )
    {   return hisTurn;  }

    hisTurn = data[front];
    hisTurn.nowTurn = true;
    for( int i=0; i<max; i++ )
    {
         data[i] = data[i+1];
    }
    rear--;
    return hisTurn;
}
bool turn::isEmpty()
{
    if( rear == -1 )
    { return true; }
    return false;
}

turn::~turn()
{
    max = 0;
    delete []data; 
    front = -1;
    rear = -1;     
}
