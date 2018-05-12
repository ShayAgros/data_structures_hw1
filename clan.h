#ifndef clan_d
#define clan_d



#include "avl.h"
#include "player.h"

namespace hw1 {


    class Clan {
	int id;
    // might not be needed
    //AvlTree<Player,Player::Comp_by_score> players_b_score;
    	AvlTree<Player*,Player::Comp_by_coins> players_by_coins;
	Player* player_highest_score;

	public:

	class Comp_by_id {

	    bool operator () (Clan* c1, Clan* c2) {
		return (c1->id < c2->id);
	    }


	};
    };

} // end namespace
#endif 
