#include <stdio.h>
#include <raylib.h>

typedef enum
{
    FIRST = 0,
    SECOND,
    THIRD,
    QUARTA,
    QUINTA,
    SEXTA,

} EnemyWave;

typedef struct RecObs
{
    Rectangle rec;
    Vector2 speed;
    bool active;
    Color color;
} RecObs;

typedef struct Faca
{
    Texture2D faca;
    Vector2 facaPosition;

} Faca;

static RecObs enemy[4] = {0};
static EnemyWave wave = {0};
static Faca faquinha[4] = {0};
static int vidas = 0;
static int level = 0;

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
    GAMEPLAY,
    GAMEOVER

} GameScreen;

// função para filtrar as passagens de frequencias baixas

/* static void AudioProcessEffectLPF(void *buffer, unsigned int frames)
{
    static float low[2] = {0.0f, 0.0f};
    static const float cutoff = 70.0f / 44100.0f;      // 70 Hz lowpass filter
    const float k = cutoff / (cutoff + 0.1591549431f); // RC filter formula

    for (unsigned int i = 0; i < frames * 2; i += 2)
    {
        float l = ((float *)buffer)[i], r = ((float *)buffer)[i + 1];
        low[0] += k * (l - low[0]);
        low[1] += k * (r - low[1]);
        ((float *)buffer)[i] = low[0];
        ((float *)buffer)[i + 1] = low[1];
    }
} */

int main(void)
{
    InitWindow(1200, 600, "Salve os Animais");

    // InitAudioDevice();

    // Music musica = LoadMusicStream("musica/terror.mp3"); // COLOCAR O ARQUIVO DE SOM BAIXADO <--

    Iniciar();

    Desenhar();

    UnloadGame();

    CloseWindow();

    return 0;
}

void Iniciar(void)
{
    for (int i = 0; i < 3; i++)
    {
        enemy[i].rec.width = 40;
        enemy[i].rec.height = 40;

        enemy[i].rec.x = GetRandomValue(1200, 1200 + 1000);
        enemy[i].rec.y = 460;
        enemy[i].speed.x = 7;
        enemy[i].speed.y = 7;
        enemy[i].active = true;
        enemy[i].color = BLUE;

        faquinha[i].faca = LoadTexture("obstaculos/faca5.png");
        faquinha[i].facaPosition.x = enemy[i].rec.x - 70;
        faquinha[i].facaPosition.y = 380;
    }

    vidas = 0;
    wave = FIRST;
    level = 0;
}

