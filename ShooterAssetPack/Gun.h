// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Gun.generated.h"

UCLASS()
class SHOOTERASSETPACK_API AGun : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGun();
	void Trigger();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:

	UPROPERTY(VisibleAnywhere)
	USceneComponent* Root;

	UPROPERTY(VisibleAnywhere)
	USkeletalMeshComponent* Mesh;

	UPROPERTY(EditDefaultsOnly)
	int32 GunRange = 2000;

	UPROPERTY(EditDefaultsOnly)
	UParticleSystem* MuzzleFlash;

	UPROPERTY(EditDefaultsOnly)
	UParticleSystem* ImpactEffect;

	UPROPERTY(EditDefaultsOnly)
	USoundBase* MuzzleSound;

	UPROPERTY(EditDefaultsOnly)
	USoundBase* ImpactSound;

	UPROPERTY(EditDefaultsOnly)
	float Damage = 10.0f;

	bool GunLineTrace(FHitResult& Hit,FVector& ShotDirection);
	AController* GetGunController();
};
