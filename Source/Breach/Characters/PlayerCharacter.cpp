// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/AnimInstance.h"
#include "Breach/Pawns/BaseGun.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "PlayerCharacter.h"


// Sets default values
APlayerCharacter::APlayerCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	GetMesh()->HideBoneByName(TEXT("Weapon"), EPhysBodyOp::PBO_None);
	if (EquippedGun != nullptr)
	{
		Gun = GetWorld()->SpawnActor<ABaseGun>(EquippedGun);
		Gun->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, TEXT("WeaponSocket"));
		Gun->SetOwner(this);
	}

	Health = MaxHealth;
	UE_LOG(LogTemp, Warning, TEXT("Total Health: %f"), Health);
	Bullets = Gun->GetMaxBullets();
	UE_LOG(LogTemp, Warning, TEXT("Total Bullets: %i"), Bullets);
}

// Called every frame
void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis(TEXT("Forward"), this, &APlayerCharacter::MoveUp);
	PlayerInputComponent->BindAxis(TEXT("Sideways"), this, &APlayerCharacter::MoveSideways);
	PlayerInputComponent->BindAxis(TEXT("LookUp"), this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis(TEXT("LookSideways"), this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAction(TEXT("Jump"), EInputEvent::IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction(TEXT("Shoot"), EInputEvent::IE_Pressed, this, &APlayerCharacter::PullTrigger);
	PlayerInputComponent->BindAction(TEXT("Reload"), EInputEvent::IE_Pressed, this, &APlayerCharacter::Reload);
}

void APlayerCharacter::MoveUp(float AxisValue)
{
	AddMovementInput(GetActorForwardVector() * AxisValue);
}

void APlayerCharacter::MoveSideways(float AxisValue)
{
	AddMovementInput(GetActorRightVector() * AxisValue);
}

void APlayerCharacter::PullTrigger()
{
	if (Bullets > 0)
	{
		Gun->PullTrigger();
		Bullets--;
		UE_LOG(LogTemp, Warning, TEXT("Bullets Remaining: %i"), Bullets);
		if (FireAnimation != nullptr)
		{
			PlayAnimMontage(FireAnimation, 1.f);
		}
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("No bullets Remaining"));
	}
}

void APlayerCharacter::Reload()
{
	Bullets = Gun->GetMaxBullets();
	UE_LOG(LogTemp, Warning, TEXT("Gun reloaded"));
}

float APlayerCharacter::TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser)
{
	float DamageToApply = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	DamageToApply = FMath::Min(Health, DamageToApply);
	Health -= DamageToApply;
	UE_LOG(LogTemp, Warning, TEXT("Remaining Health: %f"), Health);

	if (IsDead())
	{
		DetachFromControllerPendingDestroy();
		GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}

	return DamageToApply;
}

bool APlayerCharacter::IsDead()
{
	if (Health == 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}

float APlayerCharacter::GetCurrentHealth()
{
	return Health / MaxHealth;
}