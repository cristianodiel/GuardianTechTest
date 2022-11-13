#include <stdio.h>
#include <stdlib.h>
#include "999.0020.0.h"
#include "mcc_generated_files/mcc.h"

int main()
{
    int conexao = 0; /* variavel (flag) usada para indicar se há conexão entre os itens 999.0020.0 e 999.0022.0
    0 : sem conexão
    1 : itens conectados */
    int PWMLED10 = 0;

    /*Inicializar o microcontrolador (apenas chamando a função ConfigMCU);*/
    ConfigMCU();/*editei o nome desta função de inicialização nos arquivos mcc.c e mcc.h para atender ao enunciado proposto*/
    // Enable the Global Interrupts
    INTERRUPT_GlobalInterruptEnable();

    // Disable the Global Interrupts
    //INTERRUPT_GlobalInterruptDisable();

    // Enable the Peripheral Interrupts
    INTERRUPT_PeripheralInterruptEnable();

    // Disable the Peripheral Interrupts
    //INTERRUPT_PeripheralInterruptDisable();



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
    txMessage.frame.data0 = 0x01;
    txMessage.frame.data1 = 0x01;
    txMessage.frame.data2 = 0x01;
    txMessage.frame.data3 = 0x00;

    TMR0_SetInterruptHandler(TMR0_compareInterrupt); /*chamando a função timer
    conforme documentação consultada, esta funcao deve ser configurada através da interface do programa. Nela deve-se configurar que o timer tenha duração de 1 segundo*/

    while (1){/*Indiferente do item 999.0020.0 estar conectado ou não, o item 999.0022.0 precisa continuar perguntando, (ouvindo) se a conexão está mantida.*/
        /* o programa deverá enviar a cada 1 segundo uma mensagem (via CAN) “perguntando” ao item 999.0020.0 se ele está presente;*/
        void TMR0_compareInterrupt(void){
            //item 999.0020.0, a câmera está ligada?

            if(CAN_receive( &rxMessage)){/*Confirmando que o sistema foi ligado corretamente*/
                if(rxMessage.frame.data0 == 0x00&&
                   rxMessage.frame.data1 == 0x00&&
                   rxMessage.frame.data2 == 0x00&&
                   rxMessage.frame.data3 == 0x00){//Item 999.0022.0 perguntando se este item (999.0020.0) está conectado
                    CAN_transmit( &txMessage);//Enviando resposta : "Positivo, estou conectado."
                    conexao = 1;

                   }else{/*Se por algum motivo, o item 999.0022.0 perguntar algo diferente do esperado, é porque houve algum erro*/
                printf("Mensagem de debug: Comportamento do item 999.0022.0 fora do esperado. Aguardando ser conectado novamente.\n");
            conexao = 0;
            }else{/*Se por algum motivo, o item 999.0022.0 parar de perguntar se estou conectado, é porque a conexão foi perdida*/
                printf("Mensagem de debug: Fora do alcance do item 999.0022.0. Aguardando ser conectado novamente.\n");
            conexao = 0;
            }
        }
        if(conexao == 1){
            void TMR1_compareInterrupt(void){/*chamando a função timer.
        Novamente, conforme documentação consultada, esta funcao deve ser configurada através da interface do programa.
        Neste segundo caso, o timer deve ser configurado para que tenha duração de 0.5 segundo*/
                PWMLED10 = 1;
            }
        }
    }

    return 0;
}
