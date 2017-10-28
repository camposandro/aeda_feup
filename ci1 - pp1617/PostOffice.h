/*
 * PostOffice.h
 */

#ifndef SRC_POSTOFFICE_H_
#define SRC_POSTOFFICE_H_

#include "Mail.h"
#include "Postman.h"
#include <iostream>
#include <vector>
#include <algorithm>

/* EXCEÇAO NoPostmanException */
class NoPostmanException {
	string name;
public:
	NoPostmanException(string name) : name(name) {}
	string getName() const {
		return name;
	}
};

class PostOffice {
	vector<Mail *> mailToSend;
	vector<Mail *> mailToDeliver;
	vector<Postman> postmen;
	string firstZipCode, lastZipCode;
public:
	PostOffice();
	PostOffice(string firstZCode, string lastZCode);
	void addMailToSend(Mail *m);
	void addMailToDeliver(Mail *m);
	void addPostman(const Postman &p);
	vector<Mail *> getMailToSend() const;
	vector<Mail *> getMailToDeliver() const;
	vector<Postman> getPostman() const;
	vector<Mail *> removePostman(string name) {
		vector<Mail *> vector_mail;
		vector<Postman>::iterator it_postman;
		for (it_postman = postmen.begin(); it_postman != postmen.end(); it_postman++) {
			if (it_postman->getName() == name) {
				vector_mail = it_postman->getMail();
				postmen.erase(it_postman);
				break;
			}
		}
		return vector_mail;
	}
	vector<Mail *> endOfDay(unsigned int &balance) {
		balance = 0;
		vector<Mail *> vector_send;
		vector<Mail *>::const_iterator it_mailSend;
		for (it_mailSend = mailToSend.begin(); it_mailSend != mailToSend.end(); it_mailSend++)
		{
			balance += (*it_mailSend)->getPrice();

			string zipcode = (*it_mailSend)->getZipCode();
			if (zipcode >= firstZipCode && zipcode <= lastZipCode) {
				mailToDeliver.push_back(*it_mailSend);
			} else {
				vector_send.push_back(*it_mailSend);
			}
		}

		mailToSend.clear();
		return vector_send;
	}
	Postman addMailToPostman(Mail *m, string name) {
		vector<Postman>::iterator it_postman;
		for (it_postman = postmen.begin(); it_postman < postmen.end(); it_postman++)
		{
			if (it_postman->getName() == name)
			{
				it_postman->addMail(m);
				break;
			}
		}

		if (it_postman == postmen.end())
			throw NoPostmanException(name);

		return *it_postman;
	}
};

#endif /* SRC_POSTOFFICE_H_ */
