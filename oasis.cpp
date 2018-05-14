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

	// TODO: delete this abomination please
	void Oasis::addClan(int clanID, Players_Tree& players_tree, Player* best_player) {
		Clan *clan = NULL;

		try {
			clan = new Clan(clanID, players_tree, best_player);
			clans.insertNode(clan);

		} catch (std::bad_alloc& ex) {
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

	/*TODO: this function should be static !*/
	void Oasis::removeClan(int clanID) {
		Clan clan_to_search(clanID);
		Clan *clan;

		clan = clans.findValCopyInTree(&clan_to_search);
		//TODO - uncomment this.
		//clans.removeNode(clandID)
		delete clan;
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

	void Oasis::uniteClans(int clan_id1, int clan_id2) {
		Player** array1 = NULL;
		Player** array2 = NULL;
		try {

			Clan clan1_to_search(clan_id1);
			Clan clan2_to_search(clan_id2);

			Clan *clan1;
			Clan *clan2;
			int united_clan_id;

			clan1 = clans.findValCopyInTree(&clan1_to_search);
			clan2 = clans.findValCopyInTree(&clan2_to_search);

			if (clan1->getNumOfPlayers() > clan2->getNumOfPlayers() ||
				(clan1->getNumOfPlayers() == clan2->getNumOfPlayers() && 
					clan_id1 < clan_id2)) {
				united_clan_id = clan_id1;
			} else {
				united_clan_id = clan_id2;
			}

			Player* best_player1 = clan1->getBestPlayer();
			Player* best_player2 = clan2->getBestPlayer();
			Player* best_player;
			Player::Comp_by_coins compare;

			if (best_player1 == NULL) {
				best_player = best_player2;
			} else if (best_player2 == NULL) {
				best_player = best_player1;
			} else if (compare(best_player1, best_player2)) {
				best_player = best_player2;
			} else {
				best_player = best_player1;
			}
			
			// the +1 is here to avoid creating a zero
			// size array
			array1 = new Player*[ clan1->getNumOfPlayers() + 1];
			array2 = new Player*[ clan2->getNumOfPlayers() + 1];

			clan1->getPlayers().ToArray(array1);
			clan2->getPlayers().ToArray(array2);


			int united_clan_size;
			Player** united_clan = 
				mergeArraysWithChallenges(array1, clan1->getPlayers().getSize(), 
					array2, clan2->getPlayers().getSize(), &united_clan_size);

			Players_Tree* united_players_by_coins = 
				Players_Tree::BuildEmptyTree(united_clan_size);

			Players_Tree::ArrayToTree(united_players_by_coins, united_clan);

			
			removeClan(clan_id1);
			removeClan(clan_id2);
			addClan(united_clan_id, *united_players_by_coins, best_player);

			delete[] array1;
			delete[] array2;
			delete[] united_clan;
		} catch (std::bad_alloc& exx) {
			throw memoryAllocFailure();
		} catch (clans_tree::NodeDoesntExist& exc) {
			throw clanDoesntExist();
		} catch (clans_tree::AvlAllocationError& exc) {
			if (array1 != NULL) {
				delete[] array1;
			}
			if (array2 != NULL) {
				delete[] array2;
			}
			throw memoryAllocFailure();
		} catch (memoryAllocFailure& ex) {
			delete[] array1;
			delete[] array2;
			throw memoryAllocFailure();
		} catch (...) {
			std::cout << "Unexpected execption" << std::endl;
			std::cout << "uniteClan: clan_id1: " << clan_id1 << " clan_id2: " << clan_id2 << std::endl;
			assert(false);
		}
	}

	Player** Oasis::mergeArraysWithChallenges(Player** first_array, 
		int size_first,	Player** second_array, int size_second, 
		int* merged_array_size) {
		Player** merged_array = new Player*[size_first + size_second];
		if (merged_array == NULL) {
			throw memoryAllocFailure();
		}
		Player::Comp_by_coins compare;
		int index_first = 0, index_second = 0, merged_index = 0;
		while (index_first < size_first && index_second < size_second) {
			if (first_array[index_first]->getNumOfChallenges() == 0) {
				first_array[index_first]->setClan(NULL);
				index_first++;
			} else if (second_array[index_second]->getNumOfChallenges() == 0) {
					second_array[index_second]->setClan(NULL);
					index_second++;
			} else {
				if (compare(first_array[index_first], second_array[index_second])) {
					merged_array[merged_index] = first_array[index_first];
					index_first++;
				} else {
					merged_array[merged_index] = second_array[index_second];
					index_second++;
				}
				merged_index++;
			}
		}
		while (index_first < size_first) {
			if (first_array[index_first]->getNumOfChallenges() == 0) {
				first_array[index_first]->setClan(NULL);				
			} else {
				merged_array[merged_index] = first_array[index_first];
				merged_index++;
			}
			index_first++;
		}
		while (index_second < size_second) {
			if (second_array[index_second]->getNumOfChallenges() == 0) {
				second_array[index_second]->setClan(NULL);
			} else {
				merged_array[merged_index] = second_array[index_second];
				merged_index++;
			}
			index_second++;
		}
		*merged_array_size = merged_index;
		return merged_array;
	}

} // end namespace
