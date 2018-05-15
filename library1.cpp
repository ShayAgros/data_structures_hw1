#include "library1.h"
#include "oasis.h"

using hw1::Oasis;

void* init() {
    Oasis *DS = new Oasis();
    return (void*) DS;
}

StatusType addPlayer(void *DS, int playerID, int initialCoins) {

    if ( !DS || playerID <=0 || initialCoins < 0)
	return INVALID_INPUT;

    try {
	Oasis *oasis = (Oasis*)DS;
	oasis->addPlayer(playerID,initialCoins);
    } catch (Oasis::memoryAllocFailure& exc) {
	return ALLOCATION_ERROR;
    } catch (Oasis::playerExist& exc) {
	return FAILURE;
    }

    return SUCCESS;
}

StatusType addClan(void *DS, int clanID) {

    if( !DS || clanID <= 0)
	return INVALID_INPUT;

    try {
	Oasis *oasis = (Oasis*)DS;
	oasis->addClan(clanID);
    } catch (Oasis::memoryAllocFailure& exc) {
	return ALLOCATION_ERROR;
    } catch (Oasis::clanExists& exc) {
	return FAILURE;
    }
    return SUCCESS;
}

StatusType joinClan(void *DS,int playerID,int clanID) {
    
    if( !DS || playerID <=0 || clanID <=0)
	return INVALID_INPUT;

    try {
	Oasis *oasis = (Oasis*)DS;
	oasis->joinClan(playerID,clanID);
    } catch (Oasis::memoryAllocFailure& exc) {
	return ALLOCATION_ERROR;
    } catch(Oasis::clanOrPlayerDoesntExist& exc) {
	return FAILURE;
    }

    return SUCCESS;
}

StatusType completeChallange(void *DS,int playerID,int coins) {

    if( !DS || playerID <=0 || coins <= 0)
	return INVALID_INPUT;

    try {
	Oasis *oasis = (Oasis*)DS;
	oasis->completeChallange(playerID,coins);
    } catch (Oasis::memoryAllocFailure& exc) {
	return ALLOCATION_ERROR;
    } catch (Oasis::clanOrPlayerDoesntExist& exc) {
	return FAILURE;
    }

    return SUCCESS;
}

StatusType getBestPlayer(void *DS,int clanID,int *playerID) {
    
    if( !DS || clanID == 0 || !playerID)
	return INVALID_INPUT;

    try {
	Oasis *oasis = (Oasis*)DS;
	oasis->getBestPlayer(clanID,playerID);
    } catch (Oasis::memoryAllocFailure& exc) {
	return ALLOCATION_ERROR;
    } catch (Oasis::clanOrPlayerDoesntExist& exc) {
	return FAILURE;
    }
    return SUCCESS;
}

StatusType getScoreboard(void *DS,int clanID,int** players,int *numOfPlayers) {

    if( !DS || !players || !numOfPlayers || clanID == 0)
	return INVALID_INPUT;

    try {
	Oasis *oasis = (Oasis*)DS;
	oasis->getScoreboard(clanID, players, numOfPlayers);
    } catch (Oasis::memoryAllocFailure& exc) {
	return ALLOCATION_ERROR;
    } catch( Oasis::clanOrPlayerDoesntExist& exc) {
	return FAILURE;
    }

    return SUCCESS;
}

StatusType uniteClans(void *DS,int clanID1,int clanID2) {
    if( !DS || clanID1 <= 0 || clanID2 <= 0 || 
	    clanID1 == clanID2)
	return INVALID_INPUT;

    try {
	Oasis *oasis = (Oasis*)DS;
	oasis->uniteClans(clanID1,clanID2);
    } catch (Oasis::memoryAllocFailure& exc) {
	return ALLOCATION_ERROR;
    } catch (Oasis::clanDoesntExist& exc) {
	return FAILURE;
    }
    return SUCCESS;
}

void quit(void **DS) {

    Oasis *oasis = (Oasis*)(*DS);
    delete oasis;
    *DS = NULL;
}
