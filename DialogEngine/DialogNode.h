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
  UPROPERTY(EditAnyWhere, Category="Dialog")
  UDialogNode* Parent;

  UPROPERTY(EditAnyWhere, Category="Dialog")
  TMap<FString, UDialogNode*> Consequence;
  
  UPROPERTY(EditAnyWhere, Category="Dialog")
  FString Id;  
};
