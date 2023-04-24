// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_Shoot.h"
#include "AIController.h"
#include "Shooter.h"

UBTTask_Shoot::UBTTask_Shoot()
{

}

EBTNodeResult::Type UBTTask_Shoot::ExecuteTask(UBehaviorTreeComponent &OwnerComp,uint8 *NodeMemory) 
{
    Super::ExecuteTask(OwnerComp,NodeMemory);
    if(!OwnerComp.GetAIOwner()) return EBTNodeResult::Failed;
    AShooter* shooter = Cast<AShooter>(OwnerComp.GetAIOwner()->GetPawn());
    if(!shooter) return EBTNodeResult::Failed;
    shooter->Fire();

    return EBTNodeResult::Succeeded;
} 

