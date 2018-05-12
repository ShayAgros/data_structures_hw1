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
	    } catch (playerAlreadyHasClan& exc) { 
			throw playerAlreadyHasClan();
	    } catch (...) {
			std::cout << "Unexpected execption" << std::endl;
			std::cout << "joinClan: playerID: " << playerID << " clanID: " << clanID << std::endl;
			assert(false);
	    }
	}

	void Oasis::uniteClans(int clanID1, int clanID2) {
		try {

			Clan clan1_to_search(clanID1);
			Clan clan2_to_search(clanID2);

			Clan *clan1;
			Clan *clan2;
			Clan *unitedClan;
			int unitedClanID;

			clan1 = clans.findValCopyInTree(&clan1_to_search);
			clan2 = clans.findValCopyInTree(&clan2_to_search);

			if (clan1->getNumOfPlayers() > clan2->getNumOfPlayers() ||
				(clan1->getNumOfPlayers() == clan2->getNumOfPlayers() && 
					clanID1 < clanID2)) {
				unitedClanID = clanID1;
			} else {
				unitedClanID = clanID2;
			}

			Player* bestPlayer1 = clan1->getBestPlayer();
			Player* bestPlayer2 = clan2->getBestPlayer();
			Player::Comp_by_score compare;
			Player* bestPlayer;

			if (bestPlayer1 == NULL) {
				bestPlayer = bestPlayer2;
			} else if (bestPlayer2 == NULL) {
				bestPlayer = bestPlayer1;
			} else if (compare(bestPlayer1, bestPlayer2)) {
				bestPlayer = bestPlayer2;
			} else {
				bestPlayer = bestPlayer1;
			}

			Player** array1 = clan1->getPlayers().ToArray();
			Player** array2 = clan2->getPlayers().ToArray();



		} catch (std::bad_alloc& ex) {
			throw memoryAllocFailure();
		} catch (clans_tree::NodeDoesntExist& exc) {
			throw clanDoesntExist();
		} catch (...) {
			std::cout << "Unexpected execption" << std::endl;
			std::cout << "uniteClan: clanID1: " << clanID1 << " clanID2: " << clanID2 << std::endl;
			assert(false);
		}
	}

	// Sorts two arrays into one array
	// Parameters->
	//			*first_array - the first array to sort
	//			*size_first = the size of the first array
	//			*second_array - the second array to sort
	//			*size_second = the size of the second array
	// Returns ->
	//			A sorted array made of the two given arrays.
	/**
	static Player* Oasis::MergeArrays(Player* first_array, int size_first, 
		Player* second_array, int size_second) {
		Player* merged_array = new Player[size_first + size_second];
		if (merged_array == NULL) {
			return NULL;
		}
		int index_first = 0, index_second = 0, merged_index = 0;
		while (index_first < size_first && index_second < size_second) {
			if ((first_array[index_first])->GetKey() < (second_array[index_second])->GetKey()) {
				merged_array[merged_index] = first_array[index_first];
				index_first++;
			} else {
				merged_array[merged_index] = second_array[index_second];
				index_second++;
			}
			merged_index++;
		}
		while (index_first < size_first) {
			merged_array[merged_index] = first_array[index_first];
			index_first++;
			merged_index++;
		}
		while (index_second < size_second) {
			merged_array[merged_index] = second_array[index_second];
			index_second++;
			merged_index++;
		}
		return merged_array;
	}*/

} // end namespace
