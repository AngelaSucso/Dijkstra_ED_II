#include<iostream>
using namespace std;
#include<fstream>

void Primer_Trimestre(int MatrixAdy_Ciudades[][26]){
    //matriz del primer trimestre
    int matriz_Primer_Tri[25][2];
    ifstream Arch_Primer_Tri;
    Arch_Primer_Tri.open("E:\\discretasss\\primer_trimestre.txt");
    for (int i=0; i<25;i++){
        for(int j=0; j<2;j++){
            Arch_Primer_Tri >>matriz_Primer_Tri[i][j];
            //cout<<matriz_Primer_Tri[i][j]<<"   ";
        }
        //cout<<endl;
    }
    Arch_Primer_Tri.close();


    //Guardando Datos vertice-vertice-peso de la arista
    ofstream archivo_VerticesArista;
    archivo_VerticesArista.open("E:\\discretasss\\Archivo_Vertices_Aristas_1T.txt");
    for (int i=0; i<25;i++){
        int codigo=0, peso_Guardado=0;
        for(int j=0; j<2;j++){
            int elemento=matriz_Primer_Tri[i][j];
            if(j==0){
                codigo=elemento;
                
            }
            else if(j==1){
                peso_Guardado=elemento;
            }            
        }
        //cout<< codigo<<" "<<peso_Guardado;
        //cout<<endl;
        //cout<<"codigo: "<<codigo<<" --> ";
        cout<<endl;
        //cout<<"CODIGO: "<<codigo<<endl;
        for (int k=1; k<27;k++){
            int promedio=0;
            if(MatrixAdy_Ciudades[codigo][k]==1){
                promedio=(peso_Guardado+matriz_Primer_Tri[k-1][1])/2;
                //cout<<k<<" ";//<<MatrixAdy_Ciudades[0][k]<<" ";
                //cout<<"promedio con :"<<k<<" = "<<promedio<<"  ";
                archivo_VerticesArista<<codigo<<" "<<k<<" "<<promedio;
                archivo_VerticesArista<<endl;

            }
            
            //cout<<endl;
            
        }
        cout<<endl;
        
    }
    archivo_VerticesArista.close();

}

void segundo_Trimestre(int MatrixAdy_Ciudades[][26]){
    //matriz del segundo trimestre
    int matriz_Segundo_Tri[25][2];
    ifstream Arch_Segundo_Tri;
    Arch_Segundo_Tri.open("E:\\discretasss\\segundo_trimestre.txt");
    for (int i=0; i<25;i++){
        for(int j=0; j<2;j++){
            Arch_Segundo_Tri >>matriz_Segundo_Tri[i][j];
        }
    }
    Arch_Segundo_Tri.close();


    //Guardando Datos vertice-vertice-peso de la arista
    ofstream archivo_VerticesArista_2T;
    archivo_VerticesArista_2T.open("E:\\discretasss\\Archivo_Vertices_Aristas_2T.txt");
    for (int i=0; i<25;i++){
        int codigo=0, peso_Guardado=0;
        for(int j=0; j<2;j++){
            int elemento=matriz_Segundo_Tri[i][j];
            if(j==0){
                codigo=elemento;
                
            }
            else if(j==1){
                peso_Guardado=elemento;
            }            
        }

        cout<<endl;
        for (int k=1; k<27;k++){
            int promedio=0;
            if(MatrixAdy_Ciudades[codigo][k]==1){
                promedio=(peso_Guardado+matriz_Segundo_Tri[k-1][1])/2;
                archivo_VerticesArista_2T<<codigo<<" "<<k<<" "<<promedio;
                archivo_VerticesArista_2T<<endl;
            }
        }
        cout<<endl; 
    }
    archivo_VerticesArista_2T.close();

}


void tercer_trimestre(int MatrixAdy_Ciudades[][26]){
    //matriz del tercer trimestre
    int matriz_Tercer_Tri[25][2];
    ifstream Arch_Tercer_Tri;
    Arch_Tercer_Tri.open("E:\\discretasss\\tercer_trimestre.txt");
    for (int i=0; i<25;i++){
        for(int j=0; j<2;j++){
            Arch_Tercer_Tri >>matriz_Tercer_Tri[i][j];
        }
    }
    Arch_Tercer_Tri.close();


    //Guardando Datos vertice-vertice-peso de la arista
    ofstream archivo_VerticesArista_3T;
    archivo_VerticesArista_3T.open("E:\\discretasss\\Archivo_Vertices_Aristas_3T.txt");
    for (int i=0; i<25;i++){
        int codigo=0, peso_Guardado=0;
        for(int j=0; j<2;j++){
            int elemento=matriz_Tercer_Tri[i][j];
            if(j==0){
                codigo=elemento;
                
            }
            else if(j==1){
                peso_Guardado=elemento;
            }            
        }

        cout<<endl;
        for (int k=1; k<27;k++){
            int promedio=0;
            if(MatrixAdy_Ciudades[codigo][k]==1){
                promedio=(peso_Guardado+matriz_Tercer_Tri[k-1][1])/2;
                archivo_VerticesArista_3T<<codigo<<" "<<k<<" "<<promedio;
                archivo_VerticesArista_3T<<endl;
            }
        }
        cout<<endl; 
    }
    archivo_VerticesArista_3T.close();


}
int main(){
    //leyendo Matriz de adycencia de las ciudades
    int MatrixAdy_Ciudades[26][26];
    ifstream arch_CMA;
    arch_CMA.open("E:\\discretasss\\MATRIZ_CIUDADES_ADY.txt");

    for (int i=0; i<26;i++){
        for(int j=0; j<26;j++){
            
            arch_CMA >>MatrixAdy_Ciudades[i][j];
            //cout<<MatrixAdy_Ciudades[i][j]<<"   ";
        }
        //cout<<endl;
    }
    arch_CMA.close();

    Primer_Trimestre(MatrixAdy_Ciudades);
    segundo_Trimestre(MatrixAdy_Ciudades);
    tercer_trimestre(MatrixAdy_Ciudades);


    cout<<"Fin";
    return 0;
}

