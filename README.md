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

## Random Generate Array

* Perlin Noise
  * using Perlin Noise based algorithm to generate random array
  * few more features were added to diversify the results (interpolation alpha, fade rate etc)

* Visualizing

![image](https://user-images.githubusercontent.com/13249604/206855764-ba284b87-c445-4847-ae16-be1b3a3e01c0.png)

  * TerrainGenerator creates a Texture file to visualize random arrays
  * random arrays will be remapped in range of given Min/Max height


* Examples

| Bumpiness  | 2 | 4 | 8 | 16 |
| ------------- | ------------- | ------------- | ------------- | ------------- |
| Texture  | ![b2](https://user-images.githubusercontent.com/13249604/206855337-5c1e68e6-3d1d-4ead-9af5-c2e72d0e1ea8.PNG)  | ![b4](https://user-images.githubusercontent.com/13249604/206855414-73907ac9-0eba-4843-820e-67f4a2ff3993.PNG)  | ![b8](https://user-images.githubusercontent.com/13249604/206855416-f42df7cc-6690-4f56-9c4c-5604a4e26db4.PNG)  | ![b16](https://user-images.githubusercontent.com/13249604/206855420-7255d6a1-baba-435f-8f15-6d3c2a6e6951.PNG)  |



