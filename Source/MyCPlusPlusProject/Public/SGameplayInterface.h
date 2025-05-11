// SGameplayInterface.h
#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "SGameplayInterface.generated.h"

// This class declares the interface's virtual functions
UINTERFACE(MinimalAPI)
class USGameplayInterface : public UInterface
{
    GENERATED_BODY()
};

// This class declares the interface functions that can be overridden
class MYCPLUSPLUSPROJECT_API ISGameplayInterface
{
    GENERATED_BODY()

public:
    // Add interface functions here
    UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Gameplay")
    void Interact(APawn* InstigatorPawn);
};