// Fill out your copyright notice in the Description page of Project Settings.


#include "DialogNode.h"

UDialogNode::UDialogNode()
{
}

UDialogNode* UDialogNode::GetNext() const{
  return Consequence;
}

UDialogNode* UDialogNode::GetNextByName(FName name) const{
  return NamedConsequence[name];
}

