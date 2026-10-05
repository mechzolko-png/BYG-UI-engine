# Raylib 6.0 — Practical C++ Game Development Reference

> Practical Raylib 6.0 reference for learning C++ by building games.
> Use this as a lookup sheet while coding — you do **not** need to memorize the API.

---

## 0. Starting `game.cpp` template

```cpp
#include "raylib.h"

int main()
{
    InitWindow(1280, 720, "My Game");
    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        // INPUT

        float dt = GetFrameTime();

        // UPDATE

        // DRAW
        BeginDrawing();

        ClearBackground(RAYWHITE);

        // Draw here

        EndDrawing();
    }

    CloseWindow();

    return 0;
}
```

### With audio

```cpp
#include "raylib.h"

int main()
{
    InitWindow(1280, 720, "My Game");
    InitAudioDevice();

    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        float dt = GetFrameTime();

        // Input
        // Update

        BeginDrawing();

        ClearBackground(BLACK);

        // Draw

        EndDrawing();
    }

    CloseAudioDevice();
    CloseWindow();

    return 0;
}
```

---

# 1. Core / Window / Frame

| API                     | Purpose                            | Example                                  |
| ----------------------- | ---------------------------------- | ---------------------------------------- |
| `InitWindow()`          | Create window and graphics context | `InitWindow(1280, 720, "Game");`         |
| `CloseWindow()`         | Close window                       | `CloseWindow();`                         |
| `WindowShouldClose()`   | Check whether game should exit     | `while (!WindowShouldClose())`           |
| `IsWindowReady()`       | Check initialization               | `IsWindowReady()`                        |
| `IsWindowFullscreen()`  | Check fullscreen                   | `IsWindowFullscreen()`                   |
| `IsWindowHidden()`      | Check hidden                       | `IsWindowHidden()`                       |
| `IsWindowMinimized()`   | Check minimized                    | `IsWindowMinimized()`                    |
| `IsWindowMaximized()`   | Check maximized                    | `IsWindowMaximized()`                    |
| `IsWindowFocused()`     | Check focus                        | `IsWindowFocused()`                      |
| `IsWindowResized()`     | Check resize                       | `IsWindowResized()`                      |
| `GetScreenWidth()`      | Current screen width               | `GetScreenWidth()`                       |
| `GetScreenHeight()`     | Current screen height              | `GetScreenHeight()`                      |
| `GetRenderWidth()`      | Render width                       | `GetRenderWidth()`                       |
| `GetRenderHeight()`     | Render height                      | `GetRenderHeight()`                      |
| `SetWindowSize()`       | Change window size                 | `SetWindowSize(1600, 900);`              |
| `SetWindowPosition()`   | Move window                        | `SetWindowPosition(100, 100);`           |
| `SetWindowTitle()`      | Change title                       | `SetWindowTitle("My Game");`             |
| `SetWindowMinSize()`    | Minimum size                       | `SetWindowMinSize(640, 360);`            |
| `SetWindowMaxSize()`    | Maximum size                       | `SetWindowMaxSize(1920, 1080);`          |
| `SetWindowOpacity()`    | Window opacity                     | `SetWindowOpacity(0.9f);`                |
| `ToggleFullscreen()`    | Toggle fullscreen                  | `ToggleFullscreen();`                    |
| `SetWindowFullscreen()` | Set fullscreen                     | `SetWindowFullscreen(true);`             |
| `MaximizeWindow()`      | Maximize                           | `MaximizeWindow();`                      |
| `MinimizeWindow()`      | Minimize                           | `MinimizeWindow();`                      |
| `RestoreWindow()`       | Restore                            | `RestoreWindow();`                       |
| `HideWindow()`          | Hide                               | `HideWindow();`                          |
| `ShowWindow()`          | Show                               | `ShowWindow();`                          |
| `GetWindowHandle()`     | Native window handle               | `GetWindowHandle()`                      |
| `SetWindowIcon()`       | Window icon                        | `SetWindowIcon(image);`                  |
| `SetConfigFlags()`      | Configuration flags                | `SetConfigFlags(FLAG_WINDOW_RESIZABLE);` |
| `SetTargetFPS()`        | Target FPS                         | `SetTargetFPS(60);`                      |
| `GetFPS()`              | Current FPS                        | `GetFPS()`                               |
| `GetFrameTime()`        | Seconds since previous frame       | `float dt = GetFrameTime();`             |
| `GetTime()`             | Seconds since initialization       | `GetTime()`                              |
| `WaitTime()`            | Wait                               | `WaitTime(0.1);`                         |

### Basic frame structure

```cpp
while (!WindowShouldClose())
{
    float dt = GetFrameTime();

    // Input

    // Update

    BeginDrawing();

    // Render

    EndDrawing();
}
```

Mental model:

```text
INPUT
  ↓
UPDATE / GAME LOGIC
  ↓
DRAW
  ↓
NEXT FRAME
```

---

# 2. Cursor

| API                  | Purpose                |
| -------------------- | ---------------------- |
| `ShowCursor()`       | Show cursor            |
| `HideCursor()`       | Hide cursor            |
| `IsCursorHidden()`   | Check hidden           |
| `EnableCursor()`     | Enable cursor          |
| `DisableCursor()`    | Disable / lock cursor  |
| `IsCursorOnScreen()` | Check cursor on screen |

---

# 3. Keyboard Input

| API                | Purpose                 | Typical use               |
| ------------------ | ----------------------- | ------------------------- |
| `IsKeyPressed()`   | Key pressed this frame  | Jump / menu               |
| `IsKeyDown()`      | Key currently held      | Movement                  |
| `IsKeyReleased()`  | Key released this frame | Release action            |
| `IsKeyUp()`        | Key currently not held  | State check               |
| `GetKeyPressed()`  | Get queued key          | Text input                |
| `GetCharPressed()` | Get character           | Text input                |
| `SetExitKey()`     | Change exit key         | `SetExitKey(KEY_ESCAPE);` |

### Common keys

```cpp
KEY_W
KEY_A
KEY_S
KEY_D
KEY_SPACE
KEY_ESCAPE
KEY_ENTER
KEY_TAB
KEY_SHIFT
KEY_LEFT_CONTROL
KEY_RIGHT_CONTROL
KEY_LEFT_ALT
KEY_RIGHT_ALT
KEY_LEFT
KEY_RIGHT
KEY_UP
KEY_DOWN
```

### Held input

```cpp
if (IsKeyDown(KEY_W))
{
    player.y -= speed * dt;
}
```

### One-time input

