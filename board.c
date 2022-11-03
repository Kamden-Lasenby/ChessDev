// board.c

#include "stdio.h"
#include "defs.h"


void ResetBoard(S_BOARD *pos) {
	
	int index = 0;
	
	// set ALL 120 squares on board to OFFBOARD
	for(index = 0; index < BRD_SQ_NUM; ++index) {
		pos->pieces[index] = OFFBOARD;
	}
	
	// converts all 64 squares inside 120 board to EMPTY
	/*
		pieces[] is a 120 element array of the board with
		offboard squares included. we loop through 64 elements
		representing a 64 board and convert them to 120 board
	*/
	
	for(index = 0; index < 64; ++index) {
		pos->pieces[SQ120(index)] = EMPTY;
	}
	
	for(index = 0; index < 3; ++index) {
		pos->bigPce[index] = 0;
		pos->majPce[index] = 0;
		pos->minPce[index] = 0;
		pos->pawns[index] = 0ULL;
	}
	
	for(index = 0; index < 13; ++index) {
		pos->pceNum[index] = 0;
	}
	
	pos->KingSq[WHITE] = pos->KingSq[BLACK] = NO_SQ;
	
	pos->side = BOTH;
	pos->enPas = NO_SQ;
	pos->fiftyMove = 0;
	
	pos->ply = 0;
	pos->hisPly = 0;
	
	pos->castlePerm = 0;
	
	pos->posKey = 0ULL;
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
}