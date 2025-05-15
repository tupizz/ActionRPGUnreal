// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BlackholeProjectile.generated.h"

class URadialForceComponent;
class UProjectileMovementComponent;
class USphereComponent;
class UParticleSystemComponent;
class UStaticMeshComponent;

UCLASS()
class MYCPLUSPLUSPROJECT_API ABlackholeProjectile : public AActor
{
	GENERATED_BODY()
	
public:
	ABlackholeProjectile();

protected:
	UPROPERTY(visibleanywhere, BlueprintReadWrite, Category= "Components")
	USphereComponent* SphereComp;

	UPROPERTY(visibleanywhere, BlueprintReadWrite, Category= "Components")
	USphereComponent* SphereBlackHoleComp;

	UPROPERTY(visibleanywhere, BlueprintReadWrite, Category= "Components")
	UProjectileMovementComponent* MovementComp;

	UPROPERTY(visibleanywhere, BlueprintReadWrite, Category= "Components")
	UParticleSystemComponent* EffectComp;

	UPROPERTY(visibleanywhere, BlueprintReadWrite, Category= "Components")
	URadialForceComponent* RadialForceComp;
	
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Animation parameters for the radial force
	UPROPERTY(EditAnywhere, Category = "Force Animation")
	float MinRadius = 1000.0f;

	UPROPERTY(EditAnywhere, Category = "Force Animation")
	float MaxRadius = 3000.0f;

	UPROPERTY(EditAnywhere, Category = "Force Animation")
	float AnimationSpeed = 2.0f;

	// To track animation progress
	float AnimationTime = 0.0f;


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	virtual void PostInitializeComponents() override;

	UFUNCTION()
	void OnOverlappedPhysicsActor(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	                              UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
	                              const FHitResult& SweepResult);
};
