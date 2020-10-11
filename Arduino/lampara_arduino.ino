// Crea una variable de tipo numérica entera que almacenará el estado de la lámpara
// estado=1 lampara encendida, estado=0 lampara apagada
int estado;

// La función setup se ejecuta una sola vez
void setup() {
  // inicializa el pin digital 8 como salida
  pinMode(8, OUTPUT);
  // inicializa el pin digital 7 como entrada
  pinMode(7, INPUT);
}

// La función loop() se repite indefinidamente
void loop() {
  // Almacena en la variable estado el valor que recibe por el pin 7 desde el ESP8266
  estado = digitalRead(7);
  // Si el estado=1 ...
  if (estado == 1) {
    // enviará un 1 o lo que es lo mismo un valor de voltaje alto al pin 8 
    digitalWrite(8, HIGH);
  // En cualquier otro caso
  }else{
    // enviará un 0 o lo que es lo mismo un valor de voltaje bajo al pin 8
    digitalWrite(8, LOW);   // turn the LED off by making the voltage LOW
  }
  // Espera 1000 milisegundo, o sea 1 segundo
  delay(1000);                       
}
