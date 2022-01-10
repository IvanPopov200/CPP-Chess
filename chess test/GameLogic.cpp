#include "HeaderFile.h"
using namespace std;

Space::Space()
{
	piece = NoPiece;
	color = NONE;
}

void Space::setSpace(Space* space)
{
	color = space->getColor();
	piece = space->getPiece();
}

void Space::setNoPiece()
{
	color = NONE;
	piece = NoPiece;
}

Piece Space::getPiece()
{
	return piece;
}

Color Space::getColor()
{
	return color;
}

void Space::assignPieceAndColor(Piece p, Color c)
{
	piece = p;
	color = c;

}


void Board::createBoard(){
using namespace std;
cout << "WHITE IS TOP// BLACK IS BOTTOM" << endl << endl;
	cout << "   A   B   C   D   E   F   G   H " << endl;
	cout << " ---------------------------------" << endl;
	for (int i = 0; i < 8; i++)
	{
		cout << i+1 << "|";
		for (int j = 0; j < 8; j++) {
			char pr=1;

			Piece p = square[j][i].getPiece();
			Color c = square[j][i].getColor();
			
			switch (p)
			{
			case King: (c == WHITE) ? pr=75 : pr = 107;
				break;
			case Queen: (c == WHITE) ? pr=81 : pr = 113;
				break;
			case Bishop:(c == WHITE) ? pr=66 : pr=98;
				break;
			case Knight:(c == WHITE) ? pr= 72 : pr= 104;
				break;
			case Rook: (c == WHITE) ? pr= 82 : pr = 114;
				break;
			case Pawn: (c == WHITE) ? pr= 80 : pr =112;
				break;
			case NoPiece: pr = 0;
				break;
			default: cout << "Error";
				break;
			}

			cout << " " << pr << " |";
		}
		cout << endl;
		cout << " ---------------------------------";
		cout << endl;

	}
	cout << "   1   2   3   4   5   6   7   8 " << endl;
	cout << endl;

}

bool Board::doMove() {
	using namespace std;
	string move;
	int x1, x2, y1, y2;
	bool stop = false;
	while (!stop)
	{
		if (turn == WHITE)
			cout << "It is white`s turn" << endl;
		else
			cout << "It is black`s turn" << endl;
		cout << "Enter x and y coords of the piece you want to move and destination " << endl;
		cout << "Example: 5152 where 5=x 1=y of piece and 5=x 2=y of destination" << endl;
		cin >> move;
		x1 = move[0] - 49;
		y1 = move[1] - 49;
		x2 = move[2] - 49;
		y2 = move[3] - 49;
		if (getSquare(x2, y2)->getPiece() == King)
		{
			if (getSquare(x1,y1)->getColor()==WHITE)
			{
				cout << "The winner is white!" << endl;
				return false;
			}
			else if (getSquare(x1, y1)->getColor() == BLACK) 
			{
				cout << "The Winner is black!" << endl;
				return false;
			}
		}
		if (getSquare(x1, y1)->getColor() == turn)
		{


			if (makeMove(x1, y1, x2, y2) == false)
			{
				cout << "This move is not valid! Type another move" << endl;
			}
			else
				stop = true;
		}
		else
			cout << "This piece belongs to the other player" << endl;

	}
		


	if (turn == BLACK) {
		turn = WHITE;
	}
	else {
		turn = BLACK;
	}
	return true;

}

void Board::setBoard()
{
	square[0][0].assignPieceAndColor(Rook, WHITE);
	square[1][0].assignPieceAndColor(Knight, WHITE);
	square[2][0].assignPieceAndColor(Bishop, WHITE);
	square[3][0].assignPieceAndColor(Queen, WHITE);
	square[4][0].assignPieceAndColor(King, WHITE);
	square[5][0].assignPieceAndColor(Bishop, WHITE);
	square[6][0].assignPieceAndColor(Knight, WHITE);
	square[7][0].assignPieceAndColor(Rook, WHITE);

	square[0][7].assignPieceAndColor(Rook, BLACK);
	square[1][7].assignPieceAndColor(Knight, BLACK);
	square[2][7].assignPieceAndColor(Bishop, BLACK);
	square[3][7].assignPieceAndColor(Queen, BLACK);
	square[4][7].assignPieceAndColor(King, BLACK);
	square[5][7].assignPieceAndColor(Bishop, BLACK);
	square[6][7].assignPieceAndColor(Knight, BLACK);
	square[7][7].assignPieceAndColor(Rook, BLACK);

	for (int i = 0; i < 8; i++)
	{
		square[i][1].assignPieceAndColor(Pawn, WHITE);
		square[i][6].assignPieceAndColor(Pawn, BLACK);

	}
	for (int i = 2; i < 6; i++)
	{
		for (int j = 0; j < 8; j++)
			square[j][i].assignPieceAndColor(NoPiece, NONE);

	}
	for (int i = 0; i < 8; i++)
		for (int j = 0; j < 8; j++)
		{
			square[i][j].setX(i);
			square[i][j].setY(j);
		}

}

