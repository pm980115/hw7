// Noah Jacobson
// Header of "checkers.h"
// 4/19/17
// Project 6 Part 2

#ifndef CHECKERS_H
#define CHECKERS_H

#include <iostream>
#include "spaces.h"

namespace main_savitch_14 
{

	class Checkers : public game{

		public:
			// Constructor
			Checkers();
			// Displays the current state of the board
			void display_status() const;
			// resets the board
			void restart();
			// returns true/false depending on if the move is legal or not
			bool is_legal(const std::string& move) const;
			// moves the piece on the board
			void make_move(const std::string &move);
			void directions() const;
			bool is_game_over() const;
			bool is_jump(std::string &jump_move, const std::string &start = " ") const;
			void check_king();
			int evaluate() const;
			game* clone() const;
			void compute_moves(std::queue<std::string>& moves) const;
			

		private:
			Spaces board[8][8]; // 8x8 checker board of spaces
	};

}
#endif