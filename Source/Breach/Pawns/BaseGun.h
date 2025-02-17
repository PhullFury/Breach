// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "BaseGun.generated.h"

UCLASS()
class BREACH_API ABaseGun : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ABaseGun();
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void PullTrigger();
	int32 GetMaxBullets();
	float GetFireRate();

	UPROPERTY(EditAnywhere, Category = "Combat")
		int32 MaxBullets = 30;
	UPROPERTY(EditAnywhere, Category = "Combat")
		float FireRate = 0.2;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


private:
	UPROPERTY(VisibleAnywhere)
		USceneComponent* Root;
	UPROPERTY(VisibleAnywhere)
		USkeletalMeshComponent* Mesh;
	UPROPERTY(EditAnywhere, Category = "Combat")
		float MaxRange = 1000;
	UPROPERTY(EditAnywhere, Category = "Combat")
		float GunDamage = 10;
	UPROPERTY(EditAnywhere, Category = "Combat")
		bool bIsInaccurate = true;
	UPROPERTY(EditAnywhere, Category = "Combat")
		float Inaccuracy = 5;
	UPROPERTY(EditDefaultsOnly, Category = "Effects")
		UParticleSystem* MuzzleFlash;
	UPROPERTY(EditDefaultsOnly, Category = "Effects")
		UParticleSystem* ImpactFlash;
	UPROPERTY(EditDefaultsOnly, Category = "Effects")
		USoundBase* MuzzleSound;
	UPROPERTY(EditDefaultsOnly, Category = "Effects")
		USoundBase* ImpactSound;

	bool GunTrace(FHitResult& ShotResult, FVector& ShotDirection);
	AController* GetOwnerController() const;
	FVector HitLocation;
};