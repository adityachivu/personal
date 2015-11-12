#ifndef TCHESS_BOARD_HPP
#define TCHESS_BOARD_HPP

#include <iostream>
#include <vector>
#include <map>
#include <cmath>
#include <climits>
#include "tchess_piece.hpp"

#define CHESS_BOARD_SIZE 8

class Board {
public:
	Board() {
		//allocate the vector
		board.resize(CHESS_BOARD_SIZE);
		for (int i = 0; i < CHESS_BOARD_SIZE; ++i) {
			for (int j = 0; j < CHESS_BOARD_SIZE; ++j) {
				board[i].push_back(NULL);
			}
		}
	}
	void initialize() {
		Piece* x;
		turn = false; //white's turn in the beginning

		//initialize the board configuration
		// put white pieces

		for (int i = 0; i < CHESS_BOARD_SIZE; ++i) {
			x = new Pawn(White);
			board[0][i] = x;
		}

		//put spaces
		for (int i = 1; i < 7; ++i) {
			for (int j = 0; j < CHESS_BOARD_SIZE; ++j) {
				board[i][j] = NULL;
			}
		}

		//put black pieces

		for (int i = 0; i < CHESS_BOARD_SIZE; ++i) {
			x = new Pawn(Black);
			board[7][i] = x;
		}
		w_pieces_number.resize(1);
		w_pieces_number[pawn] = 8;


		b_pieces_number.resize(1);
		b_pieces_number[pawn] = 8;

	}
	Board(Board *b) {
		//allocate the vector
		board.resize(CHESS_BOARD_SIZE);
		for (int i = 0; i < CHESS_BOARD_SIZE; ++i) {
			for (int j = 0; j < CHESS_BOARD_SIZE; ++j) {
				board[i].push_back(NULL);
			}
		}
		for (int i = 0; i < CHESS_BOARD_SIZE; ++i) {
			for (int j = 0; j < CHESS_BOARD_SIZE; ++j) {
				set_piece(i, j, b->get_piece(i, j));
			}
		}
		//set parent of the new object
		set_parent(b);
		//set turn of the new object
		turn = !b->get_turn();
	}
	void print() {
		cout << "  a b c d e f g h" << endl;
		for (int i = CHESS_BOARD_SIZE - 1; i >= 0; --i) {
			cout << i + 1 << " ";
			for (int j = 0; j < CHESS_BOARD_SIZE; ++j) {
				if (board[i][j] != NULL) {
					board[i][j]->print();
				} else {
					wcout << L"  ";
				}
			}
			if (i == 6 && get_turn()) { // black's turn
				cout << "	Black";
			} else if (i == 1 && !get_turn()) { //white's turn
				cout << "	White";
			}
			cout << endl;
		}
		cout << endl;
	}

