#ifndef clan_d
#define clan_d



#include "avl.h"
#include "player.h"

namespace hw1 {
	typedef AvlTree<Player*, Player::Comp_by_coins> Players_Tree;

    class Clan {
	int id;
    // might not be needed
    //AvlTree<Player,Player::Comp_by_score> players_b_score;
	Players_Tree players_by_coins;
	Player* player_highest_score;

	Player::Comp_by_score compare;

	public:
	Clan(int id) : id(id), players_by_coins(), player_highest_score() {}
	Clan(int id, Players_Tree& players, Player* player_highest_score) : 
		id(id), players_by_coins(players), player_highest_score(player_highest_score) {}

	void addPlayer(Player *player);

	int getNumOfPlayers();

	Player* getBestPlayer();

	Players_Tree& getPlayers();



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
