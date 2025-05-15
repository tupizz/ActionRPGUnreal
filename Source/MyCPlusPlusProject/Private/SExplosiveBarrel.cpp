// Fill out your copyright notice in the Description page of Project Settings.


#include "SExplosiveBarrel.h"

#include "SCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "PhysicsEngine/RadialForceComponent.h"

// Sets default values
/* Logging in Unreal Engine:
 * 1. Use UE_LOG macro with following syntax: UE_LOG(LogTemp, Log/Warning/Error, TEXT("Message %s"), *Variable);
 * 2. View logs in:
 *    - Output Log window in editor (Window -> Developer Tools -> Output Log)
 *    - Game's log files (Saved/Logs folder)
 *    - Debug console (~key while in game)
 * Log Categories:
 * - Log: Normal messages (white)
 * - Warning: Warning messages (yellow)
 * - Error: Error messages (red)
 */

ASExplosiveBarrel::ASExplosiveBarrel()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	UE_LOG(LogTemp, Log, TEXT("Explosive Barrel Created"));

	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
	SetRootComponent(MeshComp);

	MeshComp->SetSimulatePhysics(true);
	MeshComp->SetCollisionProfileName("PhysicsActor"); 
	MeshComp->OnComponentHit.AddDynamic(this, &ASExplosiveBarrel::OnHit);

	// Valores padrão para os parâmetros da explosão
	ExplosionRadius = 1000.0f;
	ExplosionImpulse = 2000.0f;

	RadialForceComp = CreateDefaultSubobject<URadialForceComponent>(TEXT("RadialForceComp"));
	RadialForceComp->SetupAttachment(MeshComp);
	RadialForceComp->bImpulseVelChange = true;
	RadialForceComp->bAutoActivate = false;
	RadialForceComp->Radius = ExplosionRadius;
	RadialForceComp->ForceStrength = ExplosionImpulse;

	bExploded = false;
}

void ASExplosiveBarrel::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	FVector NormalImpulse, const FHitResult& Hit)
{
	UE_LOG(LogTemp, Log, TEXT("Barrel hit by: %s"), *GetNameSafe(OtherActor));
	Explode();
	Destroy();
}

void ASExplosiveBarrel::Explode()
{
    UE_LOG(LogTemp, Warning, TEXT("Barrel exploding at location: %s"), *GetActorLocation().ToString());
    // Spawnar efeito de partículas de explosão
    if (ExplosionEffect)
    {
        UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ExplosionEffect, GetActorLocation(), FRotator::ZeroRotator, FVector(20.0f));
    }

	// Draw debug sphere to visualize explosion radius
	DrawDebugSphere(
		GetWorld(),
		GetActorLocation(),
		ExplosionRadius,
		32,              // Number of segments
		FColor::Red,     // Color
		false,           // Persistent lines
		5.0f,            // Duration
		0,               // Depth priority
		2.0f             // Thickness
	);


    // Get all overlapping actors in radius
    TArray<AActor*> OverlappingActors;
    UGameplayStatics::GetAllActorsOfClass(GetWorld(), AActor::StaticClass(), OverlappingActors);

    // Apply burning effect to each actor's components
    for(auto* Actor : OverlappingActors)
    {
    	
        if(Actor && FlameEffect && Actor != this)
        {
        	// Calculate distance to actor
        	float Distance = FVector::Distance(GetActorLocation(), Actor->GetActorLocation());

        	if (Distance <= ExplosionRadius)
        	{
        		// Log the distance for debugging
        		UE_LOG(LogTemp, Log, TEXT("Actor: %s at distance: %f"), *GetNameSafe(Actor), Distance);
        	
        		UStaticMeshComponent* FindMeshComp = Cast<UStaticMeshComponent>(Actor->GetComponentByClass(UStaticMeshComponent::StaticClass()));
        		if(FindMeshComp)
        		{
        			// Ignore SCharacter class
        			if (Actor->IsA(ASCharacter::StaticClass()))
        			{
        				UE_LOG(LogTemp, Log, TEXT("Ignoring SCharacter class"));
        				continue;
        			}
				
        			UE_LOG(LogTemp, Log, TEXT("Applying flame effect to: %s"), *GetNameSafe(Actor));
        			UGameplayStatics::SpawnEmitterAttached(FlameEffect, FindMeshComp, NAME_None, 
						FVector::ZeroVector, FRotator::ZeroRotator, EAttachLocation::SnapToTarget, true);
        		}
        		else
        		{
        			UE_LOG(LogTemp, Log, TEXT("Actor: %s at distance: %f outside radius"), *GetNameSafe(Actor), Distance);
        		}
        	}
        }
    }

    // Aplicar força radial aos objetos próximos  
    RadialForceComp->FireImpulse();
}

// Called when the game starts or when spawned
void ASExplosiveBarrel::BeginPlay()
{
	Super::BeginPlay();
	// Inicializar variáveis
	bExploded = false;
}

// Called every frame 
void ASExplosiveBarrel::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}