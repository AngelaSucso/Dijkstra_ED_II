#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <queue>
using namespace std;

#define MAX 10005 /// Define maximo numero de vértices
#define Node pair< int,int > /// Define el nodo como un par(first,second)
                             /// first = vertice adyacente, second = peso de la arista
#define INF 1<<30 /// Definir INF = valor grande, representa la distancia infinita inicial.

///FUNCION PARA ABRIR Y LEER UN.TXT
vector<string> abre_txt(string dir){
    string dato;
    vector <string> lista;
    ifstream f(dir);
    while(!f.eof()){
        getline(f, dato);
        lista.push_back(dato);
    }
    return lista;
}

///FUNCION PARA GUARDAR COMO SALIDA EN EL .TXT
void guarda_txt(string cad, string dir){
    ofstream fout(dir);
    fout << cad << endl;
}

///FUNCION PARA SEPARAR LOS DATOS DEL FICHERO
template <class Container>
void split(const string& str, Container& cont, char delim = ' '){
    stringstream ss(str);
    string token;
    while (getline(ss, token, delim)) {
        cont.push_back(token);
    }
}

///FUNCION PARA CONVERTIR UN STRING A ENTERO
int strToInt(string valor){
    stringstream intValue(valor);
    int num = 0;
    intValue >> num;
    return num;
}

///FUNCION PARA IMPRIMIR VECTOR
template <typename T>
void imprimirVector(vector<T> vec){
    for(int i=0; i<vec.size(); i++){
        cout<<vec[i]<<" ";
    }
}

/**COLA DE PRIORIDAD:
 Modifica el comparador recursivo para que sea un min-Heap*/
struct comparador {
    bool operator() ( const Node &a , const Node &b ) {
        return a.second > b.second;
    }
};

vector< Node > ady[ MAX ]; /// Lista de vectores para nodos adyacentes
int distancia[ MAX ];      /// Distancia[u] = distancia de un vértice(inicial) a otro
bool visitado[ MAX ];      /// Para vértices visitados
priority_queue< Node, vector<Node>, comparador > Q; /// Comparador definido,menor valor este en el tope
int V;                     /// Numero de vertices
int previo[ MAX ];         /// Impresion de caminos

///FUNCION DE INICIALIZACION
void init(){
    for( int i = 0 ; i <= V ; ++i ){
        distancia[ i ] = INF;  /// Inicializa todas las distancias con valor INF
        visitado[ i ] = false; /// Inicializamos todos los vértices como no visitados
        previo[ i ] = -1;      /// Inicializamos el previo del vertice i con -1, aun no hay un camino
    }
}

///FUNCION PARA EL PASO DE RELAJACION
void relajacion( int actual , int adyacente , int peso )
{/**
Si( distancia [origen al vertice actual] + peso de su arista < distancia [origen al vertice adyacente] */
    if( distancia[ actual ] + peso < distancia[ adyacente ] ){
        distancia[ adyacente ] = distancia[ actual ] + peso;  /// relajamos el vertice actualizando la distancia
        previo[ adyacente ] = actual;                         /// tambien actualizamos el vertice previo
        Q.push( Node( adyacente , distancia[ adyacente ] ) ); /// agregamos adyacente a la cola de prioridad
    }
}

///Impresion del camino mas corto desde el vertice inicial al final
void print( int destino ){
    if( previo[ destino ] != -1 )    /// si aun poseo un vertice previo
        print( previo[ destino ] );  /// recursivamente sigo explorando
    cout<<destino<<" ";              /// terminada la recursion imprimo los vertices recorridos
}

string generarCSV(int final);

