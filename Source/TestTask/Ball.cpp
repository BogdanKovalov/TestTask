// Fill out your copyright notice in the Description page of Project Settings.


#include "Ball.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/SpringArmComponent.h" 
#include "Camera/CameraComponent.h"
#include "EnhancedInput/Public/InputAction.h"
#include "EnhancedInput/Public/EnhancedInputSubsystems.h"
#include "EnhancedInput/Public/EnhancedInputComponent.h"

// Sets default values
ABall::ABall()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Base Mesh"));
	SetRootComponent(BaseMesh);

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
	SpringArm->SetupAttachment(RootComponent);

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);

	BaseMesh->SetSimulatePhysics(true);

	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	bUseControllerRotationYaw = false;
}

// Called when the game starts or when spawned
void ABall::BeginPlay()
{
	Super::BeginPlay();
	PlayerController = Cast<APlayerController>(GetController());
	if (PlayerController != nullptr) {
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer())) {
			Subsystem->AddMappingContext(InputMapping, 0);
		}
	}
}

// Called every frame
void ABall::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void ABall::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent)) {
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ABall::Move);
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &ABall::Look);
		EnhancedInputComponent->BindAction(RestartLevelAction, ETriggerEvent::Triggered, this, &ABall::RestartLevel);
		EnhancedInputComponent->BindAction(LeapAction, ETriggerEvent::Triggered, this, &ABall::Dash);
	}
}

void ABall::Move(const FInputActionValue& Value) {
	if (PlayerController == nullptr) return;
	FVector2D MoveValue = Value.Get<FVector2D>();
	BaseMesh->AddForce(FVector(Camera->GetForwardVector().X, Camera->GetForwardVector().Y, 0.0f) * MoveValue.X * ForceStrenght);
	BaseMesh->AddForce(FVector(Camera->GetRightVector().X, Camera->GetRightVector().Y,0.0f) * MoveValue.Y * ForceStrenght);
}

void ABall::Look(const FInputActionValue& Value) {
	if (PlayerController == nullptr) return;
	FVector2D LookValue = Value.Get<FVector2D>();
	AddControllerYawInput(LookValue.Y);
	AddControllerPitchInput(-LookValue.X);
}

void ABall::RestartLevel(const FInputActionValue& Value) {
	UGameplayStatics::OpenLevelBySoftObjectPtr(this, GetLevel());
}

void ABall::Dash(const FInputActionValue& Value) {
	if (!(GetWorldTimerManager().IsTimerActive(DashTimer))) {
		BaseMesh->AddImpulse(FVector(Camera->GetForwardVector().X, Camera->GetForwardVector().Y,0.0f) * ImpusleValue, NAME_None, true);
		GetWorldTimerManager().SetTimer(DashTimer, DashDelay, false);
	}
}
