#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <vector>

#include "app/fundamental/impl/statemachine/sm.h"
#include "app/fundamental/impl/statemachine/base_machine.h"
#include "app/util/Console.h"

using namespace std;

int main(int argc, char const *argv[])
{
	SMDelay2<double> dl(2);
	SMDelay2<double> dl2(3);
	
	SMCascade<double, double> sm_01(&dl, &dl2);
	SMDATA pData01 = NULL;

	SMFeedback<double> sm_02(3, &sm_01);

	//sm_01.step(5);
	//sm_01.step(6);
	//sm_01.step(7);

	double inputs[] = { 5, 10, 15, 20, 25 , 26, 27, 28, 29};
	int inputs_int_[] = { 5, 10, 15, 20, 25 , 26, 27, 28, 29};
	vector<double> v_out;

	sm_01.transduce(inputs, 9, v_out);	
	Console::log(v_out);

	sm_02.transduce(inputs_int_, 9 , v_out);	
	Console::log(v_out);

	return 0;
}