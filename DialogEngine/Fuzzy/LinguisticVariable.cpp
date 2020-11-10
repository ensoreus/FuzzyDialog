// Fill out your copyright notice in the Description page of Project Settings.


#include "LinguisticVariable.h"

ULinguisticVariable::ULinguisticVariable()
{
}

void ULinguisticVariable::SetTerm(FString& term, float mfValue) {
  Terms[term] = mfValue;
}
