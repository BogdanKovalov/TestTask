// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Cube.h"
#include "ClearingCube.generated.h"

/**
 * 
 */
UCLASS()
class TESTTASK_API AClearingCube : public ACube
{
	GENERATED_BODY()
private:
	virtual void BeginPlay() override;

	UFUNCTION()
	void ClearCube(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
};
