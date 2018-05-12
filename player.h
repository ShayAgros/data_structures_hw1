#ifndef player_d
#define player_d

#include "avl.h"

namespace hw1 {

class Player {

    int id;
    int coins;

    // these fields will be of different types
    // but they need to have the player's clan id
    // and a point to it in the Clans AVL tree
    void* clan_pointer;


    public:
    Player(int id,int coins) : id(id) , coins(coins) ,
    	clan_pointer(NULL) {}


    
    ~Player() = default;


    class Comp_by_coins {
	bool operator() (Player* p1,Player* p2) {
	    return (p1->coins > p2->coins);
    	}
    };

};


} // end namespace
#endif
