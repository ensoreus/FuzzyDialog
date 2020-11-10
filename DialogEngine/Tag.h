// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Tag.generated.h"
class FJsonObject;
/**
 * 
 */
UCLASS()
class EVANGELIDEMO_API UTag : public UObject
{
	GENERATED_BODY()
public:
	UTag();

	TSharedPtr<FJsonObject> impacts;
};
