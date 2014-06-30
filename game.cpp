/*//////////////////////////////////////////////
 * Go - Fish
 * Game Class
 * Game H Implimentation
/*//////////////////////////////////////////////

#include <iostream>
#include <fstream>
#include "game.h"

using namespace std;

void game::play( int playerCount )
{	player temp;
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
              	}
        	turnPtr->enQueue( temp ); 
               	
		if( findWinner() )
               	{ toQuit = true; }
		else if( quitGame() )
               	{ 
			saveGame();
			toQuit = true; 
		}
        	if( toQuit != true )
		{	
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
bool game::saveGame( )
{
	ofstream fout("saveGame.txt");

     	char response;
     	cout << "Save game (Y/N): ";
     	cin >> response;
     	if( response == 'N' || response == 'n' )
     	{ return false; }
	
	fout << *deckPtr;
	for( int i=0; i<=turnPtr->rear + 1; i++ )
	{   fout << turnPtr->deQueue() << endl;  }
     	return true;    
}

bool game::upload( int &playerCount )
{
	int tempRank = 0;
	char tempSuit = 0;
	char *tempString = new char[15];
	player tempPlayer;
	deckPtr->clear();
	turnPtr->clear();
	ifstream fin("saveGame.txt");
	// upload cards	
	while( tempSuit != '!' )
	{
		deckPtr->push( tempRank, tempSuit );
		fin >> tempRank;
		fin >> tempSuit;
	}
	// upload players until end of doc
	while( !fin.good() )
	{
		fin >> tempString;
		tempPlayer.copy( tempPlayer.name, tempString );

		while( fin  )
		{
			fin >> tempRank;
			fin >> tempSuit;
			deckPtr->push( tempRank, tempSuit );
		}
		fin >> tempString;
		fin >> tempPlayer.book;
		playerCount++;
	}
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

