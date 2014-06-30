/*//////////////////////////////////////////////
 * Krysta A Pascual
 * Go - Fish... Main Driver
/*//////////////////////////////////////////////

#include <iostream>

#include "game.h"
using namespace std;

int main()
{
    	game temp, tempold;
	int playerCount = 0;
	char response;

	cout << "Play Old Game? (Y/N): ";
	cin >> response;
	if( response == 'y' || response == 'Y' )
	{
		tempold.upload( playerCount );
		tempold.play( playerCount );
	}
    	else
	{
		playerCount = temp.numPlayers();
    		game one( playerCount ); 
    		one.play( playerCount );
	}

    	return 0;
}
