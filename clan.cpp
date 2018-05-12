#include "clan.h"

namespace hw1 {

    typedef AvlTree<Player*,Player::Comp_by_coins> players_tree;
    void Clan::addPlayer(Player *player){

	try {
	    players_by_coins.insertNode(player);
	    player->setClan((void*)this);
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

	int Clan::getNumOfPlayers() {
		return players_by_coins.getSize();
	}

	Player* Clan::getBestPlayer() {
		return player_highest_score;
	}

	AvlTree<Player*, Player::Comp_by_coins> Clan::getPlayers() {
		return players_by_coins;
	}


} // end namespace
