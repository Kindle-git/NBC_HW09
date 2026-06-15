// NBGPlayerController.cpp


#include "Player/NBGPlayerController.h"
#include "UI/NBGChatInput.h"
#include "Kismet/KismetSystemLibrary.h"
#include "CH04NBG.h"
#include "EngineUtils.h"
#include "Kismet/GameplayStatics.h"
#include "Game/NBGGameModeBase.h"
#include "NBGPlayerState.h"
#include "Net/UnrealNetwork.h"

ANBGPlayerController::ANBGPlayerController()
{
	bReplicates = true;
}

void ANBGPlayerController::BeginPlay()
{
	Super::BeginPlay();
	
	if (IsLocalController() == false)
	{
		return;
	}
	
	FInputModeUIOnly InputModeUIOnly;
	SetInputMode(InputModeUIOnly);

	if (IsValid(ChatInputWidgetClass) == true)
	{
		ChatInputWidgetInstance = CreateWidget<UNBGChatInput>(this, ChatInputWidgetClass);
		if (IsValid(ChatInputWidgetInstance) == true)
		{
			ChatInputWidgetInstance->AddToViewport();
		}
	}
	
	if (IsValid(NotificationTextWidgetClass) == true)
	{
		NotificationTextWidgetInstance = CreateWidget<UUserWidget>(this, NotificationTextWidgetClass);
		if (IsValid(NotificationTextWidgetInstance) == true)
		{
			NotificationTextWidgetInstance->AddToViewport();
		}
	}

}

void ANBGPlayerController::SetChatMessageString(const FString& InChatMessageString)
{
	ChatMessageString = InChatMessageString;
	//PrintChatMessageString(ChatMessageString);
	
	if (IsLocalController() == true)
	{
		// ServerRPCPrintChatMessageString(InChatMessageString);		
		
		ANBGPlayerState* NBGPS = GetPlayerState<ANBGPlayerState>();
		if (IsValid(NBGPS) == true)
		{
			//FString CombinedMessageString = NBGPS->PlayerNameString + TEXT(": ") + InChatMessageString;
			FString CombinedMessageString = NBGPS->GetPlayerInfoString() + TEXT(": ") + InChatMessageString;
			
			ServerRPCPrintChatMessageString(CombinedMessageString);
		}
	}
}


void ANBGPlayerController::PrintChatMessageString(const FString& InChatMessageString)
{
	//FString NetModeString = CH04NBGFunctionLibrary::GetNetModeString(this);
	//FString CombinedMessageString = FString::Printf(TEXT("%s: %s"), *NetModeString, *InChatMessageString);
	//CH04NBGFunctionLibrary::MyPrintString(this, CombinedMessageString, 10.f);
	
	CH04NBGFunctionLibrary::MyPrintString(this, InChatMessageString, 10.f);
}

void ANBGPlayerController::GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	
	DOREPLIFETIME(ThisClass, NotificationText);
}

void ANBGPlayerController::ClientRPCPrintChatMessageString_Implementation(const FString& InChatMessageString)
{
	PrintChatMessageString(InChatMessageString);
}

void ANBGPlayerController::ServerRPCPrintChatMessageString_Implementation(const FString& InChatMessageString)
{
	//for (TActorIterator<ANBGPlayerController> It(GetWorld()); It; ++It)
	//{
	//	ANBGPlayerController* NBGPlayerController = *It;
	//	if (IsValid(NBGPlayerController) == true)
	//	{
	//		NBGPlayerController->ClientRPCPrintChatMessageString(InChatMessageString);
	//	}
	//}
	
	AGameModeBase* GM = UGameplayStatics::GetGameMode(this);
	if (IsValid(GM) == true)
	{
		ANBGGameModeBase* NBGGM = Cast<ANBGGameModeBase>(GM);
		if (IsValid(NBGGM) == true)
		{
			NBGGM->PrintChatMessageString(this, InChatMessageString);
		}
	}
}