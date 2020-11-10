// Fill out your copyright notice in the Description page of Project Settings.


#include "Speech.h"
#include "Descision.h"


USpeech::USpeech()
{
  //phrases = CreateDefaultSubobject<TArray<UPhrase*>>(TEXT("phrases"));
}

void USpeech::AddPhrase( UPhrase* phrase){
  phrases.Emplace(phrase);
}

void USpeech::AddDescision(const TArray<UDescision*>& descisions){
  for(auto& descision : descisions){
    NamedConsequence.Emplace(descision->Id, descision);
  }
}

void USpeech::AddNextSpeech(USpeech* speech){
  this->Consequence = speech;
}
