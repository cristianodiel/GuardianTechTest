#include <stdio.h>
#include <stdlib.h>
#include 999.0022.0.h"

int main()
{
    /*Inicializar o microcontrolador (apenas chamando a fun��o ConfigMCU);*/
    ConfigMCU();
    /*Confirmar a presen�a (via CAN) do item 999.0020.0, se o item 999.0020.0 estiver presente
    nada dever� acontecer, mas se ele n�o responder, o programa para de rodar at� que o item
    seja conectado.*/
    ECAN_Initialize(); // inicializa o protocolo CAN
    while (CAN_receive(*tempCanMsg)){
        //programa funciona normalmente

    }else{
        //programa para de rodar at� que o item seja conectado
    };
    /*Confirmando que o sistema foi ligado corretamente, o programa dever� enviar a cada 1
    segundo uma mensagem (via CAN) �perguntando� ao item 999.0020.0 se ele est� presente;*/
    /*Passado mais 1 segundo, se o item 999.0020.0 estiver presente nada dever� acontecer, mas se
    ele n�o responder, o programa para de rodar at� que o item seja re-conectado*/
    printf("Hello world!\n");
    return 0;
}
