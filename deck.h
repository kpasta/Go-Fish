/*//////////////////////////////////////////////
 * Go - Fish
 * Deck, Card Class
 * Deck H Drive
/*//////////////////////////////////////////////

#include <iostream>
using namespace std;
class player;
class hand;
class deck;

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
    	friend ostream &operator<<( ostream &, const deck & );
	friend ostream &operator<<( ostream &, const player & );
};

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
    	friend ostream &operator<<( ostream &, const deck & );
	private:
        	card *top;
};

