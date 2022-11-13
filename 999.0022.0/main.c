#include <stdio.h>
#include <stdlib.h>
#include "999.0022.0.h"
#include "mcc_generated_files/mcc.h"

int main()
{
    /*Inicializar o microcontrolador (apenas chamando a fun��o ConfigMCU);*/
    ConfigMCU();/*editei o nome desta fun��o de inicializa��o nos arquivos mcc.c e mcc.h para atender ao enunciado proposto*/

    // Enable the Global Interrupts
    INTERRUPT_GlobalInterruptEnable();

    // Disable the Global Interrupts
    //INTERRUPT_GlobalInterruptDisable();

    // Enable the Peripheral Interrupts
    INTERRUPT_PeripheralInterruptEnable();

    // Disable the Peripheral Interrupts
    //INTERRUPT_PeripheralInterruptDisable();



    /*Confirmar a presen�a (via CAN) do item 999.0020.0, se o item 999.0020.0 estiver presente
    nada dever� acontecer, mas se ele n�o responder, o programa para de rodar at� que o item
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

    TMR0_SetInterruptHandler(TMR0_compareInterrupt); //chamando a fun��o timer

    while (1){/*Indiferente do item 999.0020.0 estar conectado ou n�o, o item 999.0022.0 precisa continuar perguntando, (ouvindo) se a conex�o est� mantida.*/
        /* o programa dever� enviar a cada 1 segundo uma mensagem (via CAN) �perguntando� ao item 999.0020.0 se ele est� presente;*/
        void TMR0_compareInterrupt(void){
            //item 999.0020.0, a c�mera est� ligada?
            CAN_transmit( &txMessage);
            if(CAN_receive( &rxMessage)){/*Confirmando que o sistema foi ligado corretamente*/
                if(rxMessage.frame.data0 == 0x01&&
                   rxMessage.frame.data1 == 0x01&&
                   rxMessage.frame.data2 == 0x01&&
                   rxMessage.frame.data3 == 0x00){//resposta positiva do item 999.0020.0
                    /*Passado mais 1 segundo, se o item 999.0020.0 estiver presente nada dever� acontecer,*/
                    printf("Mensagem de debug: Tudo certo, o item 999.0020.0 encontra-se conectado.\n");
                   }
            }else{/*mas se ele n�o responder, o programa para de rodar at� que o item seja re-conectado*/
                printf("Mensagem de debug: O item 999.0020.0 foi desconectado. Aguardando ser conectado novamente.\n");

            }
        }
    }



    return 0;
}
