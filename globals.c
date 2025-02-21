Sound jumpWav;
Sound bumpWav;
Sound floorWav;

// Get start and end coordinates of the boxes a bounding box on the tilemap grid
void
getTilesOverlappedByBox(int* outStartX, int* outStartY, int* outEndX, int* outEndY, Vector2 center, const Vector2 size)
{
    *outStartX = (int)floorf(center.x - size.x);
    *outStartY = (int)floorf(center.y - size.y);
    *outEndX = (int)floorf(center.x + size.x);
    *outEndY = (int)floorf(center.y + size.y);
}
