// Fill out your copyright notice in the Description page of Project Settings.


#include "GASAnimInstance.h"
#include "GASCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"

void UGASAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	Character = Cast<AGASCharacter>(TryGetPawnOwner());
}

void UGASAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	if (IsValid(Character))
	{
		Velocity = Character->GetVelocity();
		Speed = Velocity.Size2D();
		MaxSpeed = Character->GetMovementSpeedBase();
		NormalizedSpeed = Speed / MaxSpeed;
		Rotation = Character->GetActorRotation();
		Direction = CalculateDirection(Velocity, Rotation);

		// MovementModeChangedDelegate
		MovementMode = Character->GetCharacterMovement()->MovementMode;

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
