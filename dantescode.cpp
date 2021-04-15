#include <OneWire.h> // libuary to read data from the pin
#include <DallasTemperature.h> // allows to use the temp sensor

// GPIO where the Heating Element is connected to
const int MOSFETSWITCH = 33;
// GPIO where the DS18B20 is connected to
const int oneWireBus = 4;

// Setup a oneWire instance to communicate with any OneWire devices
OneWire oneWire(oneWireBus);

// Pass our oneWire reference to Dallas Temperature sensor
DallasTemperature sensors(&oneWire);

void setup() {
  // Start the Serial Monitor
  Serial.begin(115200);
  // Start the DS18B20 sensor
  sensors.begin();
    pinMode (MOSFETSWITCH, OUTPUT);
    //Option: If pin doesn't read you could force the pin as an input
    //pinMode (oneWireBus, INPUT);
}

void loop() {
  sensors.requestTemperatures();
  float temperatureC = sensors.getTempCByIndex(0);
  float temperatureF = sensors.getTempFByIndex(0);
  Serial.print(temperatureC);
  Serial.println("ºC");
  Serial.print(temperatureF);
  Serial.println("ºF");
 

   if (temperatureF <= 90) { // toggle for the heating element at the desired temperature
   
       digitalWrite (MOSFETSWITCH, HIGH);// as long as temperature stays below desired temp, shit is about to go down.
    }
   
    else {
      digitalWrite (MOSFETSWITCH, LOW); //When temp is reached the switch will turn off.  
    }
 delay(5000);//DS18B20 data wire is connected to pin 15 on the NodeMCU
}
