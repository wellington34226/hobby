#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>
#include <cstdlib>
#include <ctime>

#define RESET "\033[0m"
#define RED "\033[1;31m"
#define GREEN "\033[1;32m"
#define YELLOW "\033[1;33m"
#define BLUE "\033[1;34m"
#define MAGENTA "\033[1;35m"
#define CYAN "\033[1;36m"
#define WHITE "\033[1;37m"

bool create_matriz(int** &matriz,unsigned short int l, unsigned short int c);
void imprimir (std::ostream &os,int** &m);
int linhas=10,colunas=10;

int main(int argc, char *argv[]){
	srand(time(NULL));
	int **matriz = 0;
	switch(argc){
		case 3:
			colunas = atoi(argv[2]);
		case 2:
			linhas = atoi(argv[1]);
	}
	if(create_matriz(matriz,linhas,colunas)){
		imprimir(std::cout ,matriz);
	}
}

bool create_matriz(int** &matriz,unsigned short int l, unsigned short int c){
	if((l*c) > 0){
		matriz = new int*[l+1];
		int index =0;
		for(int i=0;i<l;i++){
			*(matriz+i) = new int[c+1];
			for(int j=0;j<c;j++){
				++index;
				*(*(matriz+i)+j)=rand() % 2;
			}
		}
		return true;
	}else{
		return false;
	}
};

void imprimir (std::ostream &os,int** &m){
	std::stringstream res;
	int size = linhas*colunas;
	int set = 1;
	/*while(size > 0){
		size/=10;
		++set;
	}*/
	for(int i=0;i<linhas;i++){
		res << std::right << "[" << std::setw(set) << (*(*(m+i))?BLUE:GREEN) << *(*(m+i)) << RESET;
		for(int j=1;j<colunas;j++){
			res << "|" << std::setw(set) << (*(*(m+i)+j)?BLUE:GREEN) << *(*(m+i)+j) << RESET;
		}
		res << "]\n";
	}
	os << res.str();
};
