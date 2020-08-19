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

UCLASS()
class UDialogTreeBuilder: public UObject {
  GENERATED_BODY()
    
  public:
  UDialogTreeBuilder();
    
  UPROPERTY(EditAnywhere, Category="Dialog")
  FString sceneName;
    
  UDialogTree* build();

protected:
  void loadTree(UDialogTree* tree);
  
  UDialogNode* generateStructsFromJson( const FJsonObject& jsonObject) const;
  FString jsonFullPath(const FString& Path) const;
  
  USpeech* parseAsSpeech(const FJsonObject& json, FString KeyName, TSubclassOf<class UDialogNode> parent) const;
  USpeaker* parseAsSpeaker(const FJsonObject& json, FString KeyName, TSubclassOf<class UDialogNode> parent) const;
  UPhrase* parseAsPhrase(const FJsonObject& json, FString KeyName, TSubclassOf<class UDialogNode> parent) const;
private:
  USpeech* currentSpeech;
  UDialogNode* currentNode;
};

