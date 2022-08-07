#include <stdio.h>
#include <raylib.h>

#define NUM_MAX_ENEMIES 3

typedef struct Enemy
{
    Rectangle rec;
    Vector2 speed;
    bool active;
    Color color;
} Enemy;

static Enemy enemy[4] = {0};

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

            DrawText("Salve os Animais", 21, 22, 50, BLACK);
            DrawText("Salve os Animais", 20, 20, 50, WHITE);

            DrawText("PRESSIONE ENTER PARA INICIAR", 421, 252, 20, BLACK);
            DrawText("PRESSIONE ENTER PARA INICIAR", 420, 250, 20, WHITE);
        }
        break;

        case GAMEPLAY:
        {
            // TODO: Draw GAMEPLAY screen here!

            // Upload do background
            Texture backgroundTexture = LoadTexture("imgMenu/menu1.png");
            Vector2 BP = {0, 0};
            Rectangle FrameRecOut = {0.0f, 0.0f, (float)backgroundTexture.width, (float)backgroundTexture.height};
            // Upload do personagem
            Texture2D galinha = LoadTexture("personagem/galinha.png");
            Vector2 position = {100.0f, 430.0f};
            Rectangle boxA = {10, 430.0f, 60, 60};
            int boxASpeedX = 4;
            Rectangle boxB = {100.0f, 430.0f, 70, 70};
            // Rectangle boxCollision = {0}; // Collision rectangle

            int screenUpperLimit = 40; // Top menu limits

            bool pause = false; // Movement pause
            bool collision[5] = {false};

            //int timeaux = 0.0f;

            SetTargetFPS(60);
            float time = 0.0f;
            int frameAtual = 0;
            int pulou = 0;

            //timeaux += GetFrameTime();

            for (int i = 0; i < 3; i++)
            {
               /*  if (timeaux >= 0.1f)
                { */
                    //timeaux = 0.0f;

                    enemy[i].rec.width = 40;
                    enemy[i].rec.height = 40;

                    enemy[i].rec.x = GetRandomValue(1200, 1200 + 1000);
                    enemy[i].rec.y = 460;
                    enemy[i].speed.x = 7;
                    enemy[i].speed.y = 7;
                    enemy[i].active = true;
                    enemy[i].color = BLUE;
                //}
            }

            while (!WindowShouldClose())
            {
                if (!pause)
                    boxA.x += boxASpeedX;
                if (((boxA.x + boxA.width) >= GetScreenWidth()) || (boxA.x <= 0))
                    boxASpeedX *= -1;
                for (int i = 0; i < 3; i++)
                {
                    if (enemy[i].active)
                    {
                        enemy[i].rec.x -= enemy[i].speed.x;

                        if (enemy[i].rec.x < 0)
                        {

                            /* if (timeaux >= 0.1f)
                            { */
                                //timeaux = 0.0f;
                                enemy[i].rec.x = GetRandomValue(1200, 1200 + 1000);
                                enemy[i].rec.y = 460;
                            //}
                        }
                    }
                }
                  
    
               
                    //collision = CheckCollisionRecs(boxA, boxB);
 for (int i = 0; i < 3; i++)
            {
                    collision[i] = CheckCollisionRecs(enemy[i].rec, boxB);
            }
                

                    /* if (collision)
                        boxCollision = GetCollisionRec(boxA, boxB); */

                    // tempo para trocar frame do personagem
                    time += GetFrameTime();
                    if (time >= 0.1f)
                    {
                        time = 0.0f;
                        frameAtual += 1;
                    }
                    // condição de pulo
                    if (IsKeyDown(KEY_SPACE) && (pulou == 0))
                        pulou = 1;
                    if ((pulou == 1) && (position.y != 300))
                    {
                        position.y -= 7;
                        boxB.y -= 5;
                    }
                    if (position.y == 300)
                        pulou = 2;
                    if ((pulou == 2) && (position.y != 430))
                    {
                        position.y += 7;
                        boxB.y += 5;
                    }
                    if (position.y == 430)
                        pulou = 0;
                    // condição de scrolling do background
                    FrameRecOut.x += GetFrameTime() * speed;
                    if (FrameRecOut.x >= FrameRecOut.width)
                    {
                        FrameRecOut.x = 0;
                    }

                    BeginDrawing();

                    DrawTextureRec(backgroundTexture, FrameRecOut, BP, WHITE);
                    // DrawRectangleRec(boxB, BLUE);
                    DrawTextureRec(galinha, (Rectangle){(galinha.width / 4) * (frameAtual % 4), 0, galinha.width / 4, galinha.height}, position, WHITE);
                    // DrawRectangle(0, 0, 1200, screenUpperLimit, collision ? RED : BLACK);
                    DrawRectangleRec(boxA, GOLD);


    
                for (int i = 0; i < 3; i++){
                    if (collision[i])
                    {
                        // Draw collision area
                        // DrawRectangleRec(boxCollision, LIME);

                        // Draw collision message
                        DrawText("COLLISION!", GetScreenWidth() / 2 - MeasureText("COLLISION!", 20) / 2, screenUpperLimit / 2 - 10, 20, BLACK);
                    }
                }

                    for (int i = 0; i < 4; i++)
                    {
                        if (enemy[i].active)
                            DrawRectangleRec(enemy[i].rec, enemy[i].color);
                    }
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