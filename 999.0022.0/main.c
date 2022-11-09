#include <stdio.h>
#include <stdlib.h>
#include 999.0022.0.h"

int main()
{
    /*Inicializar o microcontrolador (apenas chamando a função ConfigMCU);*/
    ConfigMCU();
    /*Confirmar a presença (via CAN) do item 999.0020.0, se o item 999.0020.0 estiver presente
    nada deverá acontecer, mas se ele não responder, o programa para de rodar até que o item
    seja conectado.*/
    ECAN_Initialize(); // inicializa o protocolo CAN
    while (CAN_receive(*tempCanMsg)){
        //programa funciona normalmente

    }else{
        //programa para de rodar até que o item seja conectado
    };
    /*Confirmando que o sistema foi ligado corretamente, o programa deverá enviar a cada 1
    segundo uma mensagem (via CAN) “perguntando” ao item 999.0020.0 se ele está presente;*/
    /*Passado mais 1 segundo, se o item 999.0020.0 estiver presente nada deverá acontecer, mas se
    ele não responder, o programa para de rodar até que o item seja re-conectado*/
    printf("Hello world!\n");
    return 0;
}
