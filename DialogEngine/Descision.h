#pragma once

#include "CoreMinimal.h"
#include "DialogNode.h"
#include "Descision.generated.h"
class UTag;

UCLASS()
class EVANGELIDEMO_API UDescision : public UDialogNode{
  
    GENERATED_BODY()
 public:
    UDescision();

    UPROPERTY()
    class UPhrase* phrase;
    UPROPERTY()
    FName consequentSpeechId;
    UPROPERTY()
    TSet<UTag*> tags;
};
