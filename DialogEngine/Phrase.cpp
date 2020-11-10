// Fill out your copyright notice in the Description page of Project Settings.


#include "Phrase.h"

USource UPhrase::souceForString(const FString& jsSource){
  if (jsSource == "verbal"){
    return verbal;
  } else if (jsSource == "internal"){
    return internal;
  }
  return verbal;
}

UPhrase::UPhrase()
{
}

