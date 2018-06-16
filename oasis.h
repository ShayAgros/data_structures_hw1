#ifndef OASIS_H
#define OASIS_H

#include "clan.h"
#include "player.h"
#include "hash.h"
#include "min_heap.h"
#include "avl.h"

namespace hw1 {

class Oasis {
public:

	Oasis();
	~Oasis() {}

	void init(int n, int* clan_ids);

	void addClan(int clan_id);

	void addPlayer(int player_id, int score, int clan_id);

	void clanFight(int clan1, int clan2, int k1, int k2);

	int getMinClan();

	void quit();

private:
	Hash<int, Clan> _clans;
	AvlTree<int> _players_id;
	MinHeap<int> _can_fight_clans;

	class InvalidInputException {};

};

} // end namespace

#endif
