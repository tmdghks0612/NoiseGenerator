#include "PluginMainTab.h"

TSharedRef<SDockTab> SPluginMainTab::ConstructMainTab()
{
	return SNew(SDockTab)
		.TabRole(ETabRole::NomadTab)
		[
			SNew(SScrollBox)
			+ SScrollBox::Slot()
		.VAlign(VAlign_Fill)
		.Padding(5.f)
		[
			SNew(SVerticalBox)
			+ SVerticalBox::Slot()
		.VAlign(VAlign_Top)
		.Padding(0.f, 5.f, 0.f, 0.f)
		[
			SNew(STextBlock)
			.Text(FText::FromString(TEXT("Terrain Generator")))
		]
		+ SVerticalBox::Slot()
		.VAlign(VAlign_Center)
		.Padding(5.f)
		[
			SNew(SHorizontalBox)

		// Slot 1
			+ SHorizontalBox::Slot()
		.VAlign(VAlign_Center)
		.Padding(5.f)
		[
			// HorizontalBox to contain slot widgets (buttons, text etc..)
			SNew(STextBlock)
			.Text(FText::FromString(TEXT("Slot 1")))
		]

		// Slot 2
			+ SHorizontalBox::Slot()
		.VAlign(VAlign_Center)
		.Padding(5.f)
		[
			SNew(STextBlock)
			.Text(FText::FromString(TEXT("Slot 2")))
		]

		// Slot 3
			+ SHorizontalBox::Slot()
		.VAlign(VAlign_Center)
		.Padding(5.f)
		[
			SNew(STextBlock)
			.Text(FText::FromString(TEXT("Slot 3")))
		]

		// Slot 4
			+ SHorizontalBox::Slot()
		.VAlign(VAlign_Center)
		.Padding(5.f)
		[
			SNew(STextBlock)
			.Text(FText::FromString(TEXT("Slot 4")))
		]
		]
		]
		];

}
