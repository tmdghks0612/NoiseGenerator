#pragma once
#include "CoreMinimal.h"
#include "UObject/ObjectMacros.h"

class FTerrainModifier : public TSharedFromThis<FTerrainModifier>
{
public:
	FTerrainModifier();

	~FTerrainModifier();

public:
	// Get & Set inline functions
	inline int32 GetMinHeight() { return minHeight; }
	inline int32 GetMaxHeight() { return maxHeight; }

	inline void SetMinHeight(int32 InValue) { minHeight = InValue; }
	inline void SetMaxHeight(int32 InValue) { maxHeight = InValue; }

public:

	// TODO : Random Noise Generate
	void GenerateRandomNoise();

private:
	int32 minHeight;
	int32 maxHeight;

};
