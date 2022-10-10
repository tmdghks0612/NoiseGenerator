#include "STerrainGenerate.h"

#include "../Terrain/TerrainModifier.h"

#define LOCTEXT_NAMESPACE "STerainGenerate.h"

void STerrainGenerate::Construct(const FArguments& InArgs)
{
	ModifierInstance = InArgs._modifierInstance;

	constructWidgets();
}

STerrainGenerate::~STerrainGenerate()
{
}

void STerrainGenerate::constructWidgets()
{
	ChildSlot
	[
		SNew(SVerticalBox)
		+ SVerticalBox::Slot()
		.AutoHeight()
		.VAlign(VAlign_Top)
		[
			SAssignNew(minHeightEntryBox, SNumericEntryBox<int32>)
			//.HintText(FText(LOCTEXT("MinValue", "Min Height")))
		.MinDesiredValueWidth(10.f)
		]
		+ SVerticalBox::Slot()
		.AutoHeight()
		.VAlign(VAlign_Top)
		[
			SAssignNew(maxHeightTextBox, SEditableTextBox)
			.HintText(FText(LOCTEXT("MaxValue", "Max Height")))
		.MinDesiredWidth(10.f)
		]
		+ SVerticalBox::Slot()
		.AutoHeight()
		.VAlign(VAlign_Top)
		[
			SNew(SButton)
			.OnClicked(this, &STerrainGenerate::OnGenerateTerrainButtonClicked)
			[
				SNew(STextBlock)
				.Text(FText(LOCTEXT("GenerateTerrainButtonText", "Generate")))
			]
		]
	];
}

FReply STerrainGenerate::OnGenerateTerrainButtonClicked()
{
	if(false == ModifierInstance.IsValid())
		UE_LOG(LogTemp, Warning, TEXT("[TerrainGenerate] : initialized instance pointer invalid"));

	ModifierInstance->GenerateRandomNoise();
	return FReply::Handled();
}

#undef LOCTEXT_NAMESPACE
