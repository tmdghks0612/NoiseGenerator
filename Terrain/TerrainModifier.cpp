#include "TerrainModifier.h"

#include "Engine/Texture2D.h"
#include "UObject/UObjectGlobals.h"

#define LOCTEXT_NAMESPACE "FTerrainModifier"

FTerrainModifier::FTerrainModifier()
	: minHeight(0),
	maxHeight(0),
	terrainXSize(0),
	terrainYSize(0)
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
	terrain2DArray.Init(terrainXYSize, 0);
	// initialize RawImageData by size*4(RGBA)
	terrainRawImageData.Init(terrainXYSize * 4, 0);
}

void FTerrainModifier::GenerateRandomTerrain2DArray()
{
	// TESTCODE for array values
	int32 testValue = 0;
	for (int32& terrainValue : terrain2DArray)
	{
		terrainValue = testValue;
		testValue++;
	}

	testValue = 0;
	for (int8& terrainRawValue : terrainRawImageData)
	{
		terrainRawValue = testValue;
		testValue++;
	}

	// TODO : check FMath::Perlinnoise2D Usage viability
}

void FTerrainModifier::GenerateTextureByTerrain2DArray()
{
	// package path and name
	FString pathPackage = FString("/Game/TerrainTextures/");
	FString textureFileName = FString("TerrainTexture");
	
	InitTexturePackage(pathPackage, textureFileName);
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

		void* TextureData = Mip->BulkData.Lock(LOCK_READ_WRITE);

		// using only PF_R8G8B8A8, where block size of x,y is 1.
		Mip->BulkData.Realloc(terrainXSize * terrainYSize * 4);
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
	// TODO : example log print for debug
	UE_LOG(LogTemp, Log, TEXT("[FTerrianModifier] minHeight : %d, maxHeight : %d"), minHeight, maxHeight);

	// generate random values for terrain2DArray
	GenerateRandomTerrain2DArray();

	// Generate 2D Texture
	GenerateTextureByTerrain2DArray();

}

#undef LOCTEXT_NAMESPACE