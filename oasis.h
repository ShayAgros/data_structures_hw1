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

	void init(int n, int* clanIDs);

	void addClan(int _clanID);

	void addPlayer(int playerID, int _score, int _clanID);

	void clanFight(int clan1, int clan2, int k1, int k2);

	int getMinClan();

	void quit();

private:
	Hash<int, Clan> _clans;
	AvlTree<Player, Player::CompareByID> _players;
	MinHeap<int> _can_fight_clans;

	class InvalidInputException {};

};

} // end namespace

#endif
