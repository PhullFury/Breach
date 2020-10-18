// Fill out your copyright notice in the Description page of Project Settings.


#include "Barrel.h"
#include "DrawDebugHelpers.h"
#include "Kismet/GameplayStatics.h"

#define OUT

// Sets default values
ABarrel::ABarrel()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(Root);

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(Root);
}

// Called when the game starts or when spawned
void ABarrel::BeginPlay()
{
	Super::BeginPlay();
	
	Health = MaxHealth;
	UE_LOG(LogTemp, Warning, TEXT("Health: %f"), Health);
}

// Called every frame
void ABarrel::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
}

float ABarrel::TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser)
{
	float DamageToApply = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	DamageToApply = FMath::Min(Health, DamageToApply);
	Health -= DamageToApply;
	UE_LOG(LogTemp, Warning, TEXT("Remaining Health: %f"), Health);

	if (Health == 0)
	{
		UE_LOG(LogTemp, Error, TEXT("Barrel Exploded"));
		DrawDebugSphere(GetWorld(), GetActorLocation(), 500.f, 1, FColor::Red, true); 
		TArray<FHitResult> PawnsHit;
		FVector Range = GetActorLocation() * 500.f;
		FCollisionShape MySphere = FCollisionShape::MakeSphere(500.0f);
		GetWorld()->SweepMultiByChannel(OUT PawnsHit, GetActorLocation(), Range, FQuat::Identity, ECollisionChannel::ECC_GameTraceChannel1, MySphere);
		for (FHitResult Pawn : PawnsHit)
		{
			AActor* HitActor = Pawn.GetActor();
			FRadialDamageEvent BarrelDamageEvent;
			HitActor->TakeDamage(ExDamage, BarrelDamageEvent, HitActor->GetInstigatorController(), this);
		}
		Destroy();
	}

	return DamageToApply;
}