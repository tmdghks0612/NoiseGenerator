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

private:
	void constructWidgets();

protected:

	FReply OnGenerateTerrainButtonClicked();

protected:
	// min max height input TextBox widget
	TSharedPtr<SNumericEntryBox<int32>> minHeightEntryBox;
	TSharedPtr<SEditableTextBox> maxHeightTextBox;

	TSharedPtr<SButton> GenerateTerrainButton;

protected:
	TSharedPtr<FTerrainModifier> ModifierInstance;
};
