/* ********************************************************************************************** */
/* ************************************* Project 3 ************************************* */
/* ************************************* Tristan Schieler ************************************* */
/* ********************************************************************************************** */
#include <map>
#include <vector>
#include <iostream>
#include <queue>
#include <fstream>

using namespace std;

/* ********************************************************************************************** */
/* ************************************* Vertices for Graph ************************************* */
/* ********************************************************************************************** */
struct Node {
    vector<int> vertex;
    vector<Node*> neighbors; 
    bool visited;
};



/* ********************************************************************************************** */
/* ************************************* Creating Vertices ************************************* */
/* ********************************************************************************************** */
map<vector<int>, Node*> CreateVertices(vector<int> Buckets, int max){
    map<vector<int>, Node*> Graph;
    
    vector<int> temp(Buckets.size(), 0);
    int poss = Buckets.size()-1;
    int sum = 0;
    
    Node* vertex = new Node;//{temp, {}, false};
    vertex->vertex = temp;
    vertex->visited = false;
    Graph[temp] = vertex;

    while(sum != max){
        sum = 0;
        while(temp[poss] == Buckets[poss] && poss !=0){
            temp[poss] = 0;
            poss--;
        }
        temp[poss]++;
        poss = temp.size()-1;
        Node* vertex = new Node;//{temp, {}, false};
        vertex->vertex = temp;
        vertex->visited = false;
        Graph[temp] = vertex;
        for(int i = 0 ; i < temp.size() ; i++)
            sum += temp[i];
    }
    return Graph;
}



/* ********************************************************************************************** */
/* ************************************* Linking Graph ************************************* */
/* ********************************************************************************************** */
map<vector<int>, Node*> CreateGraph(map<vector<int>, Node*> Graph, vector<int> Buckets){
    map<vector<int>, Node*>::iterator i;

    //for every vertex in graph
    for(i = Graph.begin() ; i != Graph.end() ; i++){

        //dump out buckets 
        for(int j = 0 ; j < i->first.size() ; j++){
            vector<int> temp(i->first);
            temp[j] = 0;
            Node* vertex = Graph[temp];
            i->second->neighbors.push_back(vertex);
        }

        //fill up buckets
        for(int j = 0 ; j < i->first.size() ; j++){
            vector<int> temp(i->first);
            temp[j] = Buckets[j];
            Node* vertex = Graph[temp];
            i->second->neighbors.push_back(vertex);
        }

        //pour one bucket into all ohters
        for(int j = 0 ; j < i->first.size() ; j++){
                for(int k = 0 ; k < i->first.size() ; k++){
                    vector<int> copy(i->first);                    
                    
                    if(copy[j] == 0){
                        continue;
                    }
                    
                    if(j == k){
                        continue;
                    }
                    
                    if(copy[k] == Buckets[k]){
                        continue;
                    }

                    int max = Buckets[k];
                    int poss = max - copy[k];
                    int newV = copy[j] - poss;
                    if(newV <= 0){
                        copy[k] += copy[j];
                        copy[j] = 0;
                    }
                    else{
                        copy[k] += poss;
                        copy[j] -= poss;
                    }
                    
                Node* vertex = Graph[copy];
                i->second->neighbors.push_back(vertex);
            }
        }
    }
    return Graph;
}



