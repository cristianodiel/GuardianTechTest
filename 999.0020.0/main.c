#include <stdio.h>
#include <stdlib.h>
#include "999.0020.0.h"

int main()
{
    /*Inicializar o microcontrolador (apenas chamando a fun��o ConfigMCU);*/
    ConfigMCU();
    /*Receber as mensagens e responder de acordo (via CAN);*/
    ECAN_Initialize(); // inicializa o protocolo CAN
    while (CAN_receive(*tempCanMsg)){

    /* N�o iniciar a etapa abaixo sem confirmar que o sistema est� conectado;*/

    /*Piscar a cada 0,5 segundos o led que se encontra na sa�da PWMLED (pino 10). Considere
vari�vel valor 1 como ligado e vari�vel valor 0 como desligado*/

    return 0;
}
