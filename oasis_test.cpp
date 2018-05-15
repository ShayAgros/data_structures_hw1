#include <iostream>
#include <stdlib.h>
#include <assert.h>
#include "oasis.h"

#define RUN_TEST(b)	if( (b)() ) std::cout << #b << ": [PASS]" << std::endl; \
						else std::cout << #b <<  ": [FAIL]" << std::endl;
using hw1::Oasis;


bool addPlayerTest() {

    	Oasis oasis;
	int num_players = 100;
	int max_coins = 30;
	
	for( int i=1; i < num_players; i++) {
	    try {
		oasis.addPlayer(i, i%max_coins);
	    } catch (Oasis::memoryAllocFailure& exc) {
		return false;
	    } catch (Oasis::playerExist& exc) {
		return false;
	    } catch ( ... ){
		return false;
	    }

	}

	for( int i=1; i < num_players; i++) {
	    try {
		oasis.addPlayer(i, i%max_coins);
		return false;
	    } catch (Oasis::memoryAllocFailure& exc) {
		return false;
	    } catch (Oasis::playerExist& exc) {
	    }	catch ( ... ){
	    	return false;
	    }

	}
	
	return true;
}

bool addClanTest() {

    Oasis oasis;
    int num_clans = 100;
    
    for( int i=1; i < num_clans; i++) {
	try {
	    oasis.addClan(i);
	} catch (Oasis::memoryAllocFailure& exc) {
	    return false;
	} catch (Oasis::clanExists & exc) {
	    return false;
	} catch ( ... ){
	    return false;
	}
    }


    for( int i=1; i < num_clans; i++) {
	try {
	    oasis.addClan(i);
	    return false;
	} catch (Oasis::memoryAllocFailure& exc) {
	    return false;
	} catch (Oasis::clanExists & exc) {
	} catch ( ... ){
	    return false;
	}
    }

    return true;
}

bool joinClanTest() {

    Oasis oasis;
    int num_players = 1200;
    int num_clans = 30;
    int max_coins = 30;
	
    for( int i=1; i < num_players; i++) {
	try {
	    oasis.addPlayer(i, i%max_coins);
	} catch (Oasis::memoryAllocFailure& exc) {
	    return false;
	} catch (Oasis::playerExist& exc) {
	    return false;
	} catch ( ... ){
	    return false;
	}
    }

    for( int i=1; i <= num_clans; i++) {
	try {
	    oasis.addClan(i);
	} catch (Oasis::memoryAllocFailure& exc) {
	    return false;
	} catch (Oasis::clanExists & exc) {
	    return false;
	} catch ( ... ){
	    return false;
	}
    }

    for ( int i = 1; i< 2*num_players; i++ ) {
	try {

	    oasis.joinClan(i, i%(num_clans + 1) +1);

	    if( i >= num_players ||
		  ( (i % (num_clans +1)) +1) == (num_clans +1))
		return false;
	} catch (Oasis::memoryAllocFailure& exc) {
	    return false;
	} catch (Oasis::clanOrPlayerDoesntExist& exc) {
	    if( i < num_players && 
		  ((i % (num_clans+1)) +1) != (num_clans +1))
		return false;
	}

    }


    // we add players to the same clan. It shouldn't fail!
    for ( int i = 1; i< num_players; i++ ) {
	    try {

		oasis.joinClan(i, i%(num_clans + 1) +1);

		if( ((i % (num_clans+1)) +1) == (num_clans +1))
		    return false;
	    } catch (Oasis::memoryAllocFailure& exc) {
		return false;
	    } catch (Oasis::clanOrPlayerDoesntExist& exc) {
		if( ((i % (num_clans+1)) +1) != (num_clans +1))
		    return false;
	    }

	}


    for ( int i = 1; i< num_clans; i++ ) {
	try {

	    oasis.joinClan(i, i);
	    return false;
	} catch (Oasis::memoryAllocFailure& exc) {
	    return false;
	} catch (Oasis::clanOrPlayerDoesntExist& exc) {
	    return false;
	} catch ( Oasis::playerAlreadyHasClan& exc) {

	}

    }

    
    return true;
}

int main () {

    	RUN_TEST(addPlayerTest);
	RUN_TEST(addClanTest);
	RUN_TEST(joinClanTest);

	return 0;
}
