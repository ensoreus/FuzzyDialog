//
//  DialogTreeBuilder.cpp
//  CenturionInt
//
//  Created by Philipp Maluta on 30.07.2020.
//  Copyright © 2020 Epic Games, Inc. All rights reserved.
//

#include "DialogTreeBuilder.h"
#include <stdio.h>
#include <new>
#include "Speaker.h"
#include "Speech.h"
#include "Phrase.h"
#include "Dom/JsonObject.h"
#include "DialogTree.h"
#include "../CenturionIntGameMode.h"
#include "Engine/World.h"
#include "Kismet/GameplayStatics.h"

UDialogTreeBuilder::UDialogTreeBuilder(){}

UDialogTree* UDialogTreeBuilder::build(){
  auto world = GetWorld();
  auto myGameMode = Cast<ACenturionIntGameMode>(UGameplayStatics::GetGameMode(world));
  auto dialogTree =  NewObject<UDialogTree>(myGameMode->DialogTree);
  loadTree(dialogTree);
  return dialogTree;
}

void UDialogTreeBuilder::loadTree(UDialogTree* tree){

  TSharedRef<TJsonReader<TCHAR>> JsonReader = TJsonReaderFactory<TCHAR>::Create(jsonFullPath(sceneName));
  TSharedPtr<FJsonObject> JsonObject = MakeShareable(new FJsonObject);
  //  TArray<FAwesomeStruct> AwesomeStruct;
  
  if (FJsonSerializer::Deserialize(JsonReader, JsonObject) && JsonObject.IsValid())
    {
      
      if (JsonObject->GetStringField(TEXT("class")).Equals(TEXT("DialogTree"))){
	UE_LOG(LogTemp, Warning, TEXT("DialogTree found"));
	tree->sceneName = JsonObject->GetStringField(TEXT("name"));
	auto speakers = JsonObject->GetArrayField(TEXT("speakers"));
	
      }
      //GenerateStructsFromJson(AwesomeStructs, JsonObject);
    }
  else {
    if (GEngine) {
      UE_LOG(LogTemp, Warning, TEXT("No object found"));
	
    }
  }
}

UDialogNode* UDialogTreeBuilder::generateStructsFromJson( const FJsonObject& jsonObject ) const
{
  auto tree = NewObject<USpeech>();
//    tree->name = JsonObject->GetStringField(TEXT("name"));
//    TArray<TSharedPtr<FJsonValue>> objArray = JsonObject->GetArrayField(TEXT("speakers"));
//
//    for (int32 i = 0; i < objArray.Num(); i++)
//    {
//        TSharedPtr<FJsonValue> value = objArray[i];
//        TSharedPtr<FJsonObject> json = value->AsObject();
//
//        FVector  AwesomeVector  = ParseAsVector(json, FString("AwesomeVector"));
//        bool     AwesomeBoolean = json->GetBoolField(TEXT("AwesomeBoolean"));
//        float    AwesomeFloat   = json->GetNumberField(TEXT("AwesomeFloat"));
//        int32    AwesomeInteger = json->GetNumberField(TEXT("AwesomeInteger"));
//        FRotator AwesomeRotator = ParseAsRotator(json, FString("AwesomeRotator"));
//
//        FAwesomeStruct AwesomeStruct = FAwesomeStruct::BuildAwesomeStruct(
//            AwesomeVector,AwesomeBoolean,AwesomeFloat,AwesomeInteger,AwesomeRotator
//        );
//
//        tree.Push(AwesomeStruct);
//    }
    return tree;
}

FString  UDialogTreeBuilder::jsonFullPath(const FString& Path) const
{
    // Games/Content/****.json
    FString FullPath = FPaths::EngineContentDir();
    FullPath += Path;
    FString JsonStr;
    FFileHelper::LoadFileToString(JsonStr, *FullPath);

    return JsonStr;
}

USpeaker* UDialogTreeBuilder::parseAsSpeaker(const FJsonObject& json, FString KeyName, TSubclassOf<class UDialogNode> parent) const
{
  auto speaker = NewObject<USpeaker>(parent);
  speaker->name = json.GetStringField("name");
  return speaker;
}

USpeech* UDialogTreeBuilder::parseAsSpeech(const FJsonObject& json, FString KeyName, TSubclassOf<class UDialogNode> parent) const{
  auto speech = NewObject<USpeech>(parent);
  return speech;
}

UPhrase* UDialogTreeBuilder::parseAsPhrase(const FJsonObject& json, FString KeyName, TSubclassOf<class UDialogNode> parent) const{
  auto phrase = NewObject<UPhrase>(parent);
  return phrase;
}
