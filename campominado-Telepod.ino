//Placa utilizada: Esp wroom 32D, da espressif
#include "funks.h"
#include "game_campominado.h"

void setup()
{
    init_Sys();
    bip(100,500);
    bip(100,1000);
    init_game_minesweeper();
    atualizar();
    drawtext("OBRIGADO", ST77XX_WHITE, 20, 100);
    drawtext("POR", ST77XX_WHITE, 20, 120);
    drawtext("JOGAR", ST77XX_WHITE, 20, 140);
    u8g2.setFont(u8g2_font_7x14_tf);
    String init_text = "Volte Sempre!";
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
    bip(100,500);
    bip(100,1000);
}
void loop()
{

}