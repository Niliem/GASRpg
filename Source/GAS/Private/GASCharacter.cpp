// Fill out your copyright notice in the Description page of Project Settings.


#include "GASCharacter.h"
#include "Abilities/GASAbilitySystemComponent.h"
#include "Abilities/GASGameplayAbility.h"
#include "Abilities/GASAttributeSet.h"
#include "GameFramework/CharacterMovementComponent.h"

AGASCharacter::AGASCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	AbilitySystemComponent = CreateDefaultSubobject<UGASAbilitySystemComponent>("AbilitySystemComponent");
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);

	AttributeSet = CreateDefaultSubobject<UGASAttributeSet>("AttributeSet");
}

void AGASCharacter::BeginPlay()
{
	Super::BeginPlay();
}

void AGASCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	if (IsValid(AbilitySystemComponent))
	{
		AbilitySystemComponent->InitAbilityActorInfo(this, this);
		AddInitialEffect();
		AddInitialAbilities();
	}
}

void AGASCharacter::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();

	if (IsValid(AbilitySystemComponent))
	{
		AbilitySystemComponent->InitAbilityActorInfo(this, this);
		AddInitialEffect();
	}
}

UAbilitySystemComponent* AGASCharacter::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

void AGASCharacter::AcquireAbility(TSubclassOf<UGASGameplayAbility> AbilityToAcquire, int32 InputId)
{
	if (IsValid(AbilitySystemComponent) && IsValid(AbilityToAcquire))
	{
		AbilitySystemComponent->GiveAbility(FGameplayAbilitySpec(AbilityToAcquire, 1, InputId, this));
	}
}

void AGASCharacter::AcquireEffect(TSubclassOf<UGameplayEffect> EffectToAcquire, float Level)
{
	if (IsValid(AbilitySystemComponent) && IsValid(EffectToAcquire))
	{
		FGameplayEffectContextHandle EffectContext = AbilitySystemComponent->MakeEffectContext();
		EffectContext.AddSourceObject(this);

		FGameplayEffectSpecHandle NewHandle = AbilitySystemComponent->MakeOutgoingSpec(EffectToAcquire, Level, EffectContext);
		if (NewHandle.IsValid())
		{
			AbilitySystemComponent->ApplyGameplayEffectSpecToSelf(*NewHandle.Data.Get());
		}
	}
}

void AGASCharacter::AddInitialAbilities()
{
	if (HasAuthority() && IsValid(AbilitySystemComponent))
	{
		for (TSubclassOf<UGASGameplayAbility>& Ability : InitialAbilities)
		{
			AcquireAbility(Ability /* static_cast<int32>(Ability.GetDefaultObject()->AbilityInputID) */);
		}
	}
}

void AGASCharacter::AddInitialEffect()
{
	if (HasAuthority() && IsValid(AbilitySystemComponent))
	{
		for (TSubclassOf<UGameplayEffect>& GameplayEffect : InitialEffect)
		{
			AcquireEffect(GameplayEffect);
		}
	}
}

float AGASCharacter::GetMovementSpeed() const
{
	if (IsValid(AttributeSet))
	{
		return AttributeSet->GetMovementSpeed();
	}
	return 0.0f;
}

float AGASCharacter::GetMovementSpeedBase() const
{
	if (IsValid(AttributeSet))
	{
		return AttributeSet->GetMovementSpeedAttribute().GetGameplayAttributeData(AttributeSet)->GetBaseValue();
	}
	return 0.0f;
}

float AGASCharacter::GetSprintSpeedMultiplier() const
{
	if (IsValid(AttributeSet))
	{
		return AttributeSet->GetSprintSpeedMultiplier();
	}
	return 0.0f;
}
