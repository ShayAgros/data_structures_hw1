#include "oasis.h"

using hw1::Oasis;

int moduloHash(int key, int size) {
	return key % size;
}

Oasis::Oasis() : _clans(moduloHash) {}


void Oasis::init(int n, int* clanIDs) {

	_can_fight_clans.MakeHeap(n, clanIDs);

	MinHeap<int>::Node** can_fight_clans_array = _can_fight_clans.toArray();

	int size = _can_fight_clans.getSize();

	for (int i = 0; i < size; i++) {
		int _clanID = can_fight_clans_array[i]->getData();
		_clans.insert(_clanID, Clan(_clanID, can_fight_clans_array[i]));
	}
}

void Oasis::addClan(int _clanID) {
	if (_clanID < 0) {
		throw InvalidInputException();
	}
	if (_clans.doesExist(_clanID)) {
		throw Hash<int, Clan>::HashAlreadyMemberException();
	}
	MinHeap<int>::Node* min_heap_node = _can_fight_clans.insert(_clanID);
	_clans.insert(_clanID, Clan(_clanID, min_heap_node));
}

void Oasis::addPlayer(int playerID, int _score, int _clanID) {
	if (playerID < 0 && _score < 0 && _clanID < 0) {
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
