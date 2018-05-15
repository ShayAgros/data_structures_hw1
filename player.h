#ifndef player_d
#define player_d

#include "avl.h"

namespace hw1 {

class Player {

    int id;
    int coins;
    int num_of_challenges;

    // these fields will be of different types
    // but they need to have the player's clan id
    // and a point to it in the Clans AVL tree
    void *clan_pointer;


    public:
    Player(int id,int coins) : id(id) , coins(coins) ,
    	num_of_challenges(0), clan_pointer(NULL) {} 

    Player(int id) : id(id) , coins(0) ,
    	num_of_challenges(0), clan_pointer(NULL) {}

    // We need this default c'tor because the avl need it 
    // (in order to build empty tree)
    Player() : id(0), coins(0),
	    num_of_challenges(0), clan_pointer(NULL) {}

    /* returns a pointer to player's clan */
    void* getClan();

    /* sets player's clan */
    void setClan(void *clan);

    int getNumOfChallenges() {
	return num_of_challenges;
    }

    void addCoins(int new_coins);

    int getID();

    int getScore();

    ~Player() = default;


    class Comp_by_coins {
	public:
	bool operator() (Player *p1,Player *p2) {
		if (p1->coins == p2->coins) {
			return (p1->id < p2->id);
		}		
	    return (p1->coins > p2->coins);
    	}
    };

    class Comp_by_score {
	public:
	bool operator() (Player *p1, Player *p2) {
	    if( p1->num_of_challenges == p2->num_of_challenges )
		return p1->id > p2->id;
	    return ( p1->num_of_challenges < p2->num_of_challenges );
	}

    };

    class Comp_by_id {
	public:
	bool operator() (Player *p1, Player *p2) {
	    return ( p1->id < p2->id );
	}
    };

};


} // end namespace
#endif
