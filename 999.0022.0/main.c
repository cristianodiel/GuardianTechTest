#include <stdio.h>
#include <stdlib.h>
#include "999.0022.0.h"

 void ISR() iv 0x0018 ics ICS_AUTO;

int main()
{
    /*Inicializar o microcontrolador (apenas chamando a função ConfigMCU);*/
    ConfigMCU();

    /*Confirmar a presença (via CAN) do item 999.0020.0, se o item 999.0020.0 estiver presente
    nada deverá acontecer, mas se ele não responder, o programa para de rodar até que o item
    seja conectado.*/
    ECAN_Initialize(); // inicializa o protocolo CAN

    /*definindo mensagem a ser recebida*/
    uCAN_MSG rxMessage;

    /*definindo mensagem a ser transferida*/
    uCAN_MSG txMessage;
    txMessage.frame.idType = dSTANDARD_CAN_MSG_ID_2_0B;
    txMessage.frame.id = 0x022;
    txMessage.frame.dlc = 4;
    txMessage.frame.data0 = 0x00;
    txMessage.frame.data1 = 0x00;
    txMessage.frame.data2 = 0x00;
    txMessage.frame.data3 = 0x00;

    TMR0_SetInterruptHandler(TMR0_compareInterrupt); //chamando a função timer

    while (1){/*Indiferente do item 999.0020.0 estar conectado ou não, o item 999.0022.0 precisa continuar perguntando, (ouvindo) se a conexão está mantida.*/
        /* o programa deverá enviar a cada 1 segundo uma mensagem (via CAN) “perguntando” ao item 999.0020.0 se ele está presente;*/
        função_timer(1s){
            //item 999.0020.0, a câmera está ligada?
            CAN_transmit( &txMessage);
            if(CAN_receive( &rxMessage)){/*Confirmando que o sistema foi ligado corretamente*/
                if(rxMessage.frame.data0 == 0x01&&
                   rxMessage.frame.data1 == 0x01&&
                   rxMessage.frame.data2 == 0x01&&
                   rxMessage.frame.data3 == 0x00){//resposta positiva do item 999.0020.0
                    /*Passado mais 1 segundo, se o item 999.0020.0 estiver presente nada deverá acontecer,*/
                    printf("Mensagem de debug: Tudo certo, o item 999.0020.0 encontra-se conectado.\n");
                   }
            }else{/*mas se ele não responder, o programa para de rodar até que o item seja re-conectado*/
                printf("Mensagem de debug: O item 999.0020.0 foi desconectado. Aguardando ser conectado novamente.\n");

            }
        }

    }/*enquanto a função retornar false,
        o programa para de rodar até que o item seja conectado*/
        printf("Mensagem de debug: Aguardando o item 999.0020.0 ser conectado.\n");


    };



    return 0;
}
