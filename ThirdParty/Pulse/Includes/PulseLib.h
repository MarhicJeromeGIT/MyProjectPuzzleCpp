#pragma once

#include <string>
#include <vector>

namespace pulse {

	class Pulse;
	class Position;

	class PulseLib
	{
	private:
		Pulse* pulsePtr;

	public:
		PulseLib();
		
		void startGame();
		// Return all the possible moves from this position
		//void getMoves(int file, int rank); // file entre 0 et 7, rank entre 1 et 8

		// Make the AI play the next move
		struct myMove
		{
			int code;
			int origFile; // [0;7] 
			int origRank; // [0;7]
			int destFile;
			int destRank;

			myMove(){}
			myMove(int _origFile, int _origRank, int _destFile, int _destRank) :
				origFile(_origFile), origRank(_origRank), destFile(_destFile), destRank(_destRank){}
		};
		void play(myMove& aimove);

		Position* position;

		void makeMove(const myMove& move);

		// Return all the possible moves from this position
		void getMoveList(int origFile, int origRank, std::vector<myMove>& legalMoves);
		 

		void drawPos();
	};

}