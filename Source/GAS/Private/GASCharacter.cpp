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

void AGASCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	BindGASInput();
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
		InitializeAttributes();
		AddInitialEffects();
		AddInitialAbilities();
	}
}

void AGASCharacter::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();

	if (IsValid(AbilitySystemComponent))
	{
		AbilitySystemComponent->InitAbilityActorInfo(this, this);
		InitializeAttributes();

		BindGASInput();
	}
}

UAbilitySystemComponent* AGASCharacter::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

void AGASCharacter::AcquireAbility(TSubclassOf<UGASGameplayAbility> AbilityToAcquire, int32 InputId)
{
	if (HasAuthority() && IsValid(AbilitySystemComponent) && IsValid(AbilityToAcquire))
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
	for (TSubclassOf<UGASGameplayAbility>& Ability : InitialAbilities)
	{
		AcquireAbility(Ability, static_cast<int32>(Ability.GetDefaultObject()->AbilityInputID));
	}
}

void AGASCharacter::RemoveInitialAbilities()
{
	if (HasAuthority() && IsValid(AbilitySystemComponent))
	{
		TArray<FGameplayAbilitySpecHandle> AbilitiesToRemove;
		for (const FGameplayAbilitySpec& Spec : AbilitySystemComponent->GetActivatableAbilities())
		{
			if ((Spec.SourceObject == this) && InitialAbilities.Contains(Spec.Ability->GetClass()))
			{
				AbilitiesToRemove.Add(Spec.Handle);
			}
		}

		for (int32 i = 0; i < AbilitiesToRemove.Num(); i++)
		{
			AbilitySystemComponent->ClearAbility(AbilitiesToRemove[i]);
		}
	}
}

void AGASCharacter::InitializeAttributes()
{
	AcquireEffect(InitialAttributes);
}

void AGASCharacter::AddInitialEffects()
{
	for (TSubclassOf<UGameplayEffect>& GameplayEffect : InitialEffect)
	{
		AcquireEffect(GameplayEffect);
	}
}

void AGASCharacter::RemoveEffects()
{
	if (HasAuthority() && IsValid(AbilitySystemComponent))
	{
		FGameplayEffectQuery Query;
		Query.EffectSource = this;
		AbilitySystemComponent->RemoveActiveEffects(Query);
	}
}

void AGASCharacter::BindGASInput()
{
	if (!bGASInputBound && IsValid(AbilitySystemComponent) && IsValid(InputComponent))
	{
		const FGameplayAbilityInputBinds Binds(FString("Confirm"), FString("Cancel"), FString("EGASAbilityInputID"),
			static_cast<int32>(EGASAbilityInputID::Confirm), static_cast<int32>(EGASAbilityInputID::Cancel));
		AbilitySystemComponent->BindAbilityActivationToInputComponent(InputComponent, Binds);

		bGASInputBound = true;
	}
}

float AGASCharacter::GetHealth() const
{
	if (IsValid(AttributeSet))
	{
		return AttributeSet->GetHealth();
	}
	return 0.0f;
}

float AGASCharacter::GetMaxHealth() const
{
	if (IsValid(AttributeSet))
	{
		return AttributeSet->GetMaxHealth();
	}
	return 0.0f;
}

float AGASCharacter::GetHealthRegen() const
{
	if (IsValid(AttributeSet))
	{
		return AttributeSet->GetHealthRegen();
	}
	return 0.0f;
}

float AGASCharacter::GetStamina() const
{
	if (IsValid(AttributeSet))
	{
		return AttributeSet->GetStamina();
	}
	return 0.0f;
}

float AGASCharacter::GetMaxStamina() const
{
	if (IsValid(AttributeSet))
	{
		return AttributeSet->GetMaxStamina();
	}
	return 0.0f;
}

float AGASCharacter::GetStaminaRegen() const
{
	if (IsValid(AttributeSet))
	{
		return AttributeSet->GetStaminaRegen();
	}
	return 0.0f;
}

float AGASCharacter::GetStaminaCostMultiplier() const
{
	if (IsValid(AttributeSet))
	{
		return AttributeSet->GetStaminaCostMultiplier();
	}
	return 0.0f;
}

float AGASCharacter::GetAttackPower() const
{
	if (IsValid(AttributeSet))
	{
		return AttributeSet->GetAttackPower();
	}
	return 0.0f;
}

float AGASCharacter::GetAttackSpeed() const
{
	if (IsValid(AttributeSet))
	{
		return AttributeSet->GetAttackSpeed();
	}
	return 0.0f;
}

float AGASCharacter::GetDefence() const
{
	if (IsValid(AttributeSet))
	{
		return AttributeSet->GetDefence();
	}
	return 0.0f;
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
