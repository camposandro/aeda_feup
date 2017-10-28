/*
 * Mail.h
 */

#ifndef SRC_MAIL_H_
#define SRC_MAIL_H_

#include <string>
#include <vector>
using namespace std;


class Mail {
	string sender;
	string receiver;
	string zipCode;
public:
	Mail(string send, string rec, string zcode);
	virtual ~Mail();
	string getZipCode() const;
	virtual unsigned int getPrice () const = 0;
};


class RegularMail: public Mail {
	unsigned int weight;
public:
	RegularMail(string send, string rec, string code, unsigned int w);
	unsigned int getPrice () const {
		unsigned int price;
		if (weight <= 20) {
			price = 50;
		} else if (weight <= 100) {
			price = 75;
		} else if (weight <= 500) {
			price = 140;
		} else price = 325;

		return price;
	}
};


class GreenMail: public Mail {
	string type;  // "envelope", "bag", "box"
public:
	GreenMail(string send, string rec, string code, string t);
	unsigned int getPrice () const {
		unsigned int price;
		if (type == "envelope") price = 80;
		else if (type == "bag") price = 200;
		else if (type == "box") price = 240;
		return price;
	}
};


#endif /* SRC_MAIL_H_ */
