/*//////////////////////////////////////////////
 * Go - Fish
 * Turn Class
 * Turn H Drive
/*//////////////////////////////////////////////

#include <iostream>

using namespace std;
class game;
class player;


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