	Piece* get_piece(short int x, short int y) {
		return board[x][y];
	}
	void set_piece(short int x, short int y, Piece* p) {
		board[x][y] = p;
	}
	bool get_turn() {
		return turn;
	}
	vector<vector<Piece*> > get_board() {
		return board;
	}
	Board* move_piece(short int src_x, short int src_y, short int dest_x,
			short int dest_y) {
		Board *new_board = new Board(this);

		Piece* src = new_board->get_piece(src_x, src_y);
		Piece* dest = new_board->get_piece(dest_x, dest_y);
		if (dest != NULL) { //in case of a yime
			new_board->set_piece_number(dest->get_type(), dest->get_color(), -1);
		}

		new_board->set_piece(dest_x, dest_y, src);
		new_board->set_piece(src_x, src_y, NULL);

		return new_board;
	}
	Board* just_move_piece(short int src_x, short int src_y, short int dest_x,
			short int dest_y) { //to set up a conf
		Board *new_board = new Board(this);
		new_board->set_piece(dest_x, dest_y, new_board->get_piece(src_x, src_y));
		new_board->set_piece(src_x, src_y, NULL);
		return new_board;
	}


Board* move(short int src_x, short int src_y, short int dest_x,short int dest_y) {

Piece* src = get_piece(src_x, src_y);
Piece* dest = get_piece(dest_x, dest_y);

if (src == NULL) 
{
cout << "Source state is not valid." << endl;
return NULL;
}

if (src_x == dest_x && src_y == dest_y) 
{
cout << "Source is equal to destination." << endl;
return NULL;
}

//turn check
if (!get_turn() && src->get_color() != White) { //white's turn black cannot move
cout << "It's White's turn wait yours." << endl;
return NULL;
} else if (get_turn() && src->get_color() != Black) {
cout << "It's Black's turn wait yours.." << endl;
return NULL;
}

if (src->get_type() == pawn) 
{
	if (src->get_color() == White)
	{
		if ((src_x - dest_x) == -1) 
			{// move forward one step
			if (src_y == dest_y && dest == NULL) 
			{// if there is no horizontal move and there is no piece then this is valid.
				return move_piece(src_x, src_y, dest_x, dest_y);
			} else if (abs(src_y - dest_y) == 1 && dest != NULL && dest->get_color() == Black) { //if there is a enemy in the diameter is valid.
				return move_piece(src_x, src_y, dest_x, dest_y);} 
			else {
						//cout << "Pawn cannot move." << endl;
						return NULL;
					}
				} else {
					//cout << "Pawn cannot move.Err:2" << endl;
					return NULL;
				}
			} else {//if black
				if ((src_x - dest_x) == 1) {// move forward one step
					if (src_y == dest_y && dest == NULL) {// if there is no horizontal move and there is no piece then this is valid.
						return move_piece(src_x, src_y, dest_x, dest_y);
					} else if (abs(src_y - dest_y) == 1 && dest != NULL
							&& dest->get_color() == White) { //if there is a enemy in the diameter is valid.
						return move_piece(src_x, src_y, dest_x, dest_y);
					} else {
						//						cout << "Pawn cannot move.Err:3" << endl;
						return NULL;
					}
				} else {
					//					cout << "Pawn cannot move.Err:4" << endl;
					return NULL;
				}
			}
		} 

		return NULL;
	}
	//	vector<Board*> list_all_moves(){
	//		return ;
	//	}
	Board* get_parent() {
		return parent;
	}
	void set_parent(Board* parent) {
		this->parent = parent;
	}
	int evaluate_board(Board* board) {
		int eval = 0;
		for (int i = 0; i < CHESS_BOARD_SIZE; ++i) {
			for (int j = 0; j < CHESS_BOARD_SIZE; ++j) {
			    if (get_piece(i, j) != NULL)
			    {
			        int whitescore = 0;
			        int blackscore = 0;
			        if(get_piece(i, j)->get_color())
			        {
			            
			            blackscore += (7 - i);
			            if (i == 0)
			                blackscore = INT_MAX;
			            
			        if(!get_piece(i, j)->get_color())
			        {
			            whitescore += i;
			            if (i == 7)
			                whitescore = INT_MAX;
			        }
			    }

		return (whitescore-blackscore);
	}
	vector<Board*>* list_all_moves() {
		vector<Board*> *moves = new vector<Board*> ();
		Board* temp = NULL;
		PieceColor turn = get_turn() ? Black : White;

		for (int i = 0; i < CHESS_BOARD_SIZE; ++i) {
			for (int j = 0; j < CHESS_BOARD_SIZE; ++j) {
				if (get_piece(i, j) != NULL && get_piece(i, j)->get_color()== turn) {
					for (int k = 0; k < CHESS_BOARD_SIZE; ++k) {
						for (int l = 0; l < CHESS_BOARD_SIZE; ++l) {
							if (i == k && j == l) {
								continue;
							}
							if ((temp = move(i, j, k, l)) != NULL) {
								moves->push_back(temp);
							}
						}
					}
				}
			}
		}

		return moves;
	}
private:
	vector<vector<Piece*> > board;
	Board* parent;
	bool turn;
	vector<short int> w_pieces_number;
	vector<short int> b_pieces_number;
};

#endif
