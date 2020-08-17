// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DialogNode.h"
#include "Phrase.generated.h"

class USpeaker;
/**
 * 
 */

UENUM()
enum USource{
	     verbal UMETA(DisplayName = "Verbal"),
	     internal UMETA(DisplayName = "Internal")
};

UCLASS()
class UPhrase : public UDialogNode
{
  GENERATED_BODY()
  
public:
  
  UPhrase();
  UPROPERTY(EditAnywhere, Category = "Dialog")
  USpeaker *speaker;

  UPROPERTY(EditAnywhere, Category = "Dialog")
  FString text;

  UPROPERTY(EditAnywhere, Category = "Dialog")
  TEnumAsByte<USource> source;

  UPROPERTY(EditAnywhere, Category = "Dialog")
  TSubclassOf<class UDialogNode>  nextNode;
  
};