```cpp
if (IsKeyPressed(KEY_SPACE))
{
    Jump();
}
```

---

# 4. Mouse Input

| API                       | Purpose                  |
| ------------------------- | ------------------------ |
| `GetMousePosition()`      | `Vector2` mouse position |
| `GetMouseX()`             | Mouse X                  |
| `GetMouseY()`             | Mouse Y                  |
| `GetMouseDelta()`         | Mouse movement           |
| `GetMouseWheelMove()`     | Vertical wheel           |
| `GetMouseWheelMoveV()`    | Wheel `Vector2`          |
| `SetMousePosition()`      | Set position             |
| `SetMouseOffset()`        | Mouse offset             |
| `SetMouseScale()`         | Mouse scale              |
| `IsMouseButtonPressed()`  | Button pressed           |
| `IsMouseButtonDown()`     | Button held              |
| `IsMouseButtonReleased()` | Button released          |
| `IsMouseButtonUp()`       | Button not held          |

Example:

```cpp
Vector2 mouse = GetMousePosition();

if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
{
    // Click
}
```

---

# 5. Gamepad

| API                         | Purpose                 |
| --------------------------- | ----------------------- |
| `IsGamepadAvailable()`      | Check connected gamepad |
| `GetGamepadName()`          | Get name                |
| `IsGamepadButtonPressed()`  | Button pressed          |
| `IsGamepadButtonDown()`     | Button held             |
| `IsGamepadButtonReleased()` | Button released         |
| `IsGamepadButtonUp()`       | Button not held         |
| `GetGamepadButtonPressed()` | Last pressed button     |
| `GetGamepadAxisCount()`     | Number of axes          |
| `GetGamepadAxisMovement()`  | Axis value              |
| `SetGamepadVibration()`     | Rumble                  |

---

# 6. General Drawing

| API                  | Purpose               |
| -------------------- | --------------------- |
| `BeginDrawing()`     | Start drawing frame   |
| `EndDrawing()`       | End drawing frame     |
| `ClearBackground()`  | Clear screen          |
| `BeginMode2D()`      | Begin 2D camera       |
| `EndMode2D()`        | End 2D camera         |
| `BeginMode3D()`      | Begin 3D camera       |
| `EndMode3D()`        | End 3D camera         |
| `BeginTextureMode()` | Render to texture     |
| `EndTextureMode()`   | End render-to-texture |
| `BeginShaderMode()`  | Begin shader          |
| `EndShaderMode()`    | End shader            |
| `BeginBlendMode()`   | Begin blend mode      |
| `EndBlendMode()`     | End blend mode        |
| `BeginScissorMode()` | Clip rectangle        |
| `EndScissorMode()`   | End clipping          |

Example:

```cpp
BeginDrawing();

ClearBackground(BLACK);

DrawRectangle(100, 100, 200, 100, RED);

EndDrawing();
```

---

# 7. 2D Shapes

| API                             | Purpose                  |
| ------------------------------- | ------------------------ |
| `DrawPixel()`                   | Pixel                    |
| `DrawPixelV()`                  | Pixel with `Vector2`     |
| `DrawLine()`                    | Line                     |
| `DrawLineV()`                   | Line with vectors        |
| `DrawLineEx()`                  | Thick line               |
| `DrawLineBezier()`              | Bezier line              |
| `DrawCircle()`                  | Circle                   |
| `DrawCircleV()`                 | Circle with vector       |
| `DrawCircleSector()`            | Circle sector            |
| `DrawCircleSectorLines()`       | Sector outline           |
| `DrawCircleGradient()`          | Gradient circle          |
| `DrawRing()`                    | Ring                     |
| `DrawRingLines()`               | Ring outline             |
| `DrawRectangle()`               | Rectangle                |
| `DrawRectangleV()`              | Rectangle with vector    |
| `DrawRectangleRec()`            | Rectangle struct         |
| `DrawRectanglePro()`            | Rectangle with transform |
| `DrawRectangleLines()`          | Rectangle outline        |
| `DrawRectangleLinesEx()`        | Thick outline            |
| `DrawRectangleRounded()`        | Rounded rectangle        |
| `DrawRectangleRoundedLines()`   | Rounded outline          |
| `DrawRectangleRoundedLinesEx()` | Thick rounded outline    |
| `DrawRectangleGradientV()`      | Vertical gradient        |
| `DrawRectangleGradientH()`      | Horizontal gradient      |
| `DrawRectangleGradientEx()`     | Multi-corner gradient    |
| `DrawTriangle()`                | Triangle                 |
| `DrawTriangleLines()`           | Triangle outline         |
| `DrawTriangleFan()`             | Triangle fan             |
| `DrawTriangleStrip()`           | Triangle strip           |
| `DrawPoly()`                    | Polygon                  |
| `DrawPolyLines()`               | Polygon outline          |
| `DrawPolyLinesEx()`             | Thick polygon outline    |
| `DrawSplineLinear()`            | Linear spline            |
| `DrawSplineBasis()`             | Basis spline             |
| `DrawSplineCatmullRom()`        | Catmull-Rom spline       |
| `DrawSplineBezierQuadratic()`   | Quadratic Bezier         |
| `DrawSplineBezierCubic()`       | Cubic Bezier             |

Examples:

```cpp
DrawRectangle(100, 100, 200, 100, RED);

DrawCircle(500, 300, 50, BLUE);

DrawLine(0, 0, 800, 600, WHITE);
```

---

# 8. Color

`Color` contains:

```text
r = red
g = green
b = blue
a = alpha
```

Example:

```cpp
Color orange = {255, 120, 30, 255};
```

Useful predefined colors:

```cpp
LIGHTGRAY
GRAY
DARKGRAY
YELLOW
GOLD
ORANGE
PINK
RED
MAROON
GREEN
LIME
DARKGREEN
SKYBLUE
BLUE
DARKBLUE
PURPLE
VIOLET
DARKPURPLE
BEIGE
BROWN
DARKBROWN
WHITE
BLACK
BLANK
MAGENTA
RAYWHITE
```

Useful color functions:

| API                     | Purpose                   |
| ----------------------- | ------------------------- |
| `Fade()`                | Change alpha              |
| `ColorToInt()`          | Color → integer           |
| `ColorNormalize()`      | Color → normalized vector |
| `ColorFromNormalized()` | Vector → color            |
| `ColorToHSV()`          | RGB → HSV                 |
| `ColorFromHSV()`        | HSV → RGB                 |
| `ColorTint()`           | Tint                      |
| `ColorBrightness()`     | Brightness                |
| `ColorContrast()`       | Contrast                  |
| `ColorAlpha()`          | Set alpha                 |
| `ColorAlphaBlend()`     | Alpha blend               |
| `GetColor()`            | Integer → color           |

