// Copyright Epic Games, Inc. All Rights Reserved.

#include "TerrainGeneratorCommands.h"

#define LOCTEXT_NAMESPACE "FTerrainGeneratorModule"

void FTerrainGeneratorCommands::RegisterCommands()
{
	UI_COMMAND(OpenPluginWindow, "TerrainGenerator", "Bring up TerrainGenerator window", EUserInterfaceActionType::Button, FInputChord());
}

#undef LOCTEXT_NAMESPACE
