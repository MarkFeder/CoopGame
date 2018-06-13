// Fill out your copyright notice in the Description page of Project Settings.

#include "SPowerUpActor.h"


// Sets default values
ASPowerUpActor::ASPowerUpActor()
{
	PowerUpInterval = 0.0f;
	TotalNumberOfTicks = 0;

	SetReplicates(true);
}

void ASPowerUpActor::ActivatePowerUp()
{
	OnActivated();

	if (PowerUpInterval > 0.0f)
	{
		GetWorldTimerManager().SetTimer(TimerHandle_PowerUpTick, this, &ASPowerUpActor::OnTickPowerUp, PowerUpInterval, true);
	}
	else
	{
		OnTickPowerUp();
	}
}

void ASPowerUpActor::OnRep_PowerUpActive()
{
	if (bIsPowerUpActive)
	{

	}
	else
	{

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