---

# 9. Text

| API                    | Purpose                   |
| ---------------------- | ------------------------- |
| `DrawText()`           | Draw text                 |
| `DrawTextEx()`         | Draw with font            |
| `DrawTextPro()`        | Draw with origin/rotation |
| `MeasureText()`        | Text width                |
| `MeasureTextEx()`      | Text dimensions           |
| `DrawFPS()`            | Debug FPS                 |
| `LoadFont()`           | Load font                 |
| `LoadFontEx()`         | Load font with settings   |
| `LoadFontFromImage()`  | Font from image           |
| `LoadFontFromMemory()` | Font from memory          |
| `LoadFontDefault()`    | Default font              |
| `IsFontValid()`        | Check font                |
| `UnloadFont()`         | Unload font               |
| `GetGlyphIndex()`      | Glyph index               |
| `GetGlyphInfo()`       | Glyph information         |
| `GetGlyphAtlasRec()`   | Glyph atlas rectangle     |

Example:

```cpp
DrawText("Hello Raylib!", 100, 100, 30, WHITE);
```

---

# 10. Core Types

| Type           | Meaning                        | Common use             |
| -------------- | ------------------------------ | ---------------------- |
| `Vector2`      | `x, y`                         | 2D position / velocity |
| `Vector3`      | `x, y, z`                      | 3D position            |
| `Vector4`      | `x, y, z, w`                   | Advanced math          |
| `Quaternion`   | Rotation representation        | 3D rotation            |
| `Matrix`       | 4×4 matrix                     | 3D transforms          |
| `Rectangle`    | `x, y, width, height`          | Bounds / UI            |
| `Color`        | `r, g, b, a`                   | Colors                 |
| `Camera2D`     | 2D camera                      | 2D worlds              |
| `Camera3D`     | 3D camera                      | 3D worlds              |
| `Ray`          | Position + direction           | Raycasting             |
| `RayCollision` | Ray hit information            | 3D collision           |
| `BoundingBox`  | Min + max                      | 3D bounds              |
| `Transform`    | Translation / rotation / scale | 3D objects             |

---

# 11. Rectangle

```cpp
Rectangle player = {
    100,
    100,
    50,
    50
};
```

Fields:

```text
x
y
width
height
```

Useful for:

```text
UI
collision
hitboxes
sprites
source rectangles
destination rectangles
```

---

# 12. 2D Collision

| API                             | Purpose                |
| ------------------------------- | ---------------------- |
| `CheckCollisionRecs()`          | Rectangle vs rectangle |
| `CheckCollisionCircles()`       | Circle vs circle       |
| `CheckCollisionCircleRec()`     | Circle vs rectangle    |
| `CheckCollisionPointRec()`      | Point vs rectangle     |
| `CheckCollisionPointCircle()`   | Point vs circle        |
| `CheckCollisionPointTriangle()` | Point vs triangle      |
| `CheckCollisionPointLine()`     | Point vs line          |
| `CheckCollisionPointPoly()`     | Point vs polygon       |
| `CheckCollisionLines()`         | Line vs line           |
| `GetCollisionRec()`             | Intersection rectangle |

Example:

```cpp
if (CheckCollisionRecs(playerRect, wallRect))
{
    // Collision happened.
}
```

Raylib tells you that geometry intersects. Your game/physics code decides what happens afterward.

---

# 13. 2D Camera

```cpp
Camera2D camera = {0};

camera.target = player.position;

camera.offset = {
    GetScreenWidth() / 2.0f,
    GetScreenHeight() / 2.0f
};

camera.rotation = 0.0f;
camera.zoom = 1.0f;
```

Render world:

```cpp
BeginDrawing();

ClearBackground(BLACK);

BeginMode2D(camera);

DrawCircleV(player.position, 25, RED);
DrawRectangle(500, 500, 100, 100, BLUE);

EndMode2D();

EndDrawing();
```

| API                    | Purpose                   |
| ---------------------- | ------------------------- |
| `BeginMode2D()`        | World drawing with camera |
| `EndMode2D()`          | End camera                |
| `GetWorldToScreen2D()` | World → screen            |
| `GetScreenToWorld2D()` | Screen → world            |
| `GetCameraMatrix2D()`  | Get camera matrix         |

---

# 14. Image

Mental model:

```text
IMAGE
  ↓
CPU / RAM representation

TEXTURE
  ↓
GPU representation
```

| API                        | Purpose                  |
| -------------------------- | ------------------------ |
| `LoadImage()`              | Load image               |
| `LoadImageRaw()`           | Load raw image           |
| `LoadImageAnim()`          | Load animated image      |
| `LoadImageFromMemory()`    | Load from bytes          |
| `LoadImageFromTexture()`   | Texture → Image          |
| `LoadImageFromScreen()`    | Screen → Image           |
| `IsImageValid()`           | Check image              |
| `UnloadImage()`            | Free image               |
| `ExportImage()`            | Save image               |
| `ExportImageToMemory()`    | Encode image             |
| `GenImageColor()`          | Solid color              |
| `GenImageGradientLinear()` | Linear gradient          |
| `GenImageGradientRadial()` | Radial gradient          |
| `GenImageGradientSquare()` | Square gradient          |
| `GenImageChecked()`        | Checkerboard             |
| `GenImageWhiteNoise()`     | White noise              |
| `GenImagePerlinNoise()`    | Perlin noise             |
| `GenImageCellular()`       | Cellular noise           |
| `ImageCopy()`              | Copy                     |
| `ImageFromImage()`         | Crop / transform         |
| `ImageFormat()`            | Pixel format             |
| `ImageResize()`            | Resize                   |
| `ImageResizeNN()`          | Nearest-neighbor resize  |
| `ImageResizeCanvas()`      | Resize canvas            |
| `ImageMipmaps()`           | Generate mipmaps         |
| `ImageDither()`            | Dither                   |
| `ImageCrop()`              | Crop                     |
| `ImageAlphaCrop()`         | Alpha crop               |
| `ImageAlphaClear()`        | Clear alpha              |
| `ImageAlphaMask()`         | Alpha mask               |
| `ImageAlphaPremultiply()`  | Premultiply alpha        |
| `ImageBlurGaussian()`      | Gaussian blur            |
| `ImageKernelConvolution()` | Convolution              |
| `ImageFlipVertical()`      | Flip vertical            |
| `ImageFlipHorizontal()`    | Flip horizontal          |
| `ImageRotate()`            | Rotate                   |
| `ImageRotateCW()`          | Rotate clockwise         |
| `ImageRotateCCW()`         | Rotate counter-clockwise |
| `ImageColorTint()`         | Tint                     |
| `ImageColorInvert()`       | Invert                   |
| `ImageColorGrayscale()`    | Grayscale                |
| `ImageColorContrast()`     | Contrast                 |
| `ImageColorBrightness()`   | Brightness               |
| `ImageColorReplace()`      | Replace color            |
| `ImageClearBackground()`   | Clear                    |
| `ImageDrawPixel()`         | Draw pixel               |
| `ImageDrawLine()`          | Draw line                |
| `ImageDrawCircle()`        | Draw circle              |
| `ImageDrawRectangle()`     | Draw rectangle           |
| `ImageDrawTriangle()`      | Draw triangle            |
| `ImageDraw()`              | Draw image onto image    |

