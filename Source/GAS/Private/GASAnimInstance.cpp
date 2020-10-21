// Fill out your copyright notice in the Description page of Project Settings.


#include "GASAnimInstance.h"
#include "GASCharacter.h"
#include "Kismet/KismetMathLibrary.h"

void UGASAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	Character = Cast<AGASCharacter>(TryGetPawnOwner());

	if (IsValid(Character))
	{
		MaxSpeed = Character->GetMaxSpeed();
	}
}

void UGASAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	if (IsValid(Character))
	{
		Velocity = Character->GetVelocity();
		Speed = Velocity.Size(); // VectorLengthXY
		NormalizedSpeed = Speed / MaxSpeed;
		Rotation = Character->GetActorRotation();
		Direction = CalculateDirection(Velocity, Rotation);

		UpdateTurnRate(DeltaSeconds);
	}
}

void UGASAnimInstance::UpdateTurnRate(float DeltaSeconds)
{
	TurnRate = FMath::FInterpTo(
		TurnRate,
		UKismetMathLibrary::NormalizedDeltaRotator(Rotation, PrevRotation).Yaw,
		DeltaSeconds,
		TurnSmoothingRate);
	PrevRotation = Rotation;
}
