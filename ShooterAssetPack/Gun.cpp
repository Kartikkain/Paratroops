// Fill out your copyright notice in the Description page of Project Settings.


#include "Gun.h"
#include "Components/SkeletalMeshComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AGun::AGun()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(Root);

	Mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(Root);

}

// Called when the game starts or when spawned
void AGun::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AGun::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AGun::Trigger()
{
	UGameplayStatics::SpawnEmitterAttached(MuzzleFlash,Mesh,TEXT("MuzzleFlashSocket"));
	UGameplayStatics::SpawnSoundAttached(MuzzleSound,Mesh,TEXT("MuzzleFlashSocket"));

	FHitResult Hit;
	FVector ShotDirection;

	bool IsBulletHit = GunLineTrace(Hit,ShotDirection);
	if(IsBulletHit)
	{
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(),ImpactEffect,Hit.Location,ShotDirection.Rotation());
		UGameplayStatics::PlaySoundAtLocation(GetWorld(),ImpactSound,Hit.Location);
		AActor* HitActor = Hit.GetActor();
		if(HitActor)
		{
			AController* OwnerController = GetGunController();
			FPointDamageEvent DamageEvent(Damage,Hit,ShotDirection,nullptr);
			HitActor->TakeDamage(Damage,DamageEvent,OwnerController,this);
		}
	}
}

bool AGun::GunLineTrace(FHitResult& Hit,FVector& ShotDirection)
{
	AController* GunController = GetGunController();
	if(!GunController) return false;

	FVector Location;
	FRotator Rotation;
	GunController->GetPlayerViewPoint(Location,Rotation);

	FVector End = Location + Rotation.Vector() * GunRange;
	ShotDirection = -Rotation.Vector();
	FCollisionQueryParams params;
	params.AddIgnoredActor(this);
	params.AddIgnoredActor(GetOwner());

	return GetWorld()->LineTraceSingleByChannel(Hit,Location,End,ECollisionChannel::ECC_GameTraceChannel1,params);
}

AController* AGun::GetGunController()
{
	APawn* GunOwner = Cast<APawn>(GetOwner());
	if(!GunOwner) return nullptr;
	return GunOwner->GetController();
}
