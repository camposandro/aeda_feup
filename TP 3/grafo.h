#include <iostream>
#include <vector>

using namespace std;

/**
 * Versão da classe generica Grafo usando a classe vector
 */

template <class N, class A> class Aresta;

template <class N, class A>
class No {
public:
	N info;
	vector< Aresta<N,A> > arestas;
	No(N inf) {
		info = inf;
	}
};

template <class N, class A>
class Aresta {
public:
	A valor;
	No<N,A> *destino;
	Aresta(No<N,A> *dest, A val) {
		valor = val;
		destino = dest;
	}
};

// excecao  NoRepetido
template <class N>
class NoRepetido
{
public:
   N info;
   NoRepetido(N inf) { info=inf; }
};
template <class N>
std::ostream & operator<<(std::ostream &out, const NoRepetido<N> &no)
{ out << "No repetido: " << no.info; return out; }


// excecao NoInexistente
template <class N>
class NoInexistente {
public:
	N info;
	NoInexistente(N inf) {
		info = inf;
	}
};
template <class N>
std::ostream & operator<<(std::ostream &out, const NoInexistente<N> &ni)
{ out << "No inexistente: " << ni.info; return out; }

// excecao ArestaRepetida
template <class N>
class ArestaRepetida {
public:
	N info_aresta;
	ArestaRepetida(N info_aresta) : info_aresta(info_aresta) {}
};
template <class N>
std::ostream & operator<<(std::ostream &out, const ArestaRepetida<N> &ar)
{ out << "Aresta repetida: " << ar.info_aresta ; return out; }

// excecao ArestaInexistente
template <class N>
class ArestaInexistente {
public:
	N info_aresta;
	ArestaInexistente(N info_aresta) : info_aresta(info_aresta) {}
};
template <class N>
std::ostream & operator<<(std::ostream &out, const ArestaInexistente<N> &ai)
{ out << "Aresta inexistente: " << ai.info_aresta; return out; }

template <class N, class A> 
class Grafo { 
	vector< No<N,A> *> nos;
  public: 
    Grafo() {}
    ~Grafo() {}
    Grafo & inserirNo(const N &dados) {
    	typename vector< No<N,A> *>::const_iterator const_it;
    	for (const_it = nos.begin(); const_it != nos.end(); const_it++) {
    		if ((*const_it)->info == dados)
    			throw NoRepetido<N>(dados);
    	}
    	No<N,A>* novo_no = new No<N,A>(dados);
    	nos.push_back(novo_no);
    	return *this;
    }
    Grafo & inserirAresta(const N &inicio, const N &fim, const A &val) {
    	for (typename vector<No<N, A> *>::const_iterator it_nos = nos.begin(); it_nos != nos.end(); it_nos++) {
    		if ((*it_nos)->info == inicio) {
    			for (typename vector<Aresta<N, A> >::const_iterator it_arestas = (*it_nos)->arestas.begin();
    					it_arestas != (*it_nos)->arestas.end(); it_arestas++) {
    				if (it_arestas->destino->info == fim) {
    					throw ArestaRepetida<N>(inicio + " , " + fim);
    				}
    			}
    			Aresta<N,A>* nova_aresta = new Aresta<N,A>(new No<N,A>(fim), val);
    			(*it_nos)->arestas.push_back(*nova_aresta);
    			return *this;
    		}
    	}
    	throw NoInexistente<N>(inicio);
    }
    Grafo & eliminarAresta(const N &inicio, const N &fim) {
    	for (typename vector<No<N, A> *>::const_iterator it_nos = nos.begin(); it_nos != nos.end(); it_nos++) {
    		if ((*it_nos)->info == inicio) {
    	    	for (typename vector<Aresta<N, A> >::const_iterator it_arestas = (*it_nos)->arestas.begin();
    	    			it_arestas != (*it_nos)->arestas.end(); it_arestas++) {
    	    		if (it_arestas->destino->info == fim) {
    	    			(*it_nos)->arestas.erase(it_arestas);
    	    			return *this;
    	    		}
    	    	}
    	    	throw ArestaInexistente<N>(inicio + " , " + fim);
    		}
    	}
    	throw NoInexistente<N>(inicio);
    }
    A & valorAresta(const N &inicio, const N &fim) {
    	for (typename vector<No<N, A> *>::const_iterator it_nos = nos.begin(); it_nos != nos.end(); it_nos++) {
    		if ((*it_nos)->info == inicio) {
    			for (typename vector<Aresta<N, A> >::iterator it_arestas = (*it_nos)->arestas.begin();
    			    	it_arestas != (*it_nos)->arestas.end(); it_arestas++) {
    				if (it_arestas->destino->info == fim) {
    					return it_arestas->valor;
    				}
    			}
    			throw ArestaInexistente<N>(inicio + " , " + fim);
    		}
    	}
    	throw NoInexistente<N>(inicio);
    }
    int numArestas(void) const {
    	int numArestas = 0;
    	for	(int i = 0; i < numNos(); i++)
    		numArestas += (nos[i]->arestas).size();
    	return numArestas;
    }
    int numNos(void) const {
    	return nos.size();
    }
    void imprimir(std::ostream &os) const {
    	for (typename vector<No<N, A> *>::const_iterator it_nos = nos.begin(); it_nos != nos.end(); it_nos++) {
    		os << "( " << (*it_nos)->info;
    		for (typename vector<Aresta<N, A> >::iterator it_arestas = (*it_nos)->arestas.begin();
    			   it_arestas != (*it_nos)->arestas.end(); it_arestas++) {
    		   os << "[ " << it_arestas->destino->info << " " << it_arestas->valor << "] ";
    		}
    		os << ") ";
    	}
    }
};

template <class N, class A> 
std::ostream & operator<<(std::ostream &out, const Grafo<N,A> &g) {
	g.imprimir(out);
	return out;
}
