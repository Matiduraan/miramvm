#include "commons/collection/list.c"
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
typedef struct
{
    int *inicio;
    int nroSegmento;
    int tamanio;

} segmentoEnTabla_t;
typedef struct
{
    int ptrHuecoLibre;
    int tamanio;
} espacio_t;
t_list *listaSegmentos;
void *guardar_en_memoria(segmentoEnTabla_t);
void *memoria;
int main()
{

    memoria = malloc(1024);
    printf("puntero inicial memoria: %d \n", memoria);
    segmentoEnTabla_t unSegmento;
    unSegmento.inicio = memoria;
    unSegmento.nroSegmento = 0;
    unSegmento.tamanio = 8;
    segmentoEnTabla_t otroSegmento;
    otroSegmento.inicio = (memoria + sizeof(unSegmento));
    otroSegmento.nroSegmento = 1;
    otroSegmento.tamanio = 16;
    printf("Llegue hasta aca\n");
    guardar_en_memoria(unSegmento);
    /*
    *(segmentoEnTabla_t *)memoria = unSegmento;
    *(segmentoEnTabla_t *)(memoria + sizeof(unSegmento)) = otroSegmento;
    listaSegmentos = list_create();
    list_add(listaSegmentos, memoria);

    printf("Direccion inicial del segmento: %d, Numero de segmento: %d, Tamaño de segmento: %d  \n", *(segmentoEnTabla_t *)memoria, *(segmentoEnTabla_t *)(memoria + sizeof(int)), *(segmentoEnTabla_t *)(memoria + 2 * sizeof(int)));
    printf("Direccion inicial del segmento: %d, Numero de segmento: %d, Tamaño de segmento: %d  \n", *(segmentoEnTabla_t *)(memoria + sizeof(unSegmento)), *(segmentoEnTabla_t *)(memoria + sizeof(unSegmento) + sizeof(int)), *(segmentoEnTabla_t *)(memoria + 2 * sizeof(unSegmento)));
    printf("Primer elemento de la lista de segmentos : %d \n", list_get(listaSegmentos, 0));
    */
    free(memoria);
    return 0;
}
//Cambie esto porque me fue imposible hacer funcionar el pasar un void* como parametro asi que me parecio lo mejor
//Ponerle 3 parametros, que sean pcb, tcb y archivoDeTareas y que le pases NULL en los que no te interesan
//Y mandar solo lo que necesitas
void *guardar_en_memoria(segmentoEnTabla_t tcb)
{
    printf("Llegue hasta aca2\n");
    int segmentoAsignado;
    bool estaLibre;
    int huecoLibre;
    int w = 0;
    espacio_t *espaciosLibres;
    printf("Llegue hasta aca3\n");

    if (list_is_empty(listaSegmentos))
    {
        printf("Se entro al if");

        //Guarda directamente en memoria y lo agrega a la lista de segmentos
        *(segmentoEnTabla_t *)memoria = tcb;
        segmentoEnTabla_t *nuevoSegmento;
        nuevoSegmento->inicio = memoria;
        nuevoSegmento->nroSegmento = 0;
        nuevoSegmento->tamanio = sizeof(tcb);
        list_add(listaSegmentos, nuevoSegmento);
        segmentoAsignado = nuevoSegmento->nroSegmento;
    }
    else
    {
        printf("Lista de segmentos pito");
        for (int i = 0; i <= list_size(listaSegmentos); i++)
        {
            int tamActual = *(int *)(list_get(listaSegmentos, i) + 2 * sizeof(int));
            int inicioActual = *(int *)list_get(listaSegmentos, i);
            int inicioSig = *(int *)list_get(listaSegmentos, i + 1);
            if ((void *)inicioSig != NULL)
            {
                huecoLibre = inicioSig - (inicioActual + tamActual);
            }
            else
            {
                huecoLibre = *(int *)memoria + ((1024) - (inicioActual + tamActual));
            }
            if (huecoLibre != 0)
            {
                //best fit
                espaciosLibres[w].ptrHuecoLibre = inicioActual + tamActual;
                w++;

                //First fit
            }
        }
    }
}
