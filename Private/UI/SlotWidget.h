#pragma once

#include "CoreMinimal.h"

#include "Widgets/SBoxPanel.h"

class SSlotWidget
{
public:
	// not using...
	static SBoxPanel::FSlot::FSlotArguments ConstructTextSlot(FString inputStr);
	static SBoxPanel::FSlot::FSlotArguments ConstructButtonSlot();
};