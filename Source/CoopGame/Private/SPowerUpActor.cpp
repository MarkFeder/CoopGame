// Fill out your copyright notice in the Description page of Project Settings.

#include "SPowerUpActor.h"
#include "Net/UnrealNetwork.h"


// Sets default values
ASPowerUpActor::ASPowerUpActor()
{
	PowerUpInterval = 0.0f;
	TotalNumberOfTicks = 0;

	bIsPowerUpActive = false;

	SetReplicates(true);
}

void ASPowerUpActor::ActivatePowerUp(AActor* ActivateFor)
{
	OnActivated(ActivateFor);

	bIsPowerUpActive = true;
	OnRep_PowerUpActive();

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
	OnPowerUpStateChanged(bIsPowerUpActive);
}

void ASPowerUpActor::OnTickPowerUp()
{
	TicksProcessed++;

	OnPowerUpTicked();

	if (TicksProcessed >= TotalNumberOfTicks)
	{
		OnExpired();

		bIsPowerUpActive = false;
		OnRep_PowerUpActive();

		// Delete timer in our last tick
		GetWorldTimerManager().ClearTimer(TimerHandle_LifeSpanExpired);
	}
}

void ASPowerUpActor::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ASPowerUpActor, bIsPowerUpActive);
}
