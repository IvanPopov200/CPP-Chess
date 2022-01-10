#include <iostream>
#include <string>
#include "HeaderFile.h"
using namespace std;
int main()
{
	Board b;
	string newgameConfirmation;
	bool newgame = true;
	cout << "Chess by Ivan Popov" << endl;
	cout << "CHB99132" << endl;
	cout << "Press any key to start" << endl;
	cin >> newgameConfirmation;

	while (newgame) {
		b.setBoard();
		while (b.playGame());
		cout << "Press Y to start a new game, press any other key to exit ";
		cin >> newgameConfirmation;
		if (newgameConfirmation != "y")
			newgame = false;
	}


	return 0;
}