// Fill out your copyright notice in the Description page of Project Settings.


#include "SaveManager.h"

#include "SaveGameInfo.h"
#include "Kismet/GameplayStatics.h"

void USaveManager::Init()
{
	CurrentSave = Cast<USaveGameInfo>(UGameplayStatics::CreateSaveGameObject(USaveGameInfo::StaticClass()));
}

bool USaveManager::IsSaveGameExist(const FString& SlotName) const
{
	return UGameplayStatics::DoesSaveGameExist(SlotName, 0);
}

void USaveManager::LoadGame(const FString& SlotName)
{
	if (!IsSaveGameExist(SlotName))
	{
		return;
	}
	FAsyncLoadGameFromSlotDelegate LoadDelegate;
	LoadDelegate.BindUObject(this, &USaveManager::OnGameLoadFunc);
	UGameplayStatics::AsyncLoadGameFromSlot(SlotName, 0, LoadDelegate);
}

void USaveManager::SaveGame(const FString& SlotName)
{
	FAsyncSaveGameToSlotDelegate SaveDelegate;
	SaveDelegate.BindUObject(this, &USaveManager::OnGameSaveFunc);
	CurrentSave->CollectData(GetWorld());
	UGameplayStatics::AsyncSaveGameToSlot(CurrentSave, SlotName, 0, SaveDelegate);
}

void USaveManager::OnGameLoadFunc(const FString& SlotName, const int32 UserIndex, USaveGame* SaveGame)
{
	CurrentSave = Cast<USaveGameInfo>(SaveGame);
	OnGameLoaded.Broadcast(SlotName);
	CurrentSave->ApplyData(GetWorld());
}

void USaveManager::OnGameSaveFunc(const FString& SlotName, const int32 UserIndex, bool bSuccess)
{
	OnGameSaved.Broadcast(SlotName);
}
