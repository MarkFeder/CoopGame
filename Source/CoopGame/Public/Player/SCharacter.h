// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "SCharacter.generated.h"

class UCameraComponent;
class USpringArmComponent;
class ASWeapon;
class USHealthComponent;

UCLASS()
class COOPGAME_API ASCharacter : public ACharacter
{
	GENERATED_BODY()

public:

	// Sets default values for this character's properties
	ASCharacter();

protected:

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void MoveForward(float Value);

	void MoveRight(float Value);

	void BeginCrouch();

	void EndCrouch();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UCameraComponent* CameraComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	USpringArmComponent* SpringArmComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	USHealthComponent* HealthComp;

	/* Wether to setup zoom or not */
	bool bWantsToZoom;

	/* The amount zoom to be set up in the FOV */
	UPROPERTY(EditDefaultsOnly, Category = "Player")
	float ZoomedFOV;

	/* The velocity of the interpoleted zoom speed */
	UPROPERTY(EditDefaultsOnly, Category = "Player", meta = (ClampMin = 0.0, ClampMax = 100))
	float ZoomInterpSpeed;

	/* Default FOV set during begin play */
	float DefaultFOV;

	/* Starts zoom FOV effect */
	void BeginZoom();

	/* Ends zoom FOV effect */
	void EndZoom();

	/* Character's current weapon */
	UPROPERTY(Replicated)
	ASWeapon* CurrentWeapon;

	UPROPERTY(EditDefaultsOnly, Category = "Player")
	TSubclassOf<ASWeapon> StarterWeaponClass;

	UPROPERTY(VisibleDefaultsOnly, Category = "Player")
	FName WeaponAttachSocketName;

	/* Character starting fire action */
	void StartFire();

	/* Character stopping fire action */
	void StopFire();

	UFUNCTION()
	void OnHealthChanged(USHealthComponent* OwningHealthComp, float Health, float HealthDelta, const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser);

	/* Pawn died previously */
	UPROPERTY(Replicated, BlueprintReadOnly, Category = "Player")
	bool bDied;

public:	

	/* Called every frame */
	virtual void Tick(float DeltaTime) override;

	/* Called to bind functionality to input */
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	/* Get character view location */
	virtual FVector GetPawnViewLocation() const override;
};
