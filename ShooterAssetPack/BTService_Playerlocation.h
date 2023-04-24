// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Services/BTService_BlackboardBase.h"
#include "BTService_Playerlocation.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTERASSETPACK_API UBTService_Playerlocation : public UBTService_BlackboardBase
{
	GENERATED_BODY()

public:
	UBTService_Playerlocation();

protected:
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

	
};
