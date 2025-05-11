// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SGameplayInterface.h"
#include "GameFramework/Actor.h"
#include "SItemChest.generated.h"

class UStaticMeshComponent;

UCLASS()
class MYCPLUSPLUSPROJECT_API ASItemChest : public AActor, public ISGameplayInterface
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, Category = "Gameplay")
	float TargetPitch;
	
	void Interact_Implementation(APawn* InstigatorPawn);
	
public:	
	// Sets default values for this actor's properties
	ASItemChest();

protected:
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* BasicMesh;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* LidMesh;
	
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
