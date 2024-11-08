#include "Arduino_LED_Matrix.h"
ArduinoLEDMatrix matrix;    
int x=11;
int y = 3;
int up, down;
int cnt;
int g_o;
int i;
int score = 0;
int p = 50;
int ax = 1;
int pov;
int step=0;
byte angle = 1;
uint8_t frame[8][12] = {
  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
};
uint8_t frame_bd[8][12] = {
  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
};
byte frame2[8][12] = {
  { 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0 },
  { 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0 },
  { 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0 },
  { 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0 },
  { 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0 },
};
byte ggg[3][2] = {
  { 1, 1 },
  { 1, 0 },
  { 1, 0 },
};
void pi_plus() {
  if (digitalRead(5) == 0)
    ax = 0;
  else ax = 1;
}
void game_over() {
  for (int p = 0; p < 8; p++) {
    g_o = 0;
    for (int n = 0; n < 12; n++)
      if (frame[p][n] == 1)
        g_o++;
    if (g_o == 12) {
      matrix.renderBitmap(frame2, 8, 12);
      Serial.println("game over ):");
      delay(45000);
    }
  }
}
void ball() {
  score++;
  p -= 5;
  Serial.print("score =");
  Serial.print(score);
  Serial.println("!!!");
}
void udaleniye_stroki() {
  cnt = 0;
  for (int a = 0; a < 8; a++) {
    if (frame[a][0] == 1)
      cnt++;
    else
      break;
  }
  if (cnt == 8) {
    for (int z = 0; z < 8; z++) {
      for (int j = 1; j < 12; j++)
        frame[z][j - 1] = frame[z][j];
      frame[z][11] = 0;
    }
    ball();
  }
}
void move_y() {
  if (digitalRead(1) == 0) {
    if (up == 0)
      if ((y > 0))
        y--;
    up = 1;
  } else up = 0;
  if (digitalRead(2) == 0) {
    if (down == 0)
      if ((y < 7))
        y++;
    down = 1;
  } else down = 0;
}
bool risovat() {
  byte tmp_f[8][12];
  for (int i = 0; i < 8; i++)
    for (int j = 0; j < 12; j++)
      tmp_f[i][j] = frame[i][j];
  //Рисуем фигуру
  for (int i = 0; i < 3; i++)
    for (int j = 0; j < 2; j++)
      switch (angle) {
        case 1:
          {
            if ((ggg[i][j] == 1) && ((y + i) <= 7) && ((x + j) <= 11))
              tmp_f[y + i][x + j] = 1;
            break;
          }
        case 2:
          {
            if ((ggg[2 - i][j] == 1) && ((y + j) <= 7) && ((x + i) <= 11))
              tmp_f[y + j][x + i] = 1;
            break;
          }
        case 3:
          {
            if ((ggg[2 - i][1 - j] == 1) && ((y + i) <= 7) && ((x + j) <= 11))
              tmp_f[y + i][x + j] = 1;
            break;
          }
        case 4:
          {
            if ((ggg[i][1 - j] == 1) && ((y + j) <= 7) && ((x + i) <= 11))
              tmp_f[y + j][x + i] = 1;
            break;
          }
      }
  //конец
  byte tmp_cnt = 0;
  for (int i = 0; i < 8; i++)
    for (int j = 0; j < 12; j++)
      if (tmp_f[i][j] == 1)
        tmp_cnt++;
  byte frame_cnt = 0;
  for (int i = 0; i < 8; i++)
    for (int j = 0; j < 12; j++)
      if (frame_bd[i][j] == 1)
        frame_cnt++;
   Serial.print("Новых");
   Serial.println(tmp_cnt);
   Serial.print("Старых");
   Serial.println(frame_cnt);
   
  if (tmp_cnt >= frame_cnt) {
    for (int i = 0; i < 8; i++)
      for (int j = 0; j < 12; j++)
        frame[i][j] = tmp_f[i][j];
    return true;
  } else {
    for (int i = 0; i < 8; i++)
      for (int j = 0; j < 12; j++)
        frame[i][j] = frame_bd[i][j];
    return false;
  }
}
void udalat() {
  for (int i = 0; i < 8; i++)
    for (int j = 0; j < 12; j++)
      frame_bd[i][j] = frame[i][j];
  for (int i = 0; i < 3; i++)
    for (int j = 0; j < 2; j++)
      switch (angle) {
        case 1:
          {
            if ((ggg[i][j] == 1) && ((y + i) <= 7) && ((x + j) <= 11))
              frame[y + i][x + j] = 0;
            break;
          }
        case 2:
          {
            if ((ggg[2 - i][j] == 1) && ((y + j) <= 7) && ((x + i) <= 11))
              frame[y + j][x + i] = 0;
            break;
          }
        case 3:
          {
            if ((ggg[2 - i][1 - j] == 1) && ((y + i) <= 7) && ((x + j) <= 11))
              frame[y + i][x + j] = 0;
            break;
          }
        case 4:
          {
            if ((ggg[i][1 - j] == 1) && ((y + j) <= 7) && ((x + i) <= 11))
              frame[y + j][x + i] = 0;
            break;
          }
      }
}
void povorot() {
  if (digitalRead(10) == 0) {
    if (pov == 0)
      angle++;
    pov = 1;
  } else
    pov = 0;
  if (angle == 5)
    angle = 1;
  matrix.renderBitmap(frame, 8, 12);
}
void setup() {
  Serial.begin(115200);
  matrix.begin();
  pinMode(1, INPUT_PULLUP);
  pinMode(2, INPUT_PULLUP);
  pinMode(5, INPUT_PULLUP);
  pinMode(10, INPUT_PULLUP);
}
void loop() {
  udalat();
  // cnt = 0;
  i++;
  if (i >= (p * ax + 5)) {
    x--;
    i = 0;
  }
  move_y();
  pi_plus();
  game_over();
  povorot();
  bool stat = risovat();
  Serial.println(stat);
  step++;
  Serial.println(step);
  if ((x <= 0) || (frame[y][x - 1] == 1) || (!stat)) {
    udaleniye_stroki();
    x = 11;
    y = 3;
    risovat();
  }
  matrix.renderBitmap(frame, 8, 12);
  delay(10);
}