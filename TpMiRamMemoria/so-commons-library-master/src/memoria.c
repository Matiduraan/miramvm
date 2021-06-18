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
    int ptrHuecoLibre;
    int tamanio;
} espacio_t;
t_list *listaSegmentos;
void guardar_en_memoria(segmentoEnTabla_t);
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
    otroSegmento.inicio = (memoria + 101);
    otroSegmento.nroSegmento = 1;
    otroSegmento.tamanio = 16;


    listaSegmentos = list_create();
    guardar_en_memoria(unSegmento);
    printf("Segunda entrada\n");
    guardar_en_memoria(otroSegmento);

    segmentoEnTabla_t *cualquiera = list_get(listaSegmentos, 0);
    printf("Primer elemento de la lista de segmentos : %d \n", cualquiera->inicio);
    cualquiera = list_get(listaSegmentos, 1);
    printf("Segundo elemento de la lista de segmentos : %d \n", cualquiera->inicio);
    cualquiera = memoria;
    printf("Primer elemento de la memoria, segmento = #%d \n",cualquiera->nroSegmento);
    cualquiera = memoria + sizeof(segmentoEnTabla_t);
    printf("segundo elemento de la memoria, segmento = #%d \n",cualquiera->nroSegmento);



    /* *(segmentoEnTabla_t *)memoria = unSegmento;
    *(segmentoEnTabla_t *)(memoria + sizeof(unSegmento)) = otroSegmento;
    listaSegmentos = list_create();
    list_add(listaSegmentos, memoria);

    printf("Direccion inicial del segmento: %d, Numero de segmento: %d, Tamaño de segmento: %d  \n", *(segmentoEnTabla_t *)memoria, *(segmentoEnTabla_t *)(memoria + sizeof(int)), *(segmentoEnTabla_t *)(memoria + 2 * sizeof(int)));
    printf("Direccion inicial del segmento: %d, Numero de segmento: %d, Tamaño de segmento: %d  \n", *(segmentoEnTabla_t *)(memoria + sizeof(unSegmento)), *(segmentoEnTabla_t *)(memoria + sizeof(unSegmento) + sizeof(int)), *(segmentoEnTabla_t *)(memoria + 2 * sizeof(unSegmento)));
    printf("Primer elemento de la lista de segmentos : %d \n", list_get(listaSegmentos, 0));*/

    free(memoria);
    return 0;
}
//Cambie esto porque me fue imposible hacer funcionar el pasar un void* como parametro asi que me parecio lo mejor
//Ponerle 3 parametros, que sean pcb, tcb y archivoDeTareas y que le pases NULL en los que no te interesan
//Y mandar solo lo que necesitas
void guardar_en_memoria(segmentoEnTabla_t tcb)
{

    int segmentoAsignado;
    bool estaLibre;
    int *huecoLibre;
    t_list *espaciosLibres;
    espaciosLibres = list_create();


    if (list_is_empty(listaSegmentos) == 1)
    {
        //Guarda directamente en memoria y lo agrega a la lista de segmentos
        *(segmentoEnTabla_t *)memoria = tcb;

        segmentoEnTabla_t *nuevoSegmento = malloc(sizeof(segmentoEnTabla_t)) ;
        nuevoSegmento->inicio = memoria;
        nuevoSegmento->nroSegmento = 0;
        nuevoSegmento->tamanio = sizeof(tcb);
        //printf("Direccion inicial del segmento: %d, Numero de segmento: %d, Tamaño de segmento: %d  \n", *(segmentoEnTabla_t *)memoria, *(segmentoEnTabla_t *)(memoria + sizeof(int)), *(segmentoEnTabla_t *)(memoria + 2 * sizeof(int)));

        list_add(listaSegmentos, nuevoSegmento);
        segmentoAsignado = nuevoSegmento->nroSegmento;


    }
    else
    {
        int tamanioListaSegmentos = list_size(listaSegmentos);
        for (int i = 0; i < tamanioListaSegmentos; i++)
        {


            segmentoEnTabla_t *segmentoIterante = malloc(sizeof(segmentoEnTabla_t));
            segmentoIterante = list_get(listaSegmentos, i);
            printf("Segmento Iterante %d\n",segmentoIterante->nroSegmento);
            if (i == (list_size(listaSegmentos))-1)
            {
                printf("Ultimo segmento de la memoria\n");
                huecoLibre = (memoria + 1024) - *(segmentoIterante->inicio) + segmentoIterante->tamanio;
            }
            else
            {

                segmentoEnTabla_t *segmentoSiguiente = malloc(sizeof(segmentoEnTabla_t));
                segmentoSiguiente = list_get(listaSegmentos, i+1);
                printf("Segmento Siguiente %d\n",segmentoSiguiente->nroSegmento);
                *huecoLibre = *(segmentoSiguiente->inicio) - *(segmentoIterante->inicio) + (segmentoIterante->tamanio);
            }
            if (huecoLibre != 0)
            {
                //best fit

                /*espacio_t *nuevoEspacioLibre;
                nuevoEspacioLibre->ptrHuecoLibre = (*segmentoIterante->inicio) + segmentoIterante->tamanio;
                nuevoEspacioLibre->tamanio = *huecoLibre;
                list_add(espaciosLibres, nuevoEspacioLibre);*/

                /* ********************************************* */

                //First fit

                if (sizeof(tcb) <= (int*)huecoLibre)
                {
                    int posicionInicioHuecoLibre = *(segmentoIterante->inicio) + (segmentoIterante->tamanio);
                    *(segmentoEnTabla_t *)posicionInicioHuecoLibre = tcb;
                    *(segmentoEnTabla_t *)(*(segmentoIterante->inicio) + segmentoIterante->tamanio) = tcb;
                    segmentoEnTabla_t *nuevoSegmento = malloc(sizeof(segmentoEnTabla_t));
                    nuevoSegmento->inicio = posicionInicioHuecoLibre;
                    nuevoSegmento->nroSegmento = 0;
                    nuevoSegmento->tamanio = sizeof(tcb);
                    //printf("Direccion inicial del segmento: %d, Numero de segmento: %d, Tamaño de segmento: %d  \n", *(segmentoEnTabla_t *)memoria, *(segmentoEnTabla_t *)(memoria + sizeof(int)), *(segmentoEnTabla_t *)(memoria + 2 * sizeof(int)));
                    list_add(listaSegmentos, nuevoSegmento);
                    segmentoAsignado = nuevoSegmento->nroSegmento;

                }
            }
        }
    }

}
