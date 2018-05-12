#include "clan.h"

namespace hw1 {

    typedef AvlTree<Player*,Player::Comp_by_coins> players_tree;
    void Clan::addPlayer(Player *player){

	try {
	    players_by_coins.insertNode(player);

	    if( !player_highest_score ||
		    compare(player_highest_score, player)) { 
		player_highest_score = player;
	    }

	} catch ( std::bad_alloc& ex ) {
	    throw memoryAllocFailure();
	} catch (players_tree::NodeExists& exc) {
	    /*this should never happen, putting assert to catch this*/
	    bool player_already_in_clan_but_inserted_again = false;
	    assert(player_already_in_clan_but_inserted_again);
	}


    }


} // end namespace
