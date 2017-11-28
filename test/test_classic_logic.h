/*
 * test_classic_logic.h
 *
 *  Created on: 27 בנוב׳ 2017
 *      Author: yanap
 */

#ifndef TEST_TEST_CLASSIC_LOGIC_H_
#define TEST_TEST_CLASSIC_LOGIC_H_


#include "gtest/gtest.h"
#include "EnumDeclration.h"
#include "AiPlayer.h"
#include "Board.h"
#include "RegularLogic.h"
#include "Slot.h"

#include <iostream>

using namespace std;
class test_classic_logic: public testing::Test {
public:
	test_classic_logic():choosen(2,3) {
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
		cout << endl;
	}
	virtual void TearDown() {
		cout << "Setting Down" << endl;
		delete p1;
		delete rl;
	}
	void comperBord() {
		Board compered =  Board();
		rl->FlipSlots(3, 4,EnumDeclration::X);
		b->SetCellStatus(3,4,EnumDeclration::X);
		compered.SetCellStatus(4,4,EnumDeclration::X);
		compered.SetCellStatus(5,5,EnumDeclration::O);
		compered.SetCellStatus(4,5,EnumDeclration::X);
		compered.SetCellStatus(5,4,EnumDeclration::X);
		compered.SetCellStatus(3,4,EnumDeclration::X);
		EXPECT_EQ(*b, compered);
	}


protected:
	AiPlayer *p1;
	Board * b;
	Slot choosen;
	RegularLogic *rl;

};





#endif /* TEST_TEST_CLASSIC_LOGIC_H_ */
