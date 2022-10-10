// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"

#include "../UI/TabWidget.h"
#include "../Terrain/TerrainModifier.h"

class FToolBarBuilder;
class FMenuBuilder;

class FTerrainGeneratorModule : public IModuleInterface
{
public:

	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;

	/** This function will be bound to Command (by default it will bring up plugin window) */
	void PluginButtonClicked();
	
public:
	bool InitializeTerrainModifier();

private:

	void RegisterMenus();

	TSharedRef<class SDockTab> OnSpawnPluginTab(const class FSpawnTabArgs& SpawnTabArgs);

private:
	TSharedPtr<class FUICommandList> PluginCommands;

	TSharedPtr<FTerrainModifier> TerrainModifier;
	//TSharedPtr<SGenerateTerrainTab> generateTerrainTab;
};
