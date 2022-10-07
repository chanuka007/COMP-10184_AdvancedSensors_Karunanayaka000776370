#include <Arduino.h>
#include <OneWire.h>
#include <DallasTemperature.h>
//I, Sadeva Chanuka Karunanayaka, student number 000776370, certify that all code submitted is my own work;
//that I have not copied it from any other source.  I also certify that I have not allowed my work to be copied by others.
 //10/7/2022

//setup the temp sensor bus and instanciate a oneWire instance using the bus
const int oneWireBus = D3;
//instanciate addressfound boolean
bool addressFound;
DeviceAddress address;
OneWire oneWire(oneWireBus);
//use onewire reference to setup dallas temperature sensor
DallasTemperature DS18B20(&oneWire);
/* 
  Set up the serial monitor and start the temp sensor
*/
void setup(){
  Serial.begin(115200);
  DS18B20.begin();

  Serial.println("\nTemperature Application");

  //get the device address and print it if no address is found terminate program
    
   addressFound = DS18B20.getAddress(address,0);
  if(addressFound){//if address is found print it to the monitor by looping through the address

  Serial.print("Found DS18B20 sensor with address: ");
    //loop through the uin8_t value that the deviceaddress is stored in
    for(uint8_t i =0; i<8;i++){
      if(address[i]<16) Serial.print("0");
      Serial.print(address[i],HEX);
    }
    Serial.println();
  }//if no address is found print statement explaining then exit
 else{//else no address found print statement saying no sensor is installed
  Serial.println("No DS18B20 temperature sensors are installed!");
 }
  
}

void loop(){
  //only run code if the device was found
  if(addressFound){
//setup tempsensor val and store the temperature from the sensor in it
  float tempSensorVal;
  DS18B20.requestTemperatures();
  
  tempSensorVal = DS18B20.getTempCByIndex(0);
 

String judgement = "";
  //get judgement string based on what the temperature value is
  if(tempSensorVal<10.00){
    judgement="Cold!";
  }
  else if (tempSensorVal>=10.0&&tempSensorVal<15.0){
    judgement="Cool";
  }
  else if (tempSensorVal>=15.0&&tempSensorVal<25.0){
    judgement="Perfect";
  }else if (tempSensorVal>=25.0&&tempSensorVal<30.0){
    judgement="Warm";
  }else if (tempSensorVal>=30.0&&tempSensorVal<35.0){
    judgement="Hot";
  }else{
    judgement="Too Hot!";
  }
  //print value along with  string for if its warm/cold
  Serial.println("Current temperature is: "+String(tempSensorVal)+" deg. Celsius or "+judgement);
  
  
   
  }else{//else do nothing effectively terminating the program

  //using exit(0) caused issues for me
    

  }
  //loop again in 5 seconds
  delay(5000);
  
}