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
#include "Engine/World.h"
#include "Kismet/GameplayStatics.h"

UDialogTreeBuilder::UDialogTreeBuilder(){}

UDialogTree* UDialogTreeBuilder::build(){
  //auto world = GetWorld();
  //auto myGameMode = Cast<ACenturionIntGameMode>(UGameplayStatics::GetGameMode(world));
  this->tree = CreateDefaultSubobject<UDialogTree>(TEXT("UDialogTree"));// NewObject<UDialogTree>(this);
  loadTree();
  return tree;
}

void UDialogTreeBuilder::loadTree() {

  TSharedRef<TJsonReader<TCHAR>> JsonReader = TJsonReaderFactory<TCHAR>::Create(jsonFullPath(sceneName));
  TSharedPtr<FJsonObject> JsonObject = MakeShareable(new FJsonObject);
 
  if (FJsonSerializer::Deserialize(JsonReader, JsonObject) && JsonObject.IsValid())
    {
      
      if (JsonObject->GetStringField(TEXT("class")).Equals(TEXT("DialogTree"))){
	UE_LOG(LogTemp, Warning, TEXT("DialogTree found"));
	tree->sceneName = JsonObject->GetStringField(TEXT("name"));
	
	//load Speakers
	auto speakers = JsonObject->GetArrayField(TEXT("speakers"));
	  for (auto& joSpeaker : speakers){
	    auto className = FName(*(joSpeaker->AsObject()->GetStringField(TEXT("class"))));
	    if (className == FName(TEXT("speaker"))) {
	      auto speaker = parseAsSpeaker(joSpeaker->AsObject());
	      tree->speakers.Add(speaker);
	    }
	  }

	  
	  //load initial Speech
	  auto joInitialSpeech = JsonObject->GetObjectField(TEXT("initial"));
	  auto initialSpeech = parseAsSpeech(joInitialSpeech, tree->initialHook);
	  tree->initial = initialSpeech;
	  currentSpeech = initialSpeech;
      }
      //GenerateStructsFromJson(AwesomeStructs, JsonObject);
    }
  else {
    if (GEngine) {
      UE_LOG(LogTemp, Warning, TEXT("No object found"));
	
    }
  }
}

/*UDialogNode* UDialogTreeBuilder::generateStructsFromJson( const FJsonObject& jsonObject ) const
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
    }*/

FString  UDialogTreeBuilder::jsonFullPath(const FString& Path) const
{
    // Games/Content/****.json
    FString FullPath = FPaths::EngineContentDir();
    FullPath += Path;
    FString JsonStr;
    FFileHelper::LoadFileToString(JsonStr, *FullPath);

    return JsonStr;
}

USpeaker* UDialogTreeBuilder::parseAsSpeaker(TSharedPtr<FJsonObject> json)
{
  auto speaker = NewObject<USpeaker>(tree);
  speaker->name = json->GetStringField("name");
  return speaker;
}

USpeech* UDialogTreeBuilder::parseAsSpeech(TSharedPtr<FJsonObject> json, UDialogNode* parentNode)
{
  auto speech = NewObject<USpeech>(parentNode);
  speech->Id = FName(*(json->GetStringField(TEXT("id"))));
  int32 speakerIndex = json->GetNumberField(TEXT("speaker")); 
  speech->speaker = tree->speakers[speakerIndex];
  speech->Parent = parentNode;
  this->currentSpeech = speech;
  return speech;
}

UPhrase* UDialogTreeBuilder::parseAsPhrase(TSharedPtr<FJsonObject> json)
{
  auto phrase = NewObject<UPhrase>(currentSpeech);
  //phrase->text= NSLCLOCAL(json->GetStringField(TEXT("text")));
  phrase->Id = FName(*(json->GetStringField(TEXT("id"))));
  phrase->Parent = currentSpeech;
  phrase->source = UPhrase::souceForString(json->GetStringField(TEXT("source")));
  //  phrase->nextNode = //json->GetStringField(TEXT("nextId"));
  return phrase;
}
