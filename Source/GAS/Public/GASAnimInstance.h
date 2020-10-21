// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "GASAnimInstance.generated.h"

class AGASCharacter;
/**
 * 
 */
UCLASS()
class GAS_API UGASAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public:

	virtual void NativeInitializeAnimation() override;

	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

protected:

	UPROPERTY(BlueprintReadOnly, Category = "Character")
	AGASCharacter* Character;

	UPROPERTY(BlueprintReadOnly, Category = "Movement")
	FVector Velocity;

	UPROPERTY(BlueprintReadOnly, Category = "Movement")
	float Speed;

	UPROPERTY(BlueprintReadOnly, Category = "Movement")
	float MaxSpeed;

	UPROPERTY(BlueprintReadOnly, Category = "Movement")
	float NormalizedSpeed;

	UPROPERTY(BlueprintReadOnly, Category = "Rotation")
	FRotator Rotation;

	UPROPERTY(BlueprintReadOnly, Category = "Rotation")
	float Direction;

	UPROPERTY(BlueprintReadOnly, Category = "TurnRate")
	float TurnRate;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "TurnRate")
	float TurnSmoothingRate = 8.f;

private:

	void UpdateTurnRate(float DeltaSeconds);

	FRotator PrevRotation;
};
