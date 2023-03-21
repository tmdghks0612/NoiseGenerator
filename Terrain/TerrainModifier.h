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
	inline int32 GetMinHeight() { return _minHeight; }
	inline int32 GetMaxHeight() { return _maxHeight; }
	
	inline int32 GetTerrainXSize() { return _terrainXSize; }
	inline int32 GetTerrainYSize() { return _terrainYSize; }

	inline int32 GetBumpiness() { return _bumpiness; }

	inline void SetMinHeight(int32 InValue) { _minHeight = InValue; }
	inline void SetMaxHeight(int32 InValue) { _maxHeight = InValue; }

	inline void SetTerrainXSize(int32 InValue) { _terrainXSize = InValue; }
	inline void SetTerrainYSize(int32 InValue) { _terrainYSize = InValue; }

	inline void SetBumpiness(int32 InValue) { _bumpiness = InValue; }

public:

	void InitTerrain2DArray();

	// UTexture2D::CreateTransient using custom path
	void InitTexturePackage(FString pathName, FString packageName);

	// Random Noise to default array for texture output
	void GenerateRandomNoiseTexture();

	static void GenerateRandomNoiseArray(int32 xSize, int32 ySize, float genMinHeight, float genMaxHeight, int32 genBumpiness, TArray<float>& outArray);

	void GeneratePerlinNoiseOriginal();
	void GeneratePerlinNoiseCell();

private:
	// map array by input height range
	static void ClampArrayByHeightRange(const float mapMinHeight, const float mapMaxHeight, TArray<float>& inputTerrain2DArray);

	// create random noise for given cell size
	void GenerateRandomTerrain2DArrayByCellSize(const float interpolationAlpha, const int32 amplitude, const float frequency, const float startNoise);

	static void GenerateRandomTerrain2DArray(const float xSize, const float ySize, const float interpolationAlpha, const int32 amplitude, const float frequency, const float startNoise, TArray<float>& outArray);

	// create a textrue from values of terrain2DArray
	void GenerateTextureByTerrain2DArray();

	// create raw image data by cell size
	void GenerateRawImage();

	// V2

	// generate random values for cell array
	void GenerateRandomCellArray(const int32 xySize, const uint8 cellSize);

	// set values of fade functions, used for every cell
	void SetFadeArray(const uint8 cellSize, float(*fade)(float));

	void InterpolateCell();

	void InterpolateCellByBinary();


	int8 GetPowerOfCellSize(uint8 cellSize);

	static float PseudoSine(float input);

private:
	int32 _minHeight;
	int32 _maxHeight;

	int32 _terrainXSize;
	int32 _terrainYSize;

	int32 _terrainXYSize;

	int32 _bumpiness;

	int32 _cellXSize;
	int32 _cellYSize;

	int32 _pow;

	ECellSize::Type _cellSize;

	UPROPERTY()
	TArray<float> terrain2DArray;
	UPROPERTY()
	TArray<float> octaveArray;
	UPROPERTY()
	TArray<int8> terrainRawImageData;

	UPROPERTY()
	TArray<int32> cellArray;
	UPROPERTY()
	TArray<float> fadeArray;
};
