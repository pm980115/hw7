// Noah Jacobson
// Implementation of "spaces.h"
// 4/19/17
// Project 6 Part 1

#include <iostream>
#include "spaces.h"

namespace main_savitch_14 
{

	Spaces::Spaces(const bool &the_occ, const char &the_piece, const bool &the_king) {
		occupied = false;
		piece = ' ';
		king = false;
	} // constructor

	// mutators
	void Spaces::make_red() {
		piece = 'r';
	}

	void Spaces::make_black() {
		piece = 'b';
	}

	void Spaces::make_empty() {
		occupied = false;
	}

	void Spaces::make_full() {
		occupied = true;
	}

	// checking status
	bool Spaces::is_full() const {
		return occupied;
	}

	bool Spaces::is_red() const {
		return(piece == 'r');
	}

	bool Spaces::is_black() const {
		return(piece == 'b');
	}

	bool Spaces::is_king() const {
		return king;
	}

	void Spaces::make_king() {
		king = true;
	}

	// who Spaces::get_owner() const {
	// 	return owner;
	// }

	// void Spaces::set_owner(const who &w) {
	// 	owner = w;
	// }
}