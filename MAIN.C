#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char nombre[100];
    int cantidad;
    float precio;
} Producto;

void ingresarProducto(Producto** inventario, int* numProductos) {
    (*numProductos)++;
    *inventario = (Producto*)realloc(*inventario, sizeof(Producto) * (*numProductos));

    Producto nuevoProducto;

    printf("Ingrese el nombre del producto: ");
    fgets(nuevoProducto.nombre, sizeof(nuevoProducto.nombre), stdin);

    printf("Ingrese la cantidad: ");
    scanf("%d", &nuevoProducto.cantidad);

    printf("Ingrese el precio: ");
    scanf("%f", &nuevoProducto.precio);

    // Limpiar el buffer de entrada
    getchar();

    (*inventario)[*numProductos - 1] = nuevoProducto;

    printf("Producto ingresado exitosamente.\n");
}

void editarProducto(Producto* inventario, int numProductos) {
    int indice;
    printf("Ingrese el indice del producto a editar (0-%d): ", numProductos - 1);
    scanf("%d", &indice);

    if (indice >= 0 && indice < numProductos) {
        Producto* producto = &inventario[indice];

        printf("Ingrese el nuevo nombre del producto: ");
        fgets(producto->nombre, sizeof(producto->nombre), stdin);

        printf("Ingrese la nueva cantidad: ");
        scanf("%d", &producto->cantidad);

        printf("Ingrese el nuevo precio: ");
        scanf("%f", &producto->precio);

        // Limpiar el buffer de entrada
        getchar();

        printf("Producto editado exitosamente.\n");
    } else {
        printf("Indice invalido.\n");
    }
}

void eliminarProducto(Producto** inventario, int* numProductos) {
    int indice;
    printf("Ingrese el indice del producto a eliminar (0-%d): ", *numProductos - 1);
    scanf("%d", &indice);

    if (indice >= 0 && indice < *numProductos) {
        for (int i = indice; i < *numProductos - 1; i++) {
            (*inventario)[i] = (*inventario)[i + 1];
        }

        (*numProductos)--;
        Producto* temp = (Producto*)malloc(sizeof(Producto) * (*numProductos));
        memcpy(temp, *inventario, sizeof(Producto) * (*numProductos));
        free(*inventario);
        *inventario = temp;

        printf("Producto eliminado exitosamente.\n");
    } else {
        printf("Indice invalido.\n");
    }
}

void listarProductos(Producto* inventario, int numProductos) {
    printf("------ Lista de Productos ------\n");
    for (int i = 0; i < numProductos; i++) {
        printf("Producto %d:\n", i);
        printf("Nombre: %s", inventario[i].nombre);
        printf("Cantidad: %d\n", inventario[i].cantidad);
        printf("Precio: %.2f\n", inventario[i].precio);
        printf("-----------------------------\n");
    }
}

void guardarInventario(Producto* inventario, int numProductos, const char* nombreArchivo) {
    FILE* archivo = fopen(nombreArchivo, "wb");
    if (archivo != NULL) {
        fwrite(&numProductos, sizeof(int), 1, archivo);
        fwrite(inventario, sizeof(Producto), numProductos, archivo);
        fclose(archivo);
        printf("Inventario guardado exitosamente.\n");
    } else {
        printf("Error al guardar el inventario en el archivo.\n");
    }
}

void cargarInventario(Producto** inventario, int* numProductos, const char* nombreArchivo) {
    FILE* archivo = fopen(nombreArchivo, "rb");
    if (archivo != NULL) {
        fread(numProductos, sizeof(int), 1, archivo);
        *inventario = (Producto*)malloc(sizeof(Producto) * (*numProductos));
        fread(*inventario, sizeof(Producto), *numProductos, archivo);
        fclose(archivo);
        printf("Inventario cargado exitosamente.\n");
    } else {
        printf("Error al cargar el inventario desde el archivo.\n");
    }
}

int main() {
    Producto* inventario = NULL;
    int numProductos = 0;
    int opcion;

    cargarInventario(&inventario, &numProductos, "inventario.dat");

    do {
        printf("\n----- Sistema de Inventario -----\n");
        printf("1. Ingresar producto\n");
        printf("2. Editar producto\n");
        printf("3. Eliminar producto\n");
        printf("4. Listar productos\n");
        printf("5. Vender producto\n");
        printf("6. Guardar inventario en archivo\n");
        printf("7. Salir\n");
        printf("Ingrese una opcion: ");
        scanf("%d%*c", &opcion);

        switch (opcion) {
            case 1:
                ingresarProducto(&inventario, &numProductos);
                break;
            case 2:
                editarProducto(inventario, numProductos);
                break;
            case 3:
                eliminarProducto(&inventario, &numProductos);
                break;
            case 4:
                listarProductos(inventario, numProductos);
                break;
            case 5:
                // Aquí se implementaría la función de venderProducto
                printf("Funcion venderProducto no implementada.\n");
                break;
            case 6:
                guardarInventario(inventario, numProductos, "inventario.dat");
                break;
            case 7:
                printf("Hasta luego!\n");
                break;
            default:
                printf("Opcion invalida. Intente nuevamente.\n");
                break;
        }
    } while (opcion != 7);

    guardarInventario(inventario, numProductos, "inventario.dat");
    free(inventario);

    return 0;
}
