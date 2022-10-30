#include "STwoValueBox.h"

#define LOCTEXT_NAMESPACE "STwoValueBox.h"

void STwoValueBox::Construct(const FArguments& InArgs)
{
	titleText = InArgs._TitleText;

	OnFirstValueCommittedDelegate = InArgs._OnFirstValueCommittedDelegate;
	OnSecondValueCommittedDelegate = InArgs._OnSecondValueCommittedDelegate;
	GetFirstValueDelegate = InArgs._GetFirstValueDelegate;
	GetSecondValueDelegate = InArgs._GetSecondValueDelegate;

	constructWidgets();
}

STwoValueBox::~STwoValueBox()
{
}

void STwoValueBox::OnFirstValueCommitted(int32 NewValue, ETextCommit::Type CommitInfo)
{
	OnFirstValueCommittedDelegate.ExecuteIfBound(NewValue, CommitInfo);

	firstValue = NewValue;
}

void STwoValueBox::OnSecondValueCommited(int32 NewValue, ETextCommit::Type CommitInfo)
{
	OnSecondValueCommittedDelegate.ExecuteIfBound(NewValue, CommitInfo);

	secondValue = NewValue;
}

TOptional<int32> STwoValueBox::GetFirstValue() const
{
	GetFirstValueDelegate.ExecuteIfBound();

	return firstValue;
}

TOptional<int32> STwoValueBox::GetSecondValue() const
{
	GetSecondValueDelegate.ExecuteIfBound();

	return secondValue;
}

void STwoValueBox::constructWidgets()
{
	ChildSlot
	[
		SNew(SVerticalBox)
		+ SVerticalBox::Slot()
		.AutoHeight()
		.VAlign(VAlign_Top)
		[
			SNew(STextBlock)
			.Text(titleText)
		]
		+ SVerticalBox::Slot()
		.AutoHeight()
		.VAlign(VAlign_Top)
		[
			SNew(SNumericEntryBox<int32>)
			.OnValueCommitted(this, &STwoValueBox::OnFirstValueCommitted)
			.Value(this, &STwoValueBox::GetFirstValue)
		]
		+ SVerticalBox::Slot()
		.AutoHeight()
		.VAlign(VAlign_Top)
		[
			SNew(SNumericEntryBox<int32>)
			.OnValueCommitted(this, &STwoValueBox::OnSecondValueCommited)
			.Value(this, &STwoValueBox::GetSecondValue)
		]
	];
}

#undef LOCTEXT_NAMESPACE
