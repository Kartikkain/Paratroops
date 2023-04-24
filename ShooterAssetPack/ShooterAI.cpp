// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterAI.h"
#include "Kismet/GameplayStatics.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Shooter.h"

void AShooterAI::BeginPlay()
{
    Super::BeginPlay();

    if(AIBehaviour)
    {
        RunBehaviorTree(AIBehaviour);
        APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(),0);
        GetBlackboardComponent()->SetValueAsVector(TEXT("PlayerLocation"),PlayerPawn->GetActorLocation());
        GetBlackboardComponent()->SetValueAsVector(TEXT("StartLocation"),GetPawn()->GetActorLocation());
    }
    
}

void AShooterAI::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

}

bool AShooterAI::IsDead() const
{
    AShooter* characterController = Cast<AShooter>(GetPawn());
    if(characterController)
    {
        return characterController->IsDead();
    }

    return true;
}