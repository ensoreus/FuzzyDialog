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
class EVANGELIDEMO_API USpeech: public UDialogNode
{
  GENERATED_BODY()
public:

    USpeech();
  
  UPROPERTY()
    USpeaker* speaker;
  
  UFUNCTION()
    void AddPhrase( UPhrase* phrase);

  UFUNCTION()
    void AddDescision(const TArray<UDescision*>& descision);

  UFUNCTION()
    void AddNextSpeech( USpeech* speech);

  
 private:
  
  UPROPERTY()
    TArray<UPhrase*> phrases;
};
