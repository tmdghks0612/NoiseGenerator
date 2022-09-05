#include "SlotWidget.h"

SBoxPanel::FSlot::FSlotArguments SSlotWidget::ConstructTextSlot(FString inputStr)
{
	return  SNew(STextBlock).Text(FText::FromString(inputString)));
}
