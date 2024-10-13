/*******************************************************************************************
*
*   raylib [text] example - Codepoints loading
*
*   Example originally created with raylib 4.2, last time updated with raylib 2.5
*
*   Example licensed under an unmodified zlib/libpng license, which is an OSI-certified,
*   BSD-like license that allows static linking with closed source software
*
*   Copyright (c) 2022-2024 Ramon Santamaria (@raysan5)
*
********************************************************************************************/

#include "raylib.h"

#include <stdlib.h>         // Required for: calloc(), realloc(), free()
#include <string.h>         // Required for: memcpy()

// Text to be displayed, must be UTF-8 (save this code file as UTF-8)
// NOTE: It can contain all the required text for the game,
// this text will be scanned to get all the required codepoints
static char *text = "いろはにほへと　ちりぬるを\nわかよたれそ　つねならむ\nうゐのおくやま　けふこえて\nあさきゆめみし　ゑひもせす";

// Remove codepoint duplicates if requested
static int *CodepointRemoveDuplicates(int *codepoints, int codepointCount, int *codepointResultCount);

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 800;
    const int screenHeight = 450;

    rlInitWindow(screenWidth, screenHeight, "raylib [text] example - codepoints loading");

    // Get codepoints from text
    int codepointCount = 0;
    int *codepoints = rlLoadCodepoints(text, &codepointCount);

    // Removed duplicate codepoints to generate smaller font atlas
    int codepointsNoDupsCount = 0;
    int *codepointsNoDups = CodepointRemoveDuplicates(codepoints, codepointCount, &codepointsNoDupsCount);
    rlUnloadCodepoints(codepoints);

    // Load font containing all the provided codepoint glyphs
    // A texture font atlas is automatically generated
    Font font = rlLoadFontEx("resources/DotGothic16-Regular.ttf", 36, codepointsNoDups, codepointsNoDupsCount);

    // Set bilinear scale filter for better font scaling
    rlSetTextureFilter(font.texture, TEXTURE_FILTER_BILINEAR);

    rlSetTextLineSpacing(20);         // Set line spacing for multiline text (when line breaks are included '\n')

    // Free codepoints, atlas has already been generated
    free(codepointsNoDups);

    bool showFontAtlas = false;

    int codepointSize = 0;
    char *ptr = text;

    rlSetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!rlWindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        if (rlIsKeyPressed(KEY_SPACE)) showFontAtlas = !showFontAtlas;

        // Testing code: getting next and previous codepoints on provided text
        if (rlIsKeyPressed(KEY_RIGHT))
        {
            // Get next codepoint in string and move pointer
            rlGetCodepointNext(ptr, &codepointSize);
            ptr += codepointSize;
        }
        else if (rlIsKeyPressed(KEY_LEFT))
        {
            // Get previous codepoint in string and move pointer
            rlGetCodepointPrevious(ptr, &codepointSize);
            ptr -= codepointSize;
        }
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        rlBeginDrawing();

            rlClearBackground(RAYWHITE);

            rlDrawRectangle(0, 0, rlGetScreenWidth(), 70, BLACK);
            rlDrawText(rlTextFormat("Total codepoints contained in provided text: %i", codepointCount), 10, 10, 20, GREEN);
            rlDrawText(rlTextFormat("Total codepoints required for font atlas (duplicates excluded): %i", codepointsNoDupsCount), 10, 40, 20, GREEN);

            if (showFontAtlas)
            {
                // Draw generated font texture atlas containing provided codepoints
                rlDrawTexture(font.texture, 150, 100, BLACK);
                rlDrawRectangleLines(150, 100, font.texture.width, font.texture.height, BLACK);
            }
            else
            {
                // Draw provided text with laoded font, containing all required codepoint glyphs
                rlDrawTextEx(font, text, (Vector2) { 160, 110 }, 48, 5, BLACK);
            }

            rlDrawText("Press SPACE to toggle font atlas view!", 10, rlGetScreenHeight() - 30, 20, GRAY);

        rlEndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    rlUnloadFont(font);     // Unload font

    rlCloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}

// Remove codepoint duplicates if requested
// WARNING: This process could be a bit slow if there text to process is very long
static int *CodepointRemoveDuplicates(int *codepoints, int codepointCount, int *codepointsResultCount)
{
    int codepointsNoDupsCount = codepointCount;
    int *codepointsNoDups = (int *)calloc(codepointCount, sizeof(int));
    memcpy(codepointsNoDups, codepoints, codepointCount*sizeof(int));

    // Remove duplicates
    for (int i = 0; i < codepointsNoDupsCount; i++)
    {
        for (int j = i + 1; j < codepointsNoDupsCount; j++)
        {
            if (codepointsNoDups[i] == codepointsNoDups[j])
            {
                for (int k = j; k < codepointsNoDupsCount; k++) codepointsNoDups[k] = codepointsNoDups[k + 1];

                codepointsNoDupsCount--;
                j--;
            }
        }
    }

    // NOTE: The size of codepointsNoDups is the same as original array but
    // only required positions are filled (codepointsNoDupsCount)

    *codepointsResultCount = codepointsNoDupsCount;
    return codepointsNoDups;
}