#pragma once

#include "CoreMinimal.h"
#include "Layout/Visibility.h"
#include "Widgets/SCompoundWidget.h"
#include "Input/Reply.h"

#include "../Terrain/TerrainModifier.h"

class STerrainGenerate : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(STerrainGenerate)
	:	_isVisible(true),
		_modifierInstance()
	{
	}

	SLATE_ARGUMENT(bool, isVisible)
	SLATE_ARGUMENT(TSharedPtr<FTerrainModifier>, modifierInstance)

	SLATE_END_ARGS()

		void Construct(const FArguments& InArgs);
	~STerrainGenerate();

public:
	void OnMinHeightCommitted(int32 NewValue, ETextCommit::Type CommitInfo);
	void OnMaxHeightCommitted(int32 NewValue, ETextCommit::Type CommitInfo);
	
	void OnTerrainXSizeCommitted(int32 NewValue, ETextCommit::Type CommitInfo);
	void OnTerrainYSizeCommitted(int32 NewValue, ETextCommit::Type CommitInfo);

	void OnBumpinessCommitted(int32 NewValue, ETextCommit::Type CommitInfo);

private:
	void constructWidgets();

	TOptional<int32> OnGetMinHeightValue() const;
	TOptional<int32> OnGetMaxHeightValue() const;

	TOptional<int32> OnGetTerrainXSizeValue() const;
	TOptional<int32> OnGetTerrainYSizeValue() const;

	TOptional<int32> OnGetBumpiness() const;

protected:

	FReply OnGenerateTerrainOriginalButtonClicked();

protected:
	TSharedPtr<SButton> GenerateTerrainButton;

protected:
	TWeakPtr<FTerrainModifier> ModifierInstance;
};
