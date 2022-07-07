// Fill out your copyright notice in the Description page of Project Settings.


#include "GameOver.h"
#include "TanksHUD.h"
#include <Kismet/GameplayStatics.h>
#include "MyCoreStyle.h"

void UGameOver::NativeConstruct()
{
	Super::NativeConstruct();

	if (TryAgainButton)
	{
		TryAgainButton->OnClicked.AddDynamic(this, &UGameOver::OnTryAgainClicked);
	}

	if (QuitGameButton)
	{
		QuitGameButton->OnClicked.AddDynamic(this, &UGameOver::OnQuitGameClicked);
	}

	if (BackgroundImage)
	{
		FSlateBrush Brush;
		Brush.TintColor = MyCoreStyle::Get().GetColor("Background");
		BackgroundImage->SetBrush(Brush);
	}
}

void UGameOver::OnTryAgainClicked()
{
	UGameplayStatics::OpenLevel(GetWorld(), LoadLevelName);
}

void UGameOver::OnQuitGameClicked()
{
	FGenericPlatformMisc::RequestExit(false);
}
