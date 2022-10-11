#include "STerrainDetails.h"

#include "../Terrain/TerrainModifier.h"

#define LOCTEXT_NAMESPACE "STerrainDetails"

void STerrainDetails::Construct(const FArguments& InArgs)
{
	ModifierInstance = InArgs._modifierInstance;

	constructWidgets();
}

STerrainDetails::~STerrainDetails()
{
}

void STerrainDetails::constructWidgets()
{
	ChildSlot
		[
			SNew(SHorizontalBox)
			+ SHorizontalBox::Slot()
			.AutoWidth()
			.Padding(2.f)
			[
				SAssignNew(GenerateTerrainButton, SButton)
				.OnClicked(this, &STerrainDetails::OnGenerateTerrainButtonClicked)
			.ToolTipText(LOCTEXT("UpdateRevisionToolTip", "Updates the stored revision GUID on all instances of this Modifier class, marking them out-of-date."))
			.Text(LOCTEXT("UpdateRevisionText", "Update Revision"))
			]
		];
}

FReply STerrainDetails::OnGenerateTerrainButtonClicked()
{
	if (false == ModifierInstance.IsValid())
		UE_LOG(LogTemp, Warning, TEXT("[TerrainGenerate] : initialized instance pointer invalid"));

	ModifierInstance.Pin()->GenerateRandomNoise();
	return FReply::Handled();
}

#undef LOCTEXT_NAMESPACE
