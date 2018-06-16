#include "oasis.h"

using hw1::Oasis;

int moduloHash(int key, int size) {
	return key % size;
}

Oasis::Oasis() : _clans(moduloHash) {}


void Oasis::init(int n, int* clan_ids) {

	_can_fight_clans.MakeHeap(n, clan_ids);

	MinHeap<int>::Node** can_fight_clans_array = _can_fight_clans.toArray();

	int size = _can_fight_clans.getSize();

	for (int i = 0; i < size; i++) {
		int clan_id = can_fight_clans_array[i]->getData();
		_clans.insert(clan_id, Clan(clan_id, can_fight_clans_array[i]));
	}
}

void Oasis::addClan(int clan_id) {
	if (clan_id < 0) {
		throw InvalidInputException();
	}
	if (_clans.doesExist(clan_id)) {
		throw Hash<int, Clan>::HashAlreadyMemberException();
	}
	MinHeap<int>::Node* min_heap_node = _can_fight_clans.insert(clan_id);
	_clans.insert(clan_id, Clan(clan_id, min_heap_node));
}

void Oasis::addPlayer(int player_id, int score, int clan_id) {
	if (player_id < 0 && score < 0 && clan_id < 0) {
		throw InvalidInputException();
	}
}

void Oasis::clanFight(int clan1, int clan2, int k1, int k2) {

}

int Oasis::getMinClan() {
	return 0;
}

void Oasis::quit() {

}
