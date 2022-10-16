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

void STerrainGenerate::OnMinHeightCommitted(int32 NewValue, ETextCommit::Type CommitInfo)
{
	const int32 ClampValue = FMath::Clamp<int32>(NewValue, 0, 65536);

	if (ModifierInstance.IsValid())
	{
		ModifierInstance.Pin()->SetMinHeight(ClampValue);
	}
}

void STerrainGenerate::OnMaxHeightCommitted(int32 NewValue, ETextCommit::Type CommitInfo)
{
	const int32 ClampValue = FMath::Clamp<int32>(NewValue, 0, 65536);

	if (ModifierInstance.IsValid())
	{
		ModifierInstance.Pin()->SetMaxHeight(ClampValue);
	}
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
			SNew(SNumericEntryBox<int32>)
			.OnValueCommitted(this, &STerrainGenerate::OnMinHeightCommitted)
			.Value(this, &STerrainGenerate::OnGetMinHeightValue)
		]
		+ SVerticalBox::Slot()
		.AutoHeight()
		.VAlign(VAlign_Top)
		[
			SNew(SNumericEntryBox<int32>)
			.OnValueCommitted(this, &STerrainGenerate::OnMaxHeightCommitted)
			.Value(this, &STerrainGenerate::OnGetMaxHeightValue)
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

TOptional<int32> STerrainGenerate::OnGetMinHeightValue() const
{
	if (ModifierInstance.IsValid())
	{
		return ModifierInstance.Pin()->GetMinHeight();
	}
	return 0;
}

TOptional<int32> STerrainGenerate::OnGetMaxHeightValue() const
{
	if (ModifierInstance.IsValid())
	{
		return ModifierInstance.Pin()->GetMaxHeight();
	}
	return 0;
}

FReply STerrainGenerate::OnGenerateTerrainButtonClicked()
{
	if(false == ModifierInstance.IsValid())
		UE_LOG(LogTemp, Warning, TEXT("[TerrainGenerate] : initialized instance pointer invalid"));

	ModifierInstance.Pin()->GenerateRandomNoise();
	return FReply::Handled();
}

#undef LOCTEXT_NAMESPACE
