#include "ArregloConNombre.h"
#include <iostream>
#include <string>

/*
Con #include "ArregloConNombre.h" se agrega dicho fichero como una librería,
luego, acá se debe definir todo lo declarado en el .h
*/
using namespace std;

ArregloConNombre::ArregloConNombre(int num, string str) {
	numBase=num;
	nombre=str;
	for(int i=0; i<9; i++) arr[i]=numBase;
}

ArregloConNombre::~ArregloConNombre() {

}

int ArregloConNombre::getBase() {
	return numBase;
}

void ArregloConNombre::printBase() {
	cout<<"La base del arreglo es: "<< numBase << endl;
}

string ArregloConNombre::getNombre() {
	return nombre;
}

void ArregloConNombre::printNombre() {
	cout<<"El nombre de este arreglo es: "<< nombre <<endl;
}

void ArregloConNombre::printArreglo() {
	cout<<"El arreglo almacenado es: ";
	for(int i=0; i<9; i++) {
		cout<<arr[i]<<" ";
	}
	cout<<endl;
}

void ArregloConNombre::cambiaNum(int pos, int num) {
	arr[pos] = num;
}
