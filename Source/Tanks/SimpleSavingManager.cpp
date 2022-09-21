// Fill out your copyright notice in the Description page of Project Settings.


#include "SimpleSavingManager.h"

#include "SimpleSaveGame.h"
#include "Kismet/GameplayStatics.h"

void USimpleSavingManager::Init()
{
	CurrentSave = Cast<USimpleSaveGame>(UGameplayStatics::CreateSaveGameObject(USimpleSaveGame::StaticClass()));
}

bool USimpleSavingManager::IsSaveGameExist(const FString& SlotName) const
{
	return UGameplayStatics::DoesSaveGameExist(SlotName, 0);
}

void USimpleSavingManager::LoadGame(const FString& SlotName)
{
	if (!IsSaveGameExist(SlotName))
	{
		return;
	}
	FAsyncLoadGameFromSlotDelegate LoadDelegate;
	LoadDelegate.BindUObject(this, &USimpleSavingManager::OnGameLoadFunc);
	UGameplayStatics::AsyncLoadGameFromSlot(SlotName, 0, LoadDelegate);
}

void USimpleSavingManager::SaveGame(const FString& SlotName)
{
	FAsyncSaveGameToSlotDelegate SaveDelegate;
	SaveDelegate.BindUObject(this, &USimpleSavingManager::OnGameSaveFunc);
	CurrentSave->CollectData(GetWorld());
	UGameplayStatics::AsyncSaveGameToSlot(CurrentSave, SlotName, 0, SaveDelegate);
}

void USimpleSavingManager::OnGameLoadFunc(const FString& SlotName, const int32 UserIndex, USaveGame* SaveGame)
{
	CurrentSave = Cast<USimpleSaveGame>(SaveGame);
	OnGameLoaded.Broadcast(SlotName);
	CurrentSave->ApplyData(GetWorld());
}

void USimpleSavingManager::OnGameSaveFunc(const FString& SlotName, const int32 UserIndex, bool bSuccess)
{
	OnGameSaved.Broadcast(SlotName);
}
