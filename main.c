#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct
{   char nombre_ingrediente [20];
    float cantidad;                      /// en kg o en litro
    char tipo [20];                      /// "liquido" o "solido "
    float costo;                         /// costo por kg o por litro
}stockIngrediente;






///prototipado
void lecturaIngredientes (stockIngrediente [], int *);
void muestraIngredientes (stockIngrediente [], int );






int main()
{
    ///variables
    int validos = 0;
    int opcionMenu;
    stockIngrediente listaIngredientes [30];


    ///menu
    printf("\n\n\t----------------------------------------------------------------\n");
    printf("\t\t\tBIENVENID@ A LA PANADERIA DEL BARRIO!\n\t\t\t    Atendida por sus propietarios:\n\t\t\t\t Dominguez, Axel.\n\t\t\t\t Framinan, Tomas\n\t\t\t\t Garcia, Ivan.\n");
    printf("\t----------------------------------------------------------------\n\n\n");
    printf("Ingrese una opcion.\n1.INGRESO DE MATERIA PRIMA.\n2.COCINANDO LOS PREPARADOS.\n3.VENTA AL PUBLICO.\n4.RESUMEN DEL DIA.\n");
    scanf("%i", &opcionMenu);
    switch (opcionMenu)
    {
        case  1 :
            printf("\n\n\t\tINGRESO DE MATERIA PRIMA.\n");
            printf("Esta es su lista de ingredientes.");
            lecturaIngredientes(listaIngredientes, &validos);
            muestraIngredientes(listaIngredientes, validos);
            break;
    }




    return 0;
}



///implementacion



void lecturaIngredientes (stockIngrediente  listaIngredientes [], int * validos)  /// lectura de ingredientes desde archivo y guardado en estructura.
{
    FILE * fp;
    fp = fopen("stockingredientes.bin", "rb");
    int i = 0;
    if (fp != NULL)
    {
        while (fread(&listaIngredientes[i] , sizeof(stockIngrediente) , 1 , fp ) > 0 )
        {
            i++;
        }

        *validos = i;
         fclose (fp);
    }

else
{
    printf("ups. Algo malio sal.");
}
}

///muestra de ingredientes en stock.

void muestraIngredientes (stockIngrediente listaIngredientes [], int validos)
{
    printf("\n\n\t\t\tINGREDIENTES.\n");

    int cant = cantIngredientes();
    int i;
    printf ("cantidad de ingredientes : %i\n", cant );

    for (i = 0; i < validos ; i++)
    {
        printf("\nIngrediente %i", i+1);
        printf ("\n------------------------------\n");
        printf("nombre : %s\n", listaIngredientes[i].nombre_ingrediente);
        if (strcmpi (listaIngredientes[i].tipo,"liquido" ) == 0)
        {
             printf ("cantidad : %.2f litros \n", listaIngredientes[i].cantidad);
             printf("costo: %.2f por litro\n", listaIngredientes[i].costo);
        }
       else
       {
            printf ("cantidad : %.2f kilos\n", listaIngredientes[i].cantidad);
             printf("costo: %.2f por kilo\n", listaIngredientes[i].costo);
       }
        printf("tipo: %s\n", listaIngredientes[i].tipo);

        printf ("------------------------------\n");

    }
}

/// cantidad de ingredientes.
int cantIngredientes()
{
    FILE* fp;
    int cant=0;
    fp = fopen("stockingredientes.bin", "rb");
    if (fp != NULL)
    {
        fseek(fp,0,SEEK_END);
        cant = ftell(fp)/sizeof(stockIngrediente);
    }
    return cant;
}

