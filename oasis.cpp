#include "oasis.h"

using hw2::Oasis;
using hw2::Clan;

int moduloHash(int key, int size) {
	return key % size;
}

Oasis::Oasis() {
	_clans = new Hash<int, Clan>(moduloHash);
	_players_by_id = new AvlTree<int>();
	_can_fight_clans = new MinHeap<int>();
}


void Oasis::init(int n, int* clan_ids) {

	_can_fight_clans->MakeHeap(n, clan_ids);

	MinHeap<int>::Node** can_fight_clans_array = _can_fight_clans->toArray();

	int size = _can_fight_clans->getSize();

	for (int i = 0; i < size; i++) {
		int clan_id = can_fight_clans_array[i]->getData();
		_clans->insert(clan_id, new Clan(clan_id, can_fight_clans_array[i]));
	}
}

void Oasis::addClan(int clan_id) {
	if (clan_id < 0) {
		throw InvalidInputException();
	}
	if (_clans->doesExist(clan_id)) {
		throw Hash<int, Clan>::HashAlreadyMemberException();
	}
	MinHeap<int>::Node* min_heap_node = _can_fight_clans->insert(clan_id);
	_clans->insert(clan_id, new Clan(clan_id, min_heap_node));
}

void Oasis::addPlayer(int player_id, int score, int clan_id) {
	if (player_id < 0 || score < 0 || clan_id < 0) {
		throw InvalidInputException();
	}
	try {
		_players_by_id->findValCopyInTree(player_id);
		throw PlayerAlreadyExistsException();
	} catch (const AvlTree<int>::NodeDoesntExist& exc) {
	}

	if (!_clans->doesExist(clan_id)) {
		throw ClanDoesNotExistException();
	}

	_players_by_id->insertNode(player_id);
	Clan* clan = _clans->find(clan_id);
	clan->addPlayer(player_id, score);
}

void Oasis::clanFight(int clan_id1, int clan_id2, int k1, int k2) {

	int k1_grade, k2_grade;
	Clan* losing_clan;

	if (!_clans->doesExist(clan_id1) || !_clans->doesExist(clan_id2))
		throw ClanDoesNotExistException();

	Clan* clan1 = _clans->find(clan_id1);
	Clan* clan2 = _clans->find(clan_id2);


	if (!clan1->canFight() || !clan2->canFight())
		throw ClanCantFightException();

	if (clan1->getSize() < k1 || clan2->getSize() < k2)
		throw ClanDoesntHaveEnoughPlayersException();

	k1_grade = clan1->getStrongest(k1);
	k2_grade = clan2->getStrongest(k2);

	if (k1_grade == k2_grade) {
		losing_clan = (clan_id2 < clan_id1) ? clan1 : clan2;
	}
	else {
		losing_clan = (k2_grade < k1_grade) ? clan2 : clan1;
	}
	
	deleteLostClanFromHeap(losing_clan);
	losing_clan->setClanLost();
}

void Oasis::deleteLostClanFromHeap(Clan* clan) {
	//we make the losing clan to be "minimum clan"
	_can_fight_clans->decKey(clan->getMinHeapNode(), -1);
	_can_fight_clans->delMin();
}

int Oasis::getMinClan() {
	int min_clan = 0;
	try {
		min_clan = _can_fight_clans->findMin();
	} catch (const MinHeap<int>::EmptyHeapException& exc) {
		throw GotNoCanFightClansException();
	}
	return min_clan;
}

void Oasis::quit() {
	_clans->deleteAllElements();
	delete _clans;
	delete _players_by_id;
	delete _can_fight_clans;	
}
