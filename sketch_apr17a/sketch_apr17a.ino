#include <Bridge.h>

char pin13[2];
char valueStr[23];
int valueInt;

char incomming[2]={'\0'};
int previous_incomming_D2=999;
int previous_incomming_D3=999;
int previous_incomming_D4=999;
int previous_incomming_D5=999;
int previous_incomming_D6=999;
int previous_incomming_D7=999;
int previous_incomming_D8=999;
int previous_incomming_D9=999;

char outcome[4];
int outcomming_A0=0;
int outcomming_A1=0;
int outcomming_A2=0;
int outcomming_A3=0;
int outcomming_A4=0;
int outcomming_A5=0;

void setup() {
    pinMode(13,OUTPUT);
    pinMode(2,OUTPUT);    
    pinMode(3,OUTPUT);
    pinMode(4,OUTPUT);    
    pinMode(5,OUTPUT);    
    pinMode(6,OUTPUT);    
    pinMode(7,OUTPUT);
    pinMode(8,OUTPUT);    
    pinMode(9,OUTPUT);        

    Bridge.begin();   // Pins 0 and 1 should be avoided as they are used by the Bridge library.
}
 
void loop() {
    Bridge.get("Reg_done",  pin13, 2);
    digitalWrite(13, atoi(pin13));    
   
    Bridge.get("incomming_D2-O",  incomming, 2);
    if (atoi(incomming)!=previous_incomming_D2){
        previous_incomming_D2=atoi(incomming);
        Bridge.get("D2-O",  valueStr, 5);
        valueStr[4]='\0';
        valueInt = atoi(valueStr);
        if (valueInt >= 1) valueInt=1; else valueInt=0;
        digitalWrite(2, valueInt);        
    }

    Bridge.get("incomming_D3-O",  incomming, 2);
    if (atoi(incomming)!=previous_incomming_D3){
        previous_incomming_D3=atoi(incomming);
        Bridge.get("D3-O",  valueStr, 5);
        valueStr[4]='\0';
        valueInt = atoi(valueStr);
        if (valueInt >= 1) valueInt=1; else valueInt=0;        
        digitalWrite(3, valueInt);        
    }

    Bridge.get("incomming_D4-O",  incomming, 2);
    if (atoi(incomming)!=previous_incomming_D4){
        previous_incomming_D4=atoi(incomming);
        Bridge.get("D4-O",  valueStr, 5);
        valueStr[4]='\0';
        valueInt = atoi(valueStr);
        if (valueInt >= 1) valueInt=1; else valueInt=0;        
        digitalWrite(4, valueInt);        
    }

    Bridge.get("incomming_D5Pwm-O",  incomming, 2);
    if (atoi(incomming)!=previous_incomming_D5){
        previous_incomming_D5=atoi(incomming);
        Bridge.get("D5Pwm-O",  valueStr, 5);
        valueStr[4]='\0';
        valueInt = atoi(valueStr);
        if (valueInt >= 255) valueInt=255;
        else if (valueInt <= 0) valueInt=0;        
        analogWrite(5, valueInt);        
    }

    Bridge.get("incomming_D6Pwm-O",  incomming, 2);
    if (atoi(incomming)!=previous_incomming_D6){
        previous_incomming_D6=atoi(incomming);
        Bridge.get("D6Pwm-O",  valueStr, 5);
        valueStr[4]='\0';
        valueInt = atoi(valueStr);
        if (valueInt >= 255) valueInt=255;
        else if (valueInt <= 0) valueInt=0;        
        analogWrite(6, valueInt);        
    }

    Bridge.get("incomming_D7-O",  incomming, 2);
    if (atoi(incomming)!=previous_incomming_D7){
        previous_incomming_D7=atoi(incomming);
        Bridge.get("D7-O",  valueStr, 5);
        valueStr[4]='\0';
        valueInt = atoi(valueStr);
        if (valueInt >= 1) valueInt=1; else valueInt=0;        
        digitalWrite(7, valueInt);        
    }

    Bridge.get("incomming_D8-O",  incomming, 2);
    if (atoi(incomming)!=previous_incomming_D8){
        previous_incomming_D8=atoi(incomming);
        Bridge.get("D8-O",  valueStr, 5);
        valueStr[4]='\0';
        valueInt = atoi(valueStr);
        if (valueInt >= 1) valueInt=1; else valueInt=0;        
        digitalWrite(8, valueInt);        
    }

    Bridge.get("incomming_D9Pwm-O",  incomming, 2);
    if (atoi(incomming)!=previous_incomming_D9){
        previous_incomming_D9=atoi(incomming);
        Bridge.get("D9Pwm-O",  valueStr, 5);
        valueStr[4]='\0';
        valueInt = atoi(valueStr);
        if (valueInt >= 255) valueInt=255;
        else if (valueInt <= 0) valueInt=0;        
        analogWrite(9, valueInt);        
    }

    valueInt = analogRead(0);
    itoa(valueInt, valueStr, 10); 
    Bridge.put("A0-I", valueStr);
    itoa( (outcomming_A0=outcomming_A0^1), outcome, 10);
    //Bridge.put("outcomming_A0", outcome);

    valueInt = analogRead(1);
    itoa(valueInt, valueStr, 10); 
    Bridge.put("A1-I", valueStr);
    itoa( (outcomming_A1=outcomming_A1^1), outcome, 10);
    //Bridge.put("outcomming_A1", outcome);

    valueInt = analogRead(2);
    itoa(valueInt, valueStr, 10); 
    Bridge.put("A2-I", valueStr);
    itoa( (outcomming_A2=outcomming_A2^1), outcome, 10);
    //Bridge.put("outcomming_A2", outcome);

    valueInt = analogRead(3);
    itoa(valueInt, valueStr, 10); 
    Bridge.put("A3-I", valueStr);
    itoa( (outcomming_A3=outcomming_A3^1), outcome, 10);
    //Bridge.put("outcomming_A3", outcome);

    valueInt = analogRead(4);
    itoa(valueInt, valueStr, 10); 
    Bridge.put("A4-I", valueStr);
    itoa( (outcomming_A4=outcomming_A4^1), outcome, 10);
    //Bridge.put("outcomming_A4", outcome);      

    valueInt = analogRead(5);
    itoa(valueInt, valueStr, 10); 
    Bridge.put("A5-I", valueStr);
    itoa( (outcomming_A5=outcomming_A5^1), outcome, 10);
    //Bridge.put("outcomming_A5", outcome);    

    delay(10);
}
