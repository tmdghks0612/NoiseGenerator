#pragma once

#include "CoreMinimal.h"
#include "Widgets/Docking/SDockTab.h"

#include "Widgets/Layout/SScrollBox.h"
#include "Widgets/SBoxPanel.h"

#include "SlotWidget.h"

class SPluginMainTab : public SBoxPanel
{
public:
	static TSharedRef<SDockTab> ConstructMainTab();


};