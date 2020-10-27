// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "GASInputs.h"
#include "Abilities/GameplayAbility.h"
#include "GASGameplayAbility.generated.h"

/**
 * 
 */
UCLASS()
class GAS_API UGASGameplayAbility : public UGameplayAbility
{
	GENERATED_BODY()
	
public:
	UGASGameplayAbility();

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Ability")
	EGASAbilityInputID AbilityInputID = EGASAbilityInputID::None;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Ability")
	bool bActivateAbilityOnGranted;

	virtual void OnAvatarSet(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec) override;
};
