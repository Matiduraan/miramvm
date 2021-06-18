#include "commons/collections/list.c"
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
    int *ptrHuecoLibre;
    int tamanio;
} espacio_t;
t_list *listaSegmentos;
//void *guardar_en_memoria(void *);
int main()
{
    void *memoria;
    memoria = malloc(1024);
    printf("puntero inicial memoria: %d \n", memoria);

    int a = 500;
    char b = 'b';
    segmentoEnTabla_t unSegmento;
    unSegmento.inicio = memoria;
    unSegmento.nroSegmento = 0;
    unSegmento.tamanio = 8;
    segmentoEnTabla_t otroSegmento;
    otroSegmento.inicio = (memoria + sizeof(unSegmento));
    otroSegmento.nroSegmento = 1;
    otroSegmento.tamanio = 16;
    *(segmentoEnTabla_t *)memoria = unSegmento;
    *(segmentoEnTabla_t *)(memoria + sizeof(unSegmento)) = otroSegmento;
    listaSegmentos = list_create();
    list_add(listaSegmentos, memoria);

    printf("Direccion inicial del segmento: %d, Numero de segmento: %d, Tamaño de segmento: %d  \n", *(segmentoEnTabla_t *)memoria, *(segmentoEnTabla_t *)(memoria + sizeof(int)), *(segmentoEnTabla_t *)(memoria + 2 * sizeof(int)));
    printf("Direccion inicial del segmento: %d, Numero de segmento: %d, Tamaño de segmento: %d  \n", *(segmentoEnTabla_t *)(memoria + sizeof(unSegmento)), *(segmentoEnTabla_t *)(memoria + sizeof(unSegmento) + sizeof(int)), *(segmentoEnTabla_t *)(memoria + 2 * sizeof(unSegmento)));
    printf("Primer elemento de la lista de segmentos : %d \n", list_get(listaSegmentos, 0));
    free(memoria);
    return 0;
}
/*void *guardar_en_memoria(void *payload)
{
    int segmentoAsignado;
    bool estaLibre;
    int w = 0;
    espacio_t *espaciosLibres;
    if (list_is_empty(listaSegmentos))
    {
        printf("Se entro al if");

        //Guarda directamente en memoria y lo agrega a la lista de segmentos
        *memoria = *payload;
        segmentoEnTabla_t *nuevoSegmento;
        nuevoSegmento->inicio = memoria;
        nuevoSegmento->nroSegmento = 0;
        nuevoSegmento->tamanio = 2 * sizeof(int);
        list_add(listaSegmentos, nuevoSegmento);
        segmentoAsignado = nuevoSegmento->nroSegmento;
    }
    else
    {
        printf("Lista de segmentos pito");
        for (int i = 0; i <= list_size(listaSegmentos); i++)
        {
            int tamActual = list_get(listaSegmentos, i)->tamanio;
            int inicioActual = list_get(listaSegmentos, i)->inicio;
            int inicioSig = list_get(listaSegmentos, i + 1)->inicio;
            if (inicioSig != NULL)
            {
                int huecoLibre = inicioSig - (inicioActual + tamActual);
            }
            else
            {
                int huecoLibre = memoria + (256) - (inicioActual + tamActual);
            }
            if (huecoLibre != 0)
            {
                //best fit
                espaciosLibres[w]->ptrHuecoLibre = inicioActual + tamActual;
                w++;

                //First fit
            }
        }
    }
}*/
