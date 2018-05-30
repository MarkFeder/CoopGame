// Fill out your copyright notice in the Description page of Project Settings.

#include "SPowerUpActor.h"


// Sets default values
ASPowerUpActor::ASPowerUpActor()
{
	PowerUpInterval = 0.0f;
	TotalNumberOfTicks = 0;
}

// Called when the game starts or when spawned
void ASPowerUpActor::BeginPlay()
{
	Super::BeginPlay();
}

void ASPowerUpActor::ActivatePowerUp()
{
	if (PowerUpInterval > 0.0f)
	{
		GetWorldTimerManager().SetTimer(TimerHandle_LifeSpanExpired, this, &ASPowerUpActor::OnTickPowerUp, PowerUpInterval, true);
	}
	else
	{
		OnTickPowerUp();
	}
}

void ASPowerUpActor::OnTickPowerUp()
{
	TicksProcessed++;

	OnPowerUpTicked();

	if (TicksProcessed >= TotalNumberOfTicks)
	{
		OnExpired();

		// Delete timer in our last tick
		GetWorldTimerManager().ClearTimer(TimerHandle_LifeSpanExpired);
	}
}
