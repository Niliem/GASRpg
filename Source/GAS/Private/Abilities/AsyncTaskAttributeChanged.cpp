// Fill out your copyright notice in the Description page of Project Settings.


#include "Abilities/AsyncTaskAttributeChanged.h"


UAsyncTaskAttributeChanged* UAsyncTaskAttributeChanged::ListenForAttributeChange(UAbilitySystemComponent* AbilitySystemComponent, FGameplayAttribute Attribute)
{
	if (!IsValid(AbilitySystemComponent) || !Attribute.IsValid())
	{
		return nullptr;
	}

	return ListenForAttributesChange(AbilitySystemComponent, {Attribute});
}

UAsyncTaskAttributeChanged* UAsyncTaskAttributeChanged::ListenForAttributesChange(UAbilitySystemComponent* AbilitySystemComponent, TArray<FGameplayAttribute> Attributes)
{
	if (!IsValid(AbilitySystemComponent) || Attributes.Num() < 1)
	{
		return nullptr;
	}

	UAsyncTaskAttributeChanged* WaitForAttributeChangedTask = NewObject<UAsyncTaskAttributeChanged>();
	WaitForAttributeChangedTask->AbilitySystemComponent = AbilitySystemComponent;
	WaitForAttributeChangedTask->AttributesToListenFor = Attributes;

	for (FGameplayAttribute& Attribute : Attributes)
	{
		AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(Attribute).AddUObject(WaitForAttributeChangedTask, &UAsyncTaskAttributeChanged::AttributeChanged);
	}

	return WaitForAttributeChangedTask;
}

void UAsyncTaskAttributeChanged::EndTask()
{
	if (IsValid(AbilitySystemComponent))
	{
		for (FGameplayAttribute& Attribute : AttributesToListenFor)
		{
			AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(Attribute).RemoveAll(this);
		}
	}

	SetReadyToDestroy();
	MarkPendingKill();
}

void UAsyncTaskAttributeChanged::AttributeChanged(const FOnAttributeChangeData& Data)
{
	OnAttributeChanged.Broadcast(Data.Attribute, Data.NewValue, Data.OldValue);
}
