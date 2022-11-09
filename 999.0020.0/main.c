#include <stdio.h>
#include <stdlib.h>
#include "999.0020.0.h"

int main()
{
    /*Inicializar o microcontrolador (apenas chamando a função ConfigMCU);*/
    ConfigMCU();
    /*Receber as mensagens e responder de acordo (via CAN);*/
    ECAN_Initialize(); // inicializa o protocolo CAN
    while (CAN_receive(*tempCanMsg)){

    /* Não iniciar a etapa abaixo sem confirmar que o sistema está conectado;*/

    /*Piscar a cada 0,5 segundos o led que se encontra na saída PWMLED (pino 10). Considere
variável valor 1 como ligado e variável valor 0 como desligado*/

    return 0;
}
