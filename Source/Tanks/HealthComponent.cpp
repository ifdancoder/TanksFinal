// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthComponent.h"

// Sets default values for this component's properties
UHealthComponent::UHealthComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;
	// ...
}


void UHealthComponent::TakeDamage(const FDamageData& DamageData)
{
	float TakedDamageValue = DamageData.DamageValue;
	CurrentHealth -= TakedDamageValue;

	if (CurrentHealth > MaxHealth)
	{
		CurrentHealth = MaxHealth;
		if (OnHealthChanged.IsBound())
		{
			OnHealthChanged.Broadcast(TakedDamageValue);
		}
	}

	if (CurrentHealth <= 0.f)
	{
		if (OnDie.IsBound())
		{
			OnDie.Broadcast();
		}
	}
	else
	{
		if (OnHealthChanged.IsBound())
		{
			OnHealthChanged.Broadcast(TakedDamageValue);
		}
	}

}

void UHealthComponent::TakeHealInt(int InHeal)
{
	FDamageData Healing;
	Healing.DamageValue = -InHeal;
	TakeDamage(Healing);
}

float UHealthComponent::GetHealth() const
{
	return CurrentHealth;
}


void UHealthComponent::SetHealth(float InHealth)
{
	CurrentHealth = InHealth;
}

float UHealthComponent::GetHealthState() const
{
	return CurrentHealth / MaxHealth;
}

void UHealthComponent::AddHealth(float AddiditionalHealthValue)
{
	CurrentHealth = FMath::Clamp(CurrentHealth + AddiditionalHealthValue, 0.f, MaxHealth);
}

void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	CurrentHealth = MaxHealth;
}