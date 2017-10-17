// Noah Jacobson
// Implementation of "checkers.h"
// 4/19/17
// Project 6 Part 2

#include "checkers.h"
#include "spaces.h"
#include "colors.h"
#include <iostream>
#include <stdio.h>
#include <ctype.h>
#include <cmath>

namespace main_savitch_14 
{

	using namespace std;

	Checkers::Checkers() {
		for(int row = 0; row < 8; row++) {
			for(int col = 0; col < 8; col++) {
				board[row][col] = new Spaces();
			}
		}
	} // constructor

	void Checkers::directions() const {
		cout << "How to move a piece." << endl;
		cout << "1. Type the space of the piece you are currently in." << endl;
		cout << "\t- Column first then row, for example, g6." << endl;
		cout << "2. Type the space you would like to move to after your piece." << endl;
		cout << "\t - Column first then row." << endl;
		cout << "\t - An example of a move would be f6g5." << endl;
		cout << "3. If you choose to jump, enter each spot your piece will be jumping to." << endl;
		cout << "\t - An example of a single jump would be d6f4." << endl;
		cout << "\t - To do a double or more jump, enter the first jump, then you will be prompted for the second jump." << endl;
	} // directions

	void Checkers::restart() {
		for(int row = 0; row < 8; row++) {

			// three rows with pieces left aligned
			if(row == 0 || row == 2 || row == 6) {
				// setting the colums 0, 2, 4, and 6 in rows 0, 2, 6
				for(int col = 0; col <=6; col += 2) {

					// there is only one red row
					if(row == 6) { // red
						board[row][col].make_red();
						board[row][col].make_full();
					}
					// two black rows
					else if(row == 0 || row == 2) { // black
						board[row][col].make_black();
						board[row][col].make_full();
					}
					// making all others empty
					else {
						board[row][col].make_empty();
					}
				}
			}
			// three rows with pieces left aligned
			else if(row == 1 || row == 5 || row == 7) {
				// setting the columns 1, 3, 5, 7
				for(int col = 1; col <= 7; col += 2) {
					if(row == 1) { // black
						board[row][col].make_black();
						board[row][col].make_full();
					}
					else if(row == 5 || row == 7) { // red
						board[row][col].make_red();
						board[row][col].make_full();
					}
					else {
						board[row][col].make_empty();
					}
				}
			}

		}
	} // restart

	void Checkers::display_status() const {
		Spaces tmp;

		cout << B_WHITE << BOLD << BLACK << "    A  B  C  D  E  F  G  H " << B_BLACK << RESET << endl;

		for(int row = 0; row < 8; row++) {

			if(row % 2 == 0) { // starting with yellow on the even colors
				cout << B_WHITE << BOLD << BLACK << " " << (1 + row) << " " << RESET;
				for(int col = 0; col < 8; col++) {
					tmp = board[row][col];

					// if the piece is black
					if(tmp.get_color() == 'b') {
						if(tmp.is_king()) { // a king
							cout << B_YELLOW << BOLD << BLACK << " K " << RESET;
						}
						else { // regular piece
							cout << B_YELLOW << BOLD  << BLACK << " @ " << RESET;
						}
					}
					// if the piece is red
					else if(tmp.get_color() == 'r') {
						if(tmp.is_king()) { // a king
							cout << B_YELLOW << BOLD << RED << " K " << RESET;
						}
						else { // regular piece
							cout << B_YELLOW << BOLD << RED << " @ " << RESET;
						}
					}
					// if the spaces does not have a piece
					else {
						if(col % 2 == 0) { // yellow
							cout << B_YELLOW << "   " << RESET;
						}
						else { // blue
							cout << B_CYAN << "   " << RESET;
						}
					}
				} // end of inner for loop
			} 
			else {
				cout << B_WHITE << BOLD << BLACK << " " << (1 + row) << " " << RESET;

				for(int col = 0; col < 8; col++) {
					tmp = board[row][col];

					// if the piece is black
					if(tmp.get_color() == 'b') {
						if(tmp.is_king()) { // a king
							cout << B_YELLOW << BOLD << BLACK << " K " << RESET;
						}
						else { // regular piece
							cout << B_YELLOW << BOLD  << BLACK << " @ " << RESET;
						}
					}
					// if the piecec is red
					else if(tmp.get_color() == 'r') {
						if(tmp.is_king()) { // a king
							cout << B_YELLOW << BOLD << RED << " K " << RESET;
						}
						else { // regular piece
							cout << B_YELLOW << BOLD << RED << " @ " << RESET;
						}
					}
					// if the space does not have a piece 
					else {
						if(col % 2 == 1) { // yellow
							cout << B_YELLOW << "   " << RESET;
						}
						else { // blue
							cout << B_CYAN << "   " << RESET;
						}
					}
				} // end of inner for loop
			}
			cout << endl; // moving to the next line
		}
		directions();
		if(next_mover() == HUMAN) {
			cout << RED << "Player 1's turn..." << RESET << endl;
		}
		else {
			cout << "Player 2's turn..." << endl;
		}
	} // end of display_status

