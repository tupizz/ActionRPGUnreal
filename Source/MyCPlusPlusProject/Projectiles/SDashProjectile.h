// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SDashProjectile.generated.h"

class UProjectileMovementComponent;
class USphereComponent;
class UParticleSystemComponent;

UCLASS()
class MYCPLUSPLUSPROJECT_API ASDashProjectile : public AActor
{
	GENERATED_BODY()

public:
	static bool bIsBeingSpawned;
	// Sets default values for this actor's properties
	ASDashProjectile();

protected:
	FGuid UniqueID;
	
	UPROPERTY(visibleanywhere, BlueprintReadWrite, Category = "Components")
	USphereComponent* SphereComp;

	UPROPERTY(visibleanywhere, BlueprintReadWrite, Category = "Components")
	UProjectileMovementComponent* MovementComp;

	UPROPERTY(visibleanywhere, BlueprintReadWrite, Category = "Effects")
	UParticleSystemComponent* EffectComp;

	UPROPERTY(EditAnywhere, Category = "Visual effects")
	UParticleSystem* EndEffectComp;

	UPROPERTY(EditAnywhere, Category = "Visual effects")
	UParticleSystem* BeginningEffectComp;


	UPROPERTY(EditDefaultsOnly, Category = "Effects|Shake")
	TSubclassOf<UCameraShakeBase> ImpactShake;
	
	UPROPERTY(EditDefaultsOnly, Category = "Teleport")
	float TeleportDelay;

	UPROPERTY(EditDefaultsOnly, Category = "Teleport")
	float DetonateDelay;

	// Handle to cancel timer if we already hit something
	FTimerHandle TimerHandle_DelayedDetonate;

	void TeleportInstigator();

	void Explode();
	
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

// public:
// 	// Called every frame
// 	virtual void Tick(float DeltaTime) override;
};
