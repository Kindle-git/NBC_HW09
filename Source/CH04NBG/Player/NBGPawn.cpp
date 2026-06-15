// NBGPawn.cpp

#include "Player/NBGPawn.h"
#include "CH04NBG.h" 

void ANBGPawn::BeginPlay()
{
	Super::BeginPlay();
	
	FString NetRoleString = CH04NBGFunctionLibrary::GetRoleString(this);
	FString CombinedString = FString::Printf(TEXT("NBGPawn::BeginPlay() %s [%s]"), *CH04NBGFunctionLibrary::GetNetModeString(this), *NetRoleString);
	CH04NBGFunctionLibrary::MyPrintString(this, CombinedString, 10.f);
}

void ANBGPawn::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
	
	FString NetRoleString = CH04NBGFunctionLibrary::GetRoleString(this);
	FString CombinedString = FString::Printf(TEXT("NBGPawn::PossessedBy() %s [%s]"), *CH04NBGFunctionLibrary::GetNetModeString(this), *NetRoleString);
	CH04NBGFunctionLibrary::MyPrintString(this, CombinedString, 10.f);
}
