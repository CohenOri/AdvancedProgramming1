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
  // the slot that if AI chooses him Other Player has minimum (lowest) "max rank to gain in turn" in his next play
  Slot min_slot = Slot(-1,-1,EnumDeclration::E); // default value, soon it will be deleted
  int min = INT_MAX; // default val
  EnumDeclration::CellStatus other_player = EnumDeclration::OtherPlayer(this->player);
  vector<SlotWithRank> slots_with_max_m;

  // find the possible slots for AI
  Board* b_copy = this->board_->CopyBoard();
  LogicInterface* l_copy = this->logic_->CopyLogic(b_copy);
  vector<Slot> possible_slots_for_AI = l_copy->SlotsToPlace(this->player);
  // iterate on each of them, find the ma
  // for each slot in possible_slots_for_AI
  for(int i=0; i<possible_slots_for_AI.size(); i++){
    Slot AI_slot = possible_slots_for_AI[i];
    Board* b_to_play_AI_on = b_copy->CopyBoard();
    LogicInterface* l_to_play_AI_on = l_copy->CopyLogic(b_to_play_AI_on);
    // contain the max possible m given this slot
    int max_m = INT_MIN;
    Slot max_m_slot = Slot(-2,-2,EnumDeclration::E);
    // play AI
    b_to_play_AI_on->SetCellStatus(AI_slot.GetRow(), AI_slot.GetCol(), this->player);
    l_to_play_AI_on->FlipSlots(AI_slot.GetRow(), AI_slot.GetCol(), this->player);
    // return the slots other player has to choose now
    vector<Slot> possible_slots_for_other_player = l_to_play_AI_on->SlotsToPlace(other_player);
    for(int j=0; j<possible_slots_for_other_player.size(); j++){
      Slot other_slot = possible_slots_for_other_player[j];
      Board* b_to_play_other_on = b_to_play_AI_on->CopyBoard();
      LogicInterface* l_to_play_other_on = l_to_play_AI_on->CopyLogic(b_to_play_other_on);
      int m;
      // play other player
      b_to_play_other_on->SetCellStatus(other_slot.GetRow(), other_slot.GetCol(), other_player);
      l_to_play_other_on->FlipSlots(other_slot.GetRow(), other_slot.GetCol(), other_player);
      // calculate the max points difference in the given move
      /* if AI is X: calc m = oSlots - xSlots
       * if AI is O: calc m = xSlots - oSlots
       * calculates the other player points - AI points.
      */
      if(this->player == EnumDeclration::X){
        m = b_to_play_other_on->GetOSlots().size() - b_to_play_other_on->GetXSlots().size();
      } else {
        m = b_to_play_other_on->GetXSlots().size() - b_to_play_other_on->GetOSlots().size();
      }
      if (m > max_m) {
        max_m = m;
        max_m_slot = AI_slot;
      }
      // !!!!!
      // dont forget to revert back to regular order (think before if it should or not - i believe it doenst mattewr)
      delete b_to_play_other_on;
      delete l_to_play_other_on;

    }
    // if there is no slots for other player, calculate m accordingly
    if(possible_slots_for_other_player.size() == 0){
      // calculate the max points difference in the given move
      /* if AI is X: calc m = oSlots - xSlots
       * if AI is O: calc m = xSlots - oSlots
       * calculates the other player points - AI points.
      */
      int m;
      if(this->player == EnumDeclration::X){
        // since other player can't play its ok to calculate with b_to_play_AI_on and not b_to_play_other_on
        // they are practicably the same (but I had to use b_to_play_AI_on because of scope reasons)
        m = b_to_play_AI_on->GetOSlots().size() - b_to_play_AI_on->GetXSlots().size();
      } else {
        m = b_to_play_AI_on->GetXSlots().size() - b_to_play_AI_on->GetOSlots().size();
      }
      if (m > max_m) {
        max_m = m;
        max_m_slot = AI_slot;
      }
    }
    // saves the slot_with_max_m, to later choose the min of all this slots
    slots_with_max_m.push_back(SlotWithRank(max_m_slot, max_m));
    delete b_to_play_AI_on;
    delete l_to_play_AI_on;
  }
  // find the slot that AI should choose in order to make other player have the min "max_m" value
  // in shortly - find the min rank of slots_with_max_m and return the slot
  for(int i=0; i<slots_with_max_m.size(); i++){
    if(slots_with_max_m[i].GetRank() < min){
      min = slots_with_max_m[i].GetRank();
      // delete old min
      //if(min_slot != nullptr){
        //delete min_slot;
      //}
      //cout << "GELLLLLL" << endl;
      min_slot = slots_with_max_m[i].GetSlot();
    }
  }
  slots_with_max_m.clear();
  delete b_copy;
  delete l_copy;
  //Slot temp = *min_slot;
  //delete min_slot;
  return min_slot;
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
  //delete &chosen_slot;
}

char AiPlayer::getSymbol() {
  return this->symbol;
}
