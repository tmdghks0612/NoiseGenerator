#include "TerrainModifier.h"

#define LOCTEXT_NAMESPACE "FTerrainModifier"

FTerrainModifier::FTerrainModifier()
	: minHeight(0)
{
}

FTerrainModifier::~FTerrainModifier()
{
}
void FTerrainModifier::GenerateRandomNoise()
{
	// TODO : example log print for debug
	minHeight++;
	UE_LOG(LogTemp, Log, TEXT("minHeight : %d"), minHeight)
}

#undef LOCTEXT_NAMESPACE