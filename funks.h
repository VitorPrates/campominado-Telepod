#include <Arduino.h>

// display libs 240x240
#include <Adafruit_GFX.h>
#include <Adafruit_ST7789.h>
#include <SPI.h>
#include <Fonts/FreeMono12pt7b.h>
#include <Fonts/FreeMono9pt7b.h>

// display 128x64
#include <Wire.h>
#include <U8g2lib.h>

// display configs
#define TFT_CS 10
#define TFT_RST 2
#define TFT_DC 15
Adafruit_ST7789 display(TFT_CS, TFT_DC, TFT_RST);
U8G2_SSD1306_128X64_NONAME_F_SW_I2C u8g2(U8G2_R0, /* clock=*/22, /* data=*/21, /* reset=*/U8X8_PIN_NONE);

// botões
#define botB1 27
#define botB2 5
#define botBranco 16
#define botAzul 0
#define botAmarelo 4
#define botVermelho 17
//

// buzer
#define BUZZER_PIN 12
#define PWM_RESOLUTION 8

void bip(int duracao, int tom)
{
    ledcWriteTone(0, tom);
    delay(duracao);
    ledcWriteTone(0, 0);
}

void setup_hardware()
{
    // 240x240
    display.init(240, 240, SPI_MODE2);
    display.fillScreen(ST77XX_BLACK);
    display.setRotation(0);
    display.setFont(&FreeMono12pt7b);
    display.cp437(true);
    //

    // 128x64
    u8g2.begin();
    u8g2.enableUTF8Print();
    u8g2.setDisplayRotation(U8G2_R2);
    

    pinMode(BUZZER_PIN, OUTPUT);
    ledcSetup(0, 1000, PWM_RESOLUTION);
    ledcAttachPin(BUZZER_PIN, 0);

    pinMode(botB1, INPUT_PULLUP);
    pinMode(botB2, INPUT_PULLUP);
    pinMode(botBranco, INPUT_PULLUP);
    pinMode(botAzul, INPUT_PULLUP);
    pinMode(botAmarelo, INPUT_PULLUP);
    pinMode(botVermelho, INPUT_PULLUP);
}

void drawtext(String text, uint16_t color, int posx, int posy)
{
    display.setCursor(posx, posy);
    display.setTextColor(color);
    display.setTextWrap(true);
    display.print(text);
}

void init_Sys()
{
    setup_hardware();
    drawtext("TELEPOD", ST77XX_WHITE, 10, 130);
    drawtext("CAMPO MINADO!", ST77XX_CYAN, 0, 180);
    drawtext("RANDOOM COLORS", ST77XX_WHITE, 0, 230);
    u8g2.setFont(u8g2_font_7x14_tf);
    String init_text = "Iniciando...";
    String init_escrevendo = "";
    for(int i = 0; i <= 12; i++)
    {
        init_escrevendo += init_text[i];
        u8g2.clearBuffer();
        if(i%2 == 0)
        {
            u8g2.drawUTF8(0,20, "`-´");
        }
        else
        {
            u8g2.drawUTF8(0,20, "`o´");
        }
        u8g2.drawStr(0,40,String(init_escrevendo).c_str());
        u8g2.sendBuffer();
    }
    delay(200);
    u8g2.clearBuffer();
    u8g2.setFont(u8g2_font_9x15_tf);
    u8g2.drawUTF8(0,20, "`v´");
    u8g2.setFont(u8g2_font_7x14_tf);
    u8g2.drawStr(0,40,String(init_escrevendo).c_str());
    u8g2.sendBuffer();
    delay(200);
}

void atualizar()
{
    display.fillScreen(ST77XX_BLACK);
}

int read_buttons()
{
    unsigned long previousMillis = 0;
    const unsigned long delayTime = 150;
    bool new_frame = false;
    unsigned long currentMillis = millis();
    if (currentMillis - previousMillis >= delayTime)
    {
        previousMillis = currentMillis;
        if (digitalRead(botB1) == LOW)
        {
            return 1;
        }
        else if (digitalRead(botB2) == LOW)
        {
            return 2;
        }
        else if (digitalRead(botBranco) == LOW)
        {
            return 3; // baixo
        }
        else if (digitalRead(botAzul) == LOW)
        {
            return 4; // esquerda
        }
        else if (digitalRead(botAmarelo) == LOW)
        {
            return 5; // cima
        }
        else if (digitalRead(botVermelho) == LOW)
        {
            return 6; // direito
        }
        else
        {
            return 0;
        }
    }
}