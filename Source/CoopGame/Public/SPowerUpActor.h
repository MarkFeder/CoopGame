// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SPowerUpActor.generated.h"

UCLASS()
class COOPGAME_API ASPowerUpActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASPowerUpActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	/* Time between power up ticks */
	UPROPERTY(EditDefaultsOnly, Category = "PowerUps")
	float PowerUpInterval;

	/* Total times we apply the power up effect */
	UPROPERTY(EditDefaultsOnly, Category = "PowerUps")
	int32 TotalNumberOfTicks;

	FTimerHandle TimerHandle_PowerUpTick;

	/* Total number of ticks applied */
	int32 TicksProcessed;

	UFUNCTION()
	void OnTickPowerUp();

public:

	void ActivatePowerUp();

	UFUNCTION(BlueprintImplementableEvent, Category = "PowerUps")
	void OnActivated();

	UFUNCTION(BlueprintImplementableEvent, Category = "PowerUps")
	void OnPowerUpTicked();

	UFUNCTION(BlueprintImplementableEvent, Category = "PowerUps")
	void OnExpired();
};