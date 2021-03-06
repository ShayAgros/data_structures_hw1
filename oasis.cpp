#include "oasis.h"

namespace hw1 {

	/*we shorten the name in order to save us some typing*/
	typedef AvlTree<Player*,Player::Comp_by_id> players_tree_by_id;
	typedef AvlTree<Player*,Player::Comp_by_coins> players_tree_by_coins;
	typedef AvlTree<Clan*, Clan::Comp_by_id> clans_tree;

	void Oasis::addPlayer(int playerID,int initialCoins) {
	    Player *player = NULL;
	    Player::Comp_by_score compare;
		try {
		     player = new Player(playerID,initialCoins);

		     players_by_id.insertNode(player);

		     players_by_coins.insertNode(player);

		    if( !best_player ||
			compare(best_player, player)) {
			best_player = player;
		    }

		} catch ( std::bad_alloc& exc ) {
		    delete player;
		    throw memoryAllocFailure();
		} catch(players_tree_by_id::NodeExists& exc) {
		    delete player;
		    throw playerExist();
		} catch (players_tree_by_coins::NodeExists& exc) {
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

	    } catch ( std::bad_alloc& exc ) {
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

		} catch (std::bad_alloc& exc) {
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

		clans.deleteNode(clan);
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

		if( player->getClan() != NULL)
		    throw playerAlreadyHasClan();
		else if( !player->getClan() ){
		    /*if player isn't already assigned to this clan*/
		    clan->addPlayer(player);
		}

	    } catch ( std::bad_alloc& exc ) {
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

	
	void Oasis::completeChallange(int playerID,int coins) {

	    try {
		Player player_to_search(playerID);
		Player *player;
		Clan *clan;
		Player::Comp_by_score compare;

		player = players_by_id.findValCopyInTree(&player_to_search);
		clan = (Clan*)player->getClan();

		players_by_coins.deleteNode(player);

		if(clan)
		    clan->updatePlayerCoins(player,coins);
		else
		    player->addCoins(coins);

		players_by_coins.insertNode(player);

		
		if( !best_player ||
		    compare(best_player, player)) {
		    	best_player = player;
		}

	    } catch ( std::bad_alloc& exc ) {
		throw memoryAllocFailure();
	    } catch(players_tree_by_id::NodeDoesntExist& exc) {
		throw clanOrPlayerDoesntExist();
	    }  catch (...) {
		std::cout << "Unexpected execption" << std::endl;
		std::cout << "completeChalange: playerID: " << playerID << " coins: " << coins << std::endl;
		assert(false);
	    }
	}


	void Oasis::getBestPlayer(int clanID, int *playerID){
	    try {
		if(clanID < 0) {
		     *playerID = best_player ? best_player->getID() : -1;
		} else {
			Clan clan_to_search(clanID); 
			Clan *clan;
					
			clan = clans.findValCopyInTree(&clan_to_search);

			Player* best = clan->getBestPlayer();
			*playerID = best ? best->getID() : -1;
		}
	    } catch(clans_tree::NodeDoesntExist& exc) {
		throw clanOrPlayerDoesntExist();
	    } catch (...) {
		std::cout << "Unexpected execption" << std::endl;
		std::cout << "getBestPlayer: clanID: " << clanID << std::endl;
		assert(false);
	    }
	}


	void Oasis::getScoreboard(int clanID, int **players, int *numOfPlayers) {
		Player** board = NULL;
		players_tree_by_coins *tree;
		int size;

		try { 
		    if(clanID < 0) {
			tree = &players_by_coins;
		    } else {
			Clan clan_to_search(clanID); 
			Clan *team;
			team = clans.findValCopyInTree(&clan_to_search);
			tree = &team->getPlayers();
		    }

		    size = tree->getSize();
		    if(size == 0) {
			    *players = NULL;
			    *numOfPlayers = 0;
			    return;
		    }

		    board = new Player*[size];
		    *players = (int*)malloc(sizeof(int)*size);

		    tree->ToArray(board);
		    for(int i=0;i < size; i++)
			(*players)[i] = board[i]->getID();

		    *numOfPlayers = size;

		    delete[] board;

		} catch (std::bad_alloc& exc) {
		    delete board;
		    throw memoryAllocFailure();
		} catch(clans_tree::NodeDoesntExist& exc) {
		    throw clanOrPlayerDoesntExist();
		} catch (...) {
		    std::cout << "Unexpected execption" << std::endl;
		    std::cout << "getScoreBoard: clanID: " << clanID << std::endl;
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
			Player::Comp_by_score compare;

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
		} catch (std::bad_alloc& excx) {
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
		}  catch (...) {
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


	Oasis::~Oasis() {
		Clan** all_clans = new Clan*[clans.getSize() +1];
		Player** all_players = new Player*[players_by_id.getSize() +1];
		clans.ToArray(all_clans);
		players_by_id.ToArray(all_players);

		for(int i = 0; i < clans.getSize(); i++) 
			delete all_clans[i];
		for(int i = 0; i < players_by_coins.getSize(); i++) 
			delete all_players[i];

		delete[] all_clans;
		delete[] all_players;
	}


} // end namespace
