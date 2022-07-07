// Fill out your copyright notice in the Description page of Project Settings.


#include "GraphicalSettings.h"
#include "TanksHUD.h"
#include "MyCoreStyle.h"

void UGraphicalSettings::NativeConstruct()
{
	if (SaveButton)
	{
		SaveButton->OnClicked.AddDynamic(this, &UGraphicalSettings::SaveClicked);
	}

	if (BackButton)
	{
		BackButton->OnClicked.AddDynamic(this, &UGraphicalSettings::BackClicked);
	}

	if (OrdinaryButton)
	{
		OrdinaryButton->OnClicked.AddDynamic(this, &UGraphicalSettings::OrdinaryClicked);
	}

	if(BlackWhiteButton)
	{
		BlackWhiteButton->OnClicked.AddDynamic(this, &UGraphicalSettings::BlackWhiteClicked);
	}

	if(Status)
	{
		SetStatus();
	}
}

void UGraphicalSettings::SaveClicked()
{
	Cast<ATanksHUD>(GetWorld()->GetFirstPlayerController()->GetHUD())->ShowWindow(EWidgetID::Settings);
}

void UGraphicalSettings::OrdinaryClicked()
{
	MyCoreStyle::ChangeStyle(0);
	SetStatus();
}

void UGraphicalSettings::BlackWhiteClicked()
{
	MyCoreStyle::ChangeStyle(1);
	SetStatus();
}

void UGraphicalSettings::SetStatus()
{
	if (Status)
	{
		Status->SetText(MyCoreStyle::GetStatus() ? FText::FromString("Status: Black-White") : FText::FromString("Status: Ordinary"));
	}

	if (BackgroundImage)
	{
		FSlateBrush Brush;
		Brush.TintColor = MyCoreStyle::Get().GetColor("Background");
		BackgroundImage->SetBrush(Brush);
	}
}

void UGraphicalSettings::BackClicked()
{
	Cast<ATanksHUD>(GetWorld()->GetFirstPlayerController()->GetHUD())->ShowWindow(EWidgetID::Settings);
}