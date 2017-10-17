// Noah Jacobson
// Header of "spaces.h"
// 4/19/17
// Project 6 Part 1

#ifndef SPACES_H
#define SPACES_H

#include <iostream>
#include "game.h"

namespace main_savitch_14
{

	class Spaces{
		public:
			Spaces(const bool &the_occ = false, const char &the_piece = ' ', 
				   const bool &the_king = false);

			// mutators
			void make_red();
			void make_black();
			void make_empty();
			void make_full();
			void make_king();

			// checking status
			bool is_full() const;
			bool is_red() const;
			bool is_black() const;
			bool is_king() const;
			char get_color() const {return piece;}
			// setting and getting the owner
			//main_savitch_14::who get_owner() const;
			//void set_owner(const who &w) {owner = w;}

		private:
			bool occupied; // if there is a piece in the space
			char piece; // 'r' - red, 'b' - black
			bool king; // if it is a king
	};
}


#endif