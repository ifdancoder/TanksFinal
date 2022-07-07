// Fill out your copyright notice in the Description page of Project Settings.


#include "Pawns.h"

TArray<ABasePawn*> Pawns::BasePawns;

Pawns::Pawns()
{
}

Pawns::~Pawns()
{
}

void Pawns::AddPawn(ABasePawn* AddablePawn)
{
	BasePawns.Add(AddablePawn);
}

void Pawns::DelPawn(ABasePawn* DeletablePawn)
{
	BasePawns.Remove(DeletablePawn);
}

TMap<double, ABasePawn*> Pawns::GetUnFriendly(ABasePawn* ThisPawn)
{
	TMap<double, ABasePawn*> Targets;

	for (auto &i : BasePawns)
	{
		if (i && ThisPawn && (*i).GetFriendness() != (*ThisPawn).GetFriendness())
		{
			FVector a = ThisPawn->GetActorLocation();
			FVector b = i->GetActorLocation();
			Targets.Add(FVector::Dist(ThisPawn->GetActorLocation(), i->GetActorLocation()), i);
		}
	}

	Targets.KeySort([](double a, double b){return a < b;});

	return Targets;
}

