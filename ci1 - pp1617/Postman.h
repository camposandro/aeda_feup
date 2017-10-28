/*
 * Postman.h
 */

#ifndef SRC_POSTMAN_H_
#define SRC_POSTMAN_H_

#include "Mail.h"
#include <string>
#include <vector>
#include <algorithm>

/* 1a) */
template <class T>
unsigned int numberDifferent (const vector<T> & v1) {
	vector<T> v_copy = v1;
	sort(v_copy.begin(), v_copy.end());
	unsigned int counter = v_copy.size();
	for (size_t i = 0; i < v1.size(); i++) {
		if (v_copy[i + 1] == v_copy[i]) {
				counter--;
		}
	}
	return counter;
}

class Postman {
	static unsigned int g_id;
	unsigned int id;
	string name;
	vector<Mail *> myMail;
public:
	Postman();
	Postman(string name) :name(name) {
		this->id = ++g_id;
	}
	void setName(string nm);
	void addMail(Mail *m);
	void addMail(vector<Mail *> mails);
	string getName() const;
	vector<Mail *> getMail() const;
	unsigned int getID() const;
	bool operator < (const Postman &p1) {
		vector<string> zipCodesThis, zipCodesP1;
		for (size_t i = 0; i < this->getMail().size(); i++)
			zipCodesThis.push_back(this->getMail().at(i)->getZipCode());
		for (size_t j = 0; j < p1.getMail().size(); j++)
			zipCodesP1.push_back(p1.getMail().at(j)->getZipCode());

		return (numberDifferent(zipCodesThis) < numberDifferent(zipCodesP1));
	}
};


#endif /* SRC_POSTMAN_H_ */
