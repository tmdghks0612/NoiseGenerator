# TerrainGenerator
terrain generator using random noises and voxel mesh

## Intoduction
* A Unreal plugin for generating terrain. Uses multiple inputs to generate a random Terrain      
* Plugin for future use on unreal projects with random world maps

## System Goal
* Project targets to utilize Perlin noise and its modifications on maps
* Project targets to create a voxelized mesh to create data generated map for each coordinate
* Secondary goal is on the speed of the terrain generated

## Unreal Engine
* Unreal Engine's partial source will be on this repository as version managing

## Hierarchy Graph
![Terrain Generator Hierarchy Design](https://user-images.githubusercontent.com/13249604/194839277-086d4d4f-28b9-4b4d-a0b1-2c78b0a98fbb.png)
* STabWidgetMain
  * maintains the FTerrainModifier instance
  * constructs each tabs and initializes it

* FTerrainModifier
  * provides methods for each tabs to utilize
  * saves the values that needs to be shared between all tabs


