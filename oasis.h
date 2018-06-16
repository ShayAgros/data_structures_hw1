#ifndef OASIS_H
#define OASIS_H

#include "clan.h"
#include "player.h"
#include "hash.h"
#include "min_heap.h"
#include "avl.h"

namespace hw1 {

class Oasis {
private:
	Hash<int, Clan>* _clans;
	AvlTree<int>* _players_by_id;
	MinHeap<int>* _can_fight_clans;

	void deleteLostClanFromHeap(Clan* clan);

public:

	Oasis();
	~Oasis() {}

	void init(int n, int* clan_ids);

	void addClan(int clan_id);

	void addPlayer(int player_id, int score, int clan_id);

	void clanFight(int clan_id1, int clan_id2, int k1, int k2);

	int getMinClan();

	void quit();


	class InvalidInputException {};
	class ClanDoesntHaveEnoughPlayersException {};
	class ClanCantFightException {};
	class PlayerAlreadyExistsException {};
	class ClanDoesNotExistException {};
	class GotNoCanFightClansException {};

};

} // end namespace

#endif
