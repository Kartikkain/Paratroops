// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "ShooterPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTERASSETPACK_API AShooterPlayerController : public APlayerController
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;

public:
	virtual void GameHasEnded(class AActor* EndGameFocus = nullptr, bool bIsWinner = false) override;

private:
	UPROPERTY(EditAnywhere)
	TSubclassOf<class UUserWidget> LooseScreenClass;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class UUserWidget> WinScreenClass;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class UUserWidget> CrossHUDClass;

	UPROPERTY(EditAnywhere)
	float RestartDelay = 5.0f;

	UPROPERTY()
	class UUserWidget* CrossHUD;

	FTimerHandle RestartTimer;

	void LoadNextLevel();
};
