#include <iostream>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

class ListaGenericaDoble {

    private:
        class Nodo {
            public:
            int codigo;
            string nombre;
            string paterno;
            string materno;
            string carrera;

            Nodo *siguiente;
            Nodo *anterior;

            void setPunteroAnterior(Nodo *x){
                anterior = x;
            }

            Nodo *getPunteroAnterior(){
                return anterior;
            }

            void setPunteroSiguiente(Nodo *x){
                siguiente = x;
            }

            Nodo *getPunteroSiguiente(){
                return siguiente;
            }
        };

    Nodo *raiz;

    public:
        ListaGenericaDoble();
        int cantidad();
        void insertar(int pos, int code, string name, string ap, string am, string c_pro);
        void imprimir();
        void imprimirReversa();
        void eliminar(int cod);
        void modificarDatos(int codigo);
        void ordenar();
        //Utilitarios para ordenar()
        void insertarNodo(int pos, Nodo *nodo);
        void eliminarNodo(int pos);
        void insertarNodoFake(int pos);
};

ListaGenericaDoble::ListaGenericaDoble()
{
    raiz = NULL;
}

int ListaGenericaDoble::cantidad(){
    Nodo *recorrido = raiz;
    int cant = 0;
    while (recorrido != NULL)
    {
        cant++;
        recorrido = recorrido->siguiente;
    }
    return cant;
}

void ListaGenericaDoble::insertar(int pos, int code, string name, string ap, string am, string c_pro){
    Nodo* recorrido_existe = raiz;

    //Verificar si ya existe el codigp
    while(recorrido_existe != NULL){
        if(recorrido_existe->codigo == code){
            cout << "insertar(): Este codigo ya existe!!!\n";
            return;
        }
    }

    if (pos < 1){cout << "insertar(): Posicion no valida!!!\n"; return;}
    if (pos <= cantidad() + 1)
    {
        Nodo *nuevo = new Nodo();
        nuevo->codigo = code;
        nuevo->nombre = name;
        nuevo->paterno = ap;
        nuevo->materno = am;
        nuevo->carrera = c_pro;

        //Si no hay elementos y la posicion excede a 1
        if(cantidad() == 0 && pos > 1){
            cout << "insertar(): No hay elementos!!!";
            return;
        }

        if (pos == 1){
            nuevo->siguiente = raiz;
            nuevo->anterior = NULL;
            raiz = nuevo;

        }else if (pos == cantidad() + 1){
            Nodo *recorrido = raiz;
            while (recorrido->siguiente != NULL)
            {
                recorrido = recorrido->siguiente;
            }
           // nuevo->anterior = recorrido;
            recorrido->siguiente = nuevo;
            (recorrido->siguiente)->anterior = recorrido;
            nuevo->siguiente = NULL;

        }else{
            Nodo *recorrido = raiz;
            for (int f = 1; f <= pos - 2; f++)
            {
                recorrido = recorrido->siguiente;
            }

            Nodo *backup = recorrido->siguiente;
            recorrido->siguiente = nuevo;
            (recorrido->siguiente)->anterior = recorrido;
            nuevo->siguiente = backup;
            (nuevo->siguiente)->anterior = nuevo;

        }
    }else{cout << "insertar(): Posicion no valida!!!\n"; return;}
}

void ListaGenericaDoble::imprimir()
{
    Nodo *recorrido = raiz;
    int i = 1;
    cout << "    ||        Listado completo        ||    \n\n";
    while (recorrido != NULL)
    {
//        cout << "> " << i << "\n";
        cout << "Codigo  :     " << recorrido->codigo << "\n"; // U+21C4
        cout << "Nombre  :     " << recorrido->nombre << " " << recorrido->paterno << " " << recorrido->materno << "\n";
        cout << "Carrera :     " << recorrido->carrera << "\n\n";
        recorrido = recorrido->siguiente;
        i++;
    }
    if(cantidad() == 0){cout << "imprimir(): Lista vacia!!!\n"; return;}
    cout << "\n";
}

