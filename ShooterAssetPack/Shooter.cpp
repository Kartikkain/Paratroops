// Fill out your copyright notice in the Description page of Project Settings.


#include "Shooter.h"
#include "Gun.h"
#include "Components/CapsuleComponent.h"
#include "SimpleShooterGameModeBase.h"

// Sets default values
AShooter::AShooter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AShooter::BeginPlay()
{
	Super::BeginPlay();
	Gun = GetWorld()->SpawnActor<AGun>(GunClass);
	GetMesh()->HideBoneByName(TEXT("weapon_r"),EPhysBodyOp::PBO_None);
	Gun->AttachToComponent(GetMesh(),FAttachmentTransformRules::KeepRelativeTransform,TEXT("WeaponSocket"));
	Gun->SetOwner(this);

	Health = MaxHealth;
}

// Called every frame
void AShooter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AShooter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAxis(TEXT("MoveForward"),this,&AShooter::Move);
	PlayerInputComponent->BindAxis(TEXT("MoveSideWays"),this,&AShooter::MoveSideways);
	PlayerInputComponent->BindAxis(TEXT("LookHorizontaly"),this,&APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis(TEXT("LookVerticaly"),this,&APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAction(TEXT("Jump"),IE_Pressed,this,&ACharacter::Jump);
	PlayerInputComponent->BindAction(TEXT("Fire"),IE_Pressed,this,&AShooter::Fire);

}

void AShooter::Move(float AxisValue)
{
	AddMovementInput(GetActorForwardVector()*AxisValue);
}

void AShooter::MoveSideways(float AxisValue)
{
	AddMovementInput(GetActorRightVector()*AxisValue);
}

void AShooter::Fire()
{
	if(Gun)
	{
		Gun->Trigger();
	}
}

float AShooter::TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser)
{
	float DamageApplied = Super::TakeDamage(DamageAmount,DamageEvent,EventInstigator,DamageCauser);
	float DamageActor = FMath::Min(Health,DamageApplied);
	Health -= DamageActor;
	if(IsDead())
	{
		ASimpleShooterGameModeBase* GameMode = GetWorld()->GetAuthGameMode<ASimpleShooterGameModeBase>();
		if(GameMode) GameMode->Pawnkilled(this);
		DetachFromControllerPendingDestroy();
		GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}
	return DamageApplied;
}

bool AShooter::IsDead() const
{
	return Health <= 0;
}

float AShooter::GetHealthPercent() const
{
	return Health/MaxHealth;
}
