/*
 * SNumber.h
 *
 *  Created on: Mar 5, 2018
 *      Author: ducvd
 */

#ifndef APP_FUNDAMENTAL_IMPL_NUMBER_SNUMBER_H_
#define APP_FUNDAMENTAL_IMPL_NUMBER_SNUMBER_H_

#include <string> 
#include <stdio.h>
#include <stdlib.h>
#include <map>

typedef struct structRawSNumber
{
	int sign_;
	std::string number_;
	std::string dot_number_;
	bool isPower;

	int power_sign_;
	std::string power_number_;

	structRawSNumber()
	{
		sign_ = 1;
		number_ = "";
		dot_number_ = "";
		isPower = false;
		power_sign_ = 0;
		power_number_ = "";
	}

	void print()
	{
		printf("Number=sign=%d; number=%s; dot=%s; power_sign_=%d; power_number_=%s\r\n", 
					sign_,
					number_.c_str(),
					dot_number_.c_str(),
					power_sign_,
					power_number_.c_str() );
	}

} RawSNumber;

// Every numbers here
class SNumber {

public:
	SNumber(const char* szNum);
	virtual ~SNumber();

	// bool operator>(const SNumber& num1, const SNumber& num2);
	// SNumber operator+(const SNumber& num1);
	RawSNumber& rawData() { return raw; }
protected:
	bool isNumber(const char* szNum);
	int next_Values(char ch, int current_State, RawSNumber& out_put);
private:
	std::string _strNum;
	RawSNumber raw;

	std::map<int,std::string>  mapName;
};

#endif /* APP_FUNDAMENTAL_IMPL_NUMBER_SNUMBER_H_ */
