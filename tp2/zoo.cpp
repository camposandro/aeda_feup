#include "zoo.h"

// ANIMAL
int Animal::maisJovem = 0;

Animal::Animal(string nome, int idade) {
	this->nome = nome;
	this->idade = idade;
	vet = NULL;
	atualizaMaisJovem(idade);
}

int Animal::getMaisJovem() {
	return maisJovem;
}

void Animal::atualizaMaisJovem(int idadeMaisJovem) {
	if (maisJovem == 0)
		maisJovem = idadeMaisJovem;
	else if (idadeMaisJovem < maisJovem) {
		maisJovem = idadeMaisJovem;
	}
}

string Animal::getNome() const {
	return nome;
}

int Animal::getIdade() const {
	return idade;
}

string Animal::getInformacao() const {
	stringstream info;
	info << nome << ", " << idade;

	return info.str();
}

void Animal::setVet(Veterinario *vet) {
	this->vet = vet;
}

Veterinario* Animal::getVet() {
	return vet;
}


// ZOO
void Zoo::adicionaAnimal(Animal *a1) {
	animais.push_back(a1);
	Animal::atualizaMaisJovem(a1->getIdade());
}

string Zoo::getInformacao() const {
	stringstream info;
	for (size_t i = 0; i < animais.size(); i++)
		info << animais.at(i)->getInformacao() + '\n';

	return info.str();
}

bool Zoo::animalJovem(string nomeA) {
	for (vector<Animal*>::iterator it = animais.begin(); it != animais.end(); it++)
		if ((*it)->getNome() == nomeA && (*it)->eJovem()) return true;
	return false;
}

void Zoo::alocaVeterinarios(istream &isV) {
	string _nome;
	long _codOrdem;
	while (getline(isV,_nome)) {
		isV >> _codOrdem;
		isV.ignore(1000,'\n');
		Veterinario *vet = new Veterinario(_nome, _codOrdem);
		veterinarios.push_back(vet);
	}

	size_t index_vet = 0;
	for (size_t index = 0; index != animais.size(); index++) {
		animais[index]->setVet(veterinarios[index_vet]);
		index_vet++;
		if (index_vet == veterinarios.size() - 1) index_vet = 0;
	}
}

bool Zoo::removeVeterinario(string nomeV) {
	vector<Veterinario *>::iterator it_vet;
	for (it_vet = veterinarios.begin(); it_vet != veterinarios.end(); it_vet++)
		if ((*it_vet)->getNome() == nomeV) break;

	if (it_vet == veterinarios.end()) return false;

	for (vector<Animal *>::iterator it_animal = animais.begin(); it_animal != animais.end(); it_animal++) {
		if ((*it_animal)->getVet() == (*it_vet)) {
			if ((it_vet + 1) == veterinarios.end())
				(*it_animal)->setVet(*(veterinarios.begin()));
			else (*it_animal)->setVet(*(it_vet + 1));
		}
	}

	veterinarios.erase(it_vet);
	return true;
}

bool Zoo::operator<(Zoo &z2) const {
	int soma_idades = 0, soma_idades2 = 0;

	for (size_t i = 0; i < animais.size(); i++)
		soma_idades += animais.at(i)->getIdade();
	for (size_t j = 0; j < z2.animais.size(); j++)
		soma_idades2 += z2.animais.at(j)->getIdade();

	return (soma_idades < soma_idades2);
}

// CAO
Cao::Cao(string nome, int idade, string raca) : Animal(nome,idade) {
	this->raca = raca;
}

string Cao::getInformacao() const {
	stringstream info;
	info << Animal::getInformacao();
	if (vet != NULL) info << ", " << vet->getInformacao();
	info << ", " << raca;

	return info.str();
}

bool Cao::eJovem() const {
	if (idade < 5) return true;
	return false;
}

// VOADOR
Voador::Voador(int vmax, int amax) {
	velocidade_max = vmax;
	altura_max = amax;
}

string Voador::getInformacao() const {
	stringstream info;
	info << velocidade_max << ", " << altura_max;
	return info.str();
}

// MORCEGO
Morcego::Morcego(string nome, int idade, int vmax, int amax) : Animal(nome,idade), Voador(vmax,amax) {}

bool Morcego::eJovem() const {
	if (idade < 4) return true;
	return false;
}

string Morcego::getInformacao() const {
	stringstream info;
	info << Animal::getInformacao() << ", " << Voador::getInformacao();
	if (vet != NULL) info << vet->getInformacao();
	return info.str();
}

// VETERINARIO
string Veterinario::getNome() const {
	return nome;
}

int Zoo::numAnimais() const {
	return animais.size();
}

Veterinario::Veterinario(string nome, long codOrdem) {
	this->nome = nome;
	this->codOrdem = codOrdem;
}

int Zoo::numVeterinarios() const {
	return veterinarios.size();
}

string Veterinario::getInformacao() const {
	stringstream info;
	info << nome << ", " << codOrdem;
	return info.str();
}
