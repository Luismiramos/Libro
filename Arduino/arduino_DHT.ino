// incluye librerías.
#include <Wire.h>
#include "DHT.h"
// Pin digital conectado al sensor DHT.
#define DHTPIN 5        
#define DHTTYPE DHT11   // DHT11
DHT dht(DHTPIN, DHTTYPE);
// Declara variables.
char temperatura[8];
char humedad[8];
// El código de la función setup() se ejecuta una sola vez.
void setup() {
    Serial.begin(115200); 
    Wire.begin(9); // Inicia el bus con dirección 9  
    // Llama a la función requestEvent cuando el maestro solicita datos. 
    Wire.onRequest(requestEvent); 
    dht.begin();                    // Inicia el sensor DHT11  
}
// El código de la función loop() se ejecuta indefinidamente.
void loop() {
    // Lee la temperatura y la humedad
    float h = dht.readHumidity();
    // Lee la temperatura en escala Celsius 
    float t = dht.readTemperature();
    // Comprueba si hay error de lectura
    if (isnan(h) || isnan(t)) {
      Serial.println(F("Fallo leyendo el sensor DHT11!"));
   }else{
    // convierte t float en temperatura char con formato de 3 enteros y 1 decimal.
    dtostrf(t, 3, 1, temperatura);  
  dtostrf(h , 3, 1, humedad); 
  Serial.print(F("Humedad: "));
  Serial.print(humedad);
  Serial.print(F("%  Temperatura: "));
  Serial.print(temperatura);
  Serial.println(F("°C "));
  delay(40000);
    }
    delay(100);
}
// Esta función se ejecuta cuando el maestro solicita datos.
void requestEvent() {
    //Evía cadena requerida.
    Wire.write(temperatura); 
    Wire.write(humedad); 
}
