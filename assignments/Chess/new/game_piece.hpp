#ifndef GAME_PIECE_HPP
#define GAME_PIECE_HPP
//
//
//
//
//  Piece class provides piece color and piece type read and write methods.
//
//
//
//
//
//
#include <iostream>
#include <vector>
#include <map>
#include <cmath>
#include <climits>

using namespace std;

enum PieceColor {
	White, Black
};

class Piece
{

    public:
	virtual void print() = 0;
	PieceColor get_color()
	{
		return color;
	}
	
    protected:	
	PieceColor color;
	
};

class Pawn: public Piece
{
    public:
	Pawn(PieceColor color)
	{		
		this->color = color;
	}
	
	void print()
	{
		if (get_color() == White)
		{
			wcout << "+ ";
		}
		else if (get_color() == Black)
		{
			wcout << "* ";
		}
	}
};

#endif
