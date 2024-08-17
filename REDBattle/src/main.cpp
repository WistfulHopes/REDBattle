#include <cmath>
#include <fstream>
#include <Game/REDGameCommon.h>
#include <vector>
#include <raylib.h>

#include "raylib_interface/RaylibState.h"
#include "AALib/AASystemRED.h"

#define ONE_FRAME (1.f / 60.f)

int main()
{
    const int screenWidth = 1280;
    const int screenHeight = 720;

    int windowWidth = 2560;
    int windowHeight = 1440;
    
    InitWindow(windowWidth, windowHeight, "REDBattle");
    SetTargetFPS(60);
    const RenderTexture2D renderTexture = LoadRenderTexture(screenWidth, screenHeight);
    RaylibState raylibState {};
    SCENE_ID curSceneId {};

    float elapsedTime = 0.f;

    while (!WindowShouldClose())
    {
        float deltaSeconds = GetFrameTime();
        elapsedTime += deltaSeconds;

        while (elapsedTime >= ONE_FRAME)
        {
            REDGameCommon::GetInstance()->Tick(deltaSeconds);
            elapsedTime -= ONE_FRAME;
        }

        if (curSceneId != REDGameCommon::GetInstance()->GetSceneID())
        {
            raylibState.Init(REDGameCommon::GetInstance()->GetScene());
            curSceneId = REDGameCommon::GetInstance()->GetSceneID();
        }
        
        if (AASystemRED::GetInstance()) {
            raylibState.SetSysCamera(AASystemRED::GetInstance()->GetCameraManager().Get(0));
        }

        BeginDrawing();

        BeginTextureMode(renderTexture);
        ClearBackground(RAYWHITE);
        raylibState.Draw();
        EndTextureMode();

        DrawTexturePro(
            renderTexture.texture,
            {0.0f, 0.0f, (float)screenWidth, -(float)screenHeight},
            {0.0f, 0.0f, (float)windowWidth, (float)windowHeight},
            {0.0f, 0.0f},
            0.0f, WHITE
        );
        
        EndDrawing();
    }
    CloseWindow();
    return 0;
}