///FUNCION DIJLSTRA
void dijkstra( int inicial ){
    init();                         /// inicializamos nuestros arreglos
    Q.push( Node( inicial , 0 ) );  /// Insertamos el vértice inicial en la Cola de Prioridad
    distancia[ inicial ] = 0;       /// Inicializamos la distancia del inicial como 0
    int actual , adyacente , peso;
    while( !Q.empty() ){                   /// Mientras cola no este vacia
        actual = Q.top().first;            /// Obtengo de la cola el nodo con menor peso, en un comienzo será el inicial
        Q.pop();                           /// Sacamos el elemento de la cola
        if( visitado[ actual ] ) continue; /// Si el vértice actual ya fue visitado entonces sigo sacando elementos de la cola
        visitado[ actual ] = true;         /// Marco como visitado el vértice actual

        for( int i = 0 ; i < ady[actual].size() ; ++i ){ /// reviso sus adyacentes del vertice actual
            adyacente = ady[actual][ i ].first;          /// posicion del vertice adyacente
            peso = ady[actual][ i ].second;              /// peso de la arista que une actual con adyacente (actual, adyacente)
            if( !visitado[adyacente] ){                  /// si el vertice adyacente no fue visitado
                relajacion(actual, adyacente, peso);     /// realizamos el paso de relajacion
            }
        }
    }

    ///MOSTRAR EN CONSOLA
    ///Busca las distancias mas cortas a partir del vertice inicial
    cout<<"Distancias mas cortas iniciando en vertice: "<<inicial<<endl;
    for( int i = 1 ; i <= V ; ++i ){
        cout<<"Vertice "<<i<<" distancia mas corta = "<<distancia[ i ]<<endl;
    }

    cout<<"\n**************Impresion de camino mas corto**************"<<endl;
    cout<<"Ingrese vertice destino: ";
    int destino;
    scanf("%d" , &destino );
    print( destino );
    cout<<endl;

    string resultado = generarCSV(destino); /// vertice final como parametro
    guarda_txt(resultado, "dijkstra1.csv");  /// llamada a la funcion para generar .CSV
}

string generarCSV(int destino){
    ///Ingresando los nombres de los departamentos
    string cities[25]={"LIMA","CALLAO","LA LIBERTAD","AREQUIPA","MOQUEGUA","CUSCO","LAMBAYEQUE","PIURA",
    "AMAZONAS","ICA","JUNIN","ANCASH","CAJAMARCA","HUANUCO","APURIMAC","PUNO","TACNA","LORETO","SAN MARTIN",
    "AYACUCHO","HUANCAVELICA","PASCO","TUMBES","UCAYALI","MADRE DE DIOS"};

    cout<<"\nCreando archivo .csv"<<endl;
    string salida;
    salida.append("Source,Target,Label");
    int i = destino;
    while(previo[i] != -1){
        salida.append("\n");
        int x = previo[i];
        for(int j = 0; j < ady[i].size(); ++j){
            if(ady[i][j].first == x){
                int p = ady[i][j].second;
                salida.append(cities[i-1]+", "+cities[x-1]+", "+to_string(p));
                break;
            }
        }
        i = x;
    }
    return salida;
}

int main(){
    vector <string> datos=abre_txt("aristasDijkstra.txt"); ///recibe un .txt
    int E, origen, fin, peso, inicial;
    V = strToInt(datos[0]);  ///CANTIDAD DE VERTICES
    E = strToInt(datos[1]);  ///CANTIDAD DE ARISTAS

    for(int i=2; i<datos.size(); i++){
        vector<string> contenedor;
        split(datos[i], contenedor,' ');  ///leera los datos del fichero y los insertara en un vector
        origen = strToInt(contenedor[0]); ///conversion a enteros
        fin = strToInt(contenedor[1]);    ///conversion a enteros
        peso = strToInt(contenedor[2]);   ///conversion a enteros

        ady[ origen ].push_back( Node( fin, peso ) );  ///insercion del vertice origen con su peso
        ady[ fin ].push_back( Node( origen, peso ) );  ///insercion del vertice final con su peso
    }

    cout<<"Ingrese el vertice inicial: ";
    cin>>inicial;
    cout<<endl;
    ///INICIO DE FUNCION DIJKSTRA
    dijkstra( inicial );

    return 0;
}
