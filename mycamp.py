#código de base para o projeto em linguagem do arduino

import os
from time import sleep
from random import randint

# criar campo
tabela_campo = ['■'] * 225
fake_campo = tabela_campo.copy()
# inserir bombas
num_bombs: int = 25
num_inserts: int = 0
while(num_inserts < num_bombs):
    pos = randint(0, len(tabela_campo)-1)
    if(tabela_campo[pos] != 'B'):
        tabela_campo[pos] = 'B'
        num_inserts += 1

# ler campo
for i in range(len(tabela_campo)):
    pos = i
    quant_bomb = 0
    try:
        if tabela_campo[i] == "■":
            row = pos / 15
            col = pos % 15
            # Verificar a posição leste
            if col < 14 and tabela_campo[pos + 1] == "B":
                quant_bomb += 1
            # Verificar a posição oeste
            if col > 0 and tabela_campo[pos - 1] == "B":
                quant_bomb += 1
            # Verificar a posição noroeste
            if row > 0 and col > 0 and tabela_campo[pos - 16] == "B":
                quant_bomb += 1
            # Verificar a posição norte
            if row > 0 and tabela_campo[pos - 15] == "B":
                quant_bomb += 1
            # Verificar a posição nordeste
            if row > 0 and col < 14 and tabela_campo[pos - 14] == "B":
                quant_bomb += 1
            # Verificar a posição sudeste
            if row < 14 and col < 14 and tabela_campo[pos + 16] == "B":
                quant_bomb += 1
            # Verificar a posição sul
            if row < 14 and tabela_campo[pos + 15] == "B":
                quant_bomb += 1
            # Verificar a posição sudoeste
            if row < 14 and col > 0 and tabela_campo[pos + 14] == "B":
                quant_bomb += 1
    except:
        pass
    if quant_bomb != 0:
        tabela_campo[i] = str(quant_bomb)

def criar_campo():
    for i in range(225):
        if (i % 15 == 0):
            print()
        print(fake_campo[i], end=' ')


    return False

# criar_campo()

def limpeza():
    limpando = 1
    while True:
        for i in range(len(tabela_campo)):
            pos = i
            try:
                if tabela_campo[i] == "_":
                    row = pos // 15
                    col = pos % 15
                    # Verificar a posição leste
                    if col < 14 and tabela_campo[pos + 1] == "■":
                        tabela_campo[pos + 1] = '_'
                        fake_campo[pos + 1] = '_'
                        limpando += 1
                    elif col < 14 and tabela_campo[pos + 1] != "B":
                        fake_campo[pos + 1] = tabela_campo[pos + 1]

                    # Verificar a posição oeste
                    if col > 0 and tabela_campo[pos - 1] == "■":
                        tabela_campo[pos - 1] = '_'
                        fake_campo[pos - 1] = '_'
                        limpando += 1
                    elif col > 0 and tabela_campo[pos - 1] != "B":
                        fake_campo[pos - 1] = tabela_campo[pos - 1]

                    # Verificar a posição norte
                    if row > 0 and tabela_campo[pos - 15] == "■":
                        tabela_campo[pos - 15] = "_"
                        fake_campo[pos - 15] = '_'
                        limpando += 1
                    elif row > 0 and tabela_campo[pos - 15] != "B":
                        fake_campo[pos - 15] = tabela_campo[pos - 15]

                    # Verificar a posição sul
                    if row < 14 and tabela_campo[pos + 15] == "■":
                        tabela_campo[pos + 15] = '_'
                        fake_campo[pos + 15] = '_'
                        limpando += 1
                    elif row < 14 and tabela_campo[pos + 15] != "B":
                        fake_campo[pos + 15] = tabela_campo[pos + 15]
            except:
                pass
        # print(limpando)
        if(limpando == 1):
            break
        limpando = 1

posicoes_jogadas = []
while True:
    os.system('cls' if os.name == 'nt' else 'clear')
    limpeza()
    criar_campo()

    jogador = int(input('0,224:'))
    if(jogador not in posicoes_jogadas):
       posicoes_jogadas.append(jogador)
    else:
        print('já digitado!')
        continue

    if jogador < 0 or jogador > 224:
        print("Posição inválida! Digite um valor entre 0 e 224.")
        continue

    if(tabela_campo[jogador] == 'B'):
        print('ACERTOU UMA BOMBA KKKKKKKKKKKKKKKK')
        break


    if(tabela_campo[jogador] == '■'):
        tabela_campo[jogador] = '_'
        fake_campo[jogador] = '_'
        limpeza()
    else:
        fake_campo[jogador] = tabela_campo[jogador]

print('APAGANDO DADOS DO PC...')
sleep(3)

