#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include "../headers/functions.h"
#include "../headers/comparator.h"
#include "../headers/point.h"
#include "../headers/edge.h"

//Declarations

//Reads the specified input and returns two matrixes with the data and an array of points
//Complexity: O(n+n^2+n^2+n*m) => O(n(1+2n+m)) => O(n^2+nm)
void readInput(unsigned int& colonias, unsigned int** distancias, unsigned int** flujo, point* points){
	//Variables
	std::string coordenada;
	std::string aux;
	point P;
	int it = 0;

	//Initialize matrixes
	for(unsigned int i=0;i<colonias;i++){
		distancias[i] = new unsigned int[colonias];
		flujo[i] = new unsigned int[colonias];
	}
	//Get the vaules for colonias
	for(unsigned int i=0;i<colonias;i++){
		for(unsigned int j=0;j<colonias;j++){
			std::cin>>distancias[i][j];
		}
	}
	//Get the vaules for flow
	for(unsigned int i=0;i<colonias;i++){
		for(unsigned int j=0;j<colonias;j++){
			std::cin>>flujo[i][j];
		}
	}
	//Get coordinates
	for(unsigned int i=0;i<colonias;i++){
		std::cin>>coordenada;
		//Get the numbers
		for(unsigned int j=0;j<coordenada.length();j++){
			if(coordenada[j]>47 && coordenada[j]<58){
				aux+=coordenada[j];
			}else if(coordenada[j]==44){
				//Foud a ',' , add the number and clean aux
				P.x = std::stoul(aux);
				aux = "";
			}else if(coordenada[j]==41){
				//Found ')' meaning is the end fo the input and the delimiter of the y coordinate
				//Set P.y to aux, add it to the array of points, reset point and axis and set it++
				P.y = std::stoul(aux);
				points[it] = P;
				P.reset();
				aux = "";
				it++;
			}
		}
	}
}

//Prints the matrix based in the size
//Complexity: O(n^2)
void printMatrix(const unsigned int** M, const unsigned int& size){
	for(int i=0;i<size;i++){
		for(int j=0;j<size;j++){
			std::cout<<M[i][j]<<std::endl;
		}
	}
}

//Returns the root node of the Disjoint set data of nodes
//Complexity: O(n)
unsigned int Root(const unsigned int* V, const unsigned int& i){
	//Follos the parents tree until the node whose parent it´s it self
	if(V[i]==i)return i;
	return Root(V, V[i]);
}

//Makes the operation Union(A,B) in the Vertex array
//Complexity: O(2n) => O(n)
void Union(unsigned int* V, const edge& E){
	//Get the nodes of the edge
	unsigned int A = E.src;
	unsigned int B = E.dest;
	//Make B the parent of A
	V[Root(V, A)] = Root(V, B);
}

//Makes operaton Find(A,B)
//Finds if there is a cycle.
//If there is a cycle it returns true, else false.
//If both node´s root are the same means they are in the same subset therefore, there is a cycle.
//Complexity: O(2n)
bool Find(unsigned int* V, edge E){
	//Get the nodes of the edge
	unsigned int A = E.src;
	unsigned int B = E.dest;
	if(Root(V, A) == Root(V, B))return true;
	return false;
}

//Making the function class for the comparison in the heap
bool comparator::operator()(const edge& E, const edge& E2){
	return E.weight>E2.weight;
}

//Set edge overloaded
void edge::set(const unsigned int& src, const unsigned int& dest, const unsigned int& weight){
	this->src = src;
	this->dest = dest;
	this->weight = weight;
}

//Kruskal's algorithm for minimun spanning tree
//Main algorithm complexity: O(|E|(4|V|+log(|E|)))
//Complete function complexity: O(|V|+|E|log(|E|)+|E|(4|V|+log(|E|))+|V|) => O(2|V|+2|E|log(|E|)+4|E||V|) => O(2(|V|+|E|+|E|log(|E|)+2|E||V|)) => O(|V|+|E|+|E|log(|E|)+|E||V|) => O(|E|(|V|+1+log(|E|)+|V|)) => O(|E|(|V|+log(|E|)+|V|)) => O(|E|(|V|+log(|E|))) => O(|E||V|+|E|log(|E|))
void Kruskal(unsigned int** M, const unsigned int& size){
	//Variables
	edge aux;
	int pqsize;
	char E = 65;

	//Min heap for edges
	std::priority_queue<edge,std::vector<edge>,comparator> pq;

	//Array of vertex
	unsigned int* V = new unsigned int[size];
	for(unsigned int i=0;i<size;i++){
		V[i] = i;
	}

	//Read all the edges and add them to the minHeap
	for(unsigned int i=0;i<size;i++){
		for(unsigned int j=0;j<size;j++){
			//Check if edge exists between the i and j vertex
			if(M[i][j]!=0){
				aux.set(i, j, M[i][j]);
				pq.push(aux);
			}
		}
	}

	//Start building the three
	while(!pq.empty()){
		//Check if there are no cycles, create a Union of the sets
		if(!Find(V, pq.top()))Union(V, pq.top());
		pq.pop();
	}

	//Print the edges
	std::cout<<"::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::"<<std::endl;
	std::cout<<"Primera parte: "<<std::endl<<std::endl;
	for(int i=0;i<size;i++){
		std::cout<<"("<<char(E+i)<<","<<char(E+V[i])<<")"<<std::endl;
	}
	std::cout<<"::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::"<<std::endl;
}