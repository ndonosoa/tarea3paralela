#include <iostream>
#include <fstream>
#include <string.h>
#include <stdlib.h>
#include <cmath>
#include "mpi.h"

using namespace std;

#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>
#include <cmath>

using namespace std;

struct Punto{
  int pos;
  float x;
  float y;
};


void LlenarPuntos(Punto pto[]){
  FILE *infile;
    float coorx,coory;
    int i,posicion;

    infile = fopen("puntos", "r");
    if(infile == NULL){

    }else{
      while(!feof(infile)){
        fscanf(infile, "%d %f %f\n", &posicion,&coorx,&coory);
        //cout<<" "<<coorx<<" "<<coory<<" "<<posicion<<endl;
        pto[i].pos = posicion;
        pto[i].x = coorx;
        pto[i].y = coory;
        i++;
      }
    }
    fclose(infile);
}

float Dist(Punto pto[],int a,int b){
   return sqrt((pto[a].x-pto[b].x)*(pto[a].x-pto[b].x) + (pto[a].y-pto[b].y)*(pto[a].y-pto[b].y));
}

float CalcularDistancias(Punto pto[],int x,int y,int z){
	float sum =0;

	sum += Dist(pto,x-1,y-1);
	sum += Dist(pto,x-1,z-1);
	sum += Dist(pto,z-1,y-1);
	return sum;
}



void MostrarPuntos(Punto pto[]){
  for(int i=0;i<5000;i++){
    cout<<pto[i].pos<<" "<<pto[i].x<<" "<<pto[i].y<<endl;
  }
}

int main(){
  MPI_Status status;
  //size = numero de procesadores, desde el 0.
  //rank = procesador en uso
  int rank, size;

  MPI::Init();
  rank = MPI::COMM_WORLD.Get_rank(); //Se le asigna el procesador que se está usando
  size = MPI::COMM_WORLD.Get_size();
  int rango[2];
  Punto pto[5000];
  float perimetro[1],aux=0;

  LlenarPuntos(pto);
  if(rank==0){
	rango[0] = 0;
	rango[1] = 3221;
	MPI_Send(rango, 2, MPI_INT,1,0, MPI_COMM_WORLD);
	rango[0] = 3222;
	rango[1] = 6444;
	MPI_Send(rango, 2, MPI_INT,2,0, MPI_COMM_WORLD);
	rango[0] = 6445;
	rango[1] = 9665;
	MPI_Send(rango, 2, MPI_INT,3,0, MPI_COMM_WORLD);

	MPI_Recv(perimetro, 1, MPI_FLOAT, 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
	aux = aux + perimetro[0];
	MPI_Recv(perimetro, 1, MPI_FLOAT, 2, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
	aux = aux + perimetro[0];

	MPI_Recv(perimetro, 1, MPI_FLOAT, 3, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
	aux = aux + perimetro[0];

	cout<<"El perimetro final es: "<<aux<<endl;

  }
  if(rank==1){
  	MPI_Recv(rango, 2, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
  	FILE *infile;
  	int x,y,z,cont=0;
  	infile = fopen("triangulos", "r");
  	//cout<<"el rango inf y superior son: "<<rango[0]<<" "<<rango[1]<<endl;
  	while(!feof(infile)){
  		fscanf(infile,"%d %d %d\n", &x,&y,&z);
  		if(cont>=rango[0] && cont<=rango[1]){
  		perimetro[0] += CalcularDistancias(pto,x,y,z);
  		}
  		cont++;

  	}
  	MPI_Send(perimetro, 1, MPI_FLOAT,0,0, MPI_COMM_WORLD);
  	//cout<<"Hola este es el perimetro: "<<perimetro<<endl;
  }
  if(rank==2){
  	MPI_Recv(rango, 2, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
  	FILE *infile;
  	int x,y,z,cont=0;
  	infile = fopen("triangulos", "r");
  //	cout<<"el rango inf y superior son: "<<rango[0]<<" "<<rango[1]<<endl;

  	while(!feof(infile)){
  		fscanf(infile,"%d %d %d\n", &x,&y,&z);
  		if(cont>=rango[0] && cont<=rango[1]){
  		perimetro[0] += CalcularDistancias(pto,x,y,z);
  		}
  		cont++;

  	}
  	MPI_Send(perimetro, 1, MPI_FLOAT,0,0, MPI_COMM_WORLD);
  //	cout<<"Hola este es el perimetro: "<<perimetro<<endl;

  }
  if(rank==3){
  	MPI_Recv(rango, 2, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
  	FILE *infile;
  	int x,y,z,cont=0;
  	infile = fopen("triangulos", "r");
  //	cout<<"el rango inf y superior son: "<<rango[0]<<" "<<rango[1]<<endl;

  	while(!feof(infile)){
  		fscanf(infile,"%d %d %d\n", &x,&y,&z);
  		if(cont>=rango[0] && cont<=rango[1]){
  		perimetro[0] += CalcularDistancias(pto,x,y,z);
  		}
  		cont++;
  	}
  	MPI_Send(perimetro, 1, MPI_FLOAT,0,0, MPI_COMM_WORLD);
  //	cout<<"Hola este es el perimetro: "<<perimetro<<endl;

  }
  MPI_Finalize();
  
  //cout<<"La suma del perimetro total es: "<<perimetro<<endl;
  //MostrarPuntos(pto);
  return 0;
}
