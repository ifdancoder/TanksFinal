// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasePawn.h"

/**
 * 
 */
class TANKS_API Pawns
{
public:

Pawns();
~Pawns();

static void AddPawn(ABasePawn* AddablePawn);

static void DelPawn(ABasePawn* DeletablePawn);

static TMap<double, ABasePawn*> GetUnFriendly(ABasePawn* ThisPawn);

private:
	
UPROPERTY()
static TArray<ABasePawn*> BasePawns;
};
