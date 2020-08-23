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
  void loadTree();
  
  //  UDialogNode* generateStructsFromJson( const FJsonObject& jsonObject) const;
  FString jsonFullPath(const FString& Path) const;
  
  USpeech* parseAsSpeech(TSharedPtr<FJsonObject> json, UDialogNode* parentNode);
  USpeaker* parseAsSpeaker(TSharedPtr<FJsonObject> json);
  UPhrase* parseAsPhrase(TSharedPtr<FJsonObject> json);

private:
  USpeech* currentSpeech;
  UDialogNode* currentNode;
  UDialogTree* tree;
};

