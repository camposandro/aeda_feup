/*
 * Escritorio.h
 *
 *  Created on: Oct 4, 2015
 *      Author: arocha
 */

#ifndef ESCRITORIO_H_
#define ESCRITORIO_H_

#include <iostream>
#include <vector>
#include <string>
using namespace std;


class Documento {
  int numPaginas;
  float pPreto, pAmarelo;
public:
   Documento(int nPag, float pP, float pA);
   ~Documento();
   int getNumPaginas() const;
   float getPercentagemPreto() const;
   float getPercentagemAmarelo() const;
   Documento operator+(const Documento &d2) {
	   float percPreto, percAmarelo;
	   percPreto = (pPreto * numPaginas + d2.pPreto * d2.numPaginas) / (numPaginas + d2.numPaginas),
	   percAmarelo = (pAmarelo * numPaginas + d2.pAmarelo * d2.numPaginas) / (numPaginas + d2.numPaginas);
	   return Documento(numPaginas + d2.numPaginas, percPreto, percAmarelo);
   }
};

class Impressora {
protected:
  const string codigo;
  const int ano;
  vector<Documento> docsImpressos;
public:
	Impressora(string cod, int a);
	virtual ~Impressora();
	string getCodigo() const;
	int getAno() const;
	vector<Documento> getDocumentosImpressos() const;
	virtual bool imprime(Documento doc1) = 0;
	virtual int getNumPaginasImprimir() const = 0;
};

class ImpressoraPB: public Impressora {
  int numPagImprimir;
public:
   ImpressoraPB(string cod, int a, int toner);
   int getNumPaginasImprimir() const;
   bool imprime(Documento doc1) {
	   if (doc1.getNumPaginas() <= numPagImprimir) {
		   numPagImprimir -= doc1.getNumPaginas();
		   docsImpressos.push_back(doc1);
		   return true;
	   }
	   return false;
   }
};

class ImpressoraCores: public Impressora {
  float numPagImprimirPreto;
  float numPagImprimirAmarelo;
public:
   ImpressoraCores(string cod, int a, int toner);
   int getNumPaginasImprimir() const;
   bool imprime(Documento doc1) {
	   int numPagAmarelo = doc1.getPercentagemAmarelo() * doc1.getNumPaginas();
	   int numPagPreto = doc1.getPercentagemPreto() * doc1.getNumPaginas();
	   if (numPagAmarelo <= numPagImprimirAmarelo && numPagPreto <= numPagImprimirPreto) {
		   numPagImprimirPreto -= numPagPreto;
		   numPagImprimirAmarelo -= numPagAmarelo;
		   docsImpressos.push_back(doc1);
		   return true;
	   }
	   return false;
   }
};

class Funcionario {
  string codigo;
  vector<Impressora *> impressoras;
public:
  Funcionario(string cod);
  ~Funcionario();
  string getCodigo() const;
  void adicionaImpressora(Impressora *i1);
  vector<Impressora *> getImpressoras() const;
};

class Escritorio {
  vector<Impressora *> impressoras;
  vector<Funcionario> funcionarios;
public:
  Escritorio();
  ~Escritorio();
  void adicionaImpressora(Impressora *i1);
  void adicionaFuncionario(Funcionario f1);
  vector<Impressora *> getImpressoras() const;
  int numImpressorasSemResponsavel() const {
	  int counter = impressoras.size();
	  vector<Impressora *>::const_iterator it_impr;
	  for (it_impr = impressoras.begin(); it_impr != impressoras.end(); it_impr++) {
		  vector<Funcionario>::const_iterator it_func;
		  for (it_func = funcionarios.begin(); it_func != funcionarios.end(); it_func++) {
			  vector<Impressora *> impr_func = it_func->getImpressoras();
			  vector<Impressora *>::const_iterator it_impr2;
			  for (it_impr2 = impr_func.begin(); it_impr2 != impr_func.end(); it_impr2++) {
				  if ((*it_impr2)->getCodigo() == (*it_impr)->getCodigo()) {
					  counter--;
					  break;
				  }
			  }
			  if (it_impr2 != impr_func.end()) break;
		  }
		  if (it_func != funcionarios.end()) continue;
	  }
	  return counter;
  }
  vector<Impressora *> retiraImpressoras(int ano1) {
	  vector<Impressora *> impr_removidas;
	  vector<Impressora *>::iterator it_impr;
	  for (it_impr = impressoras.begin(); it_impr != impressoras.end(); it_impr++) {
		  if ((*it_impr)->getAno() < ano1) {
			  impr_removidas.push_back(*it_impr);
			  impressoras.erase(it_impr--);
		  }
	  }
	  return impr_removidas;
  }
  Impressora * imprimeDoc(Documento doc1) const {
	  for (size_t i = 0; i < impressoras.size(); i++) {
		  if (impressoras.at(i)->imprime(doc1)) {
			  return impressoras.at(i);
		  }
	  }
	  return new ImpressoraPB("inexistente", -1, -1);
  }
  vector<Impressora *> tonerBaixo() const {
	  vector<Impressora *> impr_tonerBaixo;
	  vector<Impressora *>::const_iterator it_impr;
	  for (it_impr = impressoras.begin(); it_impr != impressoras.end(); it_impr++) {
		  ImpressoraPB* pb = dynamic_cast<ImpressoraPB *> (*it_impr);
		  if (pb != NULL) {
			  if ((*it_impr)->getNumPaginasImprimir() < 30)
				  impr_tonerBaixo.push_back(*it_impr);
		  }
		  else {
			  ImpressoraCores* cores = dynamic_cast<ImpressoraCores *> (*it_impr);
			  if (cores != NULL) {
				  if ((*it_impr)->getNumPaginasImprimir() < 20)
					  impr_tonerBaixo.push_back(*it_impr);
			  }
		  }
	  }
	  return impr_tonerBaixo;
  }
  string operator()(string codImpr) {
	  vector<Funcionario>::iterator it_func;
	  for (it_func = funcionarios.begin(); it_func != funcionarios.end(); it_func++) {
		  vector<Impressora *> impr_resp = it_func->getImpressoras();
		  for (size_t i = 0; i < impr_resp.size(); i++) {
			  if (impr_resp.at(i)->getCodigo() == codImpr) {
				  return it_func->getCodigo();
			  }
		  }
	  }
	  return "nulo";
  }
};

#endif /* ESCRITORIO_H_ */
