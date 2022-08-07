#include <stdio.h>
#include <raylib.h>

// para compilar: mingw32-make PLATFORM=PLATFORM_DESKTOP

static void Iniciar(void);
static void Desenhar(void);
static void UnloadGame(void);
/* static void InitGame(void);         // Initialize game
static void UpdateGame(void);       // Update game (one frame)
static void DrawGame(void);         // Draw game (one frame)
static void UnloadGame(void);       // Unload game
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

            /*
            if(IsKeyDown(KEY_ENTER)) {
            //comeÃ§ar o jogo

            }
            */
        }
        break;
        case GAMEPLAY:
        {
            // TODO: Draw GAMEPLAY screen here!
            Texture backgroundTexture = LoadTexture("imgMenu/menu1.png");
            Vector2 BP = {0, 0};
            Rectangle FrameRecOut = {0.0f, 0.0f, (float)backgroundTexture.width, (float)backgroundTexture.height};
            // Rectangle FrameRecIn = {129.0f, 0.0f, 128.0f, 256.0f};
         while(!WindowShouldClose()){
                FrameRecOut.x += GetFrameTime() * speed;
                if (FrameRecOut.x >= FrameRecOut.width)
                {
                    FrameRecOut.x = 0;
                }
         
 BeginDrawing();
   
                DrawTextureRec(backgroundTexture, FrameRecOut, BP, WHITE);
                /* FrameRecOut.x -= FrameRecOut.height;
                DrawTextureRec(backgroundTexture, FrameRecOut, BP, WHITE);
                FrameRecOut.x += FrameRecOut.height; */
                 EndDrawing();
         }

                DrawText("GAMEPLAY SCREEN", 20, 20, 40, MAROON);
                DrawText("PRESS ENTER or TAP to JUMP to ENDING SCREEN", 421, 220, 20, MAROON);
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