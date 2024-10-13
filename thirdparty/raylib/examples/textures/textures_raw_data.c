/*******************************************************************************************
*
*   raylib [textures] example - Load textures from raw data
*
*   NOTE: Images are loaded in CPU memory (RAM); textures are loaded in GPU memory (VRAM)
*
*   Example originally created with raylib 1.3, last time updated with raylib 3.5
*
*   Example licensed under an unmodified zlib/libpng license, which is an OSI-certified,
*   BSD-like license that allows static linking with closed source software
*
*   Copyright (c) 2015-2024 Ramon Santamaria (@raysan5)
*
********************************************************************************************/

#include "raylib.h"

#include <stdlib.h>         // Required for: malloc() and free()

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 800;
    const int screenHeight = 450;

    rlInitWindow(screenWidth, screenHeight, "raylib [textures] example - texture from raw data");

    // NOTE: Textures MUST be loaded after Window initialization (OpenGL context is required)

    // Load RAW image data (512x512, 32bit RGBA, no file header)
    rlImage fudesumiRaw = rlLoadImageRaw("resources/fudesumi.raw", 384, 512, PIXELFORMAT_UNCOMPRESSED_R8G8B8A8, 0);
    Texture2D fudesumi = rlLoadTextureFromImage(fudesumiRaw);  // Upload CPU (RAM) image to GPU (VRAM)
    rlUnloadImage(fudesumiRaw);                                // Unload CPU (RAM) image data

    // Generate a checked texture by code
    int width = 960;
    int height = 480;

    // Dynamic memory allocation to store pixels data (rlColor type)
    rlColor *pixels = (rlColor *)malloc(width*height*sizeof(rlColor));

    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            if (((x/32+y/32)/1)%2 == 0) pixels[y*width + x] = ORANGE;
            else pixels[y*width + x] = GOLD;
        }
    }

    // Load pixels data into an image structure and create texture
    rlImage checkedIm = {
        .data = pixels,             // We can assign pixels directly to data
        .width = width,
        .height = height,
        .format = PIXELFORMAT_UNCOMPRESSED_R8G8B8A8,
        .mipmaps = 1
    };

    Texture2D checked = rlLoadTextureFromImage(checkedIm);
    rlUnloadImage(checkedIm);         // Unload CPU (RAM) image data (pixels)

    rlSetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    //---------------------------------------------------------------------------------------

    // Main game loop
    while (!rlWindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        // TODO: Update your variables here
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        rlBeginDrawing();

            rlClearBackground(RAYWHITE);

            rlDrawTexture(checked, screenWidth/2 - checked.width/2, screenHeight/2 - checked.height/2, rlFade(WHITE, 0.5f));
            rlDrawTexture(fudesumi, 430, -30, WHITE);

            rlDrawText("CHECKED TEXTURE ", 84, 85, 30, BROWN);
            rlDrawText("GENERATED by CODE", 72, 148, 30, BROWN);
            rlDrawText("and RAW IMAGE LOADING", 46, 210, 30, BROWN);

            rlDrawText("(c) Fudesumi sprite by Eiden Marsal", 310, screenHeight - 20, 10, BROWN);

        rlEndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    UnloadTexture(fudesumi);    // rlTexture unloading
    UnloadTexture(checked);     // rlTexture unloading

    rlCloseWindow();              // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}