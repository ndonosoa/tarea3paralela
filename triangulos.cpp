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
float CalcularDistancia(Punto pto1,Punto pto2){
	return sqrt((pto1.x-pto2.x)*(pto1.x-pto2.x) + (pto1.y-pto2.y)*(pto1.y-pto2.y));
}
float Sumar(Punto pto[]){
	FILE *infile;
		int i=0,posicion,x,y,z,var=0;
		float perimetro;

		infile = fopen("triangulos", "r");
		if(infile == NULL){

		}else{
			while(!feof(infile)){
				fscanf(infile, "%d %d %d\n", &x,&y,&z);
				//cout<<" "<<pto[x-1].pos<<" "<<pto[y-1].pos<<" "<<pto[z-1].pos<<endl;
				perimetro = perimetro + CalcularDistancia(pto[x-1],pto[y-1]) + CalcularDistancia(pto[x-1],pto[z-1]);
				perimetro += CalcularDistancia(pto[y-1],pto[z-1]);

			}
		}
		fclose(infile);
}



void MostrarPuntos(Punto pto[]){
	for(int i=0;i<5000;i++){
		cout<<pto[i].pos<<" "<<pto[i].x<<" "<<pto[i].y<<endl;
	}
}

int main(){
	for(int i =0;i<100;i++){
	Punto pto[5000];
	float perimetro;
	//Triangulo tri[5000];
	LlenarPuntos(pto);
	perimetro = Sumar(pto);
	//cout<<"La suma del perimetro total es: "<<perimetro<<endl;
	//MostrarPuntos(pto);
	}
	return 0;
}