#pragma once
#include "CoreMinimal.h"
#include "UObject/ObjectMacros.h"

#define TEXTURE_DEFAULT_X_SIZE 2048
#define TEXTURE_DEFAULT_Y_SIZE 2048

#define OCTAVE_FADE_MIN_RATE 1.5f
#define OCTAVE_FADE_MAX_RATE 2.0f

namespace ECellSize
{
	enum Type : uint8
	{
		CellBy4 = 0x4,
		CellBy8 = 0x8,
		CellBy16 = 0x10
	};
}
class FTerrainModifier : public TSharedFromThis<FTerrainModifier>
{

public:
	FTerrainModifier();

	~FTerrainModifier();

public:
	// Get & Set inline functions
	inline int32 GetMinHeight() { return minHeight; }
	inline int32 GetMaxHeight() { return maxHeight; }
	
	inline int32 GetTerrainXSize() { return terrainXSize; }
	inline int32 GetTerrainYSize() { return terrainYSize; }

	inline int32 GetBumpiness() { return bumpiness; }

	inline void SetMinHeight(int32 InValue) { minHeight = InValue; }
	inline void SetMaxHeight(int32 InValue) { maxHeight = InValue; }

	inline void SetTerrainXSize(int32 InValue) { terrainXSize = InValue; }
	inline void SetTerrainYSize(int32 InValue) { terrainYSize = InValue; }

	inline void SetBumpiness(int32 InValue) { bumpiness = InValue; }

public:

	void InitTerrain2DArray();

	// UTexture2D::CreateTransient using custom path
	void InitTexturePackage(FString pathName, FString packageName);

	// TODO : Random Noise Generate
	void GenerateRandomNoiseTexture();

private:
	// map array by input height range
	void MapArrayByHeightRange();

	// create random noise for given cell size
	void GenerateRandomTerrain2DArrayByCellSize(const float interpolationAlpha, const int32 amplitude, const float frequency);

	// create a textrue from values of terrain2DArray
	void GenerateTextureByTerrain2DArray();

	// create raw image data by cell size
	void GenerateRawImage();


private:
	int32 minHeight;
	int32 maxHeight;

	int32 terrainXSize;
	int32 terrainYSize;

	int32 terrainXYSize;

	int32 bumpiness;

	ECellSize::Type cellSize;

	UPROPERTY()
	TArray<float> terrain2DArray;
	UPROPERTY()
	TArray<float> octaveArray;
	UPROPERTY()
	TArray<int8> terrainRawImageData;
};
