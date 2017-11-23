/*
 * AiPlayer.cpp
 *
 *  Created on: 23 בנוב׳ 2017
 *      Author: yanap
 */

#include "AiPlayer.h"


AiPlayer::AiPlayer(EnumDeclration::CellStatus player) {
	  this->player = player;
	  if(player == EnumDeclration::X) {
		  this->symbol = 'X';
	  } else {
	  this->symbol = 'O';
	  }
}

AiPlayer::~AiPlayer() { }

Slot AiPlayer::Play() {
}

char AiPlayer::getSymbol() {
	return this->symbol;
}

void AiPlayer::makeAMove(Board* b, LogicInterface* logic_) {
}
