#include "TabWidget.h"

#include "STerrainDetails.h"
#include "STerrainGenerate.h"

#define LOCTEXT_NAMESPACE "STabWidgetMain"

void STabWidgetMain::Construct(const FArguments& InArgs)
{
	isVisible = InArgs._isVisible;

	ModifierInstance = InArgs._modifierInstance;
	
	//ModifierInstance = MakeShared();

	constructWidget();
}

void STabWidgetMain::constructWidget()
{
	ChildSlot
	[
		SNew(SHorizontalBox)
		+ SHorizontalBox::Slot()
		.HAlign(HAlign_Center)
		[
			SAssignNew(terrainGenerateTab, STerrainGenerate)
			.isVisible(true)
			.modifierInstance(ModifierInstance)
		]
		+ SHorizontalBox::Slot()
		.HAlign(HAlign_Center)
		[
			// TODO : pass ModifierInstance as SLATE_ARGUMENT
			SAssignNew(terrainDetailsTab, STerrainDetails)
			.modifierInstance(ModifierInstance)
		]
	];
}

#undef LOCTEXT_NAMESPACE
