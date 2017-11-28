/*
 * tt.cpp
 *
 *  Created on: 26 בנוב׳ 2017
 *      Author: yanap
 */

#include <iostream>
#include "gtest/gtest.h"
#include "test_player_Ai.h"
#include "Slot.h"
#include "test_classic_logic.h"
#include "EnumDeclration.h"

//check first time Ai choice
TEST_F(test_player_Ai, firstAiInput) {
	EXPECT_EQ(choosen, Slot(4,6));
}
//check AI choice after player 1 played.
TEST_F(test_player_Ai, SecondAiInput) {
	EXPECT_NE(choosen, Slot(2,3));
	checkSlots();
}
//check of flipping cells works by compere boards.
TEST_F(test_classic_logic, flippingTest) {
	comperBord();
}

TEST(EnumDeclration, checkWhoIsEnemy) {
	EXPECT_EQ(EnumDeclration::OtherPlayer(EnumDeclration::O), EnumDeclration::X);
	EXPECT_EQ(EnumDeclration::OtherPlayer(EnumDeclration::X), EnumDeclration::O);
	EXPECT_NE(EnumDeclration::OtherPlayer(EnumDeclration::O), EnumDeclration::O);
	EXPECT_NE(EnumDeclration::OtherPlayer(EnumDeclration::X), EnumDeclration::X);
	EXPECT_NE(EnumDeclration::OtherPlayer(EnumDeclration::X), EnumDeclration::E);
	EXPECT_NE(EnumDeclration::OtherPlayer(EnumDeclration::O), EnumDeclration::E);
	EXPECT_EQ(EnumDeclration::OtherPlayer(EnumDeclration::E), EnumDeclration::E);
}
