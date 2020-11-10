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
#include "Descision.h"
#include "Tag.h"
#include "SpeechOptionsBranch.h"
#include "Dom/JsonObject.h"
#include "DialogTree.h"
#include "Engine/World.h"
#include "Kismet/GameplayStatics.h"

UDialogTreeBuilder::UDialogTreeBuilder(){}

UDialogTree* UDialogTreeBuilder::build(const FString& dialogJsonFile){
  auto builder = NewObject<UDialogTreeBuilder>();
  builder->sceneName = dialogJsonFile;
  builder->loadTree();
  return builder->tree;
}

void UDialogTreeBuilder::loadTree() {
  tree = NewObject<UDialogTree>(this, TEXT("tree"));
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
	  if (className == FName(TEXT("Speaker"))) {
	    auto speaker = parseAsSpeaker(joSpeaker->AsObject());
	    tree->speakers.Add(speaker->name, speaker);
	  } 
	}

	//load initial Speech
	auto joInitialSpeech = JsonObject->GetObjectField(TEXT("initial"));
	auto initialSpeech = parseAsSpeech(joInitialSpeech, tree->initialHook);
	tree->initial = initialSpeech;
	nodeRepo.Add(initialSpeech->Id, initialSpeech);

	auto joThreads  = JsonObject->GetArrayField(TEXT("threads"));
        for (auto& joThread: joThreads){
          auto className = FName(*(joThread->AsObject()->GetStringField(TEXT("class"))));
          if (className == FName(TEXT("Speech"))){
            auto speech = parseAsSpeech(joThread->AsObject(), tree->initial);
	    nodeRepo.Add(speech->Id, speech);
          }
          if (className == FName(TEXT("SpeechOption"))){
            auto speechOption = parseAsSpeechBranch(joThread->AsObject());
            nodeRepo.Add(speechOption->Id, speechOption);
          }
        }
      }
    } else {
    if (GEngine) {
      UE_LOG(LogTemp, Warning, TEXT("No Dialog json file found"));
    }
  }
}

FString  UDialogTreeBuilder::jsonFullPath(const FString& Path) const
{
  // Games/Content/****.json
#if WITH_EDITOR
  FString FullPath = FPaths::ProjectContentDir() + TEXT("Dialogs/");
#else 
  FString FullPath = FPaths::ProjectContentDir() + TEXT("Dialogs/");
#endif// WITH_EDITOR
  FullPath += Path;
  FString JsonStr;
  UE_LOG(LogTemp, Warning, TEXT("Dialog full path:%s"), *(FullPath));
  FFileHelper::LoadFileToString(JsonStr, *FullPath);
  return JsonStr;
}

USpeaker* UDialogTreeBuilder::parseAsSpeaker(TSharedPtr<FJsonObject> json)
{
  auto speaker = NewObject<USpeaker>();
  speaker->name = FName(*(json->GetStringField("name")));
  UE_LOG(LogTemp, Warning, TEXT("Speaker:%s"), *(speaker->name.ToString()));
  return speaker;
}

USpeech* UDialogTreeBuilder::parseAsSpeech(TSharedPtr<FJsonObject> json, UDialogNode* parentNode)
{
  auto speech = NewObject<USpeech>();
  speech->Id = FName(*(json->GetStringField(TEXT("id"))));
  speech->Parent = parentNode;
  //this->currentSpeech = speech;
  auto parentId = FName(*(json->GetStringField(TEXT("parent"))));
  speech->Parent = nodeRepo.FindRef(parentId);
  UE_LOG(LogTemp, Warning, TEXT("Speech:%s"), *(speech->Id.ToString()));
  auto phrases = json->GetArrayField(TEXT("phrases"));
  for (auto& joPhrase : phrases) {
    auto phrase = parseAsPhrase(joPhrase->AsObject());
    speech->AddPhrase(phrase);
  }
  return speech;
}

UPhrase* UDialogTreeBuilder::parseAsPhrase(TSharedPtr<FJsonObject> json)
{
  auto phrase = NewObject<UPhrase>();
  phrase->Id = FName(*(json->GetStringField(TEXT("id"))));
  auto speakerIndex = FName(*(json->GetStringField(TEXT("speaker"))));
  auto parentId = FName(*(json->GetStringField(TEXT("parent"))));
  phrase->speaker = tree->speakers[speakerIndex];
  
  // if (parentId.IsValid()) {
  //  UE_LOG(LogTemp, Error, "No parent Id in a phrase: %s", *(phrase->Id.ToString()));
  //}
  
  phrase->Parent = nodeRepo.FindRef(parentId);
  phrase->source = UPhrase::souceForString(json->GetStringField(TEXT("source")));
  phrase->text = FText::FromString(json->GetStringField(TEXT("text")));
  UE_LOG(LogTemp, Warning, TEXT("Phrase: text:%s"), *(phrase->text.ToString()));
  return phrase;
}

UDescision* UDialogTreeBuilder::parseAsDescision(TSharedPtr<FJsonObject> json)
{
  auto descision = NewObject<UDescision>();
  descision->consequentSpeechId = FName(*(json->GetStringField(TEXT("speechId"))));
  descision->phrase = parseAsPhrase(json->GetObjectField(TEXT("phrase")));
  descision->Id = FName(*(json->GetStringField(TEXT("id"))));
   auto parentId = FName(*(json->GetStringField(TEXT("parent"))));
  descision->Parent = nodeRepo.FindRef(parentId);

  auto joTags = json->GetArrayField(TEXT("tags"));
  auto tags = TSet<UTag*>();
  for (auto &joTag: joTags){
    auto tag = parseAsTag(joTag->AsObject());
    tags.Emplace(tag);
  }
  descision->tags = tags;
  return descision;
}

UTag* UDialogTreeBuilder::parseAsTag(TSharedPtr<FJsonObject> json)
{
  auto tag = NewObject<UTag>();
  auto joImpacts = json->GetObjectField(TEXT("impacts"));
  tag->impacts = joImpacts;
  return tag;
}

USpeechOptionsBranch* UDialogTreeBuilder::parseAsSpeechBranch(TSharedPtr<FJsonObject> json)
{
  auto branch = NewObject<USpeechOptionsBranch>();
  branch->Id = FName(*(json->GetStringField(TEXT("id"))));
  branch->speaker = tree->speakers[FName(*(json->GetStringField(TEXT("speaker"))))];
  auto phrases = TArray<UPhrase*>();
  auto parentId = FName(*(json->GetStringField(TEXT("parent"))));
  branch->Parent = nodeRepo.FindRef(parentId);

  auto joPhrases = json->GetArrayField(TEXT("phrases"));
  for (auto &joPhrase : joPhrases){
    auto phrase = parseAsPhrase(joPhrase->AsObject());
    phrases.Emplace(phrase);
  }
  branch->phrases = phrases;
  return branch;
}


