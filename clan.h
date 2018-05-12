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

	Player::Comp_by_score compare;

	public:
	Clan(int id) : id(id), players_by_coins(), player_highest_score() {}

	void addPlayer(Player *player);



	class Comp_by_id {
	    public:
	    bool operator () (Clan* c1, Clan* c2) {
		return (c1->id < c2->id);
	    }
	};

	class memoryAllocFailure{};
    };

} // end namespace
#endif
