// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "EnhancedInput/Public/InputActionValue.h"
#include "Ball.generated.h"

class UInputMappingContext;
class UInputAction;
class UStaticMeshComponent;
class UCameraComponent;
class USpringArmComponent;

UCLASS()
class TESTTASK_API ABall : public APawn
{
	GENERATED_BODY()

public:
	ABall();


	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	virtual void BeginPlay() override;
protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Enhanced Input")
	UInputMappingContext* InputMapping;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Enhanced Input")
	UInputAction* MoveAction;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Enhanced Input")
	UInputAction* LookAction;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Enhanced Input")
	UInputAction* RestartLevelAction;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Enhanced Input")
	UInputAction* LeapAction;

	UPROPERTY(VisibleAnywhere, BluePrintReadOnly, Category = "Meshes")
	UStaticMeshComponent* BaseMesh;

	UPROPERTY(VisibleAnywhere, BluePrintReadOnly, Category = "Meshes")
	UCameraComponent* Camera;

	UPROPERTY(VisibleAnywhere, BluePrintReadOnly, Category = "Meshes")
	USpringArmComponent* SpringArm;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Movement")
	float ForceStrenght = 10.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Movement")
	float ImpusleValue = 400.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Movement")
	FTimerHandle DashTimer;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Movement")
	float DashDelay = 3.0f;
private:
	APlayerController* PlayerController;

	void Move(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);
	void RestartLevel(const FInputActionValue& Value);
	void Dash(const FInputActionValue& Value);
};