	bool Checkers::is_legal(const std::string& move) const {
		int curr_row, curr_col, nex_row, nex_col;
		string jump_move = "";

		// getting the current row and column of the piece
		curr_row = int(move[1] - '1');
		curr_col = int(tolower(move[0] - 'a'));

		// if the piece is not on the board
		if(curr_row > 7 || curr_row < 0 || curr_col > 7 || curr_col < 0) {
			//cout << "a" << endl;
			return false;
		}

		// getting the next row and column of the piece
		nex_row = int(move[3] - '1');
		nex_col = int(tolower(move[2] - 'a'));

		// if the user is trying to move to a spot not on the board
		if(nex_row > 7 || nex_row < 0 || nex_col > 7 || nex_col < 0) {
			//cout << "b" << endl;
			return false;
		}

		if(board[nex_row][nex_col].is_full()) { // if there is a piece in the destination
			//cout << "c" << endl;
			return false;
		}

		if(curr_row == nex_row) {
			//cout << "d" << endl;
			return false;
		}

		if(curr_col == nex_col) {
			//cout << "e" << endl;
			return false;
		}

		if(next_mover() == COMPUTER && board[curr_row][curr_col].is_red()) {
			//cout << "f" << endl;
			return false; 
		} 

		if(next_mover() == HUMAN && board[curr_row][curr_col].is_black()) {
			//cout << "g" << endl;
			return false;
		}

		// if there is a jump possible
		if(is_jump(jump_move, " ")) {
			// if the move matches with any of the jumps then the move is legal
			if(jump_move.find(move) != string::npos) {
				return true;
			}
			//cout << "h" << endl;
			return false;
		}

		if(abs(curr_row - nex_row) > 1) {
			//cout << "i" << endl;
			return false;
		}
		if(abs(curr_col - nex_col) > 1) {
			//cout << "j" << endl;
			return false;
		}

		return true;
	} // is_legal

	void Checkers::make_move(const string &move) {
		int c_r, c_c, n_r, n_c;
		string move2 = move;
		int d_r, d_c;
		// current row, colum -- next row, colum -- delete row, colum

		string jump_move = "";

		// getting the current row and column of the piece
		c_r = int(move[1] - '1');
		c_c = int(tolower(move[0] - 'a'));

		// getting the next row and column of the piece
		n_r = int(move[3] - '1');
		n_c = int(tolower(move[2] - 'a'));

		string pos;

		pos += char('a' + n_c);
		pos += char('1' + n_r);
		
		bool show = false; // to see if we must show the board for a sequential jump

		// if the move is a jump
		while(is_jump(jump_move, pos)) {

			// double jumps
			if(show) {
				
				display_status();
				cout << "Detected jump with piece: " << pos << endl;
				move2 = main_savitch_14::game::get_user_move();
				
				while(jump_move.find(move2) == string::npos) {
					cout << "You must move piece: " << pos << endl;
					move2 = main_savitch_14::game::get_user_move();
				}

			}
			// getting the current row and column of the piece
			c_r = int(move2[1] - '1');
			c_c = int(tolower(move2[0] - 'a'));

			// getting the next row and column of the piece
			n_r = int(move2[3] - '1');
			n_c = int(tolower(move2[2] - 'a'));
			// getting the spot being jumped
			d_r = (c_r + n_r) / 2;
			d_c = (c_c + n_c) / 2;

			cout << "CR: " << c_r << " C_C: " << c_c << "     N_R: " << n_r << " N_C: " << n_c << "    DR: " << d_r << " DC: " << d_c << endl;
			board[n_r][n_c] = board[c_r][c_c];
			board[c_r][c_c] = board[d_r][d_c] = new Spaces();

			pos = "";
			pos += char('a' + n_c);
			pos += char('1' + n_r);
			
			show = true;
		}
		if(show) {
			return; // jumped
		}
		// if a regular move

			board[n_r][n_c] = board[c_r][c_c];
			board[c_r][c_c] = new Spaces();
		

		// checking to see if there are any new kings 
		check_king();

		main_savitch_14::game::make_move(move);

	} // make_move

