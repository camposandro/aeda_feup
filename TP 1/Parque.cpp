#include "Parque.h"
#include <vector>

using namespace std;

ParqueEstacionamento::ParqueEstacionamento(unsigned int lot, unsigned int nMaxCli)
: lotacao(lot), numMaximoClientes(nMaxCli) {
	vagas = lot;
}

unsigned int ParqueEstacionamento::getNumLugares() const {
	return this->lotacao;
}

unsigned int ParqueEstacionamento::getNumMaximoClientes() const {
	return this->numMaximoClientes;
}

int ParqueEstacionamento::posicaoCliente(const string & nome) const {
	for (size_t i = 0; i < clientes.size(); i++) {
		if (clientes.at(i).nome == nome) {
			return i;
		}
	}
	return -1;
}

bool ParqueEstacionamento::adicionaCliente(const string & nome) {
	if (posicaoCliente(nome) == -1 && clientes.size() < numMaximoClientes) {
		InfoCartao novo_cliente;
		novo_cliente.nome = nome;
		novo_cliente.presente = false;
		clientes.push_back(novo_cliente);
		return true;
	}
	return false;
}

bool ParqueEstacionamento::entrar(const string & nome) {
	int posicao_cliente = posicaoCliente(nome);
	if (posicao_cliente != -1) {
		InfoCartao cliente = clientes.at(posicao_cliente);
		if (!cliente.presente && vagas > 0) {
			clientes.at(posicao_cliente).presente = true;
			vagas--;
			return true;
		}
		return false;
	}
	return false;
}

bool ParqueEstacionamento::retiraCliente(const string & nome) {
	int posicao_cliente = posicaoCliente(nome);
	if (posicao_cliente != -1) {
		InfoCartao cliente = clientes.at(posicao_cliente);
		if (!cliente.presente) {
			clientes.erase(clientes.begin() + posicao_cliente);
			return true;
		}
		return false;
	}
	return false;
}

bool ParqueEstacionamento::sair(const string & nome) {
	int posicao_cliente = posicaoCliente(nome);
	if (posicao_cliente != -1) {
		InfoCartao cliente = clientes.at(posicao_cliente);
		if (cliente.presente) {
			clientes.at(posicao_cliente).presente = false;
			return true;
		}
		return false;
	}
	return false;
}

unsigned int ParqueEstacionamento::getNumLugaresOcupados() const {
	return lotacao - vagas;
}

unsigned int ParqueEstacionamento::getNumClientesAtuais() const {
	return clientes.size();
}

const ParqueEstacionamento & ParqueEstacionamento::operator += (const
 ParqueEstacionamento & p2) {
	unsigned int maxClientsAdd = numMaximoClientes - this->getNumClientesAtuais();
	if (maxClientsAdd > p2.getNumClientesAtuais())
		maxClientsAdd = p2.getNumClientesAtuais();
	for (size_t i = 0; i < maxClientsAdd; i++) {
		string clienteP2 = p2.clientes.at(i).nome;
		if (posicaoCliente(clienteP2) == -1) {
			this->adicionaCliente(clienteP2);
		}
	}
	return *this;
}
