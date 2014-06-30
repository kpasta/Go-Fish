/*//////////////////////////////////////////////
 * Go - Fish
 * Hand, Card Class
 * Player H Implementation
/*//////////////////////////////////////////////

#include <iostream>
#include "player.h"
using namespace std;

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
                    			// move cursor to where the rank is
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

ostream &operator<<( ostream &out, const hand &rhs )
{
    	card *rtemp = rhs.head;
/*    	card *stemp = rhs.head;
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
        	{   cout << " ---- " << "    ";   }
        	cout << endl;
        	for( int i = 0; i < xCards; i++ )
        	{   cout << "|    |" << "    ";  }
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
            	cout << " |" << "    ";  
            	}
        	cout << endl;
        	for( int i = 0; i < xCards; i++ )
        	{   
            		cout << "| ";
            		printf( "\%2c", stemp->suit );
            		stemp = stemp->next;
            		cout << " |" << "    ";  
        	}    
        	cout << endl;
        	for( int i = 0; i < xCards; i++ )
        	{   cout << "|    |" << "    ";  }
        	cout << endl;
        	for( int i = 0; i < xCards; i++ )
        	{   cout << " ---- " << "    ";   }
        	cout << endl;
    	}
    	stemp = NULL;
    	rtemp = NULL;*/

	while( rtemp !=NULL )
	{
		out << rtemp->rank << " " << rtemp->suit << " "; 
		rtemp = rtemp->next;
	}
	cout << endl;
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
player::~player()
{
	book = 0;
	//delete []myHand;
	//myHand = NULL;
	nowTurn = false;
	//delete []name;
	//name = NULL;
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
	card *temp = rhs.myHand->head;    	
	out << rhs.name << endl;
    	out << *(rhs.myHand) << endl;
    	out << "Book: " << rhs.book << endl;
	temp == NULL;
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
        	cout << "You got this card: ";
		switch( temp->rank )
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
                        	printf( "%2i", temp->rank );
                    	}
		cout << temp->suit << endl;
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
    
    	cout << "You picked up this card: ";
	switch( temp->rank )
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
	  	printf( "%2i", temp->rank );
      	}
	cout << temp->suit << endl;
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
//////////////////////////////////////////////////////////
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
bool turn::clear()
{
	front = -1;
	rear = -1;
}

