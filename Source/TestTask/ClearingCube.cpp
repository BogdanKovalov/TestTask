// Fill out your copyright notice in the Description page of Project Settings.


#include "ClearingCube.h"
#include "Kismet/GameplayStatics.h"
#include "TestTaskGameModeBase.h"

void AClearingCube::BeginPlay()
{
	Super::BeginPlay();
	BaseMesh->OnComponentHit.AddDynamic(this, &AClearingCube::ClearCube);
}

void AClearingCube::ClearCube(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit) {
	ACube* Cube = Cast<ACube>(OtherActor);
	if (Cube == nullptr || BaseMesh->GetMaterial(0) == DirtyMaterial) return;
	Cube->ClearColor();
}