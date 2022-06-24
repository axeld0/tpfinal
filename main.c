#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct
{
    char nombre_ingrediente [20];
    float cantidad;                      /// en kg o en litro
    char tipo [20];                      /// "liquido" o "solido "
    float costo;                         /// costo por kg o por litro
} stockIngrediente;

typedef struct
{
    char nombre_preparacion[20];
    int cantidad;                        ///por unidad, no hay por peso
} Preparacion;



typedef struct
{
    char nombre_ingrediente[20];
    float cantidad;                     ///puede ser en litro o en kg
} IngredienteXReceta;

typedef struct
{
    char nombre_preparacion[20];
    IngredienteXReceta ingredientes[20]; ///Puede tener hasta 20 ingredientes
    int cantIngredientes;                ///los validos de ingredientes
} Receta;










///prototipado
void lecturaIngredientes (stockIngrediente [], int *);
void muestraIngredientes (stockIngrediente [], int );
void muestraDemanda (Preparacion [], int );
void lecturaPreparacion (Preparacion [], int *);
void lecturaRecetas (Receta [],IngredienteXReceta[], int * , int *);
void muestraRecetas (Receta[],IngredienteXReceta[], int );






int main()
{
    ///variables
    int validos = 0;
    int validos2 = 0;
    int opcionMenu;
    char continuar;
    stockIngrediente listaIngredientes [30];
    IngredienteXReceta ingXRece [30];
    Preparacion demanda [30];
    Receta recetas [30];


/// header
    printf("\n\n\t----------------------------------------------------------------\n");
    printf("\t\t\tBIENVENID@ A LA PANADERIA DEL BARRIO!\n\t\t\t    Atendida por sus propietarios:\n\t\t\t\t Dominguez, Axel.\n\t\t\t\t Framinan, Tomas\n\t\t\t\t Garcia, Ivan.\n");
    printf("\t----------------------------------------------------------------\n\n\n");
    ///menu
    do
    {
        printf("\n\nQue parte del proceso desea ver?\n\n1.INGRESO DE MATERIA PRIMA.\n2.COCINANDO LOS PREPARADOS.\n3.VENTA AL PUBLICO.\n4.RESUMEN DEL DIA.\n5.SALIR\n");
        scanf("%i", &opcionMenu);

        switch (opcionMenu)
        {
        case  1 :
            printf("\n\n\t\tINGRESO DE MATERIA PRIMA.\n");
            printf("Esta es su lista de ingredientes.");
            lecturaIngredientes(listaIngredientes, &validos);
            muestraIngredientes(listaIngredientes, validos);
            break;
        case  2 :
            printf("\n\n\t\tCOCINANDO LOS PREPARADOS");
            lecturaPreparacion (demanda , &validos);
            muestraDemanda (demanda,validos);
            system("pause");
            printf ("Ahora, las recetas!");
            lecturaRecetas (recetas, ingXRece , &validos , &validos2);
            muestraRecetas (recetas, ingXRece, validos);



        }
    }
    while (opcionMenu != 5);




    return 0;
}



///implementacion

///PASO 1
void lecturaIngredientes (stockIngrediente  listaIngredientes [], int * validos)  /// lectura de ingredientes desde archivo y guardado en estructura.
{
    FILE * fp;
    fp = fopen("stockingredientes.bin", "rb");
    int i = 0;
    if (fp != NULL)
    {
        while (fread(&listaIngredientes[i], sizeof(stockIngrediente), 1, fp ) > 0 )
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


///PASO 2

///traido de demanda
void lecturaPreparacion (Preparacion demanda [], int * validos)
{
    FILE * fp;
    fp = fopen ("demanda.bin", "rb");
    int i = 0;
    if (fp != NULL)
    {
        while (fread(&demanda[i], sizeof(Preparacion), 1, fp ) > 0 )
        {
            i++;
        }

        *validos = i;
        fclose (fp);
    }
    else
    {
        printf("ups! algo malio sal.");
    }
}

void muestraDemanda (Preparacion demanda [], int validos)
{
    printf("\n\n\t\t\tDEMANDA.\n");

    int cant = cantDemanda();
    int i;
    printf ("cantidad de demanda : %i\n", cant );

    for (i = 0; i < validos ; i++)
    {
        printf("\nPedido %i", i+1);
        printf ("\n------------------------------\n");
        printf("nombre : %s\n", demanda[i].nombre_preparacion);
        printf ("cantidad : %i \n", demanda[i].cantidad);
        printf ("------------------------------\n");
    }


}

/// cantidad de demanda.
int cantDemanda()
{
    FILE* fp;
    int cant=0;
    fp = fopen("demanda.bin", "rb");
    if (fp != NULL)
    fseek(fp,0,SEEK_END);
    cant = ftell(fp)/sizeof(Preparacion);

return cant;
}

///recetas
void lecturaRecetas (Receta recetas[], IngredienteXReceta ingXRece [] , int * validos, int * validos2)
{
    FILE * fp;
    fp = fopen ("recetas.bin", "rb");
    int i = 0;
    int j = 0;
    if (fp != NULL)
    {
        while (fread(&recetas[i], sizeof(Receta), 1 , fp ) > 0)
        {
            i++;
        }
        *validos = i;

        while (fread(&ingXRece[i], sizeof(IngredienteXReceta), 1 , fp ) > 0 )
        {
            j++;
        }
        *validos2 = j;
        fclose(fp);
    }
    else
    {
        printf("ups! algo malio sal.");
    }
}

void muestraRecetas (Receta recetas [], IngredienteXReceta ingXRece [], int validos)
{
    printf("\n\n\t\t\tRECETAS.\n");

    int cant = cantDemanda();
    int i;
    printf ("cantidad de demanda : %i\n", cant );

    for (i = 0; i < validos ; i++)
    {
        printf("\nPedido %i", i+1);
        printf ("\n------------------------------\n");
        printf("nombre : %s\n", recetas[i].nombre_preparacion);
        printf ("Cantidad de ingrediente DISPONIBLE : %.2f \n", ingXRece[i].cantidad);
        printf ("Nombre del ingrediente : %s \n", ingXRece[i].nombre_ingrediente);
        printf ("cantidad de ingredientes NECESARIA: %i \n", recetas[i].cantIngredientes);
        printf ("------------------------------\n");
    }

}
