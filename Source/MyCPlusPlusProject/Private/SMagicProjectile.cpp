// Fill out your copyright notice in the Description page of Project Settings.

// Include required header files
#include "SMagicProjectile.h"
#include "Components/SphereComponent.h" // For collision sphere
#include "GameFramework/ProjectileMovementComponent.h" // For projectile movement
#include "Particles/ParticleSystemComponent.h" // For visual effects

// Constructor - Sets up the default properties and components of the magic projectile
ASMagicProjectile::ASMagicProjectile()
{
	// // Enable Tick() to run every frame - can be disabled to improve performance
	// PrimaryActorTick.bCanEverTick = true;

	// Create and setup the sphere collision component
	SphereComp = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComp"));
	SphereComp->SetCollisionProfileName("Projectile"); // Set collision profile to "Projectile"
	RootComponent = SphereComp; // Make the sphere the root component of this actor

	// Create and setup the visual effects component
	EffectComp = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("EffectComp"));
	EffectComp->SetupAttachment(SphereComp); // Attach effects to the sphere component

	// Create and configure the projectile movement component
	MovementComp = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("MovementComp"));
	MovementComp->InitialSpeed = 2000.0f; // Set how fast the projectile moves
	MovementComp->bRotationFollowsVelocity = true; // Make projectile rotate to match its movement direction
	MovementComp->bInitialVelocityInLocalSpace = true; // Use local space for initial velocity
}

// Called when the projectile starts existing in the game
void ASMagicProjectile::BeginPlay()
{
	// Call parent class BeginPlay first
	Super::BeginPlay();
	
}

// // Called every frame to update the projectile
// void ASMagicProjectile::Tick(float DeltaTime)
// {
// 	// Call parent class Tick first
// 	Super::Tick(DeltaTime);
//
// }