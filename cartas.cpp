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

//shift 3
struct carta_t{
	//nipe_t nipe;
	//number_t number;
	uint8_t carta;
	struct carta_t *ante;
	struct carta_t *next;
	carta_t(uint8_t ni=0,uint8_t nu=0,struct carta_t *ca = NULL,struct carta_t *cn = NULL){
		carta = ((ni & 0x0F) << 4) | (nu & 0x0F);
		ante = ca;
		next = cn;
	};
};

struct baralho_t{
	carta_t **itens;
	baralho_t(uint32_t cartas=0){
		itens = new carta_t*[cartas+1];
		for(uint8_t ni=1,index=0;ni <= 4;ni++){
			for(uint8_t nu=1;nu<=13 && index < cartas;nu++,index++){
				*(itens+index)	= new carta_t(ni,nu,*(itens+((index-1) % cartas)),*(itens+((index+1) % cartas)));
			}
		}
		*(itens+cartas+1) = NULL;
	};
};

struct deck_t{
	baralho_t **itens;
	deck_t(uint32_t baralhos=0,uint32_t cartas=0){
		itens = new baralho_t*[baralhos+1];
		for(uint32_t i=0;i < baralhos;i++){
			*(itens+i) = new baralho_t(cartas);
		}
		*(itens+baralhos+1) = NULL;
	};
};

std::ostream& operator<< (std::ostream &os, const carta_t &c);
std::ostream& operator<< (std::ostream &os, const baralho_t &b);
std::ostream& operator<< (std::ostream &os, const deck_t &d);

bool embaralhar(deck_t &d);

int main(int argc, char *argv[]){
	srand(time(NULL));
	uint32_t baralhos=1,cartas=52,embaralhamentos=1;
	switch(argc){
		case 4:
			embaralhamentos = atoi(argv[3]);
		case 3:
			baralhos = atoi(argv[2]);
		case 2:
			cartas = atoi(argv[1]);
	}
	deck_t deck(baralhos,cartas);
	std::cout << "Sem embaralhar" << std::endl << deck; //imprimi deck antes de embralhar
	for(int i=0;i < embaralhamentos && embaralhar(deck);i++){
		std::cout << "Embaralhamento:" << i+1 << std::endl << deck;//imprime deck a cada embaralhada
	}
};

std::ostream& operator<< (std::ostream &os, const carta_t &c){
	std::stringstream number;
	switch(c.carta & 0x0F){
		case 1:
			number << "Ás";
			break;
		case 2:
			number << "Dois";
			break;
		case 3:
			number << "Três";
			break;
		case 4:
			number << "Quatro";
			break;
		case 5:
			number << "Cinco";
			break;
		case 6:
			number << "Seis";
			break;
		case 7:
			number << "Sete";
			break;
		case 8:
			number << "Oito";
			break;
		case 9:
			number << "Nove";
			break;
		case 10:
			number << "Dez";
			break;
		case 11:
			number << "Valete";
			break;
		case 12:
			number << "Dama";
			break;
		case 13:
			number << "Rei";
			break;
		default:
			number << "Coringa" << unsigned(c.carta);
			break;
	};
	std::stringstream res;
	if((c.carta & 0x0F) > 0){
		switch(c.carta >> 4){
			case 4:
				res << GREEN << number.str() << " de paus";
				break;
			case 3:
				res << YELLOW   << number.str() << " de ouros";
				break;
			case 2:
				res << RED   << number.str() << " de copas";
				break;
			case 1:
				res << BLUE << number.str() << " de espadas";
				break;
			default:
				res << WHITE << unsigned(c.carta);
				break;
		};	
	}else{
		res << WHITE << number.str();
	}
	
	os << res.str() << RESET;
	return os;
};
std::ostream& operator<< (std::ostream &os, const baralho_t &b){
	std::stringstream res;
	int index=0;
	res << std::left << "[";
	while(*(b.itens+index)!=NULL){
	  res << std::endl << std::setw(5) << "" << std::setw(5) << "" << *(*(b.itens+index));
		++index;
	}
	os << res.str() << std::endl << std::setw(5) << " " << "]";
	return os;
};
std::ostream& operator<< (std::ostream &os, const deck_t &d){
	std::stringstream res;
	res << "{";
	int index=0;
	while(*(d.itens+index)!=NULL){
		res << std::endl
		    << std::left
		    << std::setw(5)
		    << " "          << *(*(d.itens+index));
		++index;
	}
	os << res.str() << std::endl << "}" << std::endl;
	return os;
};
bool embaralhar(deck_t &d){
	int baralhos = 0,cartas = 0,rand1,rand2,rand3,rand4;

	carta_t *temp;
	while(*(d.itens+baralhos)!=NULL){
		while(*((*(d.itens+baralhos))->itens+cartas)!=NULL){
			++cartas;
		}
		++baralhos;
	}
	if(baralhos*cartas){
		for(int i=0;i < cartas/2;++i){
				if(baralhos == 1){
					rand1 = rand() % cartas;
					rand2 = rand() % cartas;
					temp = (*((*(d.itens))->itens+rand1));
					(*((*(d.itens))->itens+rand1)) = (*((*(d.itens))->itens+rand2));
					(*((*(d.itens))->itens+rand2)) = temp;
				}else{
					rand1 = rand() % baralhos;
					rand2 = rand() % cartas;
					rand3 = rand() % baralhos;
					rand4 = rand() % cartas;
					temp  = (*((*(d.itens+rand1))->itens+rand2));
					(*((*(d.itens+rand1))->itens+rand2)) = (*((*(d.itens+rand3))->itens+rand4));
					(*((*(d.itens+rand3))->itens+rand4)) = temp;
				}
		}
		return true;
	}else{
		return false;
	}
};
