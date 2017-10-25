#include "parque.h"
#include "insertionSort.h"
#include "sequentialSearch.h"
#include <vector>
#include <algorithm>

using namespace std;

ParqueEstacionamento::ParqueEstacionamento(unsigned int lot, unsigned int nMaxCli):
	lotacao(lot), numMaximoClientes(nMaxCli) {
    numClientes = 0;
    vagas=lot; 
}

ParqueEstacionamento::~ParqueEstacionamento() {}

vector<InfoCartao> ParqueEstacionamento::getClientes() const { return clientes; }


bool ParqueEstacionamento::adicionaCliente(const string & nome)
{
 	if ( numClientes == numMaximoClientes ) return false;
	if ( posicaoCliente(nome) != -1 ) return false;
	InfoCartao info;
	info.nome = nome;
    info.presente = false;
    info.frequencia = 0;
	clientes.push_back(info);
	numClientes++;
	return true;
}
 
bool ParqueEstacionamento::retiraCliente(const string & nome)
{
	for (vector<InfoCartao>::iterator it = clientes.begin(); it != clientes.end(); it++)
		if ( it->nome == nome ) {
			if ( it->presente == false ) {
				clientes.erase(it);
				numClientes--;
				return true;
			}
			else return false;
		}
	return false;
}
  
unsigned int ParqueEstacionamento::getNumLugares() const
{
	return lotacao;
}
                   
unsigned int ParqueEstacionamento::getNumLugaresOcupados() const
{
	return lotacao-vagas;
}

bool ParqueEstacionamento::entrar(const string & nome)
{
	if ( vagas == 0 ) return false;
	int pos = posicaoCliente(nome);
	if ( pos == -1 ) return false;
	if ( clientes[pos].presente == true ) return false;
	clientes[pos].presente = true;
	clientes[pos].frequencia++;
	vagas--;
	return true;
}

bool ParqueEstacionamento::sair(const string & nome)
{
	int pos = posicaoCliente(nome);
	if ( pos == -1 ) return false;
	if ( clientes[pos].presente == false ) return false;
	clientes[pos].presente = false;
	vagas++;
	return true;
}

/* 1.a) */
int ParqueEstacionamento::posicaoCliente(const string & nome) const {
	/* cria cliente com nome do param */
	InfoCartao cliente_nome;
	cliente_nome.nome = nome;

	int indiceCliente = sequentialSearch(clientes, cliente_nome);
	return indiceCliente;
}

/* 1.b) */
int ParqueEstacionamento::getFrequencia(const string &nome) const {
	int pos = posicaoCliente(nome);
	if (pos == -1) throw ClienteNaoExistente(nome);
	return clientes[pos].frequencia;
}

/* 1.c) */
void ParqueEstacionamento::ordenaClientesPorFrequencia() {
	insertionSort(clientes);
}

/* 1.d) */
vector<string> ParqueEstacionamento::clientesGamaUso(int n1, int n2) {
	vector<InfoCartao> clientes_retorno;
	for (size_t i = 0; i < clientes.size(); i++)
		if (clientes[i].frequencia >= n1 && clientes[i].frequencia <= n2)
			clientes_retorno.push_back(clientes[i]);

	// ordena por freq e nome
	insertionSort(clientes_retorno);

	// retorna vetor de nomes apenas
	vector<string> clientes_string;
	for (size_t j = 0; j < clientes_retorno.size(); j++)
		clientes_string.push_back(clientes_retorno[j].nome);

	return clientes_string;
}

/* 1.e) */
bool ordenaNome(const InfoCartao &ic1, const InfoCartao &ic2) {
	return ic1.nome < ic2.nome;
}

void ParqueEstacionamento::ordenaClientesPorNome() {
	sort(clientes.begin(), clientes.end(), ordenaNome);
}

/* 1.f) */
InfoCartao ParqueEstacionamento::getClienteAtPos(vector<InfoCartao>::size_type p) const {
	if (p >= clientes.size()) throw PosicaoNaoExistente(p);
	else return clientes[p];
}

ostream & operator<<(ostream & os, const ParqueEstacionamento & pe) {
	vector<InfoCartao> clientes = pe.getClientes();
	vector<InfoCartao>::const_iterator it_clientes;
	for (it_clientes = clientes.begin(); it_clientes != clientes.end(); it_clientes++) {
		os << "Nome: " << (*it_clientes).nome << endl
		<< "Presente: " << (*it_clientes).presente << endl
		<< "Frequencia: " << (*it_clientes).frequencia << endl;
		if (it_clientes != clientes.end() - 1) os << endl;
	}
	return os;
}

/* 2.a)
 * Algoritmo de complexidade temporal O(n^2) uma vez que possuímos 2 ciclos for
 * cujo tempo de execução depende única e exclusivamente do tamanho dos vetores
 * linha e coluna da matriz. Atenção que o ciclo for para imprimir os tabs tem
 * complexidade constante O(1), uma vez que não depende do número de linhas ou colunas.
 */

/* 2b)
 * Algoritmo de pesquisa binária, por isso tem complexidade temporal que no pior dos casos
 * é igual a O(log(n)), caso em que o valor a pesquisar não se encontra no vetor. No melhor
 * dos casos temos apenas uma iteração em que o elemento a encontrar se encontra a meio do array,
 * caso em que a complexidade temporal é de O(1).
 * Em termos de complexidade espacial, temos O(1) no pior dos casos.
 */

