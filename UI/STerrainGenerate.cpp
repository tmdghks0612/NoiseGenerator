#include "STerrainGenerate.h"

#include "../Terrain/TerrainModifier.h"
#include "STwoValueBox.h"

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
	const int32 ClampValue = FMath::Clamp<int32>(NewValue, 0, 32767);

	if (ModifierInstance.IsValid())
	{
		ModifierInstance.Pin()->SetMinHeight(ClampValue);
	}
}

void STerrainGenerate::OnMaxHeightCommitted(int32 NewValue, ETextCommit::Type CommitInfo)
{
	const int32 ClampValue = FMath::Clamp<int32>(NewValue, 0, 32767);

	if (ModifierInstance.IsValid())
	{
		ModifierInstance.Pin()->SetMaxHeight(ClampValue);
	}
}

void STerrainGenerate::OnTerrainXSizeCommitted(int32 NewValue, ETextCommit::Type CommitInfo)
{
	const int32 ClampValue = FMath::Clamp<int32>(NewValue, 0, 32767);

	if (ModifierInstance.IsValid())
	{
		ModifierInstance.Pin()->SetTerrainXSize(ClampValue);
	}
}

void STerrainGenerate::OnTerrainYSizeCommitted(int32 NewValue, ETextCommit::Type CommitInfo)
{
	const int32 ClampValue = FMath::Clamp<int32>(NewValue, 0, 32767);

	if (ModifierInstance.IsValid())
	{
		ModifierInstance.Pin()->SetTerrainYSize(ClampValue);
	}
}

void STerrainGenerate::OnBumpinessCommitted(int32 NewValue, ETextCommit::Type CommitInfo)
{
	const int32 ClampValue = FMath::Clamp<int32>(NewValue, 0, 32767);

	if (ModifierInstance.IsValid())
	{
		ModifierInstance.Pin()->SetBumpiness(ClampValue);
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
		.Padding(0.5f, 0.5f, 0.5f, 0.f)
		[
			SNew(STwoValueBox)
			.TitleText(FText::FromString("Terrain XY Size"))
			.OnFirstValueCommittedDelegate(this, &STerrainGenerate::OnTerrainXSizeCommitted)
			.OnSecondValueCommittedDelegate(this, &STerrainGenerate::OnTerrainYSizeCommitted)
		]
		+ SVerticalBox::Slot()
		.AutoHeight()
		.VAlign(VAlign_Top)
		.Padding(0.5f, 0.5f, 0.5f, 0.f)
		[
			SNew(STwoValueBox)
			.TitleText(FText::FromString("Min/Max Height"))
			.OnFirstValueCommittedDelegate(this, &STerrainGenerate::OnMinHeightCommitted)
			.OnSecondValueCommittedDelegate(this, &STerrainGenerate::OnMaxHeightCommitted)
		]
		+ SVerticalBox::Slot()
		.AutoHeight()
		.VAlign(VAlign_Top)
		.Padding(0.5f, 0.5f, 0.5f, 0.f)
		[
			SNew(STextBlock)
			.Text(FText::FromString("Bumpiness"))
		]
		+ SVerticalBox::Slot()
		.AutoHeight()
		.VAlign(VAlign_Top)
		.Padding(0.5f, 0.5f, 0.5f, 0.5f)
		[
			SNew(SNumericEntryBox<int32>)
			.OnValueCommitted(this, &STerrainGenerate::OnBumpinessCommitted)
			.Value(this, &STerrainGenerate::OnGetBumpiness)
		]
		+ SVerticalBox::Slot()
		.AutoHeight()
		.VAlign(VAlign_Top)
		[
			SNew(SButton)
			.OnClicked(this, &STerrainGenerate::OnGenerateTerrainOriginalButtonClicked)
			[
				SNew(STextBlock)
				.Text(FText(LOCTEXT("GenerateTerrainButtonText", "Generate Terrain2D")))
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

TOptional<int32> STerrainGenerate::OnGetTerrainXSizeValue() const
{
	if (ModifierInstance.IsValid())
	{
		return ModifierInstance.Pin()->GetTerrainXSize();
	}
	return 0;
}

TOptional<int32> STerrainGenerate::OnGetTerrainYSizeValue() const
{
	if (ModifierInstance.IsValid())
	{
		return ModifierInstance.Pin()->GetTerrainYSize();
	}
	return 0;
}

TOptional<int32> STerrainGenerate::OnGetBumpiness() const
{
	if (ModifierInstance.IsValid())
	{
		return ModifierInstance.Pin()->GetBumpiness();
	}
	return 0;
}

FReply STerrainGenerate::OnGenerateTerrainOriginalButtonClicked()
{
	if(false == ModifierInstance.IsValid())
		UE_LOG(LogTemp, Warning, TEXT("[TerrainGenerate] : initialized instance pointer invalid"));

	ModifierInstance.Pin()->GeneratePerlinNoiseOriginal();
	return FReply::Handled();
}

#undef LOCTEXT_NAMESPACE
