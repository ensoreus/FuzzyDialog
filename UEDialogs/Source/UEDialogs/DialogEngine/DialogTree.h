
// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DialogTree.generated.h"

class UDialogNode;
class USpeaker;
class USpeech;
class FJsonObject;

/**
 * 
 */
UCLASS()
class UDialogTree : public UObject
{
  GENERATED_BODY()
  
public:
  UDialogTree();

  UPROPERTY(EditAnywhere, Category = "Dialog")
  class UDialogNode* currentNode;
  UPROPERTY(EditAnywhere, Category = "Dialog")
  FString sceneName;
  UPROPERTY(EditAnywhere, Category = "Dialog")
  TArray<USpeaker*> speakers;
  UPROPERTY(EditAnywhere, Category = "Dialog")
  class USpeech* initial;
  UPROPERTY(EditAnywhere, Category = "Dialog")
  class UDialogNode* initialHook;
  //void loadTree();
  void buildNextSubtree();
};



 
