// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Cube.generated.h"

class UStaticMeshComponent;
class UNavigationSystemV1;
class ATestTaskGameModeBase;
class UNiagaraSystem;
class USoundBase;

UCLASS()
class TESTTASK_API ACube : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ACube();

	void ClearColor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
protected:
	UPROPERTY(EditDefaultsOnly, BluePrintReadOnly, Category = "Meshes")
	UStaticMeshComponent* BaseMesh;

	UPROPERTY(EditDefaultsOnly, BluePrintReadOnly, Category = "Movement")
	float ForceStrenght = 10.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Movement")
	float ForceDelay = 0.3f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Materials")
	UMaterial* ClearMaterial;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Materials")
	UMaterial* DirtyMaterial;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Effects")
	UNiagaraSystem* CleanEventParticles;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Effects")
	UNiagaraSystem* ContaminateEventParticles;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Effects")
	USoundBase* HitBallSound;

	ATestTaskGameModeBase* GameMode ;

	UNavigationSystemV1* NavigationSystem;

	FTimerHandle AddingForceTimer;

private:
	UFUNCTION()
	void Paint(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	UFUNCTION()
	void HandlePainting();
};