	void Checkers::check_king() {
		for(int c = 0; c < 8; c++) {
			if(board[0][c].is_red()) {
				board[0][c].make_king();
			}
			if(board[7][c].is_black()) {
				board[7][c].make_king();
			}
		}
	}

	bool Checkers::is_game_over() const {
		int black, red; // number of pieces left
		red = black = 0;

		for(int row = 0; row < 8; row++) {
			for(int col = 0; col < 8; col++) {
				if(board[row][col].is_full()) {
					if(board[row][col].is_red()) {
						red++;
					}
					else {
						black++;
					}
				}
			}
		}

		if(red == 0 || black == 0) {
			return true;
		}
		return false;
	} // is_game_over

	bool Checkers::is_jump(string &jump_move, const string &start) const {
		Spaces spot;
		bool jump = false;
		jump_move = "";

		// if regular jump
		if(start == " ") {
			// Player 1 is red
			if(next_mover() == HUMAN) {

				for(int r = 0; r < 8; r++) {
					for(int c = 0; c < 8; c++) {
						
						spot = board[r][c];
						// making sure the spot is red
						if(spot.get_color() == 'r') {

							// jumping left, 
							if(r >= 2 && c >= 2 && board[r-1][c-1].get_color() == 'b' && !board[r-2][c-2].is_full()) {
								jump = true;
								// adding jump
								jump_move += char('a' + c);
								jump_move += char('1' + r);
								jump_move += char('a' + c - 2);
								jump_move += char('1' + r - 2);
								jump_move += ".";
							}

							// jumping right
							if(r >= 2 && c <= 5 && board[r-1][c+1].get_color() == 'b' && !board[r-2][c+2].is_full()) {
								jump = true;
								// adding jump
								jump_move += char('a' + c);
								jump_move += char('1' + r);
								jump_move += char('a' + c + 2);
								jump_move += char('1' + r - 2);
								jump_move += ".";
							}

							// looking for additional jumps if spot is a king
							if(spot.is_king()) {

								// jumping behind left
								if(r <= 6 && c >= 2 && board[r+1][c-1].get_color() == 'b' && !board[r+2][c-2].is_full()) {
									jump = true;
									// adding jump
									jump_move += char('a' + c);
									jump_move += char('1' + r);
									jump_move += char('a' + c - 2);
									jump_move += char('1' + r + 2);
									jump_move += ".";
								}

								// jumping behind right
								if(r <= 6 && c <= 5 && board[r+1][c+1].get_color() == 'b' && !board[r+2][c+2].is_full()) {
									jump = true;
									// adding jump
									jump_move += char('a' + c);
									jump_move += char('1' + r);
									jump_move += char('a' + c + 2);
									jump_move += char('1' + r + 2);
									jump_move += ".";
								}

							}
						} //
					}
				}
			}

			// Player 2 is black
			else {

				for(int r = 0; r < 8; r++) {
					for(int c = 0; c < 8; c++) {
						
						spot = board[r][c];
						// making sure the spot is black
						if(spot.get_color() == 'b') {

							// jumping left, 
							if(r <= 5 && c >= 2 && board[r+1][c-1].get_color() == 'r' && !board[r+2][c-2].is_full()) {
								jump = true;
								// adding jump
								jump_move += char('a' + c);       // colum
								jump_move += char('1' + r);             // row
								jump_move += char('a' + c - 2);   // dest col
								jump_move += char('1' + r + 2);         // dest row
								jump_move += ".";
							}

							// jumping right
							if(r <= 5 && c <= 5 && board[r+1][c+1].get_color() == 'r' && !board[r+2][c+2].is_full()) {
								jump = true;
								// adding jump
								jump_move += char('a' + c);       // colum
								jump_move += char('1' + r);            // row
								jump_move += char('a' + c + 2);   // dest col
								jump_move += char('1' + r + 2);         // dest row
								jump_move += ".";
							}

							// looking for additional jumps if spot is a king
							if(spot.is_king()) {

								// jumping behind left
								if(r >= 2 && c >= 2 && board[r-1][c-1].get_color() == 'r' && !board[r-2][c-2].is_full()) {
									jump = true;
									// adding jump
									jump_move += char('a' + c);       // colum
									jump_move += char('1' + r);            // row
									jump_move += char('a' + c - 2);   // dest col
									jump_move += char('1' + r + 2);         // dest row
									jump_move += ".";
								}

								// jumping behind right
								if(r >= 2 && c <= 5 && board[r-1][c+1].get_color() == 'r' && !board[r-2][c+2].is_full()) {
									jump = true;
									// adding jump
									jump_move += char('a' + c);       // colum
									jump_move += char('1' + r);            // row
									jump_move += char('a' + c + 2);   // dest col
									jump_move += char('1' + r + 2);         // dest row
									jump_move += ".";
								}

							}
						} //
					}
				}
			}
		}

		// looking for a double jump with a starting spot
		else {

			int r = int(start[1] - '1');
			int c = int(tolower(start[0] - 'a'));
			Spaces spot = board[r][c];

			// Player 1 
			if(spot.is_red()) {
				//cout << "human" << endl;
				// jumping left
				if(r >= 2 && c >= 2 && board[r-1][c-1].get_color() == 'b' && !board[r-2][c-2].is_full()) {
					jump = true;
					// adding jump
					cout << "jLEFT" << endl;
					jump_move += char('a' + c);
					jump_move += char('1' + r);
					jump_move += char('a' + c - 2);
					jump_move += char('1' + r - 2);
					jump_move += ".";
				}

				// jumping right
				if(r >= 2 && c <= 5 && board[r-1][c+1].get_color() == 'b' && !board[r-2][c+2].is_full()) {
					jump = true;
					// adding jump
					cout << "jRIGHT" << endl;
					jump_move += char('a' + c);
					jump_move += char('1' + r);
					jump_move += char('a' + c + 2);
					jump_move += char('1' + r - 2);
					jump_move += ".";
				}

				// looking for additional jumps if spot is a king
				if(spot.is_king()) {

					// jumping behind left
					if(r <= 6 && c >= 2 && board[r+1][c-1].get_color() == 'b' && !board[r+2][c-2].is_full()) {
						jump = true;
						// adding jump
						jump_move += char('a' + c);
						jump_move += char('1' + r);
						jump_move += char('a' + c - 2);
						jump_move += char('1' + r + 2);
						jump_move += ".";
					}

					// jumping behind right
					if(r <= 6 && c <= 5 && board[r+1][c+1].get_color() == 'b' && !board[r+2][c+2].is_full()) {
						jump = true;
						// adding jump
						jump_move += char('a' + c);
						jump_move += char('1' + r);
						jump_move += char('a' + c + 2);
						jump_move += char('1' + r + 2);
						jump_move += ".";
					}

				}

			}

			// Player 2
			else if(spot.is_black()){
				
				// jumping left
				if(r <= 5 && c >= 2 && board[r+1][c-1].get_color() == 'r' && !board[r+2][c-2].is_full()) {
					jump = true;
					// adding jump
					cout << "jLEFT" << endl;
					jump_move += char('a' + c);       // colum
					jump_move += char('1' + r);            // row
					jump_move += char('a' + c - 2);   // dest col
					jump_move += char('1' + r + 2);         // dest row
					jump_move += ".";
				}

				// jumping right
				if(r <= 5 && c <= 5 && board[r+1][c+1].get_color() == 'r' && !board[r+2][c+2].is_full()) {
					jump = true;
					// adding jump
					cout << "jRIGHT" << endl;
					jump_move += char('a' + c);       // colum
					jump_move += char('1' + r);        // row
					jump_move += char('a' + c + 2);   // dest col
					jump_move += char('1' + r + 2);         // dest row
					jump_move += ".";
				}

				// looking for additional jumps if spot is a king
				if(spot.is_king()) {

					// jumping behind left
					if(r >= 2 && c >= 2 && board[r-1][c-1].get_color() == 'r' && !board[r-2][c-2].is_full()) {
						jump = true;
						// adding jump
						jump_move += char('a' + c);       // colum
						jump_move += char('1' + r);       // row
						jump_move += char('a' + c - 2);   // dest col
						jump_move += char('1' + r - 2);         // dest row
						jump_move += ".";
					}

					// jumping behind right
					if(r >= 2 && c <= 5 && board[r-1][c+1].get_color() == 'r' && !board[r-2][c+2].is_full()) {
						jump = true;
						// adding jump
						jump_move += char('a' + c);       // colum
						jump_move += char('1' + r);         // row
						jump_move += char('a' + c + 2);   // dest col
						jump_move += char('1' + r - 2);         // dest row
						jump_move += ".";
					}

				}
			}
		}
		return jump;
	} // is_jump_possible

