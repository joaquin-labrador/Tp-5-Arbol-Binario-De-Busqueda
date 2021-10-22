
#include "arbolesABB.h"

int main (){
    //cargarArchivo();
    nodoArbol * arbol = NULL;
    nodo * lista = NULL;
    cargarArbol(&arbol);
    printf("Visualizacion de los nodos en en Inorder:\n");
    inorder(arbol);
    system("pause");
    system("cls");
    copiaArbolALista(arbol,&lista);
    printf("Lista:\n");
    verLista(lista);
    system("pause");
    system("cls");
    printf("Funcion de visualizacion de busqueda por nodo\n\n");
    nodoPorlegajo(arbol,1003);
    system("pause");
    system("cls");
    nodoArbol *nodoEnc = busquedaPorLegajo(arbol,989);
    printf("Funcion del retorno por persona\n\n");
    if(nodoEnc)
        mostrador(nodoEnc->dato);
    else
        printf("El legajo ingresado es incorrecto\n");
    system("pause");
    system("cls");
    nodoEnc = busquedaPorNombre(arbol,"joaquin labrador");
    if(nodoEnc)
        mostrador(nodoEnc->dato);
    else    
        printf("El nombre que ah ingresado es incorrecto\n");
    system("pause");
    system("cls");
    printf("La cantidad de nodos del arbol es |%d|\n",cantidadDeNodo(arbol));
    printf("Altura del arbol es |%d|\n",alturaArbol(arbol));
    printf("Cantidad de hojas : %d \n",cantidadHojas(arbol));
    system("pause");
    system("cls");
    int legajo = 29;
    printf("Elimno el nodo con el legajo |%d|\n",legajo);
    eliminarNodo(&arbol,legajo);
    inorder(arbol);

return 0;
}

//Generacion de archivo
persona crearStruct(){
      srand(time(NULL));
    persona datos;
    printf("Ingrese Nombre y Apellido \n");
    fflush(stdin);
    gets(datos.nombre);
    printf("Ingrese la edad del alumno \n");
    scanf("%d",&datos.edad);
    int ver;
    do{
        datos.legajo = 100;
        ver = verficador(datos.legajo);
    }while(ver == 1);
    return datos;
} 
int verficador(int legajo){
    FILE *buffer = fopen(FILE_ARBOL,"rb");
    persona aux;
    int flag = 0;
    if(buffer != NULL){
        while(fread(&aux,sizeof(persona),1,buffer)>0 && flag == 0){
            if(aux.legajo == legajo){
                return 1;
                flag = 1;
            }
        }
        fclose(buffer);
    }
    if(flag == 0){
        return 0;
    }
}
void cargarArchivo(){
    persona aux;
    FILE *buffer = fopen(FILE_ARBOL,"ab");
    char s;
    do{
        aux = crearStruct();
        fwrite(&aux,sizeof(persona),1,buffer);
        printf("Desea seguir cargando alumno al archivo\n");
        fflush(stdin);
        scanf("%c",&s);
    }while(s == 's');
    fclose(buffer);
}
void verArchivo(){
    FILE *buffer = fopen(FILE_ARBOL,"rb");
    persona aux;
    if(buffer != NULL){
        while(fread(&aux,sizeof(persona),1,buffer)>0){
            printf("Nombre Y Apellido : %s\n",aux.nombre);
            printf("Edad : %d\n",aux.edad);
            printf("Legajo : %d\n",aux.legajo);
            printf(".....................................\n");
            printf("\n\n");
        }
        fclose(buffer);
    }
}
//1
void cargarArbol(nodoArbol **a){
    FILE *buffer = fopen(FILE_ARBOL,"rb");
    persona aux;
    if(buffer != NULL){
        while(fread(&aux,sizeof(persona),1,buffer) > 0){
            insertarOrdenado(a,aux);
        }
        fclose(buffer);
    }
}
nodoArbol *crearNodo(persona a){
    nodoArbol *nuevo = (nodoArbol*)malloc(sizeof(nodoArbol));
    nuevo->dato = a;
    nuevo->der=NULL;
    nuevo->izq=NULL;
    return nuevo;
}
void insertarOrdenado(nodoArbol **a,persona dato){
    /*solucion recursiva*/
    //Cuando el recorrido llegue a un espacio vacio (NULL) se inserta
    
    if(*a){
        if(dato.legajo > (*a)->dato.legajo)
            insertarOrdenado(&((*a)->der),dato);
        else
            insertarOrdenado(&((*a)->izq),dato);
    }
    else
        *a = crearNodo(dato);
}