void ListaGenericaDoble::imprimirReversa(){
    Nodo *recorrido = raiz;
    int i = cantidad();

    cout << "    ||   Listado completo (Reversa)   ||    \n\n";
    if(cantidad() == 0){cout << "imprimirReversa(): Lista vacia!!!\n"; return;}
    while (recorrido->siguiente != NULL){
        recorrido = recorrido->siguiente;
    }

    while(recorrido != NULL){
//        cout << "> " << i << "\n";
        cout << "Codigo  :     " << recorrido->codigo << "\n"; // U+21C4
        cout << "Nombre  :     " << recorrido->nombre << " " << recorrido->paterno << " " << recorrido->materno << "\n";
        cout << "Carrera :     " << recorrido->carrera << "\n\n";
        recorrido = recorrido->anterior;
        i--;
    }

    cout << "\n";
}

void ListaGenericaDoble::eliminar(int cod){
    if(cantidad() == 0){cout << "eliminar(): Lista vacia!!!\n"; return;}
    Nodo *recorrido = raiz;

    //Si se encuentra en el primero
    if(recorrido->codigo == cod){
        raiz = raiz->siguiente;
        if(raiz != NULL){raiz->anterior = NULL;}


    //Si se encuentra despues
    }else{
        while((recorrido->siguiente)->codigo != cod){
            recorrido = recorrido->siguiente;

            //Si se llega al final y todavia no se ha encontrado el elemento
            if (recorrido->siguiente == NULL){cout << "eliminar(): Este codigo no existe!!!\n"; return;}
        }

        recorrido->siguiente = (recorrido->siguiente)->siguiente;

        //Solo se actualiza el siguiente si el eliminado no fue el ultimo elemento
        if(recorrido->siguiente != NULL){(recorrido->siguiente)->anterior = recorrido;}
    }
}

void ListaGenericaDoble::modificarDatos(int codigo){
    if(cantidad() == 0){cout << "modificarDatos(): Lista vacia!!!\n"; return;}

    Nodo *recorrido = raiz;
    int opcion;
    int posicion = 1;

    int int_aux;
    string string_aux;

    cout << "Modificar Datos\n";
    cout << "1: Modificar Codigo\n";
    cout << "2: Modificar Nombre\n";
    cout << "3: Modificar Apellido Paterno\n";
    cout << "4: Modificar Apellido Materno\n";
    cout << "5: Modificar Carrera Profesional\n";
    cin >> opcion;
    //1: Codigo / 2: Nombre / 3: Paterno / 4: Materno

    //Encontrar el nodo
    while(recorrido->codigo != codigo){
        recorrido = recorrido->siguiente;
        posicion++;

        //Si no se encuentra el Nodo
        if(recorrido == NULL){cout << "modificarDatos(): No existe el codigo!!!\n"; return;}
    }

    //Codigo
    if(opcion == 1){
        cout << "> Posicion " << posicion << "\n";
        cout << "   Codigo:  " << recorrido->codigo << "\n";
        cout << "   Escriba un nuevo Codigo:  \n";
        cin >> int_aux;
        recorrido->codigo = int_aux;

    //Nombre
    }else if(opcion == 2){
        cout << "> Posicion " << posicion << "\n";
        cout << "   Nombre:  " << recorrido->nombre << "\n";
        cout << "   Escriba un nuevo Nombre:  \n";
        cin >> string_aux;
        recorrido->nombre = string_aux;
    }else if(opcion == 3){
        cout << "> Posicion " << posicion << "\n";
        cout << "   Apellido Paterno:  " << recorrido->paterno << "\n";
        cout << "   Escriba un nuevo Apellido Paterno:  \n";
        cin >> string_aux;
        recorrido->paterno = string_aux;
    }else if(opcion == 4){
        cout << "> Posicion " << posicion << "\n";
        cout << "   Apellido Materno:  " << recorrido->materno << "\n";
        cout << "   Escriba un nuevo Apellido Materno:  \n";
        cin >> string_aux;
        recorrido->materno = string_aux;
    }else if(opcion == 5){
        cout << "> Posicion " << posicion << "\n";
        cout << "   Carrera Profesional:  " << recorrido->carrera << "\n";
        cout << "   Escriba una Carrera Profesional:  \n";
        cin >> string_aux;
        recorrido->carrera = string_aux;
    }else{cout << "modificarDatos(): Ingrese una posicion correcta!!!\n";}
}

