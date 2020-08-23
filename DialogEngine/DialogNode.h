// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DialogNode.generated.h"

/**
 * 
 */

UCLASS()
class UDialogNode: public UObject
{
    GENERATED_BODY()
public:
  UDialogNode();
  UPROPERTY(EditAnywhere, Category="Dialog")
  UDialogNode* Parent;

  UPROPERTY(EditAnywhere, Category="Dialog")
  TMap<FName, UDialogNode*> Consequence;
  
  UPROPERTY(EditAnywhere, Category="Dialog" )
  FName Id;  
};
