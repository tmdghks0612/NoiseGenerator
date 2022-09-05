// Copyright Epic Games, Inc. All Rights Reserved.

#include "TerrainGenerator.h"
#include "TerrainGeneratorStyle.h"
#include "TerrainGeneratorCommands.h"
#include "LevelEditor.h"
#include "Widgets/Docking/SDockTab.h"
#include "Widgets/Layout/SBox.h"
#include "Widgets/Text/STextBlock.h"
#include "ToolMenus.h"

static const FName TerrainGeneratorTabName("TerrainGenerator");

#define LOCTEXT_NAMESPACE "FTerrainGeneratorModule"

void FTerrainGeneratorModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
	
	FTerrainGeneratorStyle::Initialize();
	FTerrainGeneratorStyle::ReloadTextures();

	FTerrainGeneratorCommands::Register();
	
	PluginCommands = MakeShareable(new FUICommandList);

	PluginCommands->MapAction(
		FTerrainGeneratorCommands::Get().OpenPluginWindow,
		FExecuteAction::CreateRaw(this, &FTerrainGeneratorModule::PluginButtonClicked),
		FCanExecuteAction());

	UToolMenus::RegisterStartupCallback(FSimpleMulticastDelegate::FDelegate::CreateRaw(this, &FTerrainGeneratorModule::RegisterMenus));
	
	FGlobalTabmanager::Get()->RegisterNomadTabSpawner(TerrainGeneratorTabName, FOnSpawnTab::CreateRaw(this, &FTerrainGeneratorModule::OnSpawnPluginTab))
		.SetDisplayName(LOCTEXT("FTerrainGeneratorTabTitle", "TerrainGenerator"))
		.SetMenuType(ETabSpawnerMenuType::Hidden);
}

void FTerrainGeneratorModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.

	UToolMenus::UnRegisterStartupCallback(this);

	UToolMenus::UnregisterOwner(this);

	FTerrainGeneratorStyle::Shutdown();

	FTerrainGeneratorCommands::Unregister();

	FGlobalTabmanager::Get()->UnregisterNomadTabSpawner(TerrainGeneratorTabName);
}

TSharedRef<SDockTab> FTerrainGeneratorModule::OnSpawnPluginTab(const FSpawnTabArgs& SpawnTabArgs)
{
	return SPluginMainTab::ConstructMainTab();

	/*
 
 FText WidgetText = FText::Format(
		LOCTEXT("WindowWidgetText", "Add code to {0} in {1} to override this window's contents"),
		FText::FromString(TEXT("FTerrainGeneratorModule::OnSpawnPluginTab")),
		FText::FromString(TEXT("TerrainGenerator.cpp"))
		);

	return SNew(SDockTab)
		.TabRole(ETabRole::NomadTab)
		[
			// Put your tab content here!
			SNew(SBox)
			.HAlign(HAlign_Center)
			.VAlign(VAlign_Center)
			[
				SNew(STextBlock)
				.Text(WidgetText)
			]
		];
		*/
}

void FTerrainGeneratorModule::PluginButtonClicked()
{
	FGlobalTabmanager::Get()->TryInvokeTab(TerrainGeneratorTabName);
}

void FTerrainGeneratorModule::RegisterMenus()
{
	// Owner will be used for cleanup in call to UToolMenus::UnregisterOwner
	FToolMenuOwnerScoped OwnerScoped(this);

	{
		UToolMenu* Menu = UToolMenus::Get()->ExtendMenu("LevelEditor.MainMenu.Window");
		{
			FToolMenuSection& Section = Menu->FindOrAddSection("WindowLayout");
			Section.AddMenuEntryWithCommandList(FTerrainGeneratorCommands::Get().OpenPluginWindow, PluginCommands);
		}
	}

	{
		UToolMenu* ToolbarMenu = UToolMenus::Get()->ExtendMenu("LevelEditor.LevelEditorToolBar");
		{
			FToolMenuSection& Section = ToolbarMenu->FindOrAddSection("Settings");
			{
				FToolMenuEntry& Entry = Section.AddEntry(FToolMenuEntry::InitToolBarButton(FTerrainGeneratorCommands::Get().OpenPluginWindow));
				Entry.SetCommandList(PluginCommands);
			}
		}
	}
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FTerrainGeneratorModule, TerrainGenerator)