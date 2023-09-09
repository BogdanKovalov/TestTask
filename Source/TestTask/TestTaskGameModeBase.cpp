// Copyright Epic Games, Inc. All Rights Reserved.


#include "TestTaskGameModeBase.h"
#include "ClearingCube.h"
#include "Cube.h"
#include "Kismet/GameplayStatics.h"

void ATestTaskGameModeBase::BeginPlay() {
	TArray<AActor*> AllClearingCubes;
	UGameplayStatics::GetAllActorsOfClass(this, AClearingCube::StaticClass(), AllClearingCubes);
	AmountOfClearingCubes = AllClearingCubes.Num();

	TArray<AActor*> AllCubes;
	UGameplayStatics::GetAllActorsOfClass(this, ACube::StaticClass(), AllCubes);
	AmountOfClearCubes = AllCubes.Num();
}

void ATestTaskGameModeBase::CubeCleared(AActor* ClearedActor) {
	++AmountOfClearCubes;
	if (Cast<AClearingCube>(ClearedActor)) ++AmountOfClearingCubes;
}

void ATestTaskGameModeBase::CubePainted(AActor* PaintedActor) {
	--AmountOfClearCubes;
	if (Cast<AClearingCube>(PaintedActor)) --AmountOfClearingCubes;
}