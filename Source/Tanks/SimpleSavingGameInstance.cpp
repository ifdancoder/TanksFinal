// Fill out your copyright notice in the Description page of Project Settings.


#include "SimpleSavingGameInstance.h"

#include "SimpleSavingManager.h"
#include "Kismet/GameplayStatics.h"

void USimpleSavingGameInstance::Init()
{
	Super::Init();

	GLog->Log(ELogVerbosity::Warning, TEXT("MyGameInstance::Init Success"));

	SaveManager = NewObject<USimpleSavingManager>(this);
	SaveManager->Init();

}

USimpleSavingManager* USimpleSavingGameInstance::GetSaveManager(UObject* WorldContextObject)
{
	auto* MyInstance = Cast<USimpleSavingGameInstance>(UGameplayStatics::GetGameInstance(WorldContextObject));
	return MyInstance ? MyInstance->SaveManager : nullptr;
}
