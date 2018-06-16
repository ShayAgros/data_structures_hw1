#include "library2.h"
#include "oasis.h"
#include "hash.h"
#include "clan.h"

using namespace hw1;

void* init(int n,int *clanIDs) {

    Oasis* oasis = NULL ; 

    if( n < 2 )
	return NULL;

    for( int i=0; i<n ; i++)
	if ( clanIDs[i] < 0 )
	    return NULL;

    try {
	oasis = new Oasis();
	oasis->init(n,clanIDs);

    } catch (std::bad_alloc& ex){ 
	return NULL;
    }

    return (void*)oasis;
}

StatusType addClan(void *DS, int clanID) {
    Oasis* oasis = (Oasis*)DS;

    if( !DS )
	return INVALID_INPUT;

    try {
	oasis->addClan(clanID);
    } catch(std::bad_alloc& ex) {
    	return ALLOCATION_ERROR;
    } catch (Oasis::InvalidInputException& exc) {
	return INVALID_INPUT;
    } catch (Hash<int,Clan>::HashAlreadyMemberException& exc) {
	return FAILURE;
    }

    return SUCCESS;
}

StatusType addPlayer(void *DS,int playerID, int score, int clan) {

    Oasis* oasis = (Oasis*)DS;

    if( !DS )
	return INVALID_INPUT;
    try {
	oasis->addPlayer(playerID,score, clan);
    } catch (std::bad_alloc& ex) {
	return ALLOCATION_ERROR;
    } catch (Oasis::InvalidInputException& exc) {
	return INVALID_INPUT;
    } catch (Oasis::PlayerAlreadyExistsException& exc) {
	return FAILURE;
    } catch (Oasis::ClanDoesNotExistException& exc) {
	return FAILURE;
    }

    return SUCCESS;
}

StatusType clanFight(void *DS,int clan1, int clan2, int k1, int k2) {

    Oasis* oasis = (Oasis*)DS;

    if( !DS || k1<=0 || k2<=0 || clan1 < 0
	    || clan2 < 0 )
	return INVALID_INPUT;

    if ( clan1 == clan2 )
	return FAILURE;
    
    try {
	oasis->clanFight(clan1, clan2, k1, k2);

    } catch (std::bad_alloc& ex) {
	return ALLOCATION_ERROR;
    } catch (Oasis::clanDosntExist& exc) {
	return FAILURE;
    } catch ( Oasis::clanCantFight& exc) {
	return FAILURE;
    } catch (Oasis::clanDoesntHaveEnoughPlayers& exc) {
	return FAILURE;
    } 
    return SUCCESS;
}

StatusType getMinClan(void *DS,int *clan) {

    Oasis* oasis = (Oasis*)DS;

    if( !DS || !clan)
	return INVALID_INPUT;

    try {
	*clan = oasis->getMinClan();

    } catch (Oasis::GotNoCanFightClansException& exc) {
	return FAILURE;
    }

    return SUCCESS;
}

void quit(void **DS) {

    if( !DS )
	return;

    Oasis* oasis = (Oasis*)*DS;

    if( !oasis )
	return;

    oasis->quit();

    delete oasis;
    *DS = NULL;
}
