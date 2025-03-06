// Copyright Epic Games, Inc. All Rights Reserved.

#include "ue5flecsGameMode.h"
#include "ue5flecsPlayerController.h"
#include "ue5flecsCharacter.h"
#include "UObject/ConstructorHelpers.h"

Aue5flecsGameMode::Aue5flecsGameMode()
{
	// use our custom PlayerController class
	PlayerControllerClass = Aue5flecsPlayerController::StaticClass();

	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/TopDown/Blueprints/BP_TopDownCharacter"));
	if (PlayerPawnBPClass.Class != nullptr)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}

	// set default controller to our Blueprinted controller
	static ConstructorHelpers::FClassFinder<APlayerController> PlayerControllerBPClass(TEXT("/Game/TopDown/Blueprints/BP_TopDownPlayerController"));
	if(PlayerControllerBPClass.Class != NULL)
	{
		PlayerControllerClass = PlayerControllerBPClass.Class;
	}
}