// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DialogTreeBrowser.generated.h"

/**
 * 
 */

class USpeech;
class UDialogNode;
class UDialogTree;
class UPhrase;
class UDescision;

DECLARE_DELEGATE(FOnNextDelegateSignature)
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FSpeechDelegate);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FThoughtDelegate);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FDescisionDelegate);

UCLASS(Blueprintable, BlueprintType)
class EVANGELIDEMO_API UDialogTreeBrowser: public UObject
{
  GENERATED_BODY()
public:
    UDialogTreeBrowser();
  
  DECLARE_EVENT_OneParam(UDialogTreeBrowser, FSpeak, const USpeech*);
    FSpeak OnAddSpeech;

    DECLARE_EVENT_OneParam(UDialogTreeBrowser, FThought, const UPhrase*);
    FThought OnAddThoughts;

    DECLARE_EVENT_OneParam(UDialogTreeBrowser, FDescision, const UDescision*);
    FDescision OnDescisionChallenge;

     
    //FOnNextDelegateSignature OnNextDelegate;

  
    UFUNCTION(BlueprintCallable, Category = "Dialog Browser")
    void Think();

    UFUNCTION(BlueprintCallable, Category = "Dialog Browser")
    void Say();

    UFUNCTION(BlueprintCallable)
    void OpenScene(const FString& sceneName);

    UFUNCTION(BlueprintCallable)
      void Back();
    
    //    UFUNCTION(BlueprintCallable)
    //    void Decide();

    UFUNCTION(BlueprintCallable, Category = "Dialog Browser")
    void ResolveDecision(const FName& decidedId);

    UFUNCTION(BlueprintCallable, Category = "Dialog Browser")
      USpeaker* GetSpeaker(const FName& speakerId) const;

 protected:
    UPROPERTY(BlueprintAssignable, Category = "Dialog Browser")
      FSpeechDelegate SpeechDelegate;
    UPROPERTY(BlueprintAssignable, Category = "Dialog Browser")
      FThoughtDelegate ThoughtDelegate;
    UPROPERTY(BlueprintAssignable, Category = "Dialog Browser")
      FDescisionDelegate DescisionDelegate;
    
 private:
    UPROPERTY()
    UDialogTree* Tree;

    UFUNCTION()
    void StepNext();

};
