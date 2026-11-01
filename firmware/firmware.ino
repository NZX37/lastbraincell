#include <Arduino.h>
#include <Wire.h>
#include <SPI.h>
#include <stdio.h>
#include <string.h>
#include <GxEPD2_BW.h>

#define EPD_MOSI 11
#define EPD_SCK 12
#define EPD_CS 10
#define EPD_DC 9
#define EPD_RST 8
#define EPD_BUSY 7

#define PIN_JOY_H 5
#define PIN_JOY_V 4
#define PIN_JOY_SEL 6

#define PIN_SDA 17
#define PIN_SCL 18

GxEPD2_BW<GxEPD2_290_T94, GxEPD2_290_T94::HEIGHT> display(GxEPD2_290_T94(EPD_CS, EPD_DC, EPD_RST, EPD_BUSY));

struct Date { int y, m, d; };

static const char *MONTHS[] = {"January", "February", "March", "April", "May", "June",
                               "July", "August", "September", "October", "November", "December"};
static const char *WD[] = {"Su", "Mo", "Tu", "We", "Th", "Fr", "Sa"};

static long todayDay = 0;
static long viewDay = 0;

static int centerH = 2048, centerV = 2048;
static const int DEADZONE = 900;
static bool hLatched = false, vLatched = false;

static bool isLeap(int y) { return (y % 4 == 0 && y % 100 != 0) || y % 400 == 0; }

static int daysInMonth(int y, int m) {
  static const int dm[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
  return (m == 2 && isLeap(y)) ? 29 : dm[m - 1];
}

static long toDays(Date dt) {
  long n = 0;
  for (int y = 2000; y < dt.y; y++) n += isLeap(y) ? 366 : 365;
  for (int m = 1; m < dt.m; m++) n += daysInMonth(dt.y, m);
  return n + dt.d - 1;
}

static Date fromDays(long n) {
  Date dt = {2000, 1, 1};
  while (n >= (isLeap(dt.y) ? 366 : 365)) {
    n -= isLeap(dt.y) ? 366 : 365;
    dt.y++;
  }
  while (n >= daysInMonth(dt.y, dt.m)) {
    n -= daysInMonth(dt.y, dt.m);
    dt.m++;
  }
  dt.d = (int)n + 1;
  return dt;
}

static int weekday(Date dt) { return (int)((6 + toDays(dt)) % 7); }

static uint8_t bcd2dec(uint8_t b) { return (b >> 4) * 10 + (b & 0x0F); }

static bool rtcRead(Date &out) {
  Wire.beginTransmission(0x68);
  Wire.write(0x00);
  if (Wire.endTransmission() != 0) return false;
  if (Wire.requestFrom((uint8_t)0x68, (uint8_t)7) != 7) return false;
  for (int i = 0; i < 3; i++) Wire.read();
  Wire.read();
  out.d = bcd2dec(Wire.read());
  out.m = bcd2dec(Wire.read() & 0x1F);
  out.y = 2000 + bcd2dec(Wire.read());
  return true;
}

static Date buildDate() {
  static const char *mn[] = {"Jan", "Feb", "Mar", "Apr", "May", "Jun",
                             "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};
  char m[4] = {0};
  int d = 1, y = 2026;
  sscanf(__DATE__, "%3s %d %d", m, &d, &y);
  Date out = {y, 1, d};
  for (int i = 0; i < 12; i++)
    if (strcmp(m, mn[i]) == 0) out.m = i + 1;
  return out;
}

static void refreshToday() {
  Date now;
  if (!rtcRead(now) || now.y < 2024) now = buildDate();
  todayDay = toDays(now);
}

static int readAvg(int pin) {
  long s = 0;
  for (int i = 0; i < 16; i++) {
    s += analogRead(pin);
    delay(2);
  }
  return (int)(s / 16);
}

static int axisDirection(int raw, int centre, bool &latched) {
  int dev = raw - centre;
  if (dev > DEADZONE) {
    if (!latched) {
      latched = true;
      return +1;
    }
  } else if (dev < -DEADZONE) {
    if (!latched) {
      latched = true;
      return -1;
    }
  } else {
    latched = false;
  }
  return 0;
}

static void drawCalendar() {
  Date v = fromDays(viewDay);
  Date t = fromDays(todayDay);

  const int W = display.width();
  const int H = display.height();
  const int wdY = 22;
  const int gridY = 34;
  const int cw = W / 7;
  const int ch = (H - gridY) / 6;
  const int first = weekday({v.y, v.m, 1});

  char buf[40];

  display.setFullWindow();
  display.firstPage();
  do {
    display.fillScreen(GxEPD_WHITE);
    display.setTextColor(GxEPD_BLACK);

    display.setTextSize(2);
    display.setCursor(4, 2);
    snprintf(buf, sizeof buf, "%s %d", MONTHS[v.m - 1], v.y);
    display.print(buf);

    display.setTextSize(1);
    snprintf(buf, sizeof buf, "%04d-%02d-%02d", v.y, v.m, v.d);
    display.setCursor(W - 4 - 6 * (int)strlen(buf), 4);
    display.print(buf);

    for (int c = 0; c < 7; c++) {
      display.setCursor(c * cw + (cw - 12) / 2, wdY);
      display.print(WD[c]);
    }

    for (int d = 1; d <= daysInMonth(v.y, v.m); d++) {
      int idx = first + d - 1;
      int x = (idx % 7) * cw;
      int y = gridY + (idx / 7) * ch;

      bool selected = (d == v.d);
      bool isToday = (v.y == t.y && v.m == t.m && d == t.d);

      if (selected) display.fillRect(x + 1, y + 1, cw - 2, ch - 2, GxEPD_BLACK);
      if (isToday) display.drawRect(x + 1, y + 1, cw - 2, ch - 2, GxEPD_BLACK);

      display.setTextColor(selected ? GxEPD_WHITE : GxEPD_BLACK);
      snprintf(buf, sizeof buf, "%d", d);
      display.setCursor(x + 4, y + (ch - 8) / 2);
      display.print(buf);
    }
  } while (display.nextPage());
}

void setup() {
  Serial.begin(115200);
  pinMode(PIN_JOY_SEL, INPUT_PULLUP);
  analogReadResolution(12);

  Wire.begin(PIN_SDA, PIN_SCL);
  SPI.begin(EPD_SCK, -1, EPD_MOSI, EPD_CS);
  display.init(115200);
  display.setRotation(1);

  centerH = readAvg(PIN_JOY_H);
  centerV = readAvg(PIN_JOY_V);

  refreshToday();
  viewDay = todayDay;
  drawCalendar();
}

void loop() {
  bool redraw = false;
  int dh = axisDirection(analogRead(PIN_JOY_H), centerH, hLatched);
  if (dh != 0) {
    viewDay += dh;
    redraw = true;
  }
  int dv = axisDirection(analogRead(PIN_JOY_V), centerV, vLatched);
  if (dv != 0) {
    viewDay += dv * 7;
    redraw = true;
  }
  static bool btnWasDown = false;
  bool btnDown = digitalRead(PIN_JOY_SEL) == LOW;
  if (btnDown && !btnWasDown) {
    refreshToday();
    viewDay = todayDay;
    redraw = true;
  }
  btnWasDown = btnDown;
  if (redraw) drawCalendar();
  delay(20);
}