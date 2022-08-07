#include <stdio.h>
#include <raylib.h>

// para compilar: mingw32-make PLATFORM=PLATFORM_DESKTOP

static void Iniciar(void);
static void Desenhar(void);
static void UnloadGame(void);

int main(void)
{
  InitWindow(1200, 600, "Janela Teste");

  float speed = 200.0;

  Texture backgroundTexture = LoadTexture("imgMenu/menu1.png");
  Vector2 BP = {0, 0};
  Rectangle FrameRecOut = {0.0f, 0.0f, (float)backgroundTexture.width/2,  (float)backgroundTexture.height};
  //Rectangle FrameRecIn = {129.0f, 0.0f, 128.0f, 256.0f};
 while(!WindowShouldClose()){
  FrameRecOut.y += GetFrameTime() * speed;
  if (FrameRecOut.y >= FrameRecOut.height){
    FrameRecOut.y = 0;
  }

  BeginDrawing();
   ClearBackground(BLUE);
  DrawTextureRec(backgroundTexture, FrameRecOut, BP, WHITE);

  EndDrawing();
 }




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
   Texture Background = LoadTexture("imgMenu/menu1.png");
  

  while (!WindowShouldClose())
  {

    BeginDrawing();
    ClearBackground(BLUE);
     DrawTexture(Background, 0, 0, WHITE);
    
    // Image bgImage = LoadImage("menu.png");
    DrawText("Salve os Animais", 21, 22, 40, BLACK);
    DrawText("Salve os Animais", 20, 20, 40, WHITE);

    DrawText("PRESSIONE ENTER PARA INICIAR", 421, 252, 20, BLACK);
    DrawText("PRESSIONE ENTER PARA INICIAR", 420, 250, 20, WHITE);
    EndDrawing();
    
  }
}
void UnloadGame(void)
{
}
