// Fill out your copyright notice in the Description page of Project Settings.


#include "SaveGameInstance.h"

#include "SaveManager.h"
#include <Kismet/GameplayStatics.h>

void USaveGameInstance::Init()
{
	Super::Init();

	UE_LOG(LogTemp, Warning, TEXT("USaveGameInstance::Init()"));

	SaveManager = NewObject<USaveManager>(this);
	SaveManager->Init();
}

USaveManager* USaveGameInstance::GetSaveManager(UObject* WorldContextObject)
{
	auto* MyInstance = Cast<USaveGameInstance>(UGameplayStatics::GetGameInstance(WorldContextObject));
	return MyInstance ? MyInstance->SaveManager : nullptr;
}