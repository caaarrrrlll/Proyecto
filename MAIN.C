#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char nombre[100];
    int cantidad;
    float precio;
} Producto;

void ingresarProducto(Producto** inventario, int* numeroProductos) {
    (*numeroProductos)++;
    *inventario = (Producto*)realloc(*inventario, sizeof(Producto) * (*numeroProductos));

    Producto nuevoProducto;

    printf("Ingrese el nombre del producto: ");
    fgets(nuevoProducto.nombre, sizeof(nuevoProducto.nombre), stdin);

    printf("Ingrese la cantidad: ");
    scanf("%d", &nuevoProducto.cantidad);

    printf("Ingrese el precio: ");
    scanf("%f", &nuevoProducto.precio);

    
    getchar();

    (*inventario)[*numeroProductos - 1] = nuevoProducto;

    printf("Producto ingresado exitosamente.\n");
}

void editarProducto(Producto* inventario, int numeroProductos) {
    int indice;
    printf("Ingrese el indice del producto a editar (1-%d): ", numeroProductos - 1);
    scanf("%d", &indice);

    if (indice >= 1 && indice < numeroProductos) {
        Producto* producto = &inventario[indice];

        printf("Ingrese el nuevo nombre del producto: ");
        fgets(producto->nombre, sizeof(producto->nombre), stdin);

        printf("Ingrese la nueva cantidad: ");
        scanf("%d", &producto->cantidad);

        printf("Ingrese el nuevo precio: ");
        scanf("%f", &producto->precio);

       
        getchar();

        printf("Producto editado exitosamente.......\n");

    } else {
        printf("Indice invalido.....\n");
    }
}

void eliminarProducto(Producto** inventario, int* numeroProductos) {
    int indice;
    printf("Ingrese el indice del producto a eliminar (1-%d): ", *numeroProductos - 1);
    scanf("%d", &indice);

    if (indice >= 1 && indice < *numeroProductos) {
        for (int i = indice; i < *numeroProductos - 1; i++) {
            (*inventario)[i] = (*inventario)[i + 1];
        }

        (*numeroProductos)--;
        Producto* temp = (Producto*)malloc(sizeof(Producto) * (*numeroProductos));
        memcpy(temp, *inventario, sizeof(Producto) * (*numeroProductos));
        free(*inventario);
        *inventario = temp;

        printf("Producto eliminado exitosamente.\n");
    } else {
        printf("Indice invalido.\n");
    }
}

void listarProductos(Producto* inventario, int numeroProductos) {
    printf("------ Lista de Productos ------\n");
    for (int i = 0; i < numeroProductos; i++) {
        printf("Producto %d:\n", i);

        printf("Nombre: %s", inventario[i].nombre);

        printf("Cantidad: %d\n", inventario[i].cantidad);

        printf("Precio: %.2f\n", inventario[i].precio);

        printf("-----------------------------\n");
    }
}

void guardarInventario(Producto* inventario, int numeroProductos, const char* nombreArchivo) {
    FILE* archivo = fopen(nombreArchivo, "wb");
    if (archivo != NULL) {
        fwrite(&numeroProductos, sizeof(int), 1, archivo);
        fwrite(inventario, sizeof(Producto), numeroProductos, archivo);
        fclose(archivo);
        printf("Inventario guardado exitosamente.\n");
    } else {
        printf("Error al guardar el inventario en el archivo.\n");
    }
}

void cargarInventario(Producto** inventario, int* numeroProductos, const char* nombreArchivo) {
    FILE* archivo = fopen(nombreArchivo, "rb");
    if (archivo != NULL) {
        fread(numeroProductos, sizeof(int), 1, archivo);
        *inventario = (Producto*)malloc(sizeof(Producto) * (*numeroProductos));
        fread(*inventario, sizeof(Producto), *numeroProductos, archivo);
        fclose(archivo);
        printf("Inventario cargado exitosamente.\n");
    } else {
        printf("Error al cargar el inventario desde el archivo.\n");
    }
}

int main() {
    Producto* inventario = NULL;
    int numeroProductos = 0;
    int opcion;

    cargarInventario(&inventario, &numeroProductos, "inventario.dat");

    do {
        printf("----- Sistema de Inventario -----\n");

        printf("1. Ingresar producto\n");

        printf("2. Editar producto\n");

        printf("3. Eliminar producto\n");

        printf("4. Listar productos\n");

        printf("5. Guardar inventario en archivo\n");

        printf("6. Salir\n");

        printf("Ingrese una opcion: ");
        scanf("%d%*c", &opcion);
        printf("------------------------------------\n");

        switch (opcion) {
            case 1:
                ingresarProducto(&inventario, &numeroProductos);
                break;
            case 2:
                editarProducto(inventario, numeroProductos);
                break;
            case 3:
                eliminarProducto(&inventario, &numeroProductos);
                break;
            case 4:
                listarProductos(inventario, numeroProductos);
                break;

            case 5:
                guardarInventario(inventario, numeroProductos, "inventario.dat");
                break;
            case 6:
                printf("Hasta luego!...\n");
                break;
            default:
                printf("Opcion invalida. Intente nuevamente......\n");
                break;
        }
    } while (opcion != 7);

    guardarInventario(inventario, numeroProductos, "inventario.dat");
    free(inventario);

    return 0;
}
