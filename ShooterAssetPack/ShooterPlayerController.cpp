// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterPlayerController.h"
#include "TimerManager.h"
#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"

void AShooterPlayerController::BeginPlay()
{
    Super::BeginPlay();
    
    CrossHUD = CreateWidget(this,CrossHUDClass);
    if(CrossHUD) CrossHUD->AddToViewport();

}

void AShooterPlayerController::GameHasEnded(class AActor* EndGameFocus, bool bIsWinner)
{
    Super::GameHasEnded(EndGameFocus,bIsWinner);
    CrossHUD->RemoveFromViewport();
    if(bIsWinner)
    {
        UUserWidget* WinScreen = CreateWidget(this,WinScreenClass);
        if(WinScreen) WinScreen->AddToViewport();
        GetWorldTimerManager().SetTimer(RestartTimer,this,&AShooterPlayerController::LoadNextLevel,RestartDelay);
    }
    else
    {
        UUserWidget* LooseScreen = CreateWidget(this,LooseScreenClass);
        if(LooseScreen) LooseScreen->AddToViewport();
        GetWorldTimerManager().SetTimer(RestartTimer,this,&APlayerController::RestartLevel,RestartDelay);
    }   
}

void AShooterPlayerController::LoadNextLevel()
{
    UGameplayStatics::OpenLevel(GetWorld(),TEXT("MainMenu"),true);
}

