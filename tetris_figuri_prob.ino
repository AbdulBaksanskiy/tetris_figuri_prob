#include "Arduino_LED_Matrix.h"
ArduinoLEDMatrix matrix;
struct Figures {
  byte w, h;
  byte matrix[4][2];
  byte my1,my2;
};
Figures g[7] = {
  { 2, 3, { { 1, 0 }, { 1, 0 }, { 1, 1 }, { 0, 0 } }, 5, 6},
  { 2, 3, { { 0, 1 }, { 0, 1 }, { 1, 1 }, { 0, 0 } }, 5, 6},
  { 2, 3, { { 1, 0 }, { 1, 1 }, { 0, 1 }, { 0, 0 } }, 5, 6},
  { 2, 3, { { 0, 1 }, { 1, 1 }, { 1, 0 }, { 0, 0 } }, 5, 6},
  { 2, 3, { { 1, 0 }, { 1, 1 }, { 1, 0 }, { 0, 0 } }, 5, 6},
  { 1, 4, { { 1, 0 }, { 1, 0 }, { 1, 0 }, { 1, 0 } }, 4, 7},
  { 2, 2, { { 1, 1 }, { 1, 1 }, { 0, 0 }, { 0, 0 } }, 6, 6}
};
byte fn = random(6);
int x = 11;
int y = 3;
int up, down;
int cnt;
int g_o;
int i;
int score = 0;
int p = 50;
int ax = 1;
int pov;
int step = 0;
int l;
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
uint8_t frame2[8][12] = {
  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
  { 0, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 0 },
  { 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1 },
  { 0, 1, 0, 1, 1, 0, 0, 1, 0, 0, 0, 1 },
  { 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 0, 1 },
  { 0, 1, 1, 1, 1, 0, 1, 0, 1, 1, 1, 0 },
  { 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
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
  for (int i = 0; i < 10; i++) {
    cnt = 0;
    for (int a = 0; a < 8; a++) {
      if (frame[a][i] == 1)
        cnt++;
      else
        break;
    }
    if (cnt == 8) {
      for (int z = 0; z < 8; z++) {
        for (int j = i; j < 11; j++)
          frame[z][j] = frame[z][j + 1];
        frame[z][11] = 0;
      }
      ball();
      i--;
    }
  }
}
void move_y() {
  for (int i = 0; i < 8; i++)
      for (int j = 0; j < 12; j++)
  if ((angle == 1) || (angle == 3)) l = g[fn].my1;
  if ((angle == 2) || (angle == 4)) l = g[fn].my2;
  if (digitalRead(1) == 0) {
    if (up == 0)
      if ((y > 0)%%())
        y--;
    up = 1;
  } else up = 0;
  if (digitalRead(2) == 0) {
    if (down == 0)
      if ((y < l))
        y++;
    down = 1;
  } else down = 0;
}
bool ris_uda(int data) {
  if (data == 0)
    for (int i = 0; i < 8; i++)
      for (int j = 0; j < 12; j++)
        frame_bd[i][j] = frame[i][j];
  for (int i = 0; i < g[fn].h; i++)
    for (int j = 0; j < g[fn].w; j++)
      switch (angle) {
        case 1:
          {
            if ((g[fn].matrix[i][j] == 1) && ((y + i) <= 7) && ((x + j) <= 11))
              frame[y + i][x + j] = data;
            break;
          }
        case 2:
          {
            if ((g[fn].matrix[g[fn].h - 1 - i][j] == 1) && ((y + j) <= 7) && ((x + i) <= 11))
              frame[y + j][x + i] = data;
            break;
          }
        case 3:
          {
            if ((g[fn].matrix[g[fn].h - 1 - i][g[fn].w - 1 - j] == 1) && ((y + i) <= 7) && ((x + j) <= 11))
              frame[y + i][x + j] = data;
            break;
          }
        case 4:
          {
            if ((g[fn].matrix[i][g[fn].w - 1 - j] == 1) && ((y + j) <= 7) && ((x + i) <= 11))
              frame[y + j][x + i] = data;
            break;
          }
      }
  int cnt_f = 0;
  int cnt_f_bd = 0;
  if (data == 1) {
    for (int i = 0; i < 8; i++)
      for (int j = 0; j < 12; j++) {
        if (frame[i][j] == 1)
          cnt_f++;
        if (frame_bd[i][j] == 1)
          cnt_f_bd++;
      }
  }
  if (cnt_f_bd > cnt_f) {
    for (int i = 0; i < 8; i++)
      for (int j = 0; j < 12; j++)
        frame[i][j] = frame_bd[i][j];
    return false;
  } else return true;
}
void povorot() {
  if (digitalRead(10) == 0) {
    if (pov == 0) {
      if (y == g[fn].my2) y = g[fn].my1;
      angle++;
    }
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
};
void loop() {
  cnt = 0;
  ris_uda(0);
  i++;
  if (i >= (p * ax + 5)) {
    x--;
    i = 0;
  }
  move_y();
  pi_plus();
  game_over();
  povorot();
  bool stat = ris_uda(1);
  // Serial.println(stat);
  step++;
  // Serial.println(step);

  if ((x <= 0) || (!stat)) {
    udaleniye_stroki();
    x = 11;
    y = 3;
    fn = random(6);
    ris_uda(0);
    ris_uda(1);
  }
  matrix.renderBitmap(frame, 8, 12);
  delay(10);
}