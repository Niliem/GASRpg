// Fill out your copyright notice in the Description page of Project Settings.


#include "GASCharacter.h"

AGASCharacter::AGASCharacter()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AGASCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

float AGASCharacter::GetMaxSpeed_Implementation() const
{
	return 350.0f;
}
