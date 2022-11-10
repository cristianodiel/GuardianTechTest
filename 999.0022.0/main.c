#include <stdio.h>
#include <stdlib.h>
#include "999.0022.0.h"

int main()
{
    /*Inicializar o microcontrolador (apenas chamando a função ConfigMCU);*/
    ConfigMCU();

    /*Confirmar a presença (via CAN) do item 999.0020.0, se o item 999.0020.0 estiver presente
    nada deverá acontecer, mas se ele não responder, o programa para de rodar até que o item
    seja conectado.*/
    ECAN_Initialize(); // inicializa o protocolo CAN

    uCAN_MSG rxMessage;
    while (CAN_receive(&rxMessage)){//programa funciona normalmente
        /*Confirmando que o sistema foi ligado corretamente, o programa deverá enviar a cada 1
        segundo uma mensagem (via CAN) “perguntando” ao item 999.0020.0 se ele está presente;*/
        função_timer(1s){
            //item 999.0020.0, a câmera está ligada?
            CAN_transmit(uCAN_MSG *tempCanMsg);
            CAN_receive(uCAN_MSG *tempCanMsg);
        }

    }else{/*enquanto a função retornar false,
        o programa para de rodar até que o item seja conectado*/
        //printf("Mensagem de debug: Aguardando o item 999.0020.0 ser conectado.\n");
        void ISR() iv 0x0018 ics ICS_AUTO {/*insira o código aqui*/};

    };

    /*Passado mais 1 segundo, se o item 999.0020.0 estiver presente nada deverá acontecer, mas se
    ele não responder, o programa para de rodar até que o item seja re-conectado*/

    return 0;
}
