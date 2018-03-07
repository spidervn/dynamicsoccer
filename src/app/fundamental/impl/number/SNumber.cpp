/*
 * SNumber.cpp
 *
 *  Created on: Mar 5, 2018
 *      Author: ducvd
 */

#include <fundamental/impl/number/SNumber.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

using namespace std;

int START = 0;
int INVALID = -1;
int SIGN = 1;
int NUMBER = 2;
int DOT_REAL = 3;
int REAL_NUMBER = 4;
int FINISH_NUMBER = 5;
int FINISH_REAL_NUMBER = 6;

int START_POWER = 7;
int SIGN_POWER = 8;
int NUMBER_POWER = 9;
int FINISH_NUMBER_POWER = 10;
int END = 11;

SNumber::SNumber(const char* szNum) 
{
	_strNum = szNum;
	isNumber(szNum);

	mapName[START] = "START";
	mapName[INVALID] = "INVALID";
	mapName[SIGN] = "SIGN";
	mapName[NUMBER] = "NUMBER";
	mapName[DOT_REAL] = "DOT_REAL";
	mapName[REAL_NUMBER] = "REAL_NUMBER";
	mapName[FINISH_NUMBER] = "FINISH_NUMBER";
	mapName[FINISH_REAL_NUMBER] = "FINISH_REAL_NUMBER";

	mapName[START_POWER] = "START_POWER";
	mapName[SIGN_POWER] = "SIGN_POWER";
	mapName[NUMBER_POWER] = "NUMBER_POWER";
	mapName[FINISH_NUMBER_POWER] = "FINISH_NUMBER_POWER";
	mapName[END] = "END";
}

SNumber::~SNumber() 
{
}

//bool SNumber::operator>(const SNumber& num1, const SNumber& num2)
//{
//	return true;
//}
//
//SNumber SNumber::operator+(const SNumber& num1)
//{
//	return SNumber("");
//}
//
//bool SNumber::operator>(const SNumber& num1, const SNumber& num2)
//{
//	return true;
//}

bool SNumber::isNumber(const char* szNum)
{
	/*
	 * What is Number's representation
	 *	+1000
	 *	+ 10000
	 *	100
	 *	-100
	 *	- 1000
	 *  10E10
	 *  10e10
	 *  +10E10
	 *  +10e10
	 *
	 *  10E-10
	 *  10e-10
	 *  -10E-10
	 *  -10E-10
	 *
	 *  +1000.23456
	 *  1000.23456
	 */

	 /*
	  *		Number types
	  *			Type01 = [space][+/-][space](number)[space]
	  *			Type02 = [space][+/-][space](number)(e/E)(number)[space]
	  */
	int n = strlen(szNum);	

	/*
		Dummy approach:
			Use a scanner from Left to Right 
							
	*/
	int type = 1;
	
	/*
	int START = 0;
	int INVALID = -1;
	int SIGN = 1;
	int NUMBER = 2;
	int DOT_REAL = 3;
	int REAL_NUMBER = 4;
	int FINISH_NUMBER = 5;
	int FINISH_REAL_NUMBER = 6;

	int START_POWER = 7;
	int SIGN_POWER = 8;
	int NUMBER_POWER = 9;
	int FINISH_NUMBER_POWER = 10;
	int END = 11;
	*/

	int state = START;

	for (int i = 0; i < n; ++i)
	{
		int nwState = next_Values(szNum[i], state, raw);
		state = nwState;
	}

	printf("Number=%s; Final state=%s\n", szNum, mapName[state].c_str());
	raw.print();
	
	// State Machine
	//	Type = Start, Invalid, TypeNumber, TypeE
	//	Start ->(space)-> Start
	//	Start ->(+) -> PreNumber
	//  Start ->(-) -> PreNumber
	//	Start ->(0-9) -> Seminumber
	//	SemiNumber->(0-9) -> SemiNumber
	//  Seminumber->(+/-/Space) -> Invalid -> End
	//  
	//
	//	States
	//		- Start
	//		- Sign
	//		- Number
	//		- RealNumber
	//		- StartPower
	//		- SignPower
	//		- NumberPower
	//		- RealNumberPower
	//		- Invalid
	
	return true;
}

