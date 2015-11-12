#include <iostream>
#include <vector>
#include <map>
#include <cmath>
#include <climits>
#include "game_board.hpp"
#include "game_piece.hpp"
#include "game_algorithms.hpp"
#include <stdlib.h>

int main() {

    clearScreen();
	cout<< "\n\nTo play the game, enter your move as source letter source number destination letter destination number."<<endl;
	cout<< "For example, 'b 1 b 2' will move your piece from b1 to b2.\n\n\n"<<endl;

	Board *b = new Board();
	Board *test;
	Board *b_ab= new Board();
	b->initialize();
	b_ab->initialize();
	b->print();

	char src_x = 0, src_y = 0, dest_x = 0, dest_y = 0;

	while (true) {
	
		int flag=0;
	
			while(flag==0)
			{
				cout << "\tEnter your move: ";
				cin >> src_y >> src_x >> dest_y >> dest_x;
				cout << endl;
	
				src_x -= '1';
				dest_x -= '1';

				src_y -= 'a';
				dest_y -= 'a';
		
				test = b->move(src_x, src_y, dest_x, dest_y);
				if(test==NULL)
				{
					cout << "\tInvalid move. Try again." << endl << endl;
				}
				else
				{
					flag=1;
					clearScreen();
				}
			}
		
			b = test;
			b_ab=test;
			b->print();
			if(!b->get_player()&&dest_x==7)
			{
				cout<< "\tWhite won!"<<endl;
				break;	
			}

			for (int j = 0; j < BOARD_SIZE; ++j)
			{ 
				if(b->get_piece(0,j)!=NULL&& b->get_piece(0,j)->get_color())
				{
					cout<< "\tBlack won!"<<endl;
					break;
				}
			}
			

			if(b->list_all_moves()==NULL)
			{
				cout<< "\tDraw!"<<endl;
				break;
			}
		
		//  Pruning Frequency
		count_prune=0;
		count_ab=0;
		count_wab=0;
		b = ABMinMax(b,6);
		//b_ab=MinMax(b,6);
		
		cout<< "\tCount Prune: " << count_prune << endl;
		cout<< "\tCount AB: " << count_ab << endl;
		cout<< "\tCount Without AB: " << count_wab << "\n\n";

		if(b!=NULL)
		{
			b->print();
			if(!b->get_player()&&dest_x==7)
			{
				cout<< "\tWhite won!"<<endl;
				return 0;	
			}
			for (int j = 0; j < BOARD_SIZE; ++j)
			{ 
			    if(b->get_piece(0,j)!=NULL&& b->get_piece(0,j)->get_color())
				{
					cout<< "\tBlack won!"<<endl;
					return 0;
				}
		    }
			if(b->list_all_moves()==NULL)
			{
				cout<< "\tDraw!"<<endl;
				return 0;
			}
			
		}
		else{
			cout<< "null exiting"<<endl;
			break;
		}
	}

	return 0;
}
