// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DialogNode.generated.h"

/**
 * 
 */

UCLASS()
class EVANGELIDEMO_API UDialogNode: public UObject
{
    GENERATED_BODY()
public:
  UDialogNode();
    UDialogNode(const UDialogNode* parent);

    UFUNCTION()
      UDialogNode* GetNext() const;

    UFUNCTION()
      UDialogNode* GetNextByName(FName name) const;
    
  UPROPERTY(EditAnywhere, Category="Dialog")
  UDialogNode* Parent;

  UPROPERTY(EditAnywhere, Category="Dialog")
  TMap<FName, UDialogNode*> NamedConsequence;
  
  UPROPERTY(EditAnywhere, Category="Dialog" )
  FName Id;

  UPROPERTY(EditAnywhere, Category="Dialog" )
    UDialogNode* Consequence;  
};
