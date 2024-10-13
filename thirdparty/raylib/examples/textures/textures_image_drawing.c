/*******************************************************************************************
*
*   raylib [textures] example - rlImage loading and drawing on it
*
*   NOTE: Images are loaded in CPU memory (RAM); textures are loaded in GPU memory (VRAM)
*
*   Example originally created with raylib 1.4, last time updated with raylib 1.4
*
*   Example licensed under an unmodified zlib/libpng license, which is an OSI-certified,
*   BSD-like license that allows static linking with closed source software
*
*   Copyright (c) 2016-2024 Ramon Santamaria (@raysan5)
*
********************************************************************************************/

#include "raylib.h"

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 800;
    const int screenHeight = 450;

    rlInitWindow(screenWidth, screenHeight, "raylib [textures] example - image drawing");

    // NOTE: Textures MUST be loaded after Window initialization (OpenGL context is required)

    rlImage cat = rlLoadImage("resources/cat.png");             // Load image in CPU memory (RAM)
    rlImageCrop(&cat, (rlRectangle){ 100, 10, 280, 380 });      // Crop an image piece
    rlImageFlipHorizontal(&cat);                              // Flip cropped image horizontally
    rlImageResize(&cat, 150, 200);                            // Resize flipped-cropped image

    rlImage parrots = rlLoadImage("resources/parrots.png");     // Load image in CPU memory (RAM)

    // Draw one image over the other with a scaling of 1.5f
    rlImageDraw(&parrots, cat, (rlRectangle){ 0, 0, (float)cat.width, (float)cat.height }, (rlRectangle){ 30, 40, cat.width*1.5f, cat.height*1.5f }, WHITE);
    rlImageCrop(&parrots, (rlRectangle){ 0, 50, (float)parrots.width, (float)parrots.height - 100 }); // Crop resulting image

    // Draw on the image with a few image draw methods
    rlImageDrawPixel(&parrots, 10, 10, RAYWHITE);
    rlImageDrawCircleLines(&parrots, 10, 10, 5, RAYWHITE);
    rlImageDrawRectangle(&parrots, 5, 20, 10, 10, RAYWHITE);

    rlUnloadImage(cat);       // Unload image from RAM

    // Load custom font for drawing on image
    rlFont font = rlLoadFont("resources/custom_jupiter_crash.png");

    // Draw over image using custom font
    rlImageDrawTextEx(&parrots, font, "PARROTS & CAT", (rlVector2){ 300, 230 }, (float)font.baseSize, -2, WHITE);

    rlUnloadFont(font);       // Unload custom font (already drawn used on image)

    Texture2D texture = rlLoadTextureFromImage(parrots);      // rlImage converted to texture, uploaded to GPU memory (VRAM)
    rlUnloadImage(parrots);   // Once image has been converted to texture and uploaded to VRAM, it can be unloaded from RAM

    rlSetTargetFPS(60);
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

            rlDrawTexture(texture, screenWidth/2 - texture.width/2, screenHeight/2 - texture.height/2 - 40, WHITE);
            rlDrawRectangleLines(screenWidth/2 - texture.width/2, screenHeight/2 - texture.height/2 - 40, texture.width, texture.height, DARKGRAY);

            rlDrawText("We are drawing only one texture from various images composed!", 240, 350, 10, DARKGRAY);
            rlDrawText("Source images have been cropped, scaled, flipped and copied one over the other.", 190, 370, 10, DARKGRAY);

        rlEndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    UnloadTexture(texture);       // rlTexture unloading

    rlCloseWindow();                // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}
