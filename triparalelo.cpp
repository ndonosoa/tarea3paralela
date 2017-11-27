#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>
#include <cmath>
#include "mpi.h"

using namespace std;



void Sumar(){
	MPI_Status status;
  //size = numero de procesadores, desde el 0.
  //rank = procesador en uso
  int rank, size;
  MPI::Init();
  rank = MPI::COMM_WORLD.Get_rank(); 
  size = MPI::COMM_WORLD.Get_size();
  float arreglo[2],arreglo2[2], arreglo3[2],rec[2],rec2[2],rec3[2];
	int receptor[1];
  if(rank==0){
  	FILE *infile;
		int i=0,posicion,x[1],y[1],z[1],var=0;
		float perimetro;

		infile = fopen("triangulos", "r");
		if(infile == NULL){

		}else{
			while(!feof(infile)){
				fscanf(infile, "%d %d %d\n", &x[0],&y[0],&z[0]);
				//cout<<x[0]<<endl;
				//cout<<" "<<pto[x-1].pos<<" "<<pto[y-1].pos<<" "<<pto[z-1].pos<<endl;
				MPI_Send(x, 1, MPI_INT,1,0, MPI_COMM_WORLD);
				MPI_Send(y, 1, MPI_INT,2,0, MPI_COMM_WORLD);
				MPI_Send(z, 1, MPI_INT,3,0, MPI_COMM_WORLD);

				MPI_Recv(rec, 2, MPI_INT, 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
				MPI_Recv(rec2, 2, MPI_INT, 2, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
				MPI_Recv(rec3, 2, MPI_INT, 3, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
				perimetro = sqrt((rec[0]-rec2[0])*(rec[0]-rec2[0]) + (rec[1]-rec2[1])*(rec[1]-rec2[1]));
				perimetro += sqrt((rec[0]-rec3[0])*(rec[0]-rec3[0]) + (rec[1]-rec3[1])*(rec[1]-rec3[1]));
				perimetro += sqrt((rec2[0]-rec3[0])*(rec2[0]-rec3[0]) + (rec2[1]-rec3[1])*(rec2[1]-rec3[1]));
				if(rank==1){
  	MPI_Recv(receptor, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
  	int num;
  	float coordx, coordy;
  	 FILE *infile;
  	 infile = fopen("puntos", "r");
  	 while(!feof(infile)){
  	 	fscanf(infile, "%d %f %f", &num,&coordx,&coordy);
  	 	if(num == receptor[0]){
  	 		arreglo[0] = coordx;
  	 		arreglo[1] = coordy;
			MPI_Send(arreglo, 2, MPI_INT,0,0, MPI_COMM_WORLD);
  	 	}
  	 }
  }
  if(rank==2){
  	MPI_Recv(receptor, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
  	int num;
  	float coordx, coordy;

  	 FILE *infile;
  	 infile = fopen("puntos", "r");
  	 while(!feof(infile)){
  	 	fscanf(infile, "%d %f %f", &num,&coordx,&coordy);
  	 	if(num == receptor[0]){
  	 		arreglo2[0] = coordx;
  	 		arreglo2[1] = coordy;
			MPI_Send(arreglo2, 2, MPI_INT,0,0, MPI_COMM_WORLD);
  	 	}
  	 }
  }
  if(rank==3){
  	MPI_Recv(receptor, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
  	int num;
  	float coordx, coordy;

  	 FILE *infile;
  	 infile = fopen("puntos", "r");
  	 while(!feof(infile)){
  	 	fscanf(infile, "%d %f %f", &num,&coordx,&coordy);
  	 	if(num == receptor[0]){
  	 		arreglo3[0] = coordx;
  	 		arreglo3[1] = coordy;
			MPI_Send(arreglo3, 2, MPI_INT,0,0, MPI_COMM_WORLD);
  	 	}
  	 }
  }				

			}
			cout<<"El perimetro es: "<<perimetro<<endl;
		}
		fclose(infile);
  }
  
	 MPI_Finalize();
}





int main(){

	Sumar();
	//cout<<"La suma del perimetro total es: "<<perimetro<<endl;

	return 0;
}