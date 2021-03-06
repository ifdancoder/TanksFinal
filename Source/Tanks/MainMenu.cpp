// Fill out your copyright notice in the Description page of Project Settings.


#include "MainMenu.h"
#include <Kismet/GameplayStatics.h>
#include <Kismet/KismetSystemLibrary.h>
#include "TanksHUD.h"
#include "SRadioButtons.h"
#include "MyCoreStyle.h"
#include "RadButWidgetStyle.h"
#include <Components/ButtonSlot.h>
#include <Components/RichTextBlock.h>


//#include "RB.h"

void UMainMenu::NativePreConstruct()
{
	Super::NativePreConstruct();

	

	/*if (RadioButtons)
	{
		RadioButtons->WidgetStyle = MyCoreStyle::Get().GetWidgetStyle<FRadButStyle>("RadioButtonsStyle");
	}*/

	if (BackgroundImage)
	{
		FSlateBrush Brush;
		Brush.TintColor = MyCoreStyle::Get().GetColor("Background");
		BackgroundImage->SetBrush(Brush);
	}

	if (HeaderText)
	{
		HeaderText->SetDefaultFont(MyCoreStyle::Get().GetFontStyle("HeaderText"));
	}

	/*if (PlayerImage)
	{
		PlayerImage->SetBrush(*MyCoreStyle::Get().GetBrush("PlayerImage"));
		Cast<UButtonSlot>(PlayerImage->Slot)->SetPadding(MyCoreStyle::Get().GetMargin("DefaultPadding"));
	}*/
}

void UMainMenu::NativeConstruct()
{
	Super::NativeConstruct();

	if (NewGameButton)
	{ 
		NewGameButton->OnClicked.AddDynamic(this, &UMainMenu::OnNewGameClicked);
	}

	if (QuitButton)
	{
		QuitButton->OnClicked.AddDynamic(this, &UMainMenu::OnQuitClicked);
	}

	if (OptionsButton)
	{
		OptionsButton->OnClicked.AddDynamic(this, &UMainMenu::OnSettingsClicked);
	}

	HUD = Cast<ATanksHUD>(GetWorld()->GetFirstPlayerController()->GetHUD());
}

void UMainMenu::OnNewGameClicked()
{
	if (InvisAnimation)
	{
		PlayAnimation(InvisAnimation);
		GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &UMainMenu::End, InvisAnimation->GetEndTime(), false);
	}
	
}

void UMainMenu::OnQuitClicked()
{
	GEngine->Exec(GetWorld(), TEXT("Exit"));
}

void UMainMenu::OnSettingsClicked()
{
	Cast<ATanksHUD>(GetWorld()->GetFirstPlayerController()->GetHUD())->ShowWindow(EWidgetID::Settings);
}

void UMainMenu::End()
{
	UGameplayStatics::OpenLevel(GetWorld(), LoadLevelName);
	UMainMenu::RemoveFromParent();
	GetWorld()->GetTimerManager().ClearTimer(TimerHandle);
}
