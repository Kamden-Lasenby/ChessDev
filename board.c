// board.c

#include "stdio.h"
#include "defs.h"


// very important function that parses a Forsyth-Edwards Notation (FEN) record.
// a FEN record is a notation style for describing a board position
// a sample (starting) record looks like this: 'rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1'
// the function parses character by character and assembles our chess board.
int Parse_Fen(char *fen, S_BOARD *pos) {
	
	ASSERT(fen!=NULL);
	ASSERT(pos!=NULL);
	
	int rank = RANK_8;
	int file = FILE_A;
	int piece = 0;
	int count = 0; //empty squares
	int i = 0; // for loop index
	int sq64;
	int sq120;
	
	ResetBoard(pos);
	
	while ((rank >= RANK_1) && *fen) {
		count = 1;
		switch (*fen) {
			case 'p': piece = bP; break;
			case 'r': piece = bR; break;
			case 'n': piece = bN; break;
			case 'b': piece = bB; break;
			case 'k': piece = bK; break;
			case 'q': piece = bQ; break;
			case 'P': piece = wP; break;
			case 'R': piece = wR; break;
			case 'N': piece = wN; break;
			case 'B': piece = wB; break;
			case 'K': piece = wK; break;
			case 'Q': piece = wQ; break;
			
			/* these cases convert empty spaces to strings
			   and then assign them to the count variable
			*/
			case '1':
			case '2':
			case '3':
			case '4':
			case '5':
			case '6':
			case '7':
			case '8':
				piece = EMPTY;
				count = *fen - '0';
				break;
				
			case '/':
			case ' ':
				rank--;
				file = FILE_A;
				fen++;
				continue;
			
			default:
				printf("FEN error \n");
				return -1;
		}
		
		/* this loop essentially uses the information parsed by the switch statement
		   to assign the pieces in the FEN to our board.
		   a cool feature of this is that count variable, which by default is equal to 1,
		   making the loop only have to run once and places the parsed piece on the board.
		   if the count is larger than one (explained in the last comment) then the loop will
		   run that many times ignoring the piece assignment operation in the if-statement.
		   small detail of the function but I thought it was cool.
		*/
		for (i = 0; i < count; i++) {
			sq64 = rank * 8 + file;
			sq120 = SQ120(sq64);
			if (piece != EMPTY) {
				pos->pieces[sq120] = piece;
			}
			file++;
		}
		
		fen++; //increase the fen pointer to next character to parse
	}
	
}

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