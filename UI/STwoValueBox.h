#pragma once

#include "CoreMinimal.h"
#include "Widgets/SCompoundWidget.h"

#include "Delegates/Delegate.h"
#include "Input/Reply.h"

class STwoValueBox : public SCompoundWidget
{
public:

	// delegates for commit
	DECLARE_DELEGATE_TwoParams(FOnInt32ValueCommitted, int32, ETextCommit::Type);

	// delegates for get value
	DECLARE_DELEGATE(FOnInt32GetValueDelegate);

public:
	SLATE_BEGIN_ARGS(STwoValueBox)
	{
	}

	SLATE_ARGUMENT(FText, TitleText);

	SLATE_EVENT(FOnInt32ValueCommitted, OnFirstValueCommittedDelegate)
	SLATE_EVENT(FOnInt32ValueCommitted, OnSecondValueCommittedDelegate)
	SLATE_EVENT(FSimpleDelegate, GetFirstValueDelegate)
	SLATE_EVENT(FSimpleDelegate, GetSecondValueDelegate)

	SLATE_END_ARGS()

public:
	void Construct(const FArguments& InArgs);
	~STwoValueBox();

public:
	void OnFirstValueCommitted(int32 NewValue, ETextCommit::Type CommitInfo);
	void OnSecondValueCommited(int32 NewValue, ETextCommit::Type CommitInfo);

	TOptional<int32> GetFirstValue() const;
	TOptional<int32> GetSecondValue() const;

private:
	FText titleText;

	int32 firstValue;
	int32 secondValue;

private:
	FSimpleDelegate GetFirstValueDelegate;
	FSimpleDelegate GetSecondValueDelegate;

	FOnInt32ValueCommitted OnFirstValueCommittedDelegate;
	FOnInt32ValueCommitted OnSecondValueCommittedDelegate;
private:
	void constructWidgets();

};
