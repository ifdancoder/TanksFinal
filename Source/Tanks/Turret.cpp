// Fill out your copyright notice in the Description page of Project Settings.


#include "Turret.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "Engine/StaticMesh.h"
#include "Components/ArrowComponent.h"
#include "Cannon.h"
#include "Kismet/KismetMathLibrary.h"
#include "UObject/NoExportTypes.h"
#include "Tanks.h"
#include "HealthComponent.h"
#include "Logging/LogMacros.h"
#include <DrawDebugHelpers.h>
#include "Pawns.h"

// Sets default values
ATurret::ATurret()
{
	PrimaryActorTick.TickInterval = 0.005f;
}

// Called when the game starts or when spawned
void ATurret::BeginPlay()
{
	Super::BeginPlay();

}

void ATurret::Destroyed()
{
	Super::Destroyed();

	if (Cannons.Num())
	{
		Cannons[CurrentCannonIndex]->Destroy();
	}
}

void ATurret::Targeting()
{
	for (auto &i : Pawns::GetUnFriendly(this))
	{
		if (IsTargetInRange(i.Value))
		{
			Target = i.Value;
			break;
		}
	}

	if (Target && IsTargetInRange(Target))
	{
		RotateToTarget();
	}

	if (Target && CanFire() && Cannons[CurrentCannonIndex] && Cannons[CurrentCannonIndex]->IsReadyToFire() && IsTargetInRange(Target))
	{
		Fire();
	}
}

void ATurret::RotateToTarget()
{
	FRotator TargetRotation = UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), Target->GetActorLocation());
	FRotator CurrRotation = TurretMesh->GetComponentRotation();

	/*UE_LOG(LogTanks, Verbose, TEXT("T: (%f, %f, %f), C: (%f, %f, %f)"), TargetRotation.Roll, TargetRotation.Pitch, TargetRotation.Yaw,
																		CurrRotation.Roll, CurrRotation.Pitch, CurrRotation.Yaw);*/
	TargetRotation.Pitch = CurrRotation.Pitch;
	TargetRotation.Roll = CurrRotation.Roll;
	TurretMesh->SetWorldRotation(FMath::RInterpConstantTo(CurrRotation, TargetRotation, GetWorld()->GetDeltaSeconds(), TargetingSpeed));
}

bool ATurret::IsTargetInRange(ABasePawn* InTarget)
{
	FHitResult HitResult;
	FVector TraceStart = GetActorLocation();
	FVector TraceEnd = InTarget->GetActorLocation();
	FCollisionQueryParams TraceParams = FCollisionQueryParams(FName(TEXT("AI Vission Trace")), true, this);
	TraceParams.bReturnPhysicalMaterial = false;

	if (GetWorld()->LineTraceSingleByChannel(HitResult, TraceStart, TraceEnd, ECC_Visibility, TraceParams))
	{
		if (HitResult.Actor != InTarget)
		{
			return false;
		}
	}

	return FVector::DistSquared(InTarget->GetActorLocation(), GetActorLocation()) <= FMath::Square(TargetingRange);
}

bool ATurret::CanFire()
{
	FVector TargetingDir = TurretMesh->GetForwardVector();
	FVector DirToPlayer = Target->GetActorLocation() - GetActorLocation();
	DirToPlayer.Normalize();
	float AimAngle = FMath::RadiansToDegrees(FMath::Acos(FVector::DotProduct(TargetingDir, DirToPlayer)));

	return AimAngle <= Accuracy;
}

// Called every frame
void ATurret::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (Pawns::GetUnFriendly(this).Num())
	{
		Targeting();
	}
}

void ATurret::TakeDamage(const FDamageData& DamageData)
{
	HealthComponent->TakeDamage(DamageData);
}

float ATurret::GetScoreForKill()
{
	return ScoreForKill;
}
