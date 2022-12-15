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
		.Padding(0.5f, 0.5f, 0.5f, 0.5f)
		[
			SAssignNew(terrainGenerateTab, STerrainGenerate)
			.isVisible(true)
			.modifierInstance(ModifierInstance.Pin())
		]
		/* [2022/12/15 tmdghks0612] terrain details tab is not ready to be updated
		+ SHorizontalBox::Slot()
		.HAlign(HAlign_Center)
		[
			// TODO : pass ModifierInstance as SLATE_ARGUMENT
			SAssignNew(terrainDetailsTab, STerrainDetails)
			.modifierInstance(ModifierInstance.Pin())
		]
		*/
	];
}

#undef LOCTEXT_NAMESPACE