int SNumber::next_Values(char ch, int current_State, RawSNumber& out_put)
{
	/*
	int START = 0;
	int INVALID = -1;
	int SIGN = 1;
	int NUMBER = 2;
	int DOT_REAL = 3;
	int REAL_NUMBER = 4;
	int FINISH_NUMBER = 5;
	int FINISH_REAL_NUMBER = 6;

	int START_POWER = 7;
	int SIGN_POWER = 8;
	int NUMBER_POWER = 9;
	int FINISH_NUMBER_POWER = 10;
	int END = 11;
	*/

	int nwState = 0;

	if (current_State == START)
	{
		if (ch == '-' || ch == '+')
		{
			nwState = SIGN;
			out_put.sign_ = ch == '+' ? 1 : -1;
		}
		else if (ch == ' ' || ch=='\t')
		{
			nwState = START;
		}
		else if (ch >= '0' && ch<='9')
		{
			nwState = NUMBER;
			out_put.number_ = ch;
			out_put.sign_ = 1;
		}
		else
		{
			nwState = INVALID;
		}
	}
	else if (current_State == INVALID)
	{
		nwState = END;
	}
	else if (current_State == SIGN)
	{
		if (ch == ' ' || ch=='\t')
		{
			nwState = SIGN;
		}
		else if (ch >= '0' && ch<='9')
		{
			nwState = NUMBER;
			out_put.number_ = ch;
		}
		else
		{
			nwState = INVALID;
		}
	}
	else if (current_State == NUMBER)
	{
		if (ch == '.')
		{
			nwState = DOT_REAL;
		}
		else if (ch >= '0' && ch<='9')
		{
			nwState = NUMBER;
		}
		else
		{
			nwState = INVALID;
		}
	}
	else if (current_State == DOT_REAL)
	{
		if (ch >= '0' && ch<='9')
		{
			nwState = REAL_NUMBER;
			out_put.dot_number_ = ch;
		}
		else
		{
			nwState = INVALID;
		}
	}
	else if (current_State == REAL_NUMBER)
	{
		if (ch >= '0' && ch<='9')
		{
			nwState = REAL_NUMBER;
			out_put.dot_number_ += ch;
		}
		else if (ch == 'e' || ch == 'E')
		{
			nwState = START_POWER; 	// Power
		}
		else
		{
			nwState = INVALID;
		}
	}
	else if (current_State == START_POWER)
	{
		if (ch == ' ' || ch=='\t')
		{
			nwState = START_POWER;
		}
		else if (ch >= '0' && ch<='9')
		{
			nwState = NUMBER_POWER;
			out_put.power_number_ = ch;
			out_put.power_sign_ = 1;
		}
		else if (ch == '+' || ch=='-')
		{
			nwState = SIGN_POWER;
			out_put.power_sign_ = ch == '+' ? 1 : -1;
		}
		else
		{
			nwState = INVALID;
		}
	}
	else if (current_State == SIGN_POWER)
	{
		if (ch == ' ' || ch=='\t')
		{
			nwState = SIGN_POWER;
		}
		else if (ch >= '0' && ch<='9')
		{
			nwState = NUMBER_POWER;
			out_put.power_number_ = ch;
		}
		else
		{
			nwState = INVALID;
		}
	}
	else if (current_State == NUMBER_POWER)
	{
		if (ch >= '0' && ch<='9')
		{
			nwState = NUMBER_POWER;
			out_put.power_number_ += ch;
		}
		else if (ch == ' ' || ch == '\t')
		{
			nwState = FINISH_NUMBER_POWER;
		}
		else
		{
			nwState = INVALID;
		}		
	}
	else if (current_State == FINISH_NUMBER_POWER)
	{
		if (ch == ' ' || ch == '\t')
		{
			nwState = FINISH_NUMBER_POWER;
		}
		else
		{
			nwState = INVALID;
		}
	}
	// if (current_State == )
	return nwState;
}
