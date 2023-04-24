// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SimpleShooterGameModeBase.h"
#include "KillEmAllGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTERASSETPACK_API AKillEmAllGameModeBase : public ASimpleShooterGameModeBase
{
	GENERATED_BODY()

public:
	virtual void Pawnkilled(class APawn* pawnkilled) override;

private:
	void EndGame(bool bIsPlayerWinner);
	
};
