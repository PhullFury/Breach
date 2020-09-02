// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GunBase.generated.h"

UCLASS()
class BREACH_API AGunBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGunBase();
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void PullTrigger();


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
	UPROPERTY(EditDefaultsOnly, Category = "Effects")
		UParticleSystem* MuzzleFlash;
	UPROPERTY(EditDefaultsOnly, Category = "Effects")
		UParticleSystem* ImpactFlash;
};
