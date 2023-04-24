// Fill out your copyright notice in the Description page of Project Settings.


#include "BTService_Playerlocation.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Pawn.h"


UBTService_Playerlocation::UBTService_Playerlocation()
{
    NodeName = "Update the player Last Location";
}

void UBTService_Playerlocation::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
    Super::TickNode(OwnerComp,NodeMemory,DeltaSeconds);

    APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(),0);
    if(!PlayerPawn) return;

    OwnerComp.GetBlackboardComponent()->SetValueAsVector(GetSelectedBlackboardKey(),PlayerPawn->GetActorLocation());

}