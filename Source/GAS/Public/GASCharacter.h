// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"
#include "GASCharacter.generated.h"

class UGASAbilitySystemComponent;
class UGASGameplayAbility;
class UGASAttributeSet;
class UGameplayEffect;

UCLASS()
class GAS_API AGASCharacter : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	AGASCharacter();

	virtual void PossessedBy(AController* NewController) override;
	virtual void OnRep_PlayerState() override;

	// Implement IAbilitySystemInterface
	virtual class UAbilitySystemComponent* GetAbilitySystemComponent() const override;

	UFUNCTION( BlueprintCallable, Category = "AbilitySystem|Abilities" )
	void AcquireAbility(TSubclassOf<UGASGameplayAbility> AbilityToAcquire, int32 InputId = -1);

	UFUNCTION( BlueprintCallable, Category = "AbilitySystem|Abilities" )
	void AcquireEffect(TSubclassOf<UGameplayEffect> EffectToAcquire, float Level = 0.0f);

	// Getters

	UFUNCTION(BlueprintCallable, Category = "AbilitySystem|Attributes")
    float GetHealth() const;

	UFUNCTION(BlueprintCallable, Category = "AbilitySystem|Attributes")
    float GetMaxHealth() const;

	UFUNCTION(BlueprintCallable, Category = "AbilitySystem|Attributes")
    float GetStamina() const;

	UFUNCTION(BlueprintCallable, Category = "AbilitySystem|Attributes")
    float GetMaxStamina() const;

	UFUNCTION(BlueprintCallable, Category = "AbilitySystem|Attributes")
    float GetAttackPower() const;

	UFUNCTION(BlueprintCallable, Category = "AbilitySystem|Attributes")
    float GetAttackSpeed() const;

	UFUNCTION(BlueprintCallable, Category = "AbilitySystem|Attributes")
    float GetDefence() const;

	UFUNCTION(BlueprintCallable, Category = "AbilitySystem|Attributes")
	float GetMovementSpeed() const;

	UFUNCTION(BlueprintCallable, Category = "AbilitySystem|Attributes")
	float GetMovementSpeedBase() const;

	UFUNCTION(BlueprintCallable, Category = "AbilitySystem|Attributes")
    float GetSprintSpeedMultiplier() const;

protected:
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UGASAbilitySystemComponent* AbilitySystemComponent;

	UPROPERTY()
	UGASAttributeSet* AttributeSet;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "AbilitySystem|Abilities")
	TArray<TSubclassOf<UGASGameplayAbility>> InitialAbilities;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "AbilitySystem|Effects")
	TArray<TSubclassOf<class UGameplayEffect>> InitialEffect;

	void AddInitialAbilities();
	void AddInitialEffect();
};
