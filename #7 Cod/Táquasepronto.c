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
static int vitoria = 40;

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

int main(void)
{
    InitWindow(1200, 600, "Salve os Animais");

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
    vitoria = 40;
}

void Desenhar(void)
{

    GameScreen currentScreen = TITLE;
    float speed = 200.0;

    Texture Background = LoadTexture("imgFundo/menu1.png");

    for (int i = 0; i < 3; i++)
    {
        faquinha[i].faca = LoadTexture("obstaculos/faca5.png");
    }

    InitAudioDevice();
    Music musica = LoadMusicStream("musica/terror.mp3");
    Music musica2 = LoadMusicStream("musica/suspense.mp3");
    Music musica3 = LoadMusicStream("musica/win.mp3");
     // Upload do background
            Texture backgroundTexture = LoadTexture("imgFundo/menu1.png");
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
            // Upload Anjolina Multiverso
            Texture2D lady = LoadTexture("personagem/anjolina.png");
            Vector2 ladyposition = {50.0f, 430.0f};
            // Upload Background WIN!!
            Texture BackgroundChoc = LoadTexture("imgFundo/chocolate3.png");
            // Upload Background LOST!!
            Texture BackgroundBlood = LoadTexture("imgFundo/blood.png");

            Texture2D chat = LoadTexture("chat.png");
            Vector2 chatposition = {150.0f, 300.0f};

            // Inicialização de váriaveis do gameplay;
            int screenUpperLimit = 40; // Top menu limits

            bool pause = false; // Movement pause
            bool collision[5] = {false};

            SetTargetFPS(60);
            float time = 0.0f;
            int frameAtual = 0;
            int pulou = 0;

            if (IsKeyPressed('P'))
                pause = !pause;

            StopMusicStream(musica);
            PlayMusicStream(musica2);

    while (!WindowShouldClose())
    {
        BeginDrawing();

        ClearBackground(BLUE);

        switch (currentScreen)
        {
        case TITLE:

        {
            PlayMusicStream(musica);

            UpdateMusicStream(musica);

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

                UpdateMusicStream(musica2); // TOCAR MUSICA

                if(IsKeyDown(KEY_P)) pause=1;

                if (!IsMusicStreamPlaying(musica2))
                {

                    UpdateMusicStream(musica2);
                }

                if (pause)
                {

                    StopMusicStream(musica2);
                }

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
                    vitoria--;
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

                //DESENHANDO GAMEPLAY
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

                    DrawText(TextFormat("RESTAM: %02i ", vitoria), 1050, 21, 21, BLACK);
                    DrawText(TextFormat("RESTAM: %02i ", vitoria), 1050, 20, 20, ORANGE);

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

                // CONDIÇÃO DE VITÓRIA
                if (level > 40)
                {
                     StopMusicStream(musica2);
                    PlayMusicStream(musica3);
                    UpdateMusicStream(musica3);
                    DrawTexture(BackgroundChoc, 0, 0, WHITE);
                    DrawTextureRec(lady, (Rectangle){0, 0, lady.width, lady.height}, ladyposition, WHITE);
                    DrawTextureRec(chat, (Rectangle){0, 0, chat.width, chat.height}, chatposition, WHITE);
                    DrawText("YOU WIN", GetScreenWidth() / 2 - MeasureText("YOU WIN", 100) / 2, GetScreenHeight() / 2 - 48, 100, GRAY);
                    DrawText("YOU WIN", GetScreenWidth() / 2 - MeasureText("YOU WIN", 100) / 2, GetScreenHeight() / 2 - 50, 100, BLACK);
                }

                // CONDIÇÃO DE DERROTA
                if (vidas > 32 && level <= 40)
                {
                    StopMusicStream(musica2);
                    PlayMusicStream(musica);
                    UpdateMusicStream(musica);

                    DrawTexture(BackgroundBlood, 0, 0, WHITE);

                    DrawText("PRESS [ENTER] TO PLAY AGAIN", GetScreenWidth() / 2 - MeasureText("PRESS [ENTER] TO PLAY AGAIN", 20) / 2, GetScreenHeight() / 2 - 48, 20, GRAY);
                    DrawText("PRESS [ENTER] TO PLAY AGAIN", GetScreenWidth() / 2 - MeasureText("PRESS [ENTER] TO PLAY AGAIN", 20) / 2, GetScreenHeight() / 2 - 50, 20, BLACK);
                    DrawText("YOU LOST", 23, 24, 150, GRAY);
                    DrawText("YOU LOST", 21, 22, 150, BLACK);
                }

                //EndDrawing();

                if (IsKeyPressed(KEY_ENTER) || IsGestureDetected(GESTURE_TAP))
                {
                    StopMusicStream(musica);
                    StopMusicStream(musica3);
            
                    PlayMusicStream(musica2);


                    Iniciar();
                    vidas = 0;
                    
                }
                if (IsKeyPressed(KEY_E) || IsGestureDetected(GESTURE_TAP))
                {
                    
                    CloseWindow();
                    
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
        if (IsKeyPressed(KEY_ENTER) || IsGestureDetected(GESTURE_TAP))
                {

                    Iniciar();
                    vidas = 0;
                }
                if (IsKeyPressed(KEY_E) || IsGestureDetected(GESTURE_TAP))
                {
                    
                    UnloadMusicStream(musica2); // Unload music stream buffers from RAM
                    StopMusicStream(musica2);
                    CloseAudioDevice(); // parar a musica
                    CloseWindow();
                    
                }
    }
}
void UnloadGame(void)
{
}