bool Board::playGame()
{
	system("cls");
	createBoard();
	return doMove();

}

bool Board::moveKing(Space* thisKing, Space* thatSpace) {

	if (((thatSpace->getX() + 1 == thisKing->getX()) || (thatSpace->getX() - 1 == thisKing->getX()) || (thatSpace->getX() == thisKing->getX())) && ((thatSpace->getY() + 1 == thisKing->getY()) || (thatSpace->getY() - 1 == thisKing->getY())||(thatSpace->getY()==thisKing->getY())))
		
	{
		
		thatSpace->setSpace(thisKing);
		thisKing->setNoPiece();
		return true;
		
	}

	
	else return false;
}
bool Board::moveQueen(Space* thisQueen, Space* thatSpace) { 
	int QueenX = thisQueen->getX();
	int QueenY = thisQueen->getY();
	int thatX = thatSpace->getX();
	int thatY = thatSpace->getY();
	
	int yIncrement;
	int xIncrement;

	bool invalid = false;
	
		if (QueenX != thatX || QueenY != thatY)
		{

			if (QueenX == thatX)
			{
				yIncrement = (thatY - QueenY) / (abs(thatY - QueenY));
				for (int i = QueenY + yIncrement; i != thatY; i += yIncrement)
				{

					if (square[thatX][i].getColor() != NONE)
						return false;

				}
			}
			else
				if (QueenY == thatY)
				{

					xIncrement = (thatX - QueenX) / (abs(thatX - QueenX));
					for (int i = QueenX + xIncrement; i != thatX; i += xIncrement)
					{
						if (square[i][thatY].getColor() != NONE)
							return false;
					}
				}
				else
					if (abs(QueenX - thatX) == abs(QueenY - thatY))
					{
						xIncrement = (thatX - QueenX) / (abs(thatX - QueenX));
						yIncrement = (thatY - QueenY) / (abs(thatY - QueenY));

						for (int i = 1; i < abs(QueenX - thatX); i++)
						{
							
							if (square[QueenX + xIncrement * i][QueenY + yIncrement * i].getColor() != NONE)
								return false;

						}
					}
					else
						return false;
		
	}


	if (invalid == false)
	{
		thatSpace->setSpace(thisQueen);
		thisQueen->setNoPiece();
		return true;
	}
	else
	{
		return false;
	}
}

bool Board::moveBishop(Space* thisBishop, Space* thatSpace) {
	int BishopX = thisBishop->getX();
	int BishopY = thisBishop->getY();
	int thatX = thatSpace->getX();
	int thatY = thatSpace->getY();
	bool invalid = false;
	Space* s;
	
		if (abs(BishopX - thatX) == abs(BishopY - thatY))
		{
			int xIncrement = (thatX - BishopX) / (abs(thatX - BishopX));
			int yIncrement = (thatY - BishopY) / (abs(thatY - BishopY));

			for (int i = 1; i < abs(BishopX - thatX); i++)
			{
				
				if (square[BishopX + xIncrement * i][BishopY + yIncrement * i].getColor() != NONE)
					return false;

			}
		}
		else
			return false;

		if (invalid == false)
		{
			thatSpace->setSpace(thisBishop);
			thisBishop->setNoPiece();
			return true;
		}
		else
		{
			return false;
		}
	
}
bool Board::moveKnight(Space* thisKnight, Space* thatSpace)
{
	
	int KnightX = thisKnight->getX();
	int KnightY = thisKnight->getY();
	int thatX = thatSpace->getX();
	int thatY = thatSpace->getY();
	
		if ((abs(KnightX - thatX) == 2 && abs(KnightY - thatY) == 1) || (abs(KnightX - thatX) == 1 && abs(KnightY - thatY) == 2))
		{
			thatSpace->setSpace(thisKnight);
			thisKnight->setNoPiece();
			return true;
		}
		else
		{
			return false;
		}
	
}

