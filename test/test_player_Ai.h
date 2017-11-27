/*
 * test_player.cpp
 *
 *  Created on: 25 בנוב׳ 2017
 *      Author: yanap
 */


#include "gtest/gtest.h"
#include "EnumDeclration.h"
#include "AiPlayer.h"
#include "Board.h"
#include "RegularLogic.h"
#include "Slot.h"

#include <iostream>

using namespace std;
class test_player_Ai: public testing::Test {
public:
	test_player_Ai():choosen(2,3) {
	}
	virtual void SetUp() {
		cout << "Setting Up" << endl;
		b = new Board();
		rl = new RegularLogic(b);
		p1 = new AiPlayer(EnumDeclration::O, b, rl);

		b->SetCellStatus(4,4,EnumDeclration::O);
		b->SetCellStatus(5,5,EnumDeclration::O);
		b->SetCellStatus(4,5,EnumDeclration::X);
		b->SetCellStatus(5,4,EnumDeclration::X);
		choosen = p1->Play();
		//cout << "this is computer's choice ";
		//choosen.Print();
		cout << endl;
	}
	virtual void TearDown() {
		cout << "Setting Down" << endl;
		delete p1;
		delete rl;
	}

	void checkSlots() {
		rl->FlipSlots(3, 4,EnumDeclration::X );
		b->SetCellStatus(3,4,EnumDeclration::X);
		choosen = p1->Play();
	//	cout << "this is computer choice second ";
	//	choosen.Print();
	  EXPECT_EQ(choosen, Slot(3,3));
	}


protected:
	AiPlayer *p1;
	Board * b;
	Slot choosen;
	RegularLogic *rl;

};





