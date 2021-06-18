#include "commons/collections/list.c"
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
typedef struct
{
    int tamanio;
    int nroSegmento;
    int *inicio;

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
    printf("%d \n", memoria);

    int a = 500;
    char b = 'b';
    segmentoEnTabla_t unSegmento;
    unSegmento.inicio = memoria;
    unSegmento.nroSegmento = 5;
    unSegmento.tamanio = 8;
    *(segmentoEnTabla_t *)memoria = unSegmento;
    /*listaSegmentos = list_create();
    guardar_en_memoria(unSegmento);
    printf("Guardado de memoria segmento nro: %d \n", *memoria);
    printf("Memoria puntero %d \n", memoria);
    *(int *)memoria = a;
    printf("Valor memoria puntero %d \n", *(int *)memoria);
    memoria += sizeof(int);
    *(char *)memoria = b;
    printf("Valor memoria puntero %c \n", *(char *)memoria);*/
    printf("Valor memoria puntero %d \n", *(segmentoEnTabla_t *)(memoria + sizeof(int)));

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
