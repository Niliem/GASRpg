// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h"
#include "GASAttributeSet.generated.h"

#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
    GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
    GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
    GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
    GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)

/**
 * 
 */
UCLASS()
class GAS_API UGASAttributeSet : public UAttributeSet
{
	GENERATED_BODY()

public:
	UGASAttributeSet();

	virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;
	virtual void PostGameplayEffectExecute(const struct FGameplayEffectModCallbackData& Data) override;
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	UPROPERTY( BlueprintReadOnly, Category = "Attributes|Health", ReplicatedUsing = OnRep_Health )
	FGameplayAttributeData Health;
	ATTRIBUTE_ACCESSORS(UGASAttributeSet, Health)

	UPROPERTY( BlueprintReadOnly, Category = "Attributes|Health", ReplicatedUsing = OnRep_MaxHealth )
	FGameplayAttributeData MaxHealth;
	ATTRIBUTE_ACCESSORS(UGASAttributeSet, MaxHealth)

	UPROPERTY( BlueprintReadOnly, Category = "Attributes|Stamina", ReplicatedUsing = OnRep_Stamina )
	FGameplayAttributeData Stamina;
	ATTRIBUTE_ACCESSORS(UGASAttributeSet, Stamina)

	UPROPERTY( BlueprintReadOnly, Category = "Attributes|Stamina", ReplicatedUsing = OnRep_MaxStamina )
	FGameplayAttributeData MaxStamina;
	ATTRIBUTE_ACCESSORS(UGASAttributeSet, MaxStamina)

	UPROPERTY( BlueprintReadOnly, Category = "Attributes|Attack", ReplicatedUsing = OnRep_AttackPower )
	FGameplayAttributeData AttackPower;
	ATTRIBUTE_ACCESSORS(UGASAttributeSet, AttackPower)

	UPROPERTY( BlueprintReadOnly, Category = "Attributes|Attack", ReplicatedUsing = OnRep_AttackSpeed )
	FGameplayAttributeData AttackSpeed;
	ATTRIBUTE_ACCESSORS(UGASAttributeSet, AttackSpeed)

	UPROPERTY( BlueprintReadOnly, Category = "Attributes|Defence", ReplicatedUsing = OnRep_Defence )
	FGameplayAttributeData Defence;
	ATTRIBUTE_ACCESSORS(UGASAttributeSet, Defence)

	UPROPERTY( BlueprintReadOnly, Category = "Attributes|MovementSpeed", ReplicatedUsing = OnRep_MovementSpeed )
	FGameplayAttributeData MovementSpeed;
	ATTRIBUTE_ACCESSORS(UGASAttributeSet, MovementSpeed)

	UPROPERTY( BlueprintReadOnly, Category = "Attributes|SprintSpeedMultiplier", ReplicatedUsing = OnRep_SprintSpeedMultiplier )
	FGameplayAttributeData SprintSpeedMultiplier;
	ATTRIBUTE_ACCESSORS(UGASAttributeSet, SprintSpeedMultiplier)

	UPROPERTY( BlueprintReadOnly, Category = "Attributes|Damage", meta = (HideFromLevelInfos) )
	FGameplayAttributeData Damage;
	ATTRIBUTE_ACCESSORS(UGASAttributeSet, Damage)

protected:
	void AdjustAttributeForMaxChange(FGameplayAttributeData& AffectedAttribute, const FGameplayAttributeData& MaxAttribute, float NewMaxValue, const FGameplayAttribute& AffectedAttributeProperty);

	UFUNCTION()
	virtual void OnRep_Health(const FGameplayAttributeData& OldHealth);

	UFUNCTION()
	virtual void OnRep_MaxHealth(const FGameplayAttributeData& OldMaxHealth);

	UFUNCTION()
	virtual void OnRep_Stamina(const FGameplayAttributeData& OldStamina);

	UFUNCTION()
	virtual void OnRep_MaxStamina(const FGameplayAttributeData& OldMaxStamina);

	UFUNCTION()
	virtual void OnRep_AttackPower(const FGameplayAttributeData& OldAttackPower);

	UFUNCTION()
	virtual void OnRep_AttackSpeed(const FGameplayAttributeData& OldAttackSpeed);

	UFUNCTION()
	virtual void OnRep_Defence(const FGameplayAttributeData& OldDefence);

	UFUNCTION()
	virtual void OnRep_MovementSpeed(const FGameplayAttributeData& OldMovementSpeed);

	UFUNCTION()
	virtual void OnRep_SprintSpeedMultiplier(const FGameplayAttributeData& OldSprintSpeedMultiplier);
};
