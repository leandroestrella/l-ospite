/*******************************************************************************************
 * "It is necessary - in order to fully understand past and present universals, and thus   *
 *  to prepare for the future - to distinguish between structures, architectures, resonant *
 *  organisms and their temporal manifestations."                                          *
 *                                                                          Iannis Xenakis *
 * "L'Ospite || El Huésped || The Host"                                                    *
 *  by Leandro Estrella [https://cargocollective.com/leandroestrella]                      *
 *  assisted by David Sanz Kirbis [https://github.com/dasaki]                              *
 *  based on Serial Event example by Tom Igoe [https://github.com/tigoe]                   *
 *  using Morse Code Library by Mark Fickett [https://github.com/markfickett/arduinomorse] *
 *******************************************************************************************/

#include <morse.h>    // morse code library
#define PIN_STATUS  9 // solenoid output pin

String inputString = "";         // a string to hold incoming data
boolean stringComplete = false;  // whether the string is complete

LEDMorseSender cqSender(PIN_STATUS);

void setup() {
  cqSender.setup();
  Serial1.begin(9600); // initialize serial:
  while (!Serial1) {
    ; // wait for serial port to connect. Needed for native USB port only
  }
  Serial1.println("ospite ready");
  inputString.reserve(200); // reserve 200 bytes for the inputString:
}

void loop() {
  /*
    SerialEvent occurs whenever a new data comes in the
    hardware serial RX.  This routine is run between each
    time loop() runs, so using delay inside loop can delay
    response.  Multiple bytes of data may be available.
  */
  while (Serial1.available()) {
    char inChar = (char)Serial1.read(); // get the new byte
    inputString += inChar;             // add it to the inputString
    /*
      if the incoming character is a newline, set a flag
      so the main loop can do something about it:
    */
    if (inChar == '\n') {
      stringComplete = true;
    }
  }
  
  /* print the string when a newline arrives: */
  if (stringComplete) {
    Serial1.println(inputString);
    cqSender.setMessage(inputString);
    cqSender.sendBlocking();
    /* clear the string: */
    inputString = "";
    stringComplete = false;
  }
}