//2)
void inorder(nodoArbol *a){
    if(a){
           
        inorder(a->izq);   
        mostrador(a->dato); 
        inorder(a->der);
       
    }
}
//3) Creacion de lista, pasar de arbol a lista y mostrar lista
void mostrador(persona a){
     printf("Nombre Y Apellido : %s\n",a.nombre);
        printf("Edad : %d\n",a.edad);
        printf("Legajo : %d\n",a.legajo);
        printf(".....................................\n");
        printf("\n\n");
}
nodo *crearNodoLista (persona dato){
    nodo *nuevo = (nodo*)malloc(sizeof(nodo));
    nuevo->dato = dato;
    nuevo->sig = NULL;
    return nuevo;
}
void insertarAlPrincipio(nodo **lista, persona dato){
    nodo *nuevo = crearNodoLista(dato);
    nuevo->sig = *lista;
    *lista = nuevo;
}
void copiaArbolALista(nodoArbol *a, nodo **lista){
    if(a != NULL){
        insertarAlPrincipio(lista,a->dato);
        copiaArbolALista(a->izq,lista);
        copiaArbolALista(a->der,lista);
    }
}
void verLista(nodo *lista){
    while(lista != NULL){
        mostrador(lista->dato);
        lista = lista->sig;
    }
}
//4) Con y sin retorno
void nodoPorlegajo (nodoArbol *a,int legajo){
    if( a != NULL && a->dato.legajo != legajo){
        nodoPorlegajo(a->izq,legajo);
        nodoPorlegajo(a->der,legajo);
    }
    else{
        if(a != NULL)
            mostrador(a->dato);
    }
}
//Recordar que el arbol esta ordenado por legajos hacia la izq los menores hacia la derecha los mayores
nodoArbol *busquedaPorLegajo(nodoArbol *a, int legajo){
    if(a != NULL){
        if(a->dato.legajo == legajo)
            return a;
        else{
            if(legajo < a->dato.legajo)//Si el parametro es mas chico que el dato en la pos act me muevo hacia la izq
                return busquedaPorLegajo(a->izq,legajo);
            else                       //Si el parametro es mas grande que el dato en la pos act me muevo hacia la der
                return busquedaPorLegajo(a->der,legajo);
        }
    }
    else
        return a;
}

//5)
//Recordar que el arbol esta ordenado por legajo no por nombre
nodoArbol *busquedaPorNombre(nodoArbol *a, char nombre[]){
    if(a != NULL){
        if(strcmpi(a->dato.nombre,nombre) == 0)
            return a;
        else{
            return busquedaPorNombre(a->izq,nombre);
            return busquedaPorNombre(a->der,nombre);
        }
    }
    else
        return a;
}
//7
int cantidadDeNodo(nodoArbol *a){
    if(a){
        return 1 + cantidadDeNodo(a->izq) + cantidadDeNodo(a->der);
       
    }
    else
        return 0;
 
   
}
//6
int alturaArbol(nodoArbol *a){
    if(a){
        if(a->izq == NULL && a->der == NULL)//Es una hoja no cuenta para la altura
        return 1;
        else
        return max(alturaArbol(a->izq),alturaArbol(a->der))+1;//La función "max" sirve para comparar los parámetros y devolver el mayor.
    }
    else
    return 0; //Cuando vuelva de la recurcion retorno 1 para que se acumule por cada recursion  
}
//8
int cantidadHojas(nodoArbol *a){
    int cant = -1;
    if(a){
        if(a->der != NULL || a->izq != NULL)//No es una hoja retorno la suma 
            cant =  cantidadHojas(a->izq) + cantidadHojas(a->der);
        else //Es una hoja retorno que hay una
            return 1;
        
    }
}   

//9
void eliminarNodo(nodoArbol **a , int legajo){
    if(*a){
        if((*a)->dato.legajo == legajo){
            if((*a)->izq != NULL && (*a)->der != NULL ){
                //Nodo de grado 2
                nodoArbol *auxgrado2 = *a;
                borrarDatoExtIzq(&(*a)->der,auxgrado2);//Envio a remplaze apartir de la derecha, el mas pequeño de eso sub arbol
            }
            else{
                nodoArbol *aux = *a;
                //Raiz o de grado 1
                if((*a)->der != NULL){
                    //Si a la derecha tiene datos el le asigno ese dato
                    *a = (*a)->der;
                }
                else{
                    *a = (*a)->izq;
                }
                free(aux);
            }
        }
        else{
            if(legajo > (*a)->dato.legajo)//Si el legajo ingresado es mayor al de la posicion act me muevo hacia la derecha
                eliminarNodo(&(*a)->der,legajo);//Paso por referencia no por copia asi modifica.
            else   
                eliminarNodo(&(*a)->izq,legajo);
        }
    }
}
//Funcion exclusiva cuando vamos a borrar nodo de grados 2
void borrarDatoExtIzq (nodoArbol **a, nodoArbol *act){
    //El primer parametro es por referecia y el segundo por copia para tener el valor
    nodoArbol *aux;
    if((*a)->izq != NULL)//Avanzamos hacia el nodo de la extrema izquierda
        borrarDatoExtIzq(&(*a)->izq,aux);
    //Cuando nos ubicamos en la extrema izquierda
    else{
        act->dato = (*a)->dato; // Reemplazo la persona, del dato que voy a borrar osea la PERSONA DE LA EXT IZQ y se la asigno a la nodo donde coincidian los datos
        //OSEA VOY A BORRAR LA EXTREMA IZQ PERO SUS DATOS SE ASIGAN AL NODO QUE PASE POR COPIA.
        aux = *a;
        //Si a la derecha de la extrema izquierda hay datos osea datos mayores a este, no debemos perder esos datos (osea por si el dato borrado no es una hoja) & si
        //es una hoja asigna NULL:
        *a = (*a)->der;
        free(aux);
    }

}
//En la funcion cuando encuentre un nodo grado 2 por referecia el nodo de la izquierda
void borrarDatoExtDer(nodoArbol **a, nodoArbol *act){
    nodoArbol *aux;
    if((*a)->der != NULL)//Avanzamos hacia el nodo de la extrema derecha
        borrarDatoExtDer(&(*a)->der,aux);
    //Cuando nos ubicamos en la extrema derecha apartir del sub arbol izq
    else{
        act->dato = (*a)->dato;
        aux = *a; //Asigno la direccion de memoria del ext der  a un aux 
        free(aux);
        *a = (*a)->izq;
    }
}