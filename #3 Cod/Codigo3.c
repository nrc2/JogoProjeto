#include <stdio.h>
#include <raylib.h>

// para compilar: mingw32-make PLATFORM=PLATFORM_DESKTOP

static void Iniciar(void);
static void Desenhar(void);
static void UnloadGame(void);
/*
static void UpdateGame(void);       // Update game (one frame)
static void UpdateDrawFrame(void);  // Update and Draw (one frame)
*/
typedef enum GameScreen
{
    TITLE = 0,
    GAMEPLAY
} GameScreen;

int main(void)
{
    InitWindow(1200, 600, "Janela Teste");

    Iniciar();
    Desenhar();

    UnloadGame();

    CloseWindow();

    return 0;
}

void Iniciar(void)
{
}
void Desenhar(void)
{
    GameScreen currentScreen = TITLE;
    float speed = 200.0;

    Texture Background = LoadTexture("imgMenu/menu1.png");

    while (!WindowShouldClose())
    {
        BeginDrawing();

        ClearBackground(BLUE);

        switch (currentScreen)
        {
        case TITLE:
        {
            // TODO: Draw TITLE screen here!
            DrawTexture(Background, 0, 0, WHITE);
            // Image bgImage = LoadImage("menu.png");
            DrawText("Salve os Animais", 21, 22, 40, BLACK);
            DrawText("Salve os Animais", 20, 20, 40, WHITE);

            DrawText("PRESSIONE ENTER PARA INICIAR", 421, 252, 20, BLACK);
            DrawText("PRESSIONE ENTER PARA INICIAR", 420, 250, 20, WHITE);

        }
        break;
        case GAMEPLAY:
        {
            // TODO: Draw GAMEPLAY screen here!
            Texture backgroundTexture = LoadTexture("imgMenu/menu1.png");
            Vector2 BP = {0, 0};
            Rectangle FrameRecOut = {0.0f, 0.0f, (float)backgroundTexture.width, (float)backgroundTexture.height};
          // Rectangle FrameRecIn = {129.0f, 0.0f, 128.0f, 256.0f};
            Texture2D galinha = LoadTexture("personagem/galinha.png");
            Vector2 position = {100.0f, 430.0f};
            //Rectangle frameRec = {0.0f, 0.0f, (float)galinha.width / 4, (float)galinha.height};
            SetTargetFPS(60);
             float time = 0.0f;
            int frameAtual = 0; 
            while (!WindowShouldClose())
            {
                 time += GetFrameTime();
                if(time >= 0.1f){
                    time = 0.0f;
                    frameAtual += 1;
                } 

                FrameRecOut.x += GetFrameTime() * speed;
                if (FrameRecOut.x >= FrameRecOut.width)
                {
                    FrameRecOut.x = 0;
                }

                BeginDrawing();

                DrawTextureRec(backgroundTexture, FrameRecOut, BP, WHITE);
                DrawTextureRec(galinha, (Rectangle){(galinha.width/4)*(frameAtual % 4), 0, galinha.width / 4, galinha.height}, position, WHITE);
               /*  if (IsKeyPressed(KEY_UP)){
                    position.y += 4.0f;
                    DrawTextureRec(galinha, frameRec, position, WHITE);
                    if(IsKeyUp(KEY_UP)){
                        position.y += 4.0f;
                        DrawTextureRec(galinha, frameRec, position, WHITE);
                        

                    } */

                

                /* FrameRecOut.x -= FrameRecOut.height;
                DrawTextureRec(backgroundTexture, FrameRecOut, BP, WHITE);
                FrameRecOut.x += FrameRecOut.height; */
                /* DrawText("GAMEPLAY SCREEN", 20, 20, 40, MAROON);
                DrawText("PRESS ENTER or TAP to JUMP to ENDING SCREEN", 421, 220, 20, MAROON); */
                EndDrawing();
            
                 if (IsKeyPressed(KEY_ENTER) || IsGestureDetected(GESTURE_TAP))
            {
                 CloseWindow();
            }
            }
        }
        
        break;
        
        default:
            break;
        
        }
        EndDrawing();

        if (currentScreen == TITLE)
        {
            if (IsKeyPressed(KEY_ENTER) || IsGestureDetected(GESTURE_TAP))
            {
                currentScreen = GAMEPLAY;
            }
        }
    }
    
}
void UnloadGame(void)
{
}