/* ********************************************************************************************** */
/* ********************************************* BFS ******************************************** */
/* ********************************************************************************************** */
vector<int> Travel(map<vector<int>, Node*> Graph, vector<int> output){
    int length = 0;
    int temp;
    int prev;
    pair<vector<int>, int> make;
    
    map<int, bool> found;
    found[0] = true;

    map<int , int> depth;
    depth[0] = 0;

    queue<pair<vector<int>, int> > que;
    make.first = Graph.begin()->first;
    make.second = 0;
    que.push(make);
    Graph.begin()->second->visited = true;
    pair<vector<int>, int> lastt;
    
    while(!que.empty()){
        prev = 0;
        lastt = que.front();
        vector<int> vertex = lastt.first;
        for(int i = 0 ; i < vertex.size() ; i++){
            prev += vertex[i]; 
        }
        que.pop();
        Node* current = Graph[vertex];
        for(int i = 0 ; i < current->neighbors.size() ; i++){
            Node* cnode = current->neighbors[i];
            if(cnode->visited == false){
                temp = 0;
                make.first = cnode->vertex;
                make.second = lastt.second + 1;    
                que.push(make);
                cnode->visited = true;
                for(int j = 0 ; j < cnode->vertex.size() ; j++){
                    temp += cnode->vertex[j];
                }
                if(!found[temp]){
                    found[temp] = true;
                    depth[temp] = make.second;
                }
            }
        }
    }
    
    int currw = 0;
    int currd = 0;
    map<int, int>::iterator i;
    for(i = depth.begin() ; i != depth.end() ; i++){
        if(i->second > currd){
            currd = i->second;
            currw = i->first;
        }
    }
    
    output.push_back(currw);
    output.push_back(currd);
    return output;
}



/* ********************************************************************************************** */
/* ************************************* # of Vertices and edges ************************************* */
/* ********************************************************************************************** */
vector<int> GetNumVandE(map<vector<int>, Node*> Graph, vector<int> output){
    int Vcount = 0;
    int Ecount = 0;
    map<vector<int>, Node*>::iterator i;
    for(i = Graph.begin() ; i != Graph.end() ; i++){
        Vcount++;
        for(int k = 0 ; k < i->second->neighbors.size() ; k++){
            Node* cnode = i->second->neighbors[k];
            if(cnode->vertex == i->first){
                continue;
            }
            Ecount++;
        }
    }
    output.push_back(Vcount);
    output.push_back(Ecount);
    return output;
}



/* ********************************************************************************************** */
/* ********************************************* input ******************************************** */
/* ********************************************************************************************** */
vector<int> Read(){
    int inputsize;
    int temp;
    vector<int> buckets;
    ifstream infs;
    infs.open("input.txt");
    //outfs.open("output.txt", std::ofstream::trunc);
    if(!infs.is_open()){
        cout << "Error opening file" << endl;
    }
    infs >> inputsize;
    for(int i = 0 ; i < inputsize ; i++){
        infs >> temp;
        buckets.push_back(temp);
    }
    infs.close();
    return buckets;
}



/* ********************************************************************************************** */
/* ******************************************* output ******************************************** */
/* ********************************************************************************************** */
void Write(vector<int> output){
    ofstream outfs;
    outfs.open("output.txt", std::ofstream::trunc);
    if(!outfs.is_open()){
        cout << "Error Opening File" << endl;
    }
    outfs << output[0] << " " << output[1] << " " << output[2] << " " << output[3];    
    outfs.close();
}



/* ********************************************************************************************** */
/* ********************************************* print ******************************************** */
/* ********************************************************************************************** */
// void print(map<vector<int>, Node*> Graph){
//     map<vector<int>, Node*>::iterator i;
//     for(i = Graph.begin() ; i != Graph.end() ; i++){
//         for(int j : i->first){
//             cout << j;
//         }
//         cout << ": ";
//         for(Node* k : i->second->neighbors){
//             for(int j : k->vertex){
//                 cout << j;
//             }
//             cout << " ";
//         }
//         cout << "\n";
//     }
// }


/* ********************************************************************************************** */
/* ********************************************* main ******************************************** */
/* ********************************************************************************************** */
int main(){
    vector<int> Buckets = Read();
    
    vector<int> output;
    int MaxWater = 0;
    for(int i = 0 ; i < Buckets.size() ; i++){
        MaxWater += Buckets[i];   
    }

    map<vector<int>, Node*> Graph = CreateVertices(Buckets, MaxWater);

    Graph = CreateGraph(Graph, Buckets);

    //print(Graph);
    
    output = GetNumVandE(Graph, output);
    output = Travel(Graph, output);

    Write(output);

    return 0;
}