---

# 15. Texture

Load:

```cpp
Texture2D playerTexture =
    LoadTexture("assets/player.png");
```

Draw:

```cpp
DrawTexture(
    playerTexture,
    100,
    100,
    WHITE
);
```

Unload:

```cpp
UnloadTexture(playerTexture);
```

| API                       | Purpose               |
| ------------------------- | --------------------- |
| `LoadTexture()`           | Load image as texture |
| `LoadTextureFromImage()`  | Image → texture       |
| `LoadTextureCubemap()`    | Cubemap               |
| `LoadTextureFromMemory()` | Bytes → texture       |
| `IsTextureValid()`        | Check                 |
| `UnloadTexture()`         | Free GPU texture      |
| `UpdateTexture()`         | Update texture        |
| `UpdateTextureRec()`      | Update region         |
| `GenTextureMipmaps()`     | Generate mipmaps      |
| `SetTextureFilter()`      | Filtering             |
| `SetTextureWrap()`        | Wrapping              |
| `DrawTexture()`           | Draw                  |
| `DrawTextureV()`          | Draw with `Vector2`   |
| `DrawTextureEx()`         | Scale / rotation      |
| `DrawTextureRec()`        | Draw source rectangle |
| `DrawTexturePro()`        | Full transform        |
| `DrawTextureNPatch()`     | 9-patch               |
| `DrawTexturePoly()`       | Polygon texture       |

---

# 16. Sprite Sheets

Typical setup:

```cpp
Texture2D spritesheet =
    LoadTexture("assets/player.png");

Rectangle source = {
    0,
    0,
    64,
    64
};

DrawTextureRec(
    spritesheet,
    source,
    playerPosition,
    WHITE
);
```

Animation:

```cpp
int frame = 0;

source.x = frame * 64;
```

Typical animation state:

```text
timer
  ↓
current frame
  ↓
source Rectangle
  ↓
DrawTextureRec()
```

---

# 17. RenderTexture2D

Useful for:

```text
post-processing
mini maps
UI
editor previews
render-to-texture
pixel-art scaling
effects
```

Create:

```cpp
RenderTexture2D target =
    LoadRenderTexture(800, 600);
```

Render into it:

```cpp
BeginTextureMode(target);

ClearBackground(BLACK);

DrawCircle(400, 300, 50, RED);

EndTextureMode();
```

Draw it:

```cpp
DrawTextureRec(
    target.texture,
    {0, 0, 800, -600},
    {0, 0},
    WHITE
);
```

Unload:

```cpp
UnloadRenderTexture(target);
```

---

# 18. Shader

| API                         | Purpose            |
| --------------------------- | ------------------ |
| `LoadShader()`              | Load shader        |
| `LoadShaderFromMemory()`    | Load shader source |
| `IsShaderValid()`           | Check              |
| `GetShaderLocation()`       | Uniform location   |
| `GetShaderLocationAttrib()` | Attribute location |
| `SetShaderValue()`          | Set uniform        |
| `SetShaderValueV()`         | Set vector / array |
| `SetShaderValueMatrix()`    | Set matrix         |
| `SetShaderValueTexture()`   | Set texture        |
| `BeginShaderMode()`         | Use shader         |
| `EndShaderMode()`           | Stop shader        |
| `UnloadShader()`            | Free shader        |

Basic:

```cpp
Shader shader = LoadShader(
    "shaders/vertex.vs",
    "shaders/fragment.fs"
);

BeginShaderMode(shader);

// Draw here

EndShaderMode();

UnloadShader(shader);
```

---

# 19. Blend Modes

```cpp
BeginBlendMode(BLEND_ALPHA);

// draw

EndBlendMode();
```

Useful modes:

```cpp
BLEND_ALPHA
BLEND_ADDITIVE
BLEND_MULTIPLIED
BLEND_ADD_COLORS
BLEND_SUBTRACT_COLORS
BLEND_ALPHA_PREMULTIPLY
```

Useful for:

```text
particles
glows
lighting
fire
effects
```

---

# 20. Scissor / Clipping

```cpp
BeginScissorMode(
    x,
    y,
    width,
    height
);

// Only this region is rendered.

EndScissorMode();
```

Useful for:

```text
scrollable panels
inventory
editor UI
console
viewport
clipped menus
```

---

# 21. Screen / Utility

| API                     | Purpose                 |
| ----------------------- | ----------------------- |
| `DrawFPS()`             | Show FPS                |
| `TakeScreenshot()`      | Screenshot              |
| `OpenURL()`             | Open URL                |
| `SetClipboardText()`    | Copy text               |
| `GetClipboardText()`    | Read text               |
| `SetShapesTexture()`    | Custom shapes texture   |
| `GetShapesTexture()`    | Current shapes texture  |
| `GetShapesTextureRec()` | Shape texture rectangle |

---

# 22. Random

| API                      | Purpose         |
| ------------------------ | --------------- |
| `GetRandomValue()`       | Random integer  |
| `SetRandomSeed()`        | Set seed        |
| `LoadRandomSequence()`   | Random sequence |
| `UnloadRandomSequence()` | Free sequence   |

Example:

```cpp
int x = GetRandomValue(0, 100);
```

---

# 23. 3D Drawing

