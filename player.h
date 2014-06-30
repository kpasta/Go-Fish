/*//////////////////////////////////////////////
 * Go - Fish
 * Hand, Card Class
 * Player H Drive
/*//////////////////////////////////////////////

#include <iostream>
#include "deck.h"
using namespace std;
class turn;
class game;
class card;

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
    	friend ostream &operator<<( ostream &, const player & );
    	friend class player;
    	private:
        	card *head, *cursor;
};

class player
{
    	public:
        	player();
        	~player();
        	void deal( deck &, int );
        	void displayHand();
        	bool getCard( int, player );
        	bool goFish( deck & );
        	void findBook();
        	player* choosePlayer( turn );
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
	bool clear();
    friend ostream &operator<<( ostream &, const game & );
    friend class game;
    friend class player;
    private:
        int front, rear, max;
        player *data;
};
