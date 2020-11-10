

#pragma once

#include "CoreMinimal.h"
#include "DialogNode.h"
#include "SpeechOptionsBranch.generated.h"
class USpeaker;
class UPhrase;
class UDescision;

UCLASS()
class EVANGELIDEMO_API USpeechOptionsBranch: public UDialogNode
{
  GENERATED_BODY()
public:
	USpeechOptionsBranch();
    class USpeaker* speaker;
    class TArray<UPhrase*> phrases;
    class TArray<UDescision*> descisions;
};