| API                     | Purpose                 |
| ----------------------- | ----------------------- |
| `DrawLine3D()`          | 3D line                 |
| `DrawPoint3D()`         | 3D point                |
| `DrawCircle3D()`        | 3D circle               |
| `DrawTriangle3D()`      | 3D triangle             |
| `DrawTriangleStrip3D()` | Triangle strip          |
| `DrawCube()`            | Cube                    |
| `DrawCubeV()`           | Cube with vector size   |
| `DrawCubeWires()`       | Wire cube               |
| `DrawCubeWiresV()`      | Wire cube               |
| `DrawSphere()`          | Sphere                  |
| `DrawSphereEx()`        | Sphere with segments    |
| `DrawSphereWires()`     | Wire sphere             |
| `DrawCylinder()`        | Cylinder                |
| `DrawCylinderEx()`      | Cylinder between points |
| `DrawCylinderWires()`   | Wire cylinder           |
| `DrawCylinderWiresEx()` | Wire cylinder           |
| `DrawCapsule()`         | Capsule                 |
| `DrawCapsuleWires()`    | Wire capsule            |
| `DrawPlane()`           | Plane                   |
| `DrawRay()`             | Ray                     |
| `DrawGrid()`            | Debug grid              |

3D frame:

```cpp
BeginDrawing();

ClearBackground(SKYBLUE);

BeginMode3D(camera);

DrawCube(
    {0, 0, 0},
    2,
    2,
    2,
    RED
);

DrawGrid(10, 1.0f);

EndMode3D();

EndDrawing();
```

---

# 24. Camera3D

```cpp
Camera3D camera = {0};

camera.position = {10, 10, 10};
camera.target = {0, 0, 0};
camera.up = {0, 1, 0};
camera.fovy = 45.0f;
camera.projection = CAMERA_PERSPECTIVE;
```

Fields:

```text
position
target
up
fovy
projection
```

Projection types:

```cpp
CAMERA_PERSPECTIVE
CAMERA_ORTHOGRAPHIC
```

---

# 25. Screen ↔ World Transforms

## 2D

```cpp
Vector2 world =
    GetScreenToWorld2D(mousePosition, camera);
```

```cpp
Vector2 screen =
    GetWorldToScreen2D(worldPosition, camera);
```

## 3D

```cpp
Ray ray =
    GetScreenToWorldRay(mousePosition, camera);
```

Useful for:

```text
editor picking
mouse interaction
3D placement
shooting
raycast selection
```

---

# 26. 3D Model

| API                     | Purpose                    |
| ----------------------- | -------------------------- |
| `LoadModel()`           | Load model                 |
| `LoadModelFromMesh()`   | Mesh → model               |
| `IsModelValid()`        | Validate                   |
| `UnloadModel()`         | Free model                 |
| `DrawModel()`           | Draw model                 |
| `DrawModelEx()`         | Draw with transform        |
| `DrawModelWires()`      | Wireframe                  |
| `DrawModelWiresEx()`    | Wireframe transform        |
| `GetModelBoundingBox()` | Bounds                     |
| `DrawBoundingBox()`     | Debug bounds               |
| `DrawBillboard()`       | Camera-facing billboard    |
| `DrawBillboardRec()`    | Billboard with source rect |
| `DrawBillboardPro()`    | Billboard with transform   |

---

# 27. Mesh Generation

| API                          | Purpose               |
| ---------------------------- | --------------------- |
| `GenMeshPoly()`              | Polygon               |
| `GenMeshPlane()`             | Plane                 |
| `GenMeshCube()`              | Cube                  |
| `GenMeshSphere()`            | Sphere                |
| `GenMeshHemiSphere()`        | Hemisphere            |
| `GenMeshCylinder()`          | Cylinder              |
| `GenMeshCone()`              | Cone                  |
| `GenMeshTorus()`             | Torus                 |
| `GenMeshKnot()`              | Knot                  |
| `GenMeshHeightmap()`         | Heightmap             |
| `GenMeshCubicmap()`          | Cubic map             |
| `UploadMesh()`               | Upload to GPU         |
| `UnloadMesh()`               | Free mesh             |
| `UpdateMeshBuffer()`         | Update GPU buffer     |
| `UpdateMeshBufferElements()` | Update part of buffer |
| `GetMeshBoundingBox()`       | Bounds                |
| `GenMeshTangents()`          | Generate tangents     |
| `ExportMesh()`               | Save mesh             |
| `ExportMeshAsCode()`         | Mesh → C code         |

---

# 28. Material

| API                      | Purpose          |
| ------------------------ | ---------------- |
| `LoadMaterialDefault()`  | Default material |
| `LoadMaterials()`        | Load materials   |
| `UnloadMaterial()`       | Free material    |
| `UnloadMaterials()`      | Free materials   |
| `SetMaterialTexture()`   | Set material map |
| `SetModelMeshMaterial()` | Assign material  |
| `GetModelMeshMaterial()` | Get material     |

---

# 29. 3D Collision / Raycast

| API                         | Purpose          |
| --------------------------- | ---------------- |
| `CheckCollisionSpheres()`   | Sphere vs sphere |
| `CheckCollisionBoxes()`     | Box vs box       |
| `CheckCollisionBoxSphere()` | Box vs sphere    |
| `GetRayCollisionSphere()`   | Ray vs sphere    |
| `GetRayCollisionBox()`      | Ray vs box       |
| `GetRayCollisionMesh()`     | Ray vs mesh      |
| `GetRayCollisionTriangle()` | Ray vs triangle  |
| `GetRayCollisionQuad()`     | Ray vs quad      |

Editor selection:

```text
Mouse
  ↓
GetScreenToWorldRay()
  ↓
Ray
  ↓
GetRayCollisionBox()
  ↓
Selected object
```

---

# 30. Model Animation

| API                           | Purpose              |
| ----------------------------- | -------------------- |
| `LoadModelAnimations()`       | Load animations      |
| `UpdateModelAnimation()`      | Update animation     |
| `UpdateModelAnimationBones()` | Update bones         |
| `UnloadModelAnimation()`      | Free animation       |
| `UnloadModelAnimations()`     | Free animation array |
| `IsModelAnimationValid()`     | Validate             |

---

# 31. Audio Device

```cpp
InitAudioDevice();
```

Later:

```cpp
CloseAudioDevice();
```

| API                    | Purpose           |
| ---------------------- | ----------------- |
| `InitAudioDevice()`    | Start audio       |
| `CloseAudioDevice()`   | Stop audio        |
| `IsAudioDeviceReady()` | Check             |
| `SetMasterVolume()`    | Master volume     |
| `GetMasterVolume()`    | Get master volume |

---

# 32. Sound Effects

```cpp
Sound jump =
    LoadSound("assets/jump.wav");

PlaySound(jump);

// ...

UnloadSound(jump);
```

