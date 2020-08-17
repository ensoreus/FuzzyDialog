// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Speaker.generated.h"

/**
 * 
 */
UCLASS()
class USpeaker: public UObject
{
  GENERATED_BODY()
  
public:
  USpeaker();

  FString name;
  FString iconName;
};
