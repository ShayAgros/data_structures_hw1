#include "oasis.h"

namespace hw1 {

        /*we shorten the name in order to save us some typing*/
    	typedef AvlTree<Player*,Player::Comp_by_id> players_tree_by_id;
	typedef AvlTree<Player*,Player::Comp_by_coins> players_tree_by_coins;
	typedef AvlTree<Clan*, Clan::Comp_by_id> clans_tree;

	void Oasis::addPlayer(int playerID,int initialCoins) {
	    	Player *player = NULL;
		try {
		     player = new Player(playerID,initialCoins);

		     players_by_coins.insertNode(player);

		     if(!best_player) /* we don't have players yet */
			 best_player = player;

		     players_by_id.insertNode(player);
		} catch ( std::bad_alloc& ex ) {
		    delete player;
		    throw memoryAllocFailure();
		} catch (players_tree_by_coins::NodeExists& exc) {
		    delete player;
		    throw playerExist();
		} catch(players_tree_by_id::NodeExists& exc) {
		    delete player;
		    // TODO: add removal of player from
		    // 'players_by_coins' tree. This exception
		    // should NEVER be invoked. 
		    
		    bool player_is_in_one_tree_but_not_in_another=false;
		    assert(player_is_in_one_tree_but_not_in_another);
		} catch (...) {
		    std::cout << "Unexpected execption" << std::endl;
		    std::cout << "addPlayer: playerID: " << playerID << std::endl;
		    assert(false);
		}
	}

	void Oasis::addClan(int clanID) {
	    Clan *clan = NULL;

	    try {
		clan = new Clan(clanID);
		clans.insertNode(clan);

	    } catch ( std::bad_alloc& ex ) {
		delete clan;
		throw memoryAllocFailure();
	    } catch (clans_tree::NodeExists& exc) {
		delete clan;
		throw clanExists();
	    } catch (...) {
		std::cout << "Unexpected execption" << std::endl;
		std::cout << "addClan: clanID: " << clanID << std::endl;
		assert(false);
	    }

	}

	void Oasis::joinClan(int playerID, int clanID) {
	    try {
		Player player_to_search(playerID);
		Clan clan_to_search(clanID);
		Player *player;
		Clan *clan;

		player = players_by_id.findValCopyInTree(&player_to_search);
		clan = clans.findValCopyInTree(&clan_to_search);

		if( player->getClan() != NULL && player->getClan() != clan)
		    throw playerAlreadyHasClan();
		else if( !player->getClan() ){
		    /*if player isn't already assigned to this clan*/
		    clan->addPlayer(player);
		}

	    } catch ( std::bad_alloc& ex ) {
		throw memoryAllocFailure();
	    } catch(players_tree_by_id::NodeDoesntExist& exc) {
		throw clanOrPlayerDoesntExist();
	    } catch(clans_tree::NodeDoesntExist& exc) {
		throw clanOrPlayerDoesntExist();
	    } catch (...) {
		std::cout << "Unexpected execption" << std::endl;
		std::cout << "joinClan: playerID: " << playerID << " clanID: " << clanID << std::endl;
		assert(false);
	    }
	}

} // end namespace
