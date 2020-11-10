// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "LinguisticVariable.generated.h"

/**
 * 
 */
UCLASS()
class ULinguisticVariable: public UObject
{
  GENERATED_BODY()
public:
  ULinguisticVariable();
  ULinguisticVariable(FString& name):Name(name){};
  UPROPERTY(EditAnyWhere, Category="Dialog")
  FString Name;
  UPROPERTY(EditAnyWhere, Category="Dialog")
  TMap<FString, float> Terms;
  void SetTerm(FString& term, float mfValue);
};


