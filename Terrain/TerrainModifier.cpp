#include "TerrainModifier.h"

#include "Engine/Texture2D.h"
#include "UObject/UObjectGlobals.h"

#include <random>

#define LOCTEXT_NAMESPACE "FTerrainModifier"

FTerrainModifier::FTerrainModifier()
	: minHeight(0),
	maxHeight(0),
	terrainXSize(0),
	terrainYSize(0),
	terrainXYSize(0),
	bumpiness(0),
	cellSize(ECellSize::Type::CellBy4)
{
}

FTerrainModifier::~FTerrainModifier()
{
}

void FTerrainModifier::InitTerrain2DArray()
{
	terrain2DArray.Empty();

	// max value of multiply x and y
	terrainXYSize = FMath::Clamp<int32>(terrainXSize * terrainYSize, 0, 1073676289);

	// initialize 2DArray by size
	terrain2DArray.Init(0, terrainXYSize);

	// initialize 2DArray by size
	octaveArray.Init(0, terrainXYSize);

	// initialize RawImageData by size*4(RGBA)
	terrainRawImageData.Init(0, terrainXYSize * 4);
}

void FTerrainModifier::InitTexturePackage(FString pathName, FString packageName)
{
	
	UTexture2D* NewTexture = nullptr;
	if (terrainXSize > 0 && terrainYSize > 0)
	{
		// create package
		pathName.Append(packageName);
		UPackage* PackagePtr = CreatePackage(*pathName);

		FName TextureName = MakeUniqueObjectName(PackagePtr, UTexture2D::StaticClass(), FName(*packageName));

		NewTexture = NewObject<UTexture2D>(
			PackagePtr,
			TextureName,
			RF_Public | RF_Standalone
			);

		NewTexture->SetPlatformData(new FTexturePlatformData());
		NewTexture->GetPlatformData()->SizeX = terrainXSize;
		NewTexture->GetPlatformData()->SizeY = terrainYSize;
		NewTexture->GetPlatformData()->PixelFormat = PF_R8G8B8A8;

		// Allocate first mipmap.
		FTexture2DMipMap* Mip = new FTexture2DMipMap();
		NewTexture->GetPlatformData()->Mips.Add(Mip);
		Mip->SizeX = terrainXSize;
		Mip->SizeY = terrainYSize;

		Mip->BulkData.Lock(LOCK_READ_WRITE);

		// using only PF_R8G8B8A8, where block size of x,y is 1.
		void* TextureData = Mip->BulkData.Realloc(terrainRawImageData.Num());
		FMemory::Memcpy(TextureData, terrainRawImageData.GetData(), terrainRawImageData.Num());

		Mip->BulkData.Unlock();
		
		// Updating Texture & mark it as unsaved
		NewTexture->AddToRoot();
		NewTexture->UpdateResource();
		PackagePtr->MarkPackageDirty();

		UE_LOG(LogTexture, Log, TEXT("terrain texture created: %s"), *packageName);
	}
	else
	{
		UE_LOG(LogTexture, Warning, TEXT("Invalid parameters specified for UTexture2D::InitTexturePackage()"));
	}
	return;
}

void FTerrainModifier::GenerateRandomNoiseTexture()
{
	UE_LOG(LogTemp, Log, TEXT("[FTerrianModifier] minHeight : %d, maxHeight : %d"), minHeight, maxHeight);

	std::random_device rd;
	std::mt19937 generator(rd());

	std::uniform_real_distribution<double> fadeRandom(OCTAVE_FADE_MIN_RATE, OCTAVE_FADE_MAX_RATE);

	InitTerrain2DArray();

	double amplitude = FMath::RandRange(float(maxHeight / OCTAVE_FADE_MAX_RATE), float(maxHeight / OCTAVE_FADE_MIN_RATE));
	
	// determined by bigger size between x and y axis
	float standardSize = ((terrainXSize > terrainYSize) ? terrainXSize : terrainYSize);
	
	float frequency = float(bumpiness) / standardSize;

	float interpolationAlpha = 1.0f;

	// if frequency exceeds standardsize, every value starts to become uniform
	while (frequency < standardSize &&
		amplitude > 1.0f)
	{
		std::uniform_real_distribution<double> noiseRandom(-360.0f / frequency, 360.0f / frequency);

		GenerateRandomTerrain2DArrayByCellSize(interpolationAlpha, amplitude, frequency, noiseRandom(generator));

		float fadeRate = fadeRandom(generator);

		amplitude /= fadeRate;
		frequency *= fadeRate;
		interpolationAlpha /= fadeRate;
	}

	ClampArrayByHeightRange(minHeight, maxHeight, terrain2DArray);

	// set raw image data according to cell size according to terrain2DArray
	GenerateRawImage();

	// Generate 2D Texture
	GenerateTextureByTerrain2DArray();
}

