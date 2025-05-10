// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "SCharacter.generated.h"

// when declaring pointers we don't need to care about the actual type
class UCameraComponent;
class USpringArmComponent;

UCLASS()
class MYCPLUSPLUSPROJECT_API ASCharacter : public ACharacter
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere)
	TSubclassOf<AActor> ProjectileClass;

public:
	// Sets default values for this character's properties
	ASCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere)
	UCameraComponent* CameraComp; // Pointer only needs to know the type exists

	UPROPERTY(VisibleAnywhere)
	USpringArmComponent* SpringArmComp; // this is used to control the camera

	void MoveForward(float Value);
	void MoveRigth(float X);
	void PrimaryAttack();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
