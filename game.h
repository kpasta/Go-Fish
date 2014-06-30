/*//////////////////////////////////////////////
 * Go - Fish
 * Game Class
 * Game H
/*//////////////////////////////////////////////

#include <iostream>
#include "player.h"
using namespace std;
class deck;

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
		bool upload( int& );
        	player findMostBooks();
    	friend ostream &operator<<( ostream &, const game & );
    	private:
       	 	deck *deckPtr;
        	turn *turnPtr;
        	player *playerPtr;
        
};
