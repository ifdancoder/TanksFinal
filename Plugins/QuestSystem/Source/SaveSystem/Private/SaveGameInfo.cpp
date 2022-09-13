// Fill out your copyright notice in the Description page of Project Settings.


#include "SaveGameInfo.h"

#include "SaveActorsSubsystem.h"
#include "Serialization/ObjectAndNameAsStringProxyArchive.h"

void USaveGameInfo::CollectData(UWorld* World)
{
	FMemoryWriter MemoryWriter(Bytes, true);
	FObjectAndNameAsStringProxyArchive Ar(MemoryWriter, true);
	Ar.ArIsSaveGame = true;
	if (auto Pawn = World->GetFirstPlayerController()->GetPawn())
	{
		Pawn->Serialize(Ar);
	}
	if (auto Subsystem = World->GetSubsystem<USaveActorsSubsystem>())
	{
		Subsystem->Serialize(Ar);
	}
	
}

void USaveGameInfo::ApplyData(UWorld* World)
{
	FMemoryReader MemoryReader(Bytes, true);
	FObjectAndNameAsStringProxyArchive Ar(MemoryReader, true);
	Ar.ArIsSaveGame = true;
	if (auto Pawn = World->GetFirstPlayerController()->GetPawn())
	{
		Pawn->Serialize(Ar);
	}
	if (auto Subsystem = World->GetSubsystem<USaveActorsSubsystem>())
	{
		Subsystem->Serialize(Ar);
	}
}
