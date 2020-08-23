// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DialogNode.h"
#include "Speech.generated.h"

class UPhrase;
class USpeaker;
/**
 * 
 */
UCLASS()
class USpeech: public UDialogNode
{
  GENERATED_BODY()
public:
	USpeech();
  USpeaker* speaker;
  TArray<UPhrase*> phrases;
};
