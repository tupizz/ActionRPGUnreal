// SExplosiveBarrel.h
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SExplosiveBarrel.generated.h"

class USoundCue;
class URadialForceComponent;
class UStaticMeshComponent;
class UParticleSystem;

UCLASS()
class MYCPLUSPLUSPROJECT_API ASExplosiveBarrel : public AActor
{
    GENERATED_BODY()
    
public:    
    // Sets default values for this actor's properties
    ASExplosiveBarrel();

protected:
    // Componente de mesh
    UPROPERTY(EditAnywhere, Category = "Components")
    UStaticMeshComponent* MeshComp;

    // Componente de impulso radial
    UPROPERTY(EditAnywhere, Category = "Components")
    URadialForceComponent* RadialForceComp;

    // Efeito de partículas para a explosão
    UPROPERTY(EditAnywhere, Category = "Effects")
    UParticleSystem* ExplosionEffect;

    UPROPERTY(EditAnywhere, Category = "Effects")
    UParticleSystem* FlameEffect;

    // Raio do dano da explosão
    UPROPERTY(EditAnywhere, Category = "Gameplay")
    float ExplosionRadius;

    // Impulso aplicado aos objetos próximos
    UPROPERTY(EditAnywhere, Category = "Gameplay")
    float ExplosionImpulse;
    
    UFUNCTION()
    void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
   
    // Make explode function BlueprintCallable so it can be triggered from Blueprints
    UFUNCTION(BlueprintCallable, Category = "Gameplay")
    void Explode();
   
    // O barril já explodiu?
    bool bExploded;
    
    // Called when the game starts or when spawned
    virtual void BeginPlay() override;

public:    
    // Called every frame
    virtual void Tick(float DeltaTime) override;
};