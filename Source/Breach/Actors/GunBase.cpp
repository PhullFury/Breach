// Fill out your copyright notice in the Description page of Project Settings.


#include "Breach/Characters/PlayerCharacter.h"
#include "Components/SkeletalMeshComponent.h"
#include "DrawDebugHelpers.h"
#include "GunBase.h"

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

//TODO implement a shoot function and also spawn some effects

void AGunBase::PullTrigger()
{
	UE_LOG(LogTemp, Warning, TEXT("You have been shot boy!"));

	APlayerCharacter* OwnerPawn = Cast< APlayerCharacter>(GetOwner());
	if (OwnerPawn == nullptr) return;
	AController* OwnerController = OwnerPawn->GetController();
	if (OwnerController == nullptr) return;

	FVector OwnerLocation;
	FRotator OwnerRotation;
	OwnerController->GetPlayerViewPoint(OUT OwnerLocation, OUT OwnerRotation);
	FVector LineEnd = OwnerLocation + OwnerRotation.Vector() * MaxRange;
	FHitResult Hit;
	FCollisionQueryParams Params;
	Params.AddIgnoredActor(this);
	Params.AddIgnoredActor(GetOwner());

	GetWorld()->LineTraceSingleByChannel(OUT Hit, OwnerLocation, LineEnd, ECollisionChannel::ECC_GameTraceChannel1, Params);

	DrawDebugPoint(GetWorld(), Hit.Location, 20, FColor::Red, true);

	//TODO Dealt damage
}