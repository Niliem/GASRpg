// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "GASCharacter.generated.h"

UCLASS()
class GAS_API AGASCharacter : public ACharacter
{
	GENERATED_BODY()

public:

	AGASCharacter();

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION(BlueprintPure, BlueprintNativeEvent, Category = "Movement")
	float GetMaxSpeed() const;
};