| API                   | Purpose         |
| --------------------- | --------------- |
| `LoadSound()`         | Load sound      |
| `LoadSoundFromWave()` | Wave → sound    |
| `IsSoundValid()`      | Validate        |
| `UnloadSound()`       | Free            |
| `PlaySound()`         | Play            |
| `StopSound()`         | Stop            |
| `PauseSound()`        | Pause           |
| `ResumeSound()`       | Resume          |
| `IsSoundPlaying()`    | Check           |
| `SetSoundVolume()`    | Volume          |
| `SetSoundPitch()`     | Pitch           |
| `SetSoundPan()`       | Stereo pan      |
| `SetSoundMulti()`     | Multiple copies |
| `GetSoundsPlaying()`  | Count playing   |

---

# 33. Music Stream

```cpp
Music music =
    LoadMusicStream("assets/music.ogg");

PlayMusicStream(music);
```

Inside loop:

```cpp
UpdateMusicStream(music);
```

Cleanup:

```cpp
UnloadMusicStream(music);
```

| API                      | Purpose    |
| ------------------------ | ---------- |
| `LoadMusicStream()`      | Load music |
| `IsMusicValid()`         | Validate   |
| `UnloadMusicStream()`    | Free       |
| `PlayMusicStream()`      | Play       |
| `IsMusicStreamPlaying()` | Check      |
| `UpdateMusicStream()`    | Update     |
| `StopMusicStream()`      | Stop       |
| `PauseMusicStream()`     | Pause      |
| `ResumeMusicStream()`    | Resume     |
| `SeekMusicStream()`      | Seek       |
| `SetMusicVolume()`       | Volume     |
| `SetMusicPitch()`        | Pitch      |
| `SetMusicPan()`          | Pan        |

---

# 34. Config Flags

Call before `InitWindow()`:

```cpp
SetConfigFlags(
    FLAG_WINDOW_RESIZABLE |
    FLAG_VSYNC_HINT
);
```

Common flags:

| Flag                            | Purpose           |
| ------------------------------- | ----------------- |
| `FLAG_VSYNC_HINT`               | VSync             |
| `FLAG_FULLSCREEN_MODE`          | Fullscreen        |
| `FLAG_WINDOW_RESIZABLE`         | Resizable         |
| `FLAG_WINDOW_UNDECORATED`       | No decorations    |
| `FLAG_WINDOW_HIDDEN`            | Hidden            |
| `FLAG_WINDOW_MINIMIZED`         | Start minimized   |
| `FLAG_WINDOW_MAXIMIZED`         | Start maximized   |
| `FLAG_WINDOW_UNFOCUSED`         | Start unfocused   |
| `FLAG_WINDOW_TOPMOST`           | Always on top     |
| `FLAG_WINDOW_ALWAYS_RUN`        | Run without focus |
| `FLAG_WINDOW_TRANSPARENT`       | Transparent       |
| `FLAG_WINDOW_HIGHDPI`           | High DPI          |
| `FLAG_MSAA_4X_HINT`             | 4× MSAA           |
| `FLAG_INTERLACED_HINT`          | Interlaced        |
| `FLAG_BORDERLESS_WINDOWED_MODE` | Borderless        |

---

# 35. `raymath.h` — Vector2

Include:

```cpp
#include "raylib.h"
#include "raymath.h"
```

| API                      | Purpose                 |
| ------------------------ | ----------------------- |
| `Vector2Zero()`          | `(0, 0)`                |
| `Vector2One()`           | `(1, 1)`                |
| `Vector2Add()`           | Add                     |
| `Vector2AddValue()`      | Add scalar              |
| `Vector2Subtract()`      | Subtract                |
| `Vector2SubtractValue()` | Subtract scalar         |
| `Vector2Multiply()`      | Component-wise multiply |
| `Vector2MultiplyV()`     | Component-wise multiply |
| `Vector2Divide()`        | Component-wise divide   |
| `Vector2Scale()`         | Scale                   |
| `Vector2Negate()`        | Negate                  |
| `Vector2Reflect()`       | Reflect                 |
| `Vector2Length()`        | Length                  |
| `Vector2LengthSqr()`     | Squared length          |
| `Vector2DotProduct()`    | Dot product             |
| `Vector2Distance()`      | Distance                |
| `Vector2DistanceSqr()`   | Squared distance        |
| `Vector2Angle()`         | Angle                   |
| `Vector2LineAngle()`     | Line angle              |
| `Vector2Normalize()`     | Normalize               |
| `Vector2Lerp()`          | Linear interpolation    |
| `Vector2Rotate()`        | Rotate                  |
| `Vector2MoveTowards()`   | Move toward             |
| `Vector2Invert()`        | Invert                  |
| `Vector2Clamp()`         | Clamp components        |
| `Vector2ClampValue()`    | Clamp magnitude         |
| `Vector2Min()`           | Component-wise minimum  |
| `Vector2Max()`           | Component-wise maximum  |
| `Vector2Transform()`     | Matrix transform        |

Example:

```cpp
Vector2 direction = {
    1.0f,
    0.0f
};

direction = Vector2Normalize(direction);

Vector2 movement =
    Vector2Scale(
        direction,
        speed * dt
    );

player =
    Vector2Add(
        player,
        movement
    );
```

---

# 36. `raymath.h` — Vector3

Important functions:

```text
Vector3Zero()
Vector3One()
Vector3Add()
Vector3AddValue()
Vector3Subtract()
Vector3SubtractValue()
Vector3Multiply()
Vector3MultiplyV()
Vector3Divide()
Vector3Scale()
Vector3Negate()
Vector3Reflect()
Vector3Length()
Vector3LengthSqr()
Vector3DotProduct()
Vector3CrossProduct()
Vector3Distance()
Vector3DistanceSqr()
Vector3Angle()
Vector3Normalize()
Vector3Project()
Vector3Reject()
Vector3OrthoNormalize()
Vector3Transform()
Vector3RotateByQuaternion()
Vector3RotateByAxisAngle()
Vector3Lerp()
Vector3Slerp()
Vector3MoveTowards()
Vector3Invert()
Vector3Clamp()
Vector3ClampValue()
Vector3Min()
Vector3Max()
Vector3Barycenter()
```

---

# 37. `raymath.h` — Matrix

```text
MatrixIdentity()
MatrixAdd()
MatrixSubtract()
MatrixMultiply()
MatrixTranslate()
MatrixRotate()
MatrixRotateX()
MatrixRotateY()
MatrixRotateZ()
MatrixRotateXYZ()
MatrixRotateZYX()
MatrixScale()
MatrixDeterminant()
MatrixTrace()
MatrixTranspose()
MatrixInvert()
MatrixNormalize()
MatrixFrustum()
MatrixPerspective()
MatrixOrtho()
MatrixLookAt()
MatrixToFloatV()
```

