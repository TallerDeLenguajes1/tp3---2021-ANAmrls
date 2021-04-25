#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 40

typedef struct Producto {
    int ProductoID;
    int Cantidad;
    char * TipoProducto;
    float PrecioUnitario;
} Producto;

typedef struct Cliente {
    int ClienteID;
    char * NombreCliente;
    int CantidadProductosAPedir;
    Producto * Productos;
} Cliente;

void CargarCLientes(Cliente * ListaClientes, char ** Tipos, int Cantidad);
void CargarProducto(Producto * ProdPedido, char ** Tipos, int ID);
void MostrarLista(Cliente * Lista, int Cantidad);

int main () {
    int CantidadClientes;
    char * TiposProductos[] = {"Galletas", "Snack", "Cigarrillos", "Caramelos", "Bebidas"};

    //Solicitar al usuario la cantidad de clientes
    do
    {
        printf("Ingrese el la cantidad de clientes que desea cargar (entre 1 y 5)\n");
        scanf("%d", &CantidadClientes);
        fflush(stdin);

    } while (CantidadClientes < 1 || CantidadClientes > 5);

    //Reservar memoria para cargar la cantidad de CLientes ingresada por el usuario
    Cliente * ListaClientes = (Cliente *) malloc(sizeof(Cliente) * CantidadClientes);

    CargarCLientes(ListaClientes, TiposProductos, CantidadClientes); //Cargar clientes
    MostrarLista(ListaClientes, CantidadClientes); //Mostrar lista de clientes
    
    //Liberar memoria reservada
    for (int i = 0; i < CantidadClientes; i++)
    {
        free(ListaClientes[i].NombreCliente);
        free(ListaClientes[i].Productos);
    }//for end 

    free(ListaClientes);
    
    getchar();

    return 0;

}

//Función para cargar clientes
void CargarCLientes(Cliente * ListaClientes, char ** Tipos, int Cantidad) {

    for (int i = 0; i < Cantidad; i++)
    {
        int aux = 1 + rand() % 5;

        ListaClientes[i].ClienteID = i + 1;

        printf("\nIngrese el nombre del cliente Nro %d:\n", ListaClientes[i].ClienteID);
        ListaClientes[i].NombreCliente = (char*) malloc(sizeof(char) * MAX);
        gets(ListaClientes[i].NombreCliente);

        ListaClientes[i].CantidadProductosAPedir = aux;

        //Generar aleatoriamente los productos asociados al cliente y sus características
        ListaClientes[i].Productos = (Producto *) malloc(sizeof(Producto) * aux);
        for (int j = 0; j < aux; j++)
        {
            CargarProducto(&(ListaClientes[i].Productos[j]), Tipos, j + 1);
        }//for end
    }//for end    
}

//Función para cargar productos
void CargarProducto(Producto * ProdPedido, char ** Tipos, int ID) {
    int aux = rand() % 4;
    
    ProdPedido->ProductoID = ID;
    ProdPedido->Cantidad = 1 + rand() % 10;
    ProdPedido->TipoProducto = *(Tipos+aux);
    ProdPedido->PrecioUnitario = (1000 + rand() % 9001)/100;
}

//Función para mostrar lista de Clientes
void MostrarLista(Cliente * Lista, int Cantidad) {

    printf("\n---------- LISTADO DE CLIENTES ----------\n");
    
    for (int i = 0; i < Cantidad; i++)
    {
        printf("\n---------- Cliente Nro %d ----------\n", i + 1);
        printf("Nombre: %s\n", Lista[i].NombreCliente);
        printf("ID Nro: %d\n", Lista[i].ClienteID);
        printf("Cantidad de productos solicitados: %d\n", Lista[i].CantidadProductosAPedir);
        
        for (int j = 0; j < Lista[i].CantidadProductosAPedir; j++)
        {
            printf("\n---------- Producto Nro %d ----------\n", j + 1);
            printf("ID del producto: %d\n", Lista[i].Productos[j].ProductoID);
            printf("Cantidad pedida: %d\n", Lista[i].Productos[j].Cantidad);
            printf("Tipo de producto: ");
            puts(Lista[i].Productos[j].TipoProducto);
            printf("Precio unitario = $%.2f\n", Lista[i].Productos[j].PrecioUnitario);
        }//for end        
    }//for end    
}