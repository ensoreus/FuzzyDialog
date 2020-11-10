//
//  DialogTreeBuilder.h
//  CenturionInt
//
//  Created by Philipp Maluta on 30.07.2020.
//  Copyright © 2020 Epic Games, Inc. All rights reserved.
//
#pragma once

#include "CoreMinimal.h"
#include "Dom/JsonObject.h"
#include "Templates/SharedPointer.h"
#include "DialogTreeBuilder.generated.h"

class UDialogTree;
class USpeaker;
class USpeech;
class UPhrase;
class UDialogNode;
class FJsonObject;
class UDescision;
class UTag;
class USpeechOptionsBranch;

UCLASS()
class EVANGELIDEMO_API UDialogTreeBuilder: public UObject {
  GENERATED_BODY()
    
  public:
  UDialogTreeBuilder();
    
  UPROPERTY(EditAnywhere, Category="Dialog")
  FString sceneName;
    
  static UDialogTree* build(const FString& jsonDialog);
  
private:
  UPROPERTY(EditAnywhere)
  UDialogNode* currentNode;

  UPROPERTY(EditAnywhere, Category="Dialog")
  UDialogTree* tree;


  UPROPERTY(EditAnywhere)
  TMap<FName, UDialogNode*> nodeRepo;
    
  void loadTree(); 
  
   FString jsonFullPath(const FString& Path) const;
  
  USpeech* parseAsSpeech(TSharedPtr<FJsonObject> json, UDialogNode* parentNode);
  USpeaker* parseAsSpeaker(TSharedPtr<FJsonObject> json);
  UPhrase* parseAsPhrase(TSharedPtr<FJsonObject> json);
  UDescision* parseAsDescision(TSharedPtr<FJsonObject> json);
  UTag* parseAsTag(TSharedPtr<FJsonObject> json);
  USpeechOptionsBranch* parseAsSpeechBranch(TSharedPtr<FJsonObject> json);
};