---

# 38. `raymath.h` — Quaternion

```text
QuaternionIdentity()
QuaternionLength()
QuaternionNormalize()
QuaternionInvert()
QuaternionMultiply()
QuaternionLerp()
QuaternionNlerp()
QuaternionSlerp()
QuaternionFromVector3ToVector3()
QuaternionFromAxisAngle()
QuaternionToAxisAngle()
QuaternionFromEuler()
QuaternionToEuler()
QuaternionTransform()
QuaternionFromMatrix()
QuaternionToMatrix()
```

---

# 39. Resource Lifetime

Common Raylib pattern:

```text
LOAD
  ↓
USE
  ↓
UNLOAD
```

Example:

```cpp
Texture2D texture =
    LoadTexture("player.png");

// Use texture

UnloadTexture(texture);
```

| Load                  | Unload                  |
| --------------------- | ----------------------- |
| `LoadTexture()`       | `UnloadTexture()`       |
| `LoadImage()`         | `UnloadImage()`         |
| `LoadFont()`          | `UnloadFont()`          |
| `LoadSound()`         | `UnloadSound()`         |
| `LoadMusicStream()`   | `UnloadMusicStream()`   |
| `LoadModel()`         | `UnloadModel()`         |
| `LoadShader()`        | `UnloadShader()`        |
| `LoadRenderTexture()` | `UnloadRenderTexture()` |
| `LoadWave()`          | `UnloadWave()`          |

---

# 40. Typical 2D Game Object

Raylib does not force an entity architecture. You define your own C++ structures/classes.

```cpp
struct Player
{
    Vector2 position;
    Vector2 velocity;

    float speed;
    float radius;

    Color color;
};
```

Update:

```cpp
void UpdatePlayer(Player& player)
{
    float dt = GetFrameTime();

    Vector2 movement = {0, 0};

    if (IsKeyDown(KEY_W))
        movement.y -= 1;

    if (IsKeyDown(KEY_S))
        movement.y += 1;

    if (IsKeyDown(KEY_A))
        movement.x -= 1;

    if (IsKeyDown(KEY_D))
        movement.x += 1;

    if (Vector2Length(movement) > 0)
        movement = Vector2Normalize(movement);

    player.position =
        Vector2Add(
            player.position,
            Vector2Scale(
                movement,
                player.speed * dt
            )
        );
}
```

Draw:

```cpp
void DrawPlayer(const Player& player)
{
    DrawCircleV(
        player.position,
        player.radius,
        player.color
    );
}
```

---

# 41. Typical Game Architecture

A small project can start with:

```text
game.cpp
```

Then:

```text
src/
├── main.cpp
├── Player.h
├── Player.cpp
├── World.h
├── World.cpp
├── Renderer.h
└── Renderer.cpp
```

Larger:

```text
src/
├── core/
├── graphics/
├── input/
├── audio/
├── physics/
├── resources/
├── world/
├── entities/
└── main.cpp
```

**Raylib is the library. Your C++ architecture is yours.**

You decide:

```text
Entity architecture
Game state
Physics
Collision response
Animation system
Resource manager
Scene/world system
UI system
Editor
ECS or no ECS
Renderer architecture
Networking
Save system
Game logic
```

---

# 42. Practical Player + Wall + Collision

```cpp
#include "raylib.h"

int main()
{
    InitWindow(1280, 720, "Collision Test");
    SetTargetFPS(60);

    Rectangle player = {
        100,
        100,
        50,
        50
    };

    Rectangle wall = {
        500,
        200,
        300,
        50
    };

    float speed = 300.0f;

    while (!WindowShouldClose())
    {
        float dt = GetFrameTime();

        if (IsKeyDown(KEY_W))
            player.y -= speed * dt;

        if (IsKeyDown(KEY_S))
            player.y += speed * dt;

        if (IsKeyDown(KEY_A))
            player.x -= speed * dt;

        if (IsKeyDown(KEY_D))
            player.x += speed * dt;

        bool collision =
            CheckCollisionRecs(player, wall);

        BeginDrawing();

        ClearBackground(BLACK);

        DrawRectangleRec(
            player,
            collision ? RED : GREEN
        );

        DrawRectangleRec(
            wall,
            GRAY
        );

        EndDrawing();
    }

    CloseWindow();

    return 0;
}
```

This demonstrates:

```text
C++
 ↓
Raylib input
 ↓
game state
 ↓
collision query
 ↓
rendering
```

---

# 43. Practical Texture Example

```cpp
#include "raylib.h"

int main()
{
    InitWindow(1280, 720, "Texture Test");

    Texture2D texture =
        LoadTexture("assets/player.png");

    Vector2 position = {
        640,
        360
    };

    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        BeginDrawing();

        ClearBackground(BLACK);

        DrawTextureV(
            texture,
            position,
            WHITE
        );

        EndDrawing();
    }

    UnloadTexture(texture);

    CloseWindow();

    return 0;
}
```

---

# 44. Practical Camera + World Example

```cpp
#include "raylib.h"

int main()
{
    InitWindow(1280, 720, "Camera Test");

    Camera2D camera = {0};

    camera.target = {400, 300};
    camera.offset = {
        640,
        360
    };
    camera.zoom = 1.0f;

    Vector2 player = {
        400,
        300
    };

    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        float dt = GetFrameTime();

        if (IsKeyDown(KEY_W))
            player.y -= 200 * dt;

        if (IsKeyDown(KEY_S))
            player.y += 200 * dt;

        if (IsKeyDown(KEY_A))
            player.x -= 200 * dt;

        if (IsKeyDown(KEY_D))
            player.x += 200 * dt;

        camera.target = player;

        BeginDrawing();

        ClearBackground(DARKGRAY);

        BeginMode2D(camera);

        DrawGrid(100, 32.0f);

        DrawCircleV(
            player,
            20,
            RED
        );

        EndMode2D();

        EndDrawing();
    }

    CloseWindow();

    return 0;
}
```

---

# 45. Practical Asset Layout

```text
project/
├── game.cpp
├── assets/
│   ├── textures/
│   ├── sounds/
│   ├── music/
│   ├── fonts/
│   ├── models/
│   └── shaders/
├── src/
└── raylib-6.0_win64_mingw-w64/
```

---

# 46. Typical Game Loop Template

