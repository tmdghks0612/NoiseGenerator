#include "TerrainModifier.h"

#define LOCTEXT_NAMESPACE "FTerrainModifier"

FTerrainModifier::FTerrainModifier()
	: minHeight(0),
	maxHeight(0)
{
}

FTerrainModifier::~FTerrainModifier()
{
}
void FTerrainModifier::GenerateRandomNoise()
{
	// TODO : example log print for debug
	UE_LOG(LogTemp, Log, TEXT("[FTerrianModifier] minHeight : %d, maxHeight : %d"), minHeight, maxHeight)
}

#undef LOCTEXT_NAMESPACE