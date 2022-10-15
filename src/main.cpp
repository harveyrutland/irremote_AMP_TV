

#include <Arduino.h>
#include "PinDefinitionsAndMore.h" // Define macros for input and output pin etc.
#include <IRremote.h>
#include <IRremote.hpp>

#define NUMBER_OF_REPEATS 3U

const int RECV_PIN = 7;
IRrecv irrecv(RECV_PIN);
decode_results results;
bool power_state = false;
int i;
IRsend irsend;
void setup()
{
    Serial.begin(9600);
    pinMode(3, OUTPUT);
    IrSender.begin();
    Serial.print(F("Ready to send IR signals at pin "));
    Serial.println(IR_SEND_PIN);
    irrecv.enableIRIn();
    irrecv.blink13(true);
}
 
void loop()
{
    if (irrecv.decode(&results))
    {
        char *on_val[] = {"6262","4214"};
        char *off_val[] = {"6263","4214"};
        char *up_val[] = {"6260","4212"};
        char *down_val[] = {"6258","4210"};
        // Serial.println(results.value, HEX);
        irrecv.resume();
        Serial.println(results.value);
        if (String(results.value) == String(on_val[0]) || String(results.value) == String(on_val[1]))
        {  
            
            for (i = 0; i <= 10; i++)
            {   
                power_state = true;
                Serial.println(i);
                Serial.print("recieved on");
                delay(20);
                irsend.sendPronto(F("0000 006D 000B 0000 0021 0022 0023 0022 0021 0024 0021 0022 0044 0024 0021 0044 0044 0024 0021 0044 0021 0022 0021 0024 0044 06C3 "), /* NEC repeat pattern*/
                                  NUMBER_OF_REPEATS);
                delay(20);
            }
        }
        else if (String(results.value) == String(off_val[0]) || String(results.value) == String(off_val[1]))
        {  
            
            for (i = 0; i <= 10; i++)
            {   
                power_state = true;
                Serial.println(i);
                Serial.print("recieved off");
                delay(20);
                irsend.sendPronto(F("0000 006D 000B 0000 0023 0022 0044 0044 0023 0022 0046 0022 0021 0044 0046 0022 0021 0044 0023 0022 0023 0022 0023 0022 0021 06C3 "), /* NEC repeat pattern*/
                                  NUMBER_OF_REPEATS);
                delay(20);
            }
        }
        else if (String(results.value) == String(up_val[0]) || String(results.value) == String(up_val[1]))
        {  
            
            for (i = 0; i <= 2; i++)
            {   
                power_state = true;
                Serial.println(i);
                Serial.print("recieved volume up");
                delay(20);
                irsend.sendPronto(F("0000 006D 000C 0000 0021 0024 0021 0024 0021 0024 0044 0022 0021 0024 0021 0024 0021 0022 0021 0046 0044 0024 0020 0024 0021 0024 0021 06C3 "), /* NEC repeat pattern*/
                                  NUMBER_OF_REPEATS);
                delay(20);
            }
        }
        else if (String(results.value) == String(down_val[0]) || String(results.value) == String(down_val[1]))
        {  
            
            for (i = 0; i <= 2; i++)
            {   
                power_state = true;
                Serial.println(i);
                Serial.print("recieved volume down");
                delay(20);
                irsend.sendPronto(F("0000 006D 000C 0000 0020 0024 0021 0024 0020 0026 0042 0024 0021 0024 0021 0024 0020 0024 0021 0046 0042 0024 0021 0024 0021 0046 0020 06C3 "), /* NEC repeat pattern*/
                                  NUMBER_OF_REPEATS);
                delay(20);
            }
        }
        
    }
}



