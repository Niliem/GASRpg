// Fill out your copyright notice in the Description page of Project Settings.


#include "Abilities/GASAbilitySystemComponent.h"

int32 UGASAbilitySystemComponent::K2_GetTagCount(FGameplayTag TagToCheck) const
{
	return GetTagCount(TagToCheck);
}