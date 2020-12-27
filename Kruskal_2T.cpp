#include<bits/stdc++.h> 
using namespace std; 
#include<fstream>

string cities[25]={"LIMA","CALLAO","LA LIBERTAD","AREQUIPA","MOQUEGUA","CUSCO","LAMBAYEQUE","PIURA",
    "AMAZONAS","ICA","JUNIN","ANCASH","CAJAMARCA","HUANUCO","APURIMAC","PUNO","TACNA","LORETO","SAN MARTIN",
    "AYACUCHO","HUANCAVELICA","PASCO","TUMBES","UCAYALI","MADRE DE DIOS"};
fstream My_File;

typedef  pair<int, int> iPair; 
  
struct Graph{ 
    int V, E; 
    vector< pair<int, iPair> > edges; 
    Graph(int V, int E){ 
        this->V = V; 
        this->E = E; 
    } 
    void addEdge(int u, int v, int w){ 
        edges.push_back({w, {u, v}}); 
    } 
    int kruskalMST(); 
}; 
  
struct DisjointSets{ 
    int *parent, *rnk; 
    int n; 
    DisjointSets(int n){ 
        this->n = n; 
        parent = new int[n+1]; 
        rnk = new int[n+1]; 
        for (int i = 0; i <= n; i++){ 
            rnk[i] = 0; 
            parent[i] = i; 
        } 
    } 

    int find(int u){ 
        if (u != parent[u]) 
            parent[u] = find(parent[u]); 
        return parent[u]; 
    } 
  
    void merge(int x, int y){ 
        x = find(x), y = find(y); 
  		if (rnk[x] > rnk[y]) 
            parent[y] = x; 
        else 
            parent[x] = y; 
  
        if (rnk[x] == rnk[y]) 
            rnk[y]++; 
    } 
}; 
  
  
int Graph::kruskalMST() { 
    // archivo csv
    fstream ReadFile("Datos_Grafo_K_2T.csv",ios::in);
    if(!ReadFile){
        cout<<"Creando archivo\n";
        fstream CreateFile("Datos_Grafo_K_2T.csv",ios::out);
        CreateFile<< " Source,Target,Label"<<endl;

        int mst_wt = 0; 
        sort(edges.begin(), edges.end()); 
        DisjointSets ds(V); 
        vector< pair<int, iPair> >::iterator it; 
        for (it=edges.begin(); it!=edges.end(); it++){ 
            int u = it->second.first; 
            int v = it->second.second; 
            int set_u = ds.find(u); 
            int set_v = ds.find(v);  
            if (set_u != set_v) {  
                CreateFile<< cities[u-1] << " ," << cities[v-1] <<  "  , "<< it->first <<endl; 
                //cities[i]
                cout << u << " - " << v <<  "      Peso: "<< it->first <<endl; 
                mst_wt += it->first; 
                ds.merge(set_u, set_v); 
            } 
        } 
    
        return mst_wt; 
    }
    My_File.open("Datos_Grafo_K_2T.csv",ios::app);
    My_File.close();
} 
  
int main(){ 
    int V = 25, E = 102; 
    Graph g(V, E); 
    int M[102][3];
    ifstream fe;

    fe.open("E:\\discretasss\\Archivo_Vertices_Aristas_2T.txt");
    int a,b,c;
    for (int i=0; i<102;i++){
        int p=0,s=0,t=0;
        for(int j=0; j<3;j++){
            a=M[i][j];
            fe >>a;//>>" ">>b>>" ">>c>>endl;
            //cout<< a<<" ";
            if (j==0){
                p=a;//primer parametro
            }   
            else if(j==1){
                s=a;//segundo parametro
            }  
            else if(j==2){
                t=a;//tercer parametro

            }
        }
        
        cout<<p<<" "<<s<<" "<<t;
        g.addEdge(p,s,t); 
        cout<<endl;
    }
    fe.close();

    //cout << "Edges of MST are \n"; 
    int mst_wt = g.kruskalMST();
    cout << "\nSuma de pesos: " << mst_wt; 
    return 0; 
}
