/*//////////////////////////////////////////////
 * Go - Fish
 * Deck, Card Class
 * Deck Implementation
/*//////////////////////////////////////////////

#include <iostream>
#include <cmath>
#include "deck.h"

using namespace std;


const char HEART = 'H';
const char DIAMOND = 'D';
const char CLUB = 'C';
const char SPADE = 'S';

card::card()
{
    	rank = 0;
    	suit = '\0';
    	next = NULL;
}

ostream &operator<<( ostream &out, const card &rhs )
{
	out << rhs.rank << " " << rhs.suit << " "; 
    	return out;
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
	if( !isEmpty() )
	{
		top = top->next;
    		temp->next = NULL;
	}
    	return temp;
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

ostream &operator<<( ostream &out, const deck &rhs )
{
	card *temp = rhs.top;
	while( temp != NULL )
	{
		out << temp->rank << " ";
		out << temp->suit << " ";
		temp = temp->next;
	}
	out << endl;
	return out;
}