```cpp
while (!WindowShouldClose())
{
    // -------------------------
    // INPUT
    // -------------------------

    // keyboard
    // mouse
    // gamepad

    // -------------------------
    // TIME
    // -------------------------

    float dt = GetFrameTime();

    // -------------------------
    // UPDATE
    // -------------------------

    // player
    // physics
    // world
    // animation
    // AI
    // game state

    // -------------------------
    // DRAW
    // -------------------------

    BeginDrawing();

    ClearBackground(BLACK);

    // world
    // entities
    // effects
    // UI

    EndDrawing();
}
```

---

# 47. Typical Update Order

A practical order:

```text
INPUT
  ↓
PLAYER INPUT STATE
  ↓
GAME LOGIC
  ↓
PHYSICS
  ↓
COLLISION
  ↓
ANIMATION
  ↓
CAMERA
  ↓
RENDER
  ↓
UI
```

This is an architecture pattern, not a Raylib requirement.

---

# 48. What You Actually Need First

You do **not** need to memorize the entire API.

For your first serious projects, become comfortable with:

```text
InitWindow()
WindowShouldClose()
SetTargetFPS()
GetFrameTime()

BeginDrawing()
EndDrawing()
ClearBackground()

DrawRectangle()
DrawRectangleRec()
DrawCircle()
DrawLine()
DrawText()

Vector2
Rectangle
Color

IsKeyDown()
IsKeyPressed()
IsKeyReleased()

GetMousePosition()
IsMouseButtonDown()
IsMouseButtonPressed()

CheckCollisionRecs()
CheckCollisionCircleRec()

Camera2D
BeginMode2D()
EndMode2D()
GetScreenToWorld2D()
GetWorldToScreen2D()

LoadTexture()
DrawTexture()
DrawTextureV()
DrawTextureEx()
DrawTextureRec()
DrawTexturePro()
UnloadTexture()

LoadFont()
DrawTextEx()
UnloadFont()

InitAudioDevice()
LoadSound()
PlaySound()
UnloadSound()

LoadMusicStream()
PlayMusicStream()
UpdateMusicStream()
UnloadMusicStream()

LoadShader()
BeginShaderMode()
EndShaderMode()
UnloadShader()

LoadRenderTexture()
BeginTextureMode()
EndTextureMode()
UnloadRenderTexture()
```

Then progress:

```text
raymath
 ↓
textures + animation
 ↓
camera
 ↓
collision / physics
 ↓
audio
 ↓
render textures
 ↓
shaders
 ↓
3D
 ↓
custom engine architecture
```

---

# 49. The Core Raylib Mental Model

```text
                         YOUR C++ PROGRAM
                                │
              ┌─────────────────┼─────────────────┐
              │                 │                 │
              ▼                 ▼                 ▼
            INPUT            UPDATE             DRAW
              │                 │                 │
              │                 │                 │
              └─────────────────┼─────────────────┘
                                │
                                ▼
                              RAYLIB
                                │
      ┌───────────────┬─────────┼─────────┬───────────────┐
      ▼               ▼         ▼         ▼               ▼
    WINDOW          INPUT     GRAPHICS   AUDIO           MATH
      │               │         │         │               │
      └───────────────┴─────────┴─────────┴───────────────┘
                                │
                                ▼
                              GAME
                                │
                                ▼
                         YOUR ENGINE CODE
```

Raylib gives you the building blocks.

**You decide:**

```text
Entity architecture
Game state
Physics
Collision response
Animation system
Resource manager
Scene/world system
UI system
Editor
ECS or no ECS
Renderer architecture
Networking
Save system
Game logic
```

That is why Raylib is useful for learning engine development: it gives you enough to make a real game without forcing a huge engine architecture onto you.

---

# 50. Build / Compile Command

Current project layout:

```text
C++/
├── game.cpp
└── raylib-6.0_win64_mingw-w64/
    └── raylib-6.0_win64_mingw-w64/
        ├── include/
        └── lib/
```

Compile:

```powershell
g++ game.cpp -I./raylib-6.0_win64_mingw-w64/raylib-6.0_win64_mingw-w64/include -L./raylib-6.0_win64_mingw-w64/raylib-6.0_win64_mingw-w64/lib -lraylib -lopengl32 -lgdi32 -lwinmm -o main.exe
```

Run:

```powershell
.\main.exe
```

---

# 51. One-Screen Lookup

| I want to...           | Start with                                                |
| ---------------------- | --------------------------------------------------------- |
| Open a game window     | `InitWindow()`                                            |
| Make the game loop     | `WindowShouldClose()`                                     |
| Control FPS            | `SetTargetFPS()`                                          |
| Get delta time         | `GetFrameTime()`                                          |
| Move an object         | `Vector2` + input + `dt`                                  |
| Read keyboard          | `IsKeyDown()` / `IsKeyPressed()`                          |
| Read mouse             | `GetMousePosition()` / mouse buttons                      |
| Draw a shape           | `DrawRectangle()` / `DrawCircle()` / `DrawLine()`         |
| Draw text              | `DrawText()`                                              |
| Make collision boxes   | `Rectangle`                                               |
| Test collision         | `CheckCollisionRecs()`                                    |
| Make a camera          | `Camera2D` / `BeginMode2D()`                              |
| Convert mouse to world | `GetScreenToWorld2D()`                                    |
| Load a sprite          | `LoadTexture()`                                           |
| Draw a sprite          | `DrawTexture()` / `DrawTexturePro()`                      |
| Animate a sprite       | `DrawTextureRec()`                                        |
| Load a font            | `LoadFont()`                                              |
| Play SFX               | `LoadSound()` + `PlaySound()`                             |
| Play music             | `LoadMusicStream()` + `UpdateMusicStream()`               |
| Render to texture      | `LoadRenderTexture()`                                     |
| Add a shader           | `LoadShader()` + `BeginShaderMode()`                      |
| Make particles/effects | Textures + shapes + blend modes                           |
| Build 3D               | `Camera3D` + `BeginMode3D()`                              |
| Draw a 3D model        | `LoadModel()` + `DrawModel()`                             |
| Shoot/select in 3D     | `GetScreenToWorldRay()` + collision                       |
| Do vector math         | `raymath.h`                                               |
| Build an editor        | Mouse + camera + world/screen transforms + render texture |
| Build an engine        | C++ architecture + Raylib systems                         |

---

# 52. Main Rule

When building something:

```text
DO NOT ASK:
"What Raylib functions do I have to memorize?"

ASK:
"What do I need the computer to do?"

Then:

problem
  ↓
choose data
  ↓
choose C++ structure
  ↓
find Raylib function(s)
  ↓
implement
  ↓
test
  ↓
refactor
```

That is the practical way to learn both **C++ and Raylib** while actually building your own engine.
