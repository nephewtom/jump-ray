// Gravity in units (tiles) per second
#define PLAYER_GRAVITY 30.0f

// How fast player accelerates.
#define PLAYER_SPEED 200.0f
#define PLAYER_GROUND_FRICTION_X 70.0f
#define PLAYER_JUMP_STRENGTH 15.0f

typedef struct {
    Vector2 position;
    Vector2 velocity;
    float jumpHoldTime;
    float animTime;
    bool isOnGround;
    bool isFacingRight;
} Player;

Player player = { {0.0f, 0.0f}, {0.0f, 0.0f}, 0.0f, 0.0f, false, false};

// Half-size of the player's box collider.
Vector2 PLAYER_SIZE = {0.3f, 0.4f};



// Checks whether the box is intersecting any tile in the tilemap.
// param `tilemap`: tilemap to check
// param `tilemapHeight`: offset of the tilemap along the Y axis
// param `center`: coordinate of the center of the box
// param `size`: half-extent of the box - half the box sides
bool
isBoxCollidingWithTilemap(const Tilemap* tilemap, float tilemapHeight, Vector2 center, const Vector2 size)
{
    center.y -= tilemapHeight;

    int startX = 0;
    int startY = 0;
    int endX = 0;
    int endY = 0;
    // Get neighbor tile ranges
    getTilesOverlappedByBox(&startX, &startY, &endX, &endY, center, size);

    // Iterate over close tiles
    for (int x = startX; x <= endX; x++) {
        for (int y = startY; y <= endY; y++) {
            // Skip if non-empty
            if (!tilemapIsTileFull(tilemap, x, y)) continue;

            // Center of the tile box
            const Vector2 boxPos = { 0.5f + (float)x, 0.5f + (float)y };
            const Vector2 sizeSum = { size.x + 0.5f, size.y + 0.5f };
            const Vector2 surfDist = {
                fabsf(center.x - boxPos.x) - sizeSum.x,
                fabsf(center.y - boxPos.y) - sizeSum.y,
            };

            // The two boxes aren't colliding, because
            // the distance between the surfaces is larger than
            // zero on one of the axes.
            if (surfDist.x > 0 || surfDist.y > 0) continue;
            return true;
        } // y
    } // x

    return false;
}

void
updatePlayer(const Tilemap* tilemap, float tilemapHeight, float delta)
{
    player.velocity.y += PLAYER_GRAVITY * delta;

    Vector2 center = { player.position.x, player.position.y + PLAYER_SIZE.y };
    Vector2 size = { 0.1, 0.05 };
    const bool isOnGround = isBoxCollidingWithTilemap(tilemap, tilemapHeight, center, size);
    // { player->position.x, player->position.y + PLAYER_SIZE.y },
    // { 0.1, 0.05 });
    if (isOnGround && !player.isOnGround) {
        PlaySound(floorWav);
    }
    player.isOnGround = isOnGround;

    if (isOnGround) {
        player.velocity.x = 0;

        const float leftStickDeadzoneX = 0.1f;
        const float leftStickDeadzoneY = 0.1f;
        float leftStickX;
        float leftStickY;

        if (IsGamepadAvailable(0)) {
            printf("Gamepad Available\n");
            leftStickX = GetGamepadAxisMovement(0, GAMEPAD_AXIS_LEFT_X);
            leftStickY = GetGamepadAxisMovement(0, GAMEPAD_AXIS_LEFT_Y);
            if (leftStickX > -leftStickDeadzoneX && leftStickX < leftStickDeadzoneX) leftStickX = 0.0f;
            if (leftStickY > -leftStickDeadzoneY && leftStickY < leftStickDeadzoneY) leftStickY = 0.0f;
        }


        if (IsKeyReleased(KEY_SPACE) ||
                IsGamepadAvailable(0) && IsGamepadButtonReleased(0, GAMEPAD_BUTTON_RIGHT_FACE_DOWN)) {
            PlaySound(jumpWav);
            // Calculate strength based on how long the user held down the jump key.
            // The numbers are kind of random, you play with it yourself.
            const float jumpStrength = Clamp(player.jumpHoldTime * 2.6f, 1.1f, 2.0f) / 2.0f;

            // If the player doesn't press anything, the direction is up.
            Vector2 dir = { 0.0f, -1.0f };
            const float xMoveStrength = 0.75f - (jumpStrength * 0.5f);
            if (IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_D) || IsGamepadAvailable(0) && leftStickX >= 0.0f) dir.x += xMoveStrength;
            if (IsKeyDown(KEY_LEFT) || IsKeyDown(KEY_A) ||  IsGamepadAvailable(0) && leftStickX <= -0.0f) dir.x -= xMoveStrength;
            // Make sure the vector is unit vector (length = 1.0).
            dir = Vector2Normalize(dir);

            // Multiply the vector length by the strength factor.
            dir = Vector2Scale(dir, jumpStrength * PLAYER_JUMP_STRENGTH);
            // Now apply the jump vector to the actual velocity
            player.velocity = dir;
        }
        if (IsKeyDown(KEY_SPACE) ||
                IsGamepadAvailable(0) && IsGamepadButtonDown(0, GAMEPAD_BUTTON_RIGHT_FACE_DOWN)) {
            player.jumpHoldTime += delta;
        } else {
            player.jumpHoldTime = 0.0f;
            if (IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_D) || IsGamepadAvailable(0) && leftStickX >= 0.0f) {
                player.velocity.x += PLAYER_SPEED * delta;
                player.isFacingRight = true;
            }
            if (IsKeyDown(KEY_LEFT) || IsKeyDown(KEY_A) || IsGamepadAvailable(0) && leftStickX <= 0.0f) {
                player.velocity.x -= PLAYER_SPEED * delta;
                player.isFacingRight = false;
            }

            if (IsKeyPressed(KEY_RIGHT) || IsKeyPressed(KEY_LEFT) || IsKeyPressed(KEY_D) || IsKeyPressed(KEY_A)) {
                player.animTime = 0;
            }
        }
    } else {
        player.jumpHoldTime = 0.0f;
    }

    // Clamp velocity
    float vel = Vector2Length(player.velocity);
    if (vel > 25.0) vel = 25.0;
    player.velocity = Vector2Scale(Vector2Normalize(player.velocity), vel);

    player.position = Vector2Add(player.position, Vector2Scale(player.velocity, delta));
}