	int Checkers::evaluate() const {
		int value = 0;
		Spaces spot;

		for(int r = 0; r < 8; r++) {
			for(int c = 0; c < 8; c++) {
				spot = board[r][c];

				if(spot.is_full() && spot.is_red()) {
					value--;
					if(spot.is_king()) {
						value--;
					}
				}
				if(spot.is_full() && spot.is_black()) {
					value++;
					if(spot.is_king()) {
						value++;
					}
				}
			}
		}
		return value;
	} // evaluate
	
	game* Checkers::clone() const {
		return new Checkers(*this);
	} // clone

	void Checkers::compute_moves(std::queue<std::string>& moves) const {
		string move = "";
		Spaces spot;
		string str;

		bool jump = false;

		if(is_jump(move, " ")) {
			// loading the strings into the queue
			for(int index = 0; index < (move.length() / 5); index++) {
				str = "";
				// getting the move from string move
				str += move[index];
				str += move[index + 1];
				str += move[index + 2];
				str += move[index + 3];
				
				// skipping the period after ever jump move

				moves.push(str);

			}
			return; // no other moves will be checked because of the force jump rule
		}

		for(int r = 0; r < 8; r++) {
			for(int c = 0; c < 8; c++) {
				spot = board[r][c];

				if(spot.is_black()) {
					// looking for backwrads moves if the spot is a king
					if(spot.is_king()) {
						// back left
						if(r >= 1 && c >= 1 && !board[r-1][c-1].is_full()) {
							move += char('a' + c);       // colum
							move += char('1' + r);       // row
							move += char('a' + c - 1);   // dest col
							move += char('1' + r - 1);   // dest row
							if(is_legal(move)) {
								moves.push(move);
							}
							
							move = "";
						}
						// back right
						if(r >= 1 && c <= 6 && !board[r-1][c+1].is_full()) {
							move += char('a' + c);       // colum
							move += char('1' + r);       // row
							move += char('a' + c + 1);   // dest col
							move += char('1' + r - 1);         // dest row
							if(is_legal(move)) {
								moves.push(move);
							}
							move = "";
						}
					}

					// looking for moves forward

					// forward left
					if(r <= 6 && c >= 1 && !board[r+1][c-1].is_full()) {
							move += char('a' + c);       // colum
							move += char('1' + r);       // row
							move += char('a' + c - 1);   // dest col
							move += char('1' + r + 1);   // dest row
							if(is_legal(move)) {
								moves.push(move);
							}
							move = "";
					}
					// forward right
					if(r <= 6 && c <= 6 && !board[r+1][c+1].is_full()) {
							move += char('a' + c);       // colum
							move += char('1' + r);       // row
							move += char('a' + c + 1);   // dest col
							move += char('1' + r + 1);   // dest row
							if(is_legal(move)) {
								moves.push(move);
							}
							move = "";
					}
				}
			}	
		}

		//cout << "moves size: " << moves.size() << endl;
	} // computer_moves

} // end of namespace