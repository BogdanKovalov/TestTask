// Fill out your copyright notice in the Description page of Project Settings.


#include "Cube.h"
#include "Ball.h"
#include "ClearingCube.h"
#include "NavigationSystem.h"
#include "AI/NavigationSystemBase.h"
#include "Kismet/GameplayStatics.h"
#include "TestTaskGameModeBase.h"
#include "NiagaraComponent.h"
#include "NiagaraFunctionLibrary.h"

// Sets default values
ACube::ACube()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Base Mesh"));
	SetRootComponent(BaseMesh);
	BaseMesh->SetSimulatePhysics(true);
}

// Called when the game starts or when spawned
void ACube::BeginPlay()
{
	Super::BeginPlay();
	NavigationSystem = Cast<UNavigationSystemV1>(GetWorld()->GetNavigationSystem());

	if (ClearMaterial != nullptr) BaseMesh->SetMaterial(0, ClearMaterial);
	BaseMesh->OnComponentHit.AddDynamic(this, &ACube::Paint);

	if (AGameModeBase* GameModeBase = UGameplayStatics::GetGameMode(this)) {
		GameMode = Cast<ATestTaskGameModeBase>(GameModeBase);
	}
	if (ContaminateEventParticles && CleanEventParticles) {
	}
}

// Called every frame
void ACube::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (NavigationSystem != nullptr && !(GetWorldTimerManager().IsTimerActive(AddingForceTimer))) {
		FNavLocation FoundedLocation;
		NavigationSystem->GetRandomReachablePointInRadius(GetActorLocation(), 5000, FoundedLocation);
		FVector ForceDirection = FoundedLocation.Location - GetActorLocation();
		ForceDirection.Normalize();
		BaseMesh->AddForce(ForceDirection * ForceStrenght);
		GetWorldTimerManager().SetTimer(AddingForceTimer, ForceDelay, false);
	}
}

void ACube::Paint(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit) {
	if (BaseMesh->GetMaterial(0) == DirtyMaterial) return;

	if (Cast<ABall>(OtherActor)) {
		HandlePainting();
	}
	else if (ACube* Cube = Cast<ACube>(OtherActor)) {
		if (Cube->BaseMesh->GetMaterial(0) == DirtyMaterial && Cast<AClearingCube>(this) == nullptr) {
			HandlePainting();
		}
	}
}

void ACube::ClearColor() {
	if (BaseMesh->GetMaterial(0) == ClearMaterial) return;
	BaseMesh->SetMaterial(0, ClearMaterial);
	if (CleanEventParticles != nullptr) UNiagaraFunctionLibrary::SpawnSystemAtLocation(this, CleanEventParticles, GetActorLocation());
	if (GameMode) GameMode->CubeCleared(this);
}

void ACube::HandlePainting() {
	BaseMesh->SetMaterial(0, DirtyMaterial);
	if (GameMode) GameMode->CubePainted(this);
	if (ContaminateEventParticles) UNiagaraFunctionLibrary::SpawnSystemAtLocation(this, ContaminateEventParticles, GetActorLocation());
	if (HitBallSound) UGameplayStatics::PlaySoundAtLocation(this, HitBallSound, GetActorLocation());
}