bool Board::moveRook(Space* thisRook, Space* thatSpace)
{
	
	int RookX = thisRook->getX();
	int RookY = thisRook->getY();
	int thatX = thatSpace->getX();
	int thatY = thatSpace->getY();
	bool invalid = false;
	
		if (RookX != thatX || RookY != thatY)
		{

			if (RookX == thatX)
			{
				int yIncrement = (thatY - RookY) / (abs(thatY - RookY));
				for (int i = RookY + yIncrement; i != thatY; i += yIncrement)
				{

					if (square[thatX][i].getColor() != NONE)
						return false;

				}
			}
			else
				if (RookY == thatY)
				{

					int xIncrement = (thatX - RookX) / (abs(thatX - RookX));
					for (int i = RookX + xIncrement; i != thatX; i += xIncrement)
					{
						if (square[i][thatY].getColor() != NONE)
							return false;
					}
				}
				else
					return false;
		
	}
	if (invalid == false)
	{
		thatSpace->setSpace(thisRook);
		thisRook->setNoPiece();
		return true;
	}
	else
	{
		 cout << "That is an invalid move for Rook";
		return false;
	}
}

bool Board::movePawn(Space* thisPawn, Space* thatSpace) {
	
	using namespace std;
	bool invalid = false;
	int PawnX = thisPawn->getX();
	int PawnY = thisPawn->getY();
	int thatX = thatSpace->getX();
	int thatY = thatSpace->getY();

	
		if (thisPawn->getColor() == WHITE)
		{

			if ((PawnX == thatX && thatY == PawnY + 1) || (PawnX == thatX && thatY == PawnY + 2) && thatSpace->getColor() == NONE)
			{
				thatSpace->setSpace(thisPawn);
				thisPawn->setNoPiece();
				return true;
			}
			else
				if ((PawnX + 1 == thatX || PawnX - 1 == thatX) && PawnY + 1 == thatY && thatSpace->getColor() == BLACK)
				{
					thatSpace->setSpace(thisPawn);
					thisPawn->setNoPiece();
					return true;
				}
				else
					return false;
		}
		else
			if (thisPawn->getColor() == BLACK)
			{
				if ((PawnX == thatX && thatY == PawnY - 1) || (PawnX == thatX && thatY == PawnY - 2) && thatSpace->getColor() == NONE)
				{
					thatSpace->setSpace(thisPawn);
					thisPawn->setNoPiece();
					return true;
				}
				else
					if ((PawnX + 1 == thatX || PawnX - 1 == thatX) && PawnY - 1 == thatY && thatSpace->getColor() == WHITE)
					{
						thatSpace->setSpace(thisPawn);
						thisPawn->setNoPiece();
						return true;
					}
					else
						return false;
			}
			else
				return false;
	
}
bool Board::makeMove(int x1, int y1, int x2, int y2) {
	
	
	if (x1 < 0 || x1>7 || y1 < 0 || y1>7 || x2 < 0 || x2>7 || y2 < 0 || y2>8)
	{
		cout << "Output is out of game board" <<  endl;
		return false;
	}
	Space* src = getSquare(x1, y1);
	Space* dest = getSquare(x2, y2);

	if (src->getColor() == dest->getColor() && dest->getColor() != NONE)
	{
		cout << "Invalid move: You already have a Piece there" <<  endl;
		return false;
	}

	switch (src->getPiece())
	{
	case King: return moveKing(src, dest);
		break;
	case Queen: return moveQueen(src, dest);
		break;
	case Bishop: return moveBishop(src, dest);
		break;
	case Knight: return moveKnight(src, dest);
		break;
	case Rook: return moveRook(src, dest);
		break;
	case Pawn: return movePawn(src, dest);
		break;
	case NoPiece:  cout << "You do not have a piece there" <<  endl;  return false;
		break;
	default:  cerr << "Error" <<  endl;
		break;
	}
	return false;
}
