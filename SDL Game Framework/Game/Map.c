#include "Map.h"

void Map_Init(Map* map, int32 StageNum) {
	Image_LoadImage(&map->BackGroundImage, "");
	Audio_LoadMusic(&map->BGM, "");
	Audio_LoadMusic(&map->DieBGM, "");

	//¸Ê ½ÃÀÛ ÁöÁ¡ ÁÂÇ¥ ÃÊ±âÈ­
	map->StartPoint.X = 0;
	map->StartPoint.Y = 0;

}

void Map_Update(Map* map) {
	
}

void Map_Render(Map* map) {

}

void Map_Release(Map* map) {

}
