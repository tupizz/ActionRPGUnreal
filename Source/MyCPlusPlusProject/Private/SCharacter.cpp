// Fill out your copyright notice in the Description page of Project Settings.


#include "SCharacter.h"

#include "CommonAnimTypes.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"

// Sets default values
ASCharacter::ASCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComp"));
	SpringArmComp->SocketOffset = FVector(0.0f, 0.0f, 30.0f); // Raise camera position
	
	/* Camera control setup:
	* bUsePawnControlRotation = true: Allows the spring arm (camera boom) to rotate with mouse/controller input
	* This enables looking around by rotating the camera while keeping the character facing forward
	*/
	SpringArmComp->bUsePawnControlRotation = true;
	SpringArmComp->SetupAttachment(RootComponent);

	// SpringArmComp->TargetArmLength = 300.0f; // Camera distance from character
	// SpringArmComp->bEnableCameraLag = true; // Enable smooth camera follow
	// SpringArmComp->CameraLagSpeed = 10.0f; // Adjust lag speed for smoother movement
	// SpringArmComp->CameraRotationLagSpeed = 10.0f; // Smooth rotation
	// SpringArmComp->CameraLagMaxDistance = 100.0f; // Maximum distance the camera can lag behind
	
	CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComp"));
	CameraComp->SetupAttachment(SpringArmComp);
	
	/* Character rotation setup:
	* bUseControllerRotationYaw = false: Prevents the character from rotating with the camera
	* This creates a "strafe" movement style where character can move sideways while looking in different directions
	*/
	bUseControllerRotationYaw = false;

	/* Character movement setup:
	* bOrientRotationToMovement = true: Rotate character to movement direction
	* This allows the character to turn to face the direction it is moving in instead of the direction it is facing
	*/
	GetCharacterMovement()->bOrientRotationToMovement = true; // Rotate character to movement direction
}

// Called when the game starts or when spawned
void ASCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

void ASCharacter::MoveForward(float Value)
{
	FRotator ControlRot = GetControlRotation();
	// we are only interested in the yaw rotation(yaw-> horizontal)
	ControlRot.Pitch = 0.0f;
	ControlRot.Roll = 0.0f;
	
	AddMovementInput(ControlRot.Vector(), Value);
}

void ASCharacter::MoveRigth(float X)
{
	FRotator ControlRot = GetControlRotation();
	// we are only interested in the yaw rotation(yaw-> horizontal)
	ControlRot.Pitch = 0.0f;
	ControlRot.Roll = 0.0f;
	
	// x = forward (red)
	// y = right (green)
	// z = up (blue)
	
	// Get the right vector (facing right relative to character's current view direction) 
	// by creating a rotation matrix from the control rotation and getting its Y axis
	FVector RightVector = FRotationMatrix(ControlRot).GetScaledAxis(EAxis::Y);
	
	// Apply movement input in the right direction scaled by input value X
	AddMovementInput(RightVector, X);
}

// Called every frame
void ASCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ASCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	
	PlayerInputComponent->BindAxis("MoveForward", this, &ASCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ASCharacter::MoveRigth);
	
	PlayerInputComponent->BindAxis("Turn", this, &ASCharacter::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp", this, &ASCharacter::AddControllerPitchInput);
	// PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	// PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);
	// PlayerInputComponent->BindAction("Crouch", IE_Pressed, this, &ACharacter::Crouch);
	// PlayerInputComponent->BindAction("Crouch", IE_Released, this, &ACharacter::UnCrouch);
	// PlayerInputComponent->BindAction("JumpAndCrouch", IE_Pressed, this, &ACharacter::JumpAndCrouch);
	// PlayerInputComponent->BindAction("ToggleGravity", IE_Pressed, this, &ACharacter::ToggleGravity);
	// PlayerInputComponent->BindAction("ToggleGravity", IE_Released, this, &ACharacter::ToggleGravity);
	// PlayerInputComponent->BindAction("StartSprint", IE_Pressed, this, &ACharacter::StartSprint);
}
