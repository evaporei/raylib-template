/*******************************************************************************************
*
*   raylib [core] example - Windows drop files
*
*   NOTE: This example only works on platforms that support drag & drop (Windows, Linux, OSX, Html5?)
*
*   Example originally created with raylib 1.3, last time updated with raylib 4.2
*
*   Example licensed under an unmodified zlib/libpng license, which is an OSI-certified,
*   BSD-like license that allows static linking with closed source software
*
*   Copyright (c) 2015-2024 Ramon Santamaria (@raysan5)
*
********************************************************************************************/

#include "raylib.h"

#include <stdlib.h>         // Required for: calloc(), free()

#define MAX_FILEPATH_RECORDED   4096
#define MAX_FILEPATH_SIZE       2048

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 800;
    const int screenHeight = 450;

    rlInitWindow(screenWidth, screenHeight, "raylib [core] example - drop files");

    int filePathCounter = 0;
    char *filePaths[MAX_FILEPATH_RECORDED] = { 0 }; // We will register a maximum of filepaths

    // Allocate space for the required file paths
    for (int i = 0; i < MAX_FILEPATH_RECORDED; i++)
    {
        filePaths[i] = (char *)RL_CALLOC(MAX_FILEPATH_SIZE, 1);
    }

    rlSetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!rlWindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        if (rlIsFileDropped())
        {
            rlFilePathList droppedFiles = rlLoadDroppedFiles();

            for (int i = 0, offset = filePathCounter; i < (int)droppedFiles.count; i++)
            {
                if (filePathCounter < (MAX_FILEPATH_RECORDED - 1))
                {
                    rlTextCopy(filePaths[offset + i], droppedFiles.paths[i]);
                    filePathCounter++;
                }
            }

            rlUnloadDroppedFiles(droppedFiles);    // Unload filepaths from memory
        }
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        rlBeginDrawing();

            rlClearBackground(RAYWHITE);

            if (filePathCounter == 0) rlDrawText("Drop your files to this window!", 100, 40, 20, DARKGRAY);
            else
            {
                rlDrawText("Dropped files:", 100, 40, 20, DARKGRAY);

                for (int i = 0; i < filePathCounter; i++)
                {
                    if (i%2 == 0) rlDrawRectangle(0, 85 + 40*i, screenWidth, 40, rlFade(LIGHTGRAY, 0.5f));
                    else rlDrawRectangle(0, 85 + 40*i, screenWidth, 40, rlFade(LIGHTGRAY, 0.3f));

                    rlDrawText(filePaths[i], 120, 100 + 40*i, 10, GRAY);
                }

                rlDrawText("Drop new files...", 100, 110 + 40*filePathCounter, 20, DARKGRAY);
            }

        rlEndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    for (int i = 0; i < MAX_FILEPATH_RECORDED; i++)
    {
        RL_FREE(filePaths[i]); // Free allocated memory for all filepaths
    }

    rlCloseWindow();          // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}