//              ORDENAR

void ListaGenericaDoble::insertarNodo(int pos, Nodo *nodo){
    if (pos < 1){cout << "insertarNodo(): Posicion no valida!!!"; return;}
    if (pos <= cantidad() + 1)
    {
        Nodo *nuevo = new Nodo();
        nuevo = nodo;

        //Si no hay elementos y la posicion excede a 1
        if(cantidad() == 0 && pos > 1){
            cout << "insertarNodo(): No hay elementos!!!";
            return;
        }

        if (pos == 1){
            nuevo->siguiente = raiz;
            (nuevo->siguiente)->anterior = nuevo;
            nuevo->anterior = NULL;
            raiz = nuevo;

        }else if (pos == cantidad() + 1){
            Nodo *recorrido = raiz;
            while (recorrido->siguiente != NULL)
            {
                recorrido = recorrido->siguiente;
            }
           // nuevo->anterior = recorrido;
            recorrido->siguiente = nuevo;
            (recorrido->siguiente)->anterior = recorrido;
            nuevo->siguiente = NULL;

        }else{
            Nodo *recorrido = raiz;
            for (int f = 1; f <= pos - 2; f++)
            {
                recorrido = recorrido->siguiente;
            }

            Nodo *backup = recorrido->siguiente;
            recorrido->siguiente = nuevo;
            (recorrido->siguiente)->anterior = recorrido;
            nuevo->siguiente = backup;
            (nuevo->siguiente)->anterior = nuevo;

        }
    }else{cout << "insertarNodo(): Posicion no valida!!!\n"; return;}
}

void ListaGenericaDoble::eliminarNodo(int pos){

    if(cantidad() == 0){cout << "eliminarNodo(): Lista vacia!!!\n"; return;}

    if(pos == 1){
        raiz = raiz->siguiente;
        if(raiz != NULL){raiz->anterior = NULL;}
    }else if(pos > 1 && pos < cantidad()){
        Nodo *recorrido = raiz;

        for(int i=1; i<pos-1; i++){
            recorrido = recorrido->siguiente;
        }

        recorrido->siguiente = recorrido->siguiente->siguiente;
        (recorrido->siguiente)->anterior = recorrido;

    }else if(pos == cantidad()){
        Nodo *recorrido = raiz;

        while(recorrido->siguiente->siguiente != NULL){
            recorrido = recorrido->siguiente;
        }

        recorrido->siguiente = NULL;
    }else{cout << "eliminarNodo(): Posicion no valida!!!\n";}
}


void ListaGenericaDoble::ordenar(){

    if(cantidad() == 0){cout << "ordenar(): Lista vacia!!!\n"; return;}

    if(cantidad() > 1){
        Nodo *recorrido = raiz;
        Nodo *recorrido_interno = raiz;
        Nodo *backup;

        Nodo *nuevo = new Nodo();
        int cant_inicial = cantidad();
        int pos_recorrido = 1;
        int pos_recorrido_interno = 1;
        bool cambio_realizado = false;

        //Para cada nodo
        for (int i = 1; i < cant_inicial; i++){
//            cout << "Nodo " << i << "\n";

            recorrido_interno = recorrido->siguiente;
            pos_recorrido_interno = 1;

            //Hasta el final
            while(recorrido_interno != NULL){
//                cout << "   Recorrido interno = " << recorrido_interno->codigo << "\n";

                //Si se encuentra uno menor se hace la inserción
                if(recorrido_interno->codigo < recorrido->codigo){
//                    cout << "   Se encontro!!\n";
                    backup = recorrido_interno->siguiente;
                    nuevo = recorrido_interno;
                    eliminarNodo(pos_recorrido + pos_recorrido_interno);
                    insertarNodo(pos_recorrido, nuevo);
                    cambio_realizado = true;
                }
                if(cambio_realizado == true){recorrido_interno = backup;}
                else{recorrido_interno = recorrido_interno->siguiente;}
                cambio_realizado = false;
                pos_recorrido_interno++;
            }
            //Se actualiza el nodo recorrido
            recorrido = raiz;
            for(int i=1; i<pos_recorrido+1; i++){
                recorrido = recorrido->siguiente;
            }
            pos_recorrido++;
//            imprimir();
        }

    }else{cout << "Ordenado!!!"; return;}
}

void ListaGenericaDoble::insertarNodoFake(int pos){
    Nodo *nuevo = new Nodo();
    nuevo->codigo = 123;
    insertarNodo(pos, nuevo);
}

int main(){
    ListaGenericaDoble *lg = new ListaGenericaDoble();
    string name;
    string a_p;
    string a_m;
    string c_p;
    int code;
    int posicion;

    string continuar;
    bool cond = true;
    int opcion;

    while(cond == true){
        cout << "=====||   REGISTRO DE ALUMNOS ||=====\n";
        cout << "                  MENU\n";
        cout << "1: Imprimir()\n";
        cout << "2: Insertar(Codigo, Nombre, A. Paterno, A. Materno, Carrera)\n";
        cout << "3: Eliminar(Codigo)\n";
        cout << "4: Eliminar Nodo(Posicion)\n";
        cout << "5: Modificar Datos(Codigo)\n";
        cout << "6: Ordenar()\n";
        cout << "7: Imprimir Reversa()\n";
        cout << "8: LIMPIAR\n";
        cout << "9: SALIR\n";
        cin >> opcion;
        if(opcion == 1){
            lg->imprimir();

        }else if (opcion == 2){
            cout << "\nNOTA: INGRESE LOS TEXTOS SIN ESPACIOS!!\n";
            cout << "Ingrese un Codigo: "; cin >> code; cout << "\n";
            cout << "Ingrese el Nombre: "; cin >> name; cout << "\n";
            cout << "Ingrese el Apellido Paterno: "; cin >> a_p; cout << "\n";
            cout << "Ingrese el Apellido Materno: "; cin >> a_m; cout << "\n";
            cout << "Ingrese la Carrera: "; cin >> c_p; cout << "\n";
            cout << "Ingrese la Posicion: "; cin >> posicion; cout << "\n";
            lg->insertar(posicion, code, name, a_p, a_m, c_p);

        }else if (opcion == 3){
            cout << "Ingrese un codigo para eliminar: "; cin >> code; cout << "\n";
            lg->eliminar(code);

        }else if (opcion == 4){
            cout << "Ingrese una posicion para eliminar: "; cin >> posicion; cout << "\n";
            lg->eliminarNodo(posicion);

        }else if (opcion == 5){
            cout << "Ingrese un Codigo para modificar datos: "; cin >> code; cout << "\n";
            lg->modificarDatos(code);

        }else if (opcion == 6){
            cout << "ORDENADO!!! \n";
            lg->ordenar();

        }else if (opcion == 7){
            lg->imprimirReversa();

        }else if(opcion == 8){
            for(int i=0; i<100; i++){cout << "\n";}

        }else if(opcion == 9){
            cond = false;
            return 0;

        }else{
            cout << "Opcion no Valida!!!";
        }

        cout << "Continuar?? (s/n): \n"; cin >> continuar; cout << "\n";
        if (continuar == "n"){cond = false; return 0;}
    }
    return 0;
}
