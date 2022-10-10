#pragma once

#include "CoreMinimal.h"

#include "Widgets/SCompoundWidget.h"
#include "Widgets/Input/SNumericEntryBox.h"
#include "Input/Reply.h"

#include "../Terrain/TerrainModifier.h"

class STerrainGenerate;
class STerrainDetails;

class STabWidgetMain : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(STabWidgetMain) :
		_isVisible(true),
		_modifierInstance()
	{
	}
		SLATE_ARGUMENT(bool, isVisible)
		SLATE_ARGUMENT(TSharedPtr<FTerrainModifier>, modifierInstance)
	SLATE_END_ARGS()

	void Construct(const FArguments& InArgs);

private:
	// layout of the widgets
	void constructWidget();

private:
	bool isVisible;

protected:

	TSharedPtr<STerrainGenerate> terrainGenerateTab;
	TSharedPtr<STerrainDetails> terrainDetailsTab;

protected:
	// Terrain Modifier Instance
	TSharedPtr<FTerrainModifier> ModifierInstance;
};
