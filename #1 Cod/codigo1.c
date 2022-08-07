#include <stdio.h>
#include <raylib.h>

// para compilar: mingw32-make PLATFORM=PLATFORM_DESKTOP

static void Iniciar(void);
static void Desenhar(void);
static void UnloadGame(void);

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

  /* int BackgroundCurrentFrane = 0;
  int BackgroundFranesCounter = 0;
  int BackgroundFranesSpeed = 1; */
  int BackgroundX = 0;
  int BackgroundY = 0;
  // int BackgroundTimer =0;

  Vector2 BackgroundPosition = {BackgroundX, BackgroundY};
  Texture2D Background = LoadTexture("menu1.png");
  Rectangle BackgroundFrameRec = {0.0f, 0.0f, (float)Background.width, (float)Background.height};

  /*
  Vector2 position = ( HenryX, HenryY );
  Texture2D Henry = LoadTexture ("Henry.png"):
  Rectangle frameRec = | 0.0f, 0.0f, (float) Eenry.width/5, (loat) Henry.height );
  */

  while (!WindowShouldClose())
  {

    BeginDrawing();
    ClearBackground(BLUE);
    DrawTextureRec(Background, BackgroundFrameRec, BackgroundPosition, WHITE);

    // Image bgImage = LoadImage("menu.png");
    DrawText("Salve os Animais", 20, 20, 40, WHITE);

    DrawText("PRESSIONE ENTER PARA INICIAR", 420, 250, 20, BLACK);
    EndDrawing();
  }
}
void UnloadGame(void)
{
}
