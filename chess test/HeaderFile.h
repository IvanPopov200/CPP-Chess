#pragma once
#include <iostream>
#include <cmath>
#include <string>

enum Piece { King, Queen, Bishop, Knight, Rook, Pawn, NoPiece };
enum  Color { WHITE, BLACK, NONE };

class Space
{

	Piece piece;
	Color color;
	int x, y;
public:
	void setSpace(Space*);
	void setNoPiece();
	void assignPieceAndColor(Piece, Color);
	Piece getPiece();
	Color getColor();
	void setX(int _x) { x = _x; }
	void setY(int _y) { y = _y; }
	int getX() { return x; }
	int getY() { return y; }
	Space();
};

class Board
{
	
	Space square[8][8];
	Color turn = WHITE;
	bool moveKing(Space* thisKing, Space* thatSpace);
	bool moveQueen(Space* thisQueen, Space* thatSpace);
	bool moveBishop(Space* thisBishop, Space* thatSpace);
	bool moveKnight(Space* thisKnight, Space* thatSpace);
	bool moveRook(Space* thisRook, Space* thatSpace);
	bool movePawn(Space* thisPawn, Space* thatSpace);
	bool makeMove(int x1, int y1, int x2, int y2);
	void createBoard();
public:
	Space* getSquare(int x, int y) {
		return &square[x][y];
	}
	void setSquare(Space* s, int x, int y) {
		square[x][y] = *s;
	}
	bool doMove();

	void setBoard();
	bool playGame();
};