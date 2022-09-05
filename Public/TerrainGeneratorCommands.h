// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Framework/Commands/Commands.h"
#include "TerrainGeneratorStyle.h"

class FTerrainGeneratorCommands : public TCommands<FTerrainGeneratorCommands>
{
public:

	FTerrainGeneratorCommands()
		: TCommands<FTerrainGeneratorCommands>(TEXT("TerrainGenerator"), NSLOCTEXT("Contexts", "TerrainGenerator", "TerrainGenerator Plugin"), NAME_None, FTerrainGeneratorStyle::GetStyleSetName())
	{
	}

	// TCommands<> interface
	virtual void RegisterCommands() override;

public:
	TSharedPtr< FUICommandInfo > OpenPluginWindow;
};