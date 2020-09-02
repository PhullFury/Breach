// Fill out your copyright notice in the Description page of Project Settings.


#include "Breach/Characters/PlayerCharacter.h"
#include "Components/SkeletalMeshComponent.h"
#include "DrawDebugHelpers.h"
#include "GunBase.h"
#include "Kismet/GameplayStatics.h"

#define OUT

// Sets default values
AGunBase::AGunBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(Root);

	Mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(Root);
}

// Called when the game starts or when spawned
void AGunBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AGunBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

//TODO Refactor the PullTrigger

void AGunBase::PullTrigger()
{
	if (MuzzleFlash != nullptr)
	{
		UGameplayStatics::SpawnEmitterAttached(MuzzleFlash, Mesh, TEXT("Muzzle"));
	}

	APlayerCharacter* OwnerPawn = Cast< APlayerCharacter>(GetOwner());
	if (OwnerPawn == nullptr) return;
	AController* OwnerController = OwnerPawn->GetController();
	if (OwnerController == nullptr) return;

	FVector OwnerLocation;
	FRotator OwnerRotation;
	OwnerController->GetPlayerViewPoint(OUT OwnerLocation, OUT OwnerRotation);
	FVector LineEnd = OwnerLocation + OwnerRotation.Vector() * MaxRange;
	FHitResult ShotResult;
	FCollisionQueryParams Params;
	Params.AddIgnoredActor(this);
	Params.AddIgnoredActor(GetOwner());

	bool bHitSuccess = GetWorld()->LineTraceSingleByChannel(OUT ShotResult, OwnerLocation, LineEnd, ECollisionChannel::ECC_GameTraceChannel1, Params);
	if (bHitSuccess)
	{
		FVector ShotDirection = -OwnerRotation.Vector();
		AActor* HitActor = ShotResult.GetActor();
		if (ImpactFlash != nullptr)
		{
			UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ImpactFlash, ShotResult.Location, ShotDirection.Rotation(), true);
		}
		if (HitActor != nullptr)
		{
			FPointDamageEvent GunDamageEvent(GunDamage, ShotResult, ShotDirection, nullptr);
			HitActor->TakeDamage(GunDamage, GunDamageEvent, OwnerController, OwnerPawn);
		}
	}
}