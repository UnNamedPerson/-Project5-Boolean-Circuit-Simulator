/*
 * File: main.c
 * Creator: George Ferguson
 * Created: Mon Nov 28 14:11:17 2016
 * Time-stamp: <Mon Nov 28 14:22:27 EST 2016 ferguson>
 */
#include <stdio.h>
#include <stdlib.h>
#include "Circuit.h"

/**
 * Two AND gates connected to make a 3-input AND circuit.
 */
static Circuit* Circuits_and3() {
	Value* in0 = new_Value(false);
	Value* in1 = new_Value(false);
	Value* in2 = new_Value(false);
	Gate* and0 = new_AndGate(in0, in1);
	Gate* and1 = new_AndGate(Gate_getOutput(and0), in2);

	Value** inputs = new_Value_array(3);
	inputs[0] = in0;
	inputs[1] = in1;
	inputs[2] = in2;
	Value** outputs = new_Value_array(1);
	outputs[0] = Gate_getOutput(and1);
	Gate** gates = new_Gate_array(2);
	gates[0] = and0;
	gates[1] = and1;
	return new_Circuit(3, inputs, 1, outputs, 2, gates);
}

static char* b2s(bool b) {
	return b ? "T" : "F";
}

static void test3In1Out(Circuit* circuit, bool in0, bool in1, bool in2) {
	Circuit_setInput(circuit, 0, in0);
	Circuit_setInput(circuit, 1, in1);
	Circuit_setInput(circuit, 2, in2);
	//Circuit_dump(circuit);
	Circuit_update(circuit);
	bool out0 = Circuit_getOutput(circuit, 0);
	printf("%s %s %s -> %s\n", b2s(in0), b2s(in1), b2s(in2), b2s(out0));
}

static Circuit* Circuite_OneBitAdder(){
    
    Value* inpx = new_Value(false);
    Value* inpy = new_Value(false);
    Value* inpC = new_Value(false);
    
//    the Invert gates
    Gate* Invx = new_Inverter(inpx);
    Gate* Invy = new_Inverter(inpy);
    Gate* Invc = new_Inverter(inpC);

//    the And gates
    Gate* And1 = new_And3Gate(Gate_getOutput(Invx), Gate_getOutput(Invy), inpC);
    Gate* And2 = new_And3Gate(Gate_getOutput(Invx), inpy, Gate_getOutput(Invc));
    Gate* And3 = new_And3Gate(Gate_getOutput(Invx), inpy, inpC);
    Gate* And4 = new_And3Gate(inpx, Gate_getOutput(Invy), Gate_getOutput(Invc));
    Gate* And5 = new_And3Gate(inpx, Gate_getOutput(Invy), inpC);
    Gate* And6 = new_And3Gate(Gate_getOutput(Invc), inpy, inpx);
    Gate* And7 = new_And3Gate(inpx, inpy, inpC);

//    the Or gates
    Gate* Or1 = new_Or4Gate(Gate_getOutput(And1), Gate_getOutput(And2), Gate_getOutput(And4), Gate_getOutput(And7));
    Gate* Or2 = new_Or4Gate(Gate_getOutput(And3), Gate_getOutput(And5), Gate_getOutput(And6), Gate_getOutput(And7));

//    array of inputs
    Value** Inputs = new_Value_array(3);
    Inputs[0] = inpx;
    Inputs[1] = inpy;
    Inputs[2] = inpC;
    
//    array of gates
    Gate** Gates = new_Gate_array(12);
    
    Gates[0] = Invx;
    Gates[1] = Invy;
    Gates[2] = Invc;

    Gates[3] = And1;
    Gates[4] = And2;
    Gates[5] = And3;
    Gates[6] = And4;
    Gates[7] = And5;
    Gates[8] = And6;
    Gates[9] = And7;

    Gates[10] = Or1;
    Gates[11] = Or2;
    
//    array of outputs
    Value** Outputs = new_Value_array(2);
    Outputs[0] = Gate_getOutput(Or1);
    Outputs[1] = Gate_getOutput(Or2);

    
    return new_Circuit(3, Inputs, 2, Outputs, 12, Gates);

}

static void testing_OneBitAdder(Circuit* circuit, bool in0, bool in1, bool in2){
    Circuit_setInput(circuit, 0, in0);
    Circuit_setInput(circuit, 1, in1);
    Circuit_setInput(circuit, 2, in2);
    Circuit_update(circuit);
}


int main(int argc, char **argv) {
//    Circuit* c = Circuits_and3();
//    printf("Some input(s) false: should be false\n");
//    test3In1Out(c, true, true, false);
//    printf("All inputs true: should be true\n");
//    test3In1Out(c, true, true, true);
    
    printf("Testing the ObeBitAdder \n");
    Circuit* OBA = Circuite_OneBitAdder();
    testing_OneBitAdder(OBA, true, true, false);
    testing_OneBitAdder(OBA, true, false, false);

}