void FTerrainModifier::GenerateRandomNoiseArray(int32 xSize, int32 ySize, float genMinHeight, float genMaxHeight, int32 genBumpiness, TArray<float>& outArray)
{
	if (xSize * ySize > 1073676289)
	{
		UE_LOG(LogTemp, Log, TEXT("[FTerrianModifier] minHeight : %d, maxHeight : %d. Size out of range 0~1073676289"), genMinHeight, genMaxHeight);
		return;
	}
	
	outArray.Init(0, xSize * ySize);
	
	std::random_device rd;
	std::mt19937 generator(rd());

	std::uniform_real_distribution<double> fadeRandom(OCTAVE_FADE_MIN_RATE, OCTAVE_FADE_MAX_RATE);

	double amplitude = FMath::RandRange(float(genMaxHeight / OCTAVE_FADE_MAX_RATE), float(genMaxHeight / OCTAVE_FADE_MIN_RATE));

	// determined by bigger size between x and y axis
	float standardSize = ((xSize > ySize) ? xSize : ySize);

	float frequency = float(genBumpiness) / standardSize;

	float interpolationAlpha = 1.0f;

	// if frequency exceeds standardsize, every value starts to become uniform
	while (frequency < standardSize &&
		amplitude > 1.0f)
	{
		std::uniform_real_distribution<double> noiseRandom(-360.0f / frequency, 360.0f / frequency);

		GenerateRandomTerrain2DArray(xSize, ySize, interpolationAlpha, amplitude, frequency, noiseRandom(generator), outArray);

		float fadeRate = fadeRandom(generator);

		amplitude /= fadeRate;
		frequency *= fadeRate;
		interpolationAlpha /= fadeRate;
	}

	ClampArrayByHeightRange(genMinHeight, genMaxHeight, outArray);
}

void FTerrainModifier::ClampArrayByHeightRange(const float clampMinHeight, const float clampMaxHeight, TArray<float>& inputTerrain2DArray)
{
	for (int32 arrayIndex = 0; arrayIndex < inputTerrain2DArray.Num(); ++arrayIndex)
	{
		inputTerrain2DArray[arrayIndex] = FMath::Clamp(inputTerrain2DArray[arrayIndex], clampMinHeight, clampMaxHeight);
	}
}

void FTerrainModifier::GenerateRandomTerrain2DArrayByCellSize(const float interpolationAlpha, const int32 amplitude, const float frequency, const float startNoise)
{
	for (int32 terrainYIndex = 0; terrainYIndex < terrainYSize; ++terrainYIndex)
	{
		for (int32 terrainXIndex = 0; terrainXIndex < terrainXSize; ++terrainXIndex)
		{
			octaveArray[terrainXSize * terrainYIndex + terrainXIndex] =
				amplitude *
				(FGenericPlatformMath::Sin(frequency * (double(terrainXIndex)) + startNoise) +
					FGenericPlatformMath::Sin(frequency * (double(terrainYIndex)) + startNoise) + 2) / 4;
		}
	}

	// interpolating octave array with decreasing
	for (int32 terrainIndex = 0; terrainIndex < terrainXYSize; ++terrainIndex)
	{
		terrain2DArray[terrainIndex] = FMath::Lerp(terrain2DArray[terrainIndex], octaveArray[terrainIndex], interpolationAlpha);
	}
}

void FTerrainModifier::GenerateRandomTerrain2DArray(const float xSize, const float ySize, const float interpolationAlpha, const int32 amplitude, const float frequency, const float startNoise, TArray<float>& outArray)
{
	TArray<float> tempOctaveArray;
	tempOctaveArray.Init(0, xSize * ySize);

	for (int32 terrainYIndex = 0; terrainYIndex < ySize; ++terrainYIndex)
	{
		for (int32 terrainXIndex = 0; terrainXIndex < xSize; ++terrainXIndex)
		{
			tempOctaveArray[xSize * terrainYIndex + terrainXIndex] =
				amplitude *
				(FGenericPlatformMath::Sin(frequency * (double(terrainXIndex)) + startNoise) +
					FGenericPlatformMath::Sin(frequency * (double(terrainYIndex)) + startNoise) + 2) / 4;
		}
	}

	// interpolating octave array with decreasing
	for (int32 terrainIndex = 0; terrainIndex < xSize * ySize; ++terrainIndex)
	{
		outArray[terrainIndex] = FMath::Lerp(outArray[terrainIndex], tempOctaveArray[terrainIndex], interpolationAlpha);
	}
}

void FTerrainModifier::GenerateTextureByTerrain2DArray()
{
	// package path and name
	FString pathPackage = FString("/Game/TerrainTextures/");
	FString textureFileName = FString("TerrainTexture");

	InitTexturePackage(pathPackage, textureFileName);
}

void FTerrainModifier::GenerateRawImage()
{
	for (int32 terrainIndex = 0; terrainIndex < terrainXYSize; ++terrainIndex)
	{
		// conversion according to texture format
		// amplitude halves, therefore leading to max value of maxHeight (according to geometric series)
		// the probability of getting max value is very low. make visualizing easy by ramping up the value
		terrainRawImageData[terrainIndex * 4] = FMath::Clamp(terrain2DArray[terrainIndex] / maxHeight * 255 * OCTAVE_FADE_MAX_RATE, 0, 255);
	}
}

#undef LOCTEXT_NAMESPACE