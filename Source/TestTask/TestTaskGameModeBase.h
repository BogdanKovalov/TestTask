// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "TestTaskGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class TESTTASK_API ATestTaskGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
public:
	void CubeCleared(AActor* ClearedActor);
	void CubePainted(AActor* PaintedActor);
protected:
	void BeginPlay() override;

	UPROPERTY(BlueprintReadOnly, Category = "Gameplay")
	int32 AmountOfClearingCubes;

	UPROPERTY(BlueprintReadOnly, Category = "Gameplay")
	int32 AmountOfClearCubes;
};
