// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

UENUM(BlueprintType)
enum class EGASAbilityInputID : uint8
{
	None				UMETA(DisplayName = "None"),
    Confirm				UMETA(DisplayName = "Confirm"),
    Cancel				UMETA(DisplayName = "Cancel"),
    Sprint			    UMETA(DisplayName = "Sprint")
};