void Desenhar(void)
{
    InitAudioDevice();
    GameScreen currentScreen = TITLE;
    float speed = 200.0;

    Texture Background = LoadTexture("imgMenu/menu1.png");

    for (int i = 0; i < 3; i++)
    {
        faquinha[i].faca = LoadTexture("obstaculos/faca5.png");
    }

    Music musica = LoadMusicStream("musica/terror.mp3");

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

            DrawText("Salve os Animais", 21, 22, 70, BLACK);
            DrawText("Salve os Animais", 20, 20, 70, WHITE);

            DrawText("Seu objetivo é salvar a galinha do abatedouro", 21, 94, 20, BLACK);
            DrawText("Seu objetivo é salvar a galinha do abatedouro", 20, 92, 20, RED);

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
            // Upload caixa amarela (chefão)
            Rectangle boxA = {10, 430.0f, 60, 60};
            int boxASpeedX = 4;
            // Upload obstáculos
            Rectangle boxB = {100.0f, 430.0f, 50, 70};
            Texture2D lady = LoadTexture("anjolina.png");
            Vector2 ladyposition = {90.0f, 430.0f};
            Texture BackgroundChoc = LoadTexture("chocolate3.png");
            Texture2D chat = LoadTexture("chat.png");
            Vector2 chatposition = {190.0f, 300.0f};
            Texture BackgroundBlood = LoadTexture("blood.png");

            int screenUpperLimit = 40; // Top menu limits

            bool pause = false; // Movement pause
            bool collision[5] = {false};

            SetTargetFPS(60);
            float time = 0.0f;
            int frameAtual = 0;
            int pulou = 0;

            if (IsKeyPressed('P'))
                pause = !pause;

            while (!WindowShouldClose())
            {
                /*   if (wave == FIRST)
                  { */
                UpdateMusicStream(musica); // TOCAR MUSICA

                ClearBackground(RAYWHITE);

                if (wave == FIRST)
                {
                    for (int i = 0; i < 3; i++)
                    {
                        if (enemy[i].active)
                        {
                            enemy[i].rec.x -= enemy[i].speed.x;
                            faquinha[i].facaPosition.x -= enemy[i].speed.x;

                            if (enemy[i].rec.x < 0)
                            {
                                enemy[i].rec.x = GetRandomValue(1200, 1200 + 1000);
                                enemy[i].rec.y = 460;
                                faquinha[i].facaPosition.x = enemy[i].rec.x - 70;
                                faquinha[i].facaPosition.y = 380;
                            }
                        }
                    }

                    // condição de scrolling do background
                    FrameRecOut.x += GetFrameTime() * speed;
                    if (FrameRecOut.x >= FrameRecOut.width)
                    {
                        FrameRecOut.x = 0;
                    }
                }
                if (pause)
                {

                    StopMusicStream(musica);
                }

                // collision = CheckCollisionRecs(boxA, boxB);
                for (int i = 0; i < 3; i++)
                {
                    collision[i] = CheckCollisionRecs(enemy[i].rec, boxB);
                    if (collision[i])
                    {
                        vidas += 1;
                    }
                }

                // Upload Barra de vida
                Rectangle boxC = {140.0f, 20.0f, 192 - vidas * 4, 30};
                Rectangle boxD = {139.0f, 19.0f, 194, 32};

                // tempo para trocar frame do personagem
                time += GetFrameTime();
                if (time >= 0.1f)
                {
                    time = 0.0f;
                    frameAtual += 1;
                }

                // condição de pulo
                if (IsKeyDown(KEY_SPACE) && (pulou == 0))
                {
                    pulou = 1;
                    level++;
                }
                if ((pulou == 1) && (position.y != 260))
                {
                    position.y -= 10;
                    boxB.y -= 10;
                }
                if (position.y == 260)
                    pulou = 2;
                if ((pulou == 2) && (position.y != 430))
                {
                    position.y += 10;
                    boxB.y += 10;
                }
                if (position.y >= 430)
                    pulou = 0;
                // Mudança de nível a partir da quantidade de pulos
                if (level >= 5)
                {
                    wave = SECOND;
                }
                if (level >= 10)
                {
                    wave = THIRD;
                }
                if (level >= 15)
                {
                    wave = QUARTA;
                }
                if (level >= 25)
                {
                    wave = QUINTA;
                }
                if (level >= 30)
                {
                    wave = SEXTA;
                }

                if (wave == SECOND)
                {

                    ClearBackground(RAYWHITE);

                    if (!pause)
                        boxA.x += boxASpeedX;
                    if (((boxA.x + boxA.width) >= GetScreenWidth()) || (boxA.x <= 0))
                        boxASpeedX *= -1;

                    for (int i = 0; i < 3; i++)
                    {
                        if (enemy[i].active)
                        {
                            enemy[i].rec.x -= enemy[i].speed.x + 1;
                            faquinha[i].facaPosition.x -= enemy[i].speed.x + 1;
                        }
                        if (enemy[i].rec.x < 0)
                        {
                            enemy[i].rec.x = GetRandomValue(1200, 1200 + 1000);
                            enemy[i].rec.y = 460;
                            faquinha[i].facaPosition.x = enemy[i].rec.x - 70;
                            faquinha[i].facaPosition.y = 380;
                        }
                    }
                    FrameRecOut.x += GetFrameTime() * speed + 1;
                    if (FrameRecOut.x >= FrameRecOut.width)
                    {
                        FrameRecOut.x = 0;
                    }
                }

                if (wave == THIRD)
                {

                    ClearBackground(RAYWHITE);

                    if (!pause)
                        boxA.x += boxASpeedX;
                    if (((boxA.x + boxA.width) >= GetScreenWidth()) || (boxA.x <= 0))
                        boxASpeedX *= -1;

                    for (int i = 0; i < 3; i++)
                    {
                        if (enemy[i].active)
                        {
                            enemy[i].rec.x -= enemy[i].speed.x + 2;
                            faquinha[i].facaPosition.x -= enemy[i].speed.x + 2;
                        }
                        if (enemy[i].rec.x < 0)
                        {
                            enemy[i].rec.x = GetRandomValue(1200, 1200 + 1000);
                            enemy[i].rec.y = 460;
                            faquinha[i].facaPosition.x = enemy[i].rec.x - 70;
                            faquinha[i].facaPosition.y = 380;
                        }
                    }
                    FrameRecOut.x += GetFrameTime() * speed + 2;
                    if (FrameRecOut.x >= FrameRecOut.width)
                    {
                        FrameRecOut.x = 0;
                    }
                }

                if (wave == QUARTA)
                {

                    ClearBackground(RAYWHITE);

                    if (!pause)
                        boxA.x += boxASpeedX;
                    if (((boxA.x + boxA.width) >= GetScreenWidth()) || (boxA.x <= 0))
                        boxASpeedX *= -1;

                    for (int i = 0; i < 3; i++)
                    {
                        if (enemy[i].active)
                        {
                            enemy[i].rec.x -= enemy[i].speed.x + 3;
                            faquinha[i].facaPosition.x -= enemy[i].speed.x + 3;
                        }
                        if (enemy[i].rec.x < 0)
                        {
                            enemy[i].rec.x = GetRandomValue(1200, 1200 + 1000);
                            enemy[i].rec.y = 460;
                            faquinha[i].facaPosition.x = enemy[i].rec.x - 70;
                            faquinha[i].facaPosition.y = 380;
                        }
                    }
                    FrameRecOut.x += GetFrameTime() * speed + 3;
                    if (FrameRecOut.x >= FrameRecOut.width)
                    {
                        FrameRecOut.x = 0;
                    }
                }

                if (wave == QUINTA)
                {

                    ClearBackground(RAYWHITE);

                    if (!pause)
                        boxA.x += boxASpeedX;
                    if (((boxA.x + boxA.width) >= GetScreenWidth()) || (boxA.x <= 0))
                        boxASpeedX *= -1;

                    for (int i = 0; i < 3; i++)
                    {
                        if (enemy[i].active)
                        {
                            enemy[i].rec.x -= enemy[i].speed.x + 5;
                            faquinha[i].facaPosition.x -= enemy[i].speed.x + 5;
                        }
                        if (enemy[i].rec.x < 0)
                        {
                            enemy[i].rec.x = GetRandomValue(1200, 1200 + 1000);
                            enemy[i].rec.y = 460;
                            faquinha[i].facaPosition.x = enemy[i].rec.x - 70;
                            faquinha[i].facaPosition.y = 380;
                        }
                    }
                    FrameRecOut.x += GetFrameTime() * speed + 4;
                    if (FrameRecOut.x >= FrameRecOut.width)
                    {
                        FrameRecOut.x = 0;
                    }
                }
                if (wave == SEXTA)
                {

                    ClearBackground(RAYWHITE);

                    if (!pause)
                        boxA.x += boxASpeedX;
                    if (((boxA.x + boxA.width) >= GetScreenWidth()) || (boxA.x <= 0))
                        boxASpeedX *= -1;

                    for (int i = 0; i < 3; i++)
                    {
                        if (enemy[i].active)
                        {
                            enemy[i].rec.x -= enemy[i].speed.x + 7;
                            faquinha[i].facaPosition.x -= enemy[i].speed.x + 7;
                        }
                        if (enemy[i].rec.x < 0)
                        {
                            enemy[i].rec.x = GetRandomValue(1200, 1200 + 1000);
                            enemy[i].rec.y = 460;
                            faquinha[i].facaPosition.x = enemy[i].rec.x - 70;
                            faquinha[i].facaPosition.y = 380;
                        }
                    }
                    FrameRecOut.x += GetFrameTime() * speed + 7;
                    if (FrameRecOut.x >= FrameRecOut.width)
                    {
                        FrameRecOut.x = 0;
                    }
                }

                BeginDrawing();
                if (vidas <= 32)
                {
                    DrawTextureRec(backgroundTexture, FrameRecOut, BP, WHITE);
                    // DrawRectangleRec(boxB, BLUE);
                    DrawTextureRec(galinha, (Rectangle){(galinha.width / 4) * (frameAtual % 4), 0, galinha.width / 4, galinha.height}, position, WHITE);
                    /*  DrawRectangleRec(boxA, GOLD);
                     */
                    for (int i = 0; i < 3; i++)
                    {
                        if (collision[i])
                        {
                            // Draw collision message
                            DrawText("COLLISION!", GetScreenWidth() / 2 - MeasureText("COLLISION!", 20) / 2, screenUpperLimit / 2 - 10, 20, BLACK);
                        }
                    }

                    DrawText(TextFormat("LIFE:"), 20, 20, 40, RED);
                    DrawText(TextFormat("LIFE:"), 21, 21, 40, BLACK);

                    DrawRectangleRec(boxD, WHITE);
                    DrawRectangleRec(boxC, RED);

                    for (int i = 0; i < 4; i++)
                    {
                        if (enemy[i].active)
                        {
                            // DrawRectangleRec(enemy[i].rec, enemy[i].color);
                        }
                        DrawTextureRec(
                            faquinha[i].faca,
                            (Rectangle){0, 0, faquinha[0].faca.width, faquinha[0].faca.height},
                            faquinha[i].facaPosition, WHITE);
                    }
                }
                if (level > 40)
                {
                    DrawTexture(BackgroundChoc, 0, 0, WHITE);
                    DrawTextureRec(lady, (Rectangle){0, 0, lady.width, lady.height}, ladyposition, WHITE);
                    DrawTextureRec(chat, (Rectangle){0, 0, chat.width, chat.height}, chatposition, WHITE);
                    DrawText("YOU WIN", GetScreenWidth() / 2 - MeasureText("YOU WIN", 100) / 2, GetScreenHeight() / 2 - 49, 100, GRAY);
                    DrawText("YOU WIN", GetScreenWidth() / 2 - MeasureText("YOU WIN", 100) / 2, GetScreenHeight() / 2 - 50, 100, BLACK);
                }

                if (vidas > 32 && level <= 40)
                {
                    DrawTexture(BackgroundBlood, 0, 0, WHITE);

                    DrawText("PRESS [ENTER] TO PLAY AGAIN", GetScreenWidth() / 2 - MeasureText("PRESS [ENTER] TO PLAY AGAIN", 20) / 2, GetScreenHeight() / 2 - 48, 20, GRAY);
                    DrawText("PRESS [ENTER] TO PLAY AGAIN", GetScreenWidth() / 2 - MeasureText("PRESS [ENTER] TO PLAY AGAIN", 20) / 2, GetScreenHeight() / 2 - 50, 20, BLACK);
                    DrawText("YOU LOST", 23, 24, 150, GRAY);
                    DrawText("YOU LOST", 21, 22, 150, BLACK);
                }

                EndDrawing();

                if (IsKeyPressed(KEY_ENTER) || IsGestureDetected(GESTURE_TAP))
                {
                    /*  UnloadMusicStream(musica); // Unload music stream buffers from RAM

                     CloseAudioDevice(); // parar a musica */

                    Iniciar();
                    vidas = 0;
                }
                //}
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