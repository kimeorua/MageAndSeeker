// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "GenericTeamAgentInterface.h"
#include "MagePlayerController.generated.h"

/**
 * 
 */
UCLASS()
class MAGEANDSEEKER_API AMagePlayerController : public APlayerController, public IGenericTeamAgentInterface
{
	GENERATED_BODY()

public:
	AMagePlayerController();

	virtual FGenericTeamId GetGenericTeamId() const override;

private:
	FGenericTeamId MageTeamId;
};
