#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>
#include <cmath>

using namespace std;








int main(){

	FILE *infile;
  infile = fopen("triangulos","r");
  int x,cont=0;
  while(!feof(infile)){
    fscanf(infile,"%d %d %d\n",&x,&x,&x);
    cont++;
  }
  cout<<cont;
	//cout<<"La suma del perimetro total es: "<<perimetro<<endl;

	return 0;
}