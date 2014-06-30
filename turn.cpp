/*//////////////////////////////////////////////
 * Go - Fish
 * Turn Class
 * Turn H Implimentation
/*//////////////////////////////////////////////

#include <iostream>
#include "turn.h"
using namespace std;

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
