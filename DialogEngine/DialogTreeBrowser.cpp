// Fill out your copyright notice in the Description page of Project Settings.


#include "DialogTreeBrowser.h"
#include "DialogTree.h"
#include "DialogNode.h"
#include "DialogTreeBuilder.h"
#include "Speech.h"
#include "Descision.h"

UDialogTreeBrowser::UDialogTreeBrowser()
{
  //this->OnNextDelegate.BindUObject(this, &UDialogTreeBrowser::StepNext);
  
}

void UDialogTreeBrowser::Think(){
  
}


void UDialogTreeBrowser::Say(){
  StepNext();
  auto current = Tree->currentNode;
  auto speech = Cast<USpeech>(current);
  if (speech != nullptr){
    OnAddSpeech.Broadcast(speech);
    SpeechDelegate.Broadcast();
    return;
  }

  auto descision = Cast<UDescision>(current);

  if(descision != nullptr){
    OnDescisionChallenge.Broadcast(descision);
  }
    
}


void UDialogTreeBrowser::OpenScene(const FString& sceneName){
  UE_LOG(LogTemp, Warning, TEXT("OpenScene"));
  // Tree = UDialogTreeBuilder().build(sceneName);
}

void UDialogTreeBrowser::Back(){
  
}

void UDialogTreeBrowser::StepNext(){
  auto current = Tree->currentNode;
  auto nextNode = current->GetNext();
  Tree->currentNode = current;
}

USpeaker* UDialogTreeBrowser::GetSpeaker(const FName& speakerId) const {
  return Tree->speakers[speakerId];
}


void UDialogTreeBrowser::ResolveDecision(const FName& decidedId){
  
}
