/*
 * Value.c
 * Creator: George Ferguson
 * Created: Sun Nov 27 14:08:51 2016
 */

#include <stdlib.h>
#include <stdio.h>
#include "Value.h"

typedef struct Value {
	bool value;
} Value;

typedef bool value;

value* v(bool v){
    value* this = (value*)malloc(sizeof(value));
    this = v;
    return this;
};

Value* new_Value(bool value) {
	Value* this = (Value*)malloc(sizeof(Value));
	this->value = value;
	return this;
}

Value** new_Value_array(int len) {
	Value** this = (Value**)calloc(sizeof(Value*), len);
	return this;
}

bool Value_getValue(Value* this) {
	return this->value;
}

void Value_setValue(Value* this, bool b) {
	this->value = b;
}

void Value_print(Value* this) {
	printf("0x%lx=%s", this, this->value ? "true" : "false");
}
