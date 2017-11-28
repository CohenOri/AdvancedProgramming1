/*
 * AiPlayer.cpp
 *
 *  Created on: 23 בנוב׳ 2017
 *      Author: yanap
 */

#include "AiPlayer.h"

AiPlayer::AiPlayer(EnumDeclration::CellStatus player) {
  this->player = player;
  if (player == EnumDeclration::X) {
    this->symbol = 'X';
  } else {
    this->symbol = 'O';
  }
}

AiPlayer::~AiPlayer() {}

Slot AiPlayer::Play() {
  /**
   * Choose slot based on minMax algorithm,
   * AI is looking for slot that if AI chooses him
   * Other Player (enemy) has minimum (lowest) "max possible rank to gain in turn" in his next play
   */
  Slot minSlot = Slot(-1,-1,EnumDeclration::E); // default value, soon it will be deleted
  int min = INT_MAX; // default val
  EnumDeclration::CellStatus otherPlayer = EnumDeclration::OtherPlayer(this->player);
  vector<SlotWithRank> slotsWithMaxM;
  /**
   * find the possible slots for AI, and check for each one: "what is the max possible rank to gain in turn"
   * for Other Player (enemy) - also known as 'm'.
   * create copies of logic & board to work at without hurting original board and logic
   */
  Board* bCopy = this->board_->CopyBoard();
  LogicInterface* lCopy = this->logic_->CopyLogic(bCopy);
  vector<Slot> possibleSlotsForAi = lCopy->SlotsToPlace(this->player);
  for(int i=0; i<possibleSlotsForAi.size(); i++){
    Slot aiSlot = possibleSlotsForAi[i];
    Board* bToPlayAiOn = bCopy->CopyBoard();
    LogicInterface* lToPlayAiOn = lCopy->CopyLogic(bToPlayAiOn);
    // contain the max possible m given this slot
    int maxM = INT_MIN; // default val
    Slot maxMSlot = Slot(-2,-2,EnumDeclration::E);
    // play AI
    bToPlayAiOn->SetCellStatus(aiSlot.GetRow(), aiSlot.GetCol(), this->player);
    lToPlayAiOn->FlipSlots(aiSlot.GetRow(), aiSlot.GetCol(), this->player);
    // return the slots other player has to choose now
    vector<Slot> possibleSlotsForOtherPlayer = lToPlayAiOn->SlotsToPlace(otherPlayer);
    for(int j=0; j<possibleSlotsForOtherPlayer.size(); j++){
      Slot otherSlot = possibleSlotsForOtherPlayer[j];
      Board* bToPlayOtherOn = bToPlayAiOn->CopyBoard();
      LogicInterface* lToPlayOtherOn = lToPlayAiOn->CopyLogic(bToPlayOtherOn);
      int m;
      // play other player
      bToPlayOtherOn->SetCellStatus(otherSlot.GetRow(), otherSlot.GetCol(), otherPlayer);
      lToPlayOtherOn->FlipSlots(otherSlot.GetRow(), otherSlot.GetCol(), otherPlayer);
      // find max m
      FindMaxM(aiSlot, bToPlayOtherOn, m, maxM, maxMSlot);
      delete bToPlayOtherOn;
      delete lToPlayOtherOn;
    }
    // if there is no slots for other player, calculate m accordingly
    if(possibleSlotsForOtherPlayer.size() == 0){
      int m;
      // find max m
      FindMaxM(aiSlot, bToPlayAiOn, m, maxM, maxMSlot);
    }
    // saves the slotWithMaxM, to later choose the min of all this slots
    slotsWithMaxM.push_back(SlotWithRank(maxMSlot, maxM));
    delete bToPlayAiOn;
    delete lToPlayAiOn;
  }
  /**
   * find FindMinSlotRank from the array of max possible ranks for enemy player
   * = find the min of the Max according to minMax algorithm
   */
  minSlot = FindMinSlotRank(min, slotsWithMaxM);
  slotsWithMaxM.clear();
  delete bCopy;
  delete lCopy;
  return minSlot;
}

Slot AiPlayer::FindMinSlotRank(int min, vector<SlotWithRank> &slotsWithMaxM) {
  Slot minSlot = Slot(-1,-1,EnumDeclration::E); // default value, soon it will be deleted
  for(int i=0; i<slotsWithMaxM.size(); i++){
    if(slotsWithMaxM[i].GetRank() < min){
      min = slotsWithMaxM[i].GetRank();
      minSlot = slotsWithMaxM[i].GetSlot();
    }
  }
  return minSlot;
}

void AiPlayer::FindMaxM(const Slot &aiSlot, const Board *bToCalculateWith, int m, int &maxM, Slot &maxMSlot) const {
  if(player == EnumDeclration::X){
        m = bToCalculateWith->GetOSlots().size() - bToCalculateWith->GetXSlots().size();
      } else {
        m = bToCalculateWith->GetXSlots().size() - bToCalculateWith->GetOSlots().size();
      }
  if (m > maxM) {
        maxM = m;
        maxMSlot = aiSlot;
      }
}

void AiPlayer::makeAMove(Board *b, LogicInterface *logic) {
  this->board_ = b;
  this->logic_ = logic;
  // get the chosen slot from the player (AI), confirm its legal slot and add it to the board_.
  // get the chosen slot from the player, confirm its legal slot and add it to the board_.
  Slot chosen_slot = Play();
  if (chosen_slot.ExistInVector(logic_->SlotsToPlace(this->player))) {
    b->SetCellStatus(chosen_slot.GetRow(), chosen_slot.GetCol(), this->player);
    logic_->FlipSlots(chosen_slot.GetRow(), chosen_slot.GetCol(), this->player);
    // print the slot AI chose
    cout << getSymbol() << " played: ";
    chosen_slot.Print();
    cout << endl;
  } else {
    cout << "ILLEGAL PLACE FOR TAG "<< getSymbol() << " try again" << endl;
    makeAMove(b, logic_);
  }
}

char AiPlayer::getSymbol() {
  return this->symbol;
}
