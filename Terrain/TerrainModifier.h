#pragma once
#include "CoreMinimal.h"
#include "UObject/ObjectMacros.h"

class FTerrainModifier : public TSharedFromThis<FTerrainModifier>
{
public:
	FTerrainModifier();

	~FTerrainModifier();

public:
	// TODO : Random Noise Generate
	void GenerateRandomNoise();

private:
	int32 minHeight;
	int32 maxHeight;

};
