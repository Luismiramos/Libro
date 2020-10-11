// incluye librerías
#include <Wire.h>
#include "defines.h"
#include "Credentials.h"
#include <MySQL_Generic_WiFi.h>
// Valores de la base de datos.
IPAddress server_addr(192, 168, 1, 148);
uint16_t server_port = 3306;    // Opción de puerto: 5698
char default_database[] = "iot";     
char default_table[]    = "ambiente";
// Variables de los datos.
String temperatura="";
String humedad="";
String frase;
//Variable con la instrucción que borra datos de la base de datos.
String TRUNCA_SQL = String("TRUNCATE TABLE ") + default_database + "." + default_table;
//Variable con la instrucción que inserta datos en la base de datos
String INSERT_SQL = String("INSERT INTO ") + default_database + "." + default_table + " (temperatura, humedad) VALUES ('" + temperatura + "', '" + humedad + "')";
//Conexión a la base de datos
MySQL_Connection conn((Client *)&client);
MySQL_Query sql_query = MySQL_Query(&conn);
// El código de la función setup() se ejecuta una sola vez.
void setup()
{
  Wire.begin(); // El maestro inicia el bus I2C.
  Serial.begin(115200);
  while (!Serial);
  WiFi.begin(ssid, pass);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
}
// Función para el borrado y la inserción de datos, se ejecuta cuando es llamada
void runInsert(void)
{
String INSERT_SQL = String("INSERT INTO ") + default_database + "." + default_table + " (temperatura, humedad) VALUES ('" + temperatura + "', '" + humedad + "')";
  // Initiate the query class instance
  MySQL_Query query_mem = MySQL_Query(&conn);
  if (conn.connected())
  {
    Serial.println(INSERT_SQL); 
    if ( !query_mem.execute(TRUNCA_SQL.c_str()) )
      Serial.println("Error de borrado");
    else
      Serial.println("Datos borrados");
    if ( !query_mem.execute(INSERT_SQL.c_str()) )
      Serial.println("Error de inserción");
    else    
      Serial.println("Datos insertados");  
  }
  else
  {
    Serial.println("Desconectado del servidor");
  }
}

// Esta función se ejecuta indefinidamente.
void loop() {
  // Solicita datos con un ancho de 8 del esclavo con dirección 9.
  Wire.requestFrom(9, 8);
  while(Wire.available()){
  // Lee datos recibidos del esclavo.  
     char c = Wire.read();
  // Almacena los datos en la variable frase.
  frase = String(frase + c); 
  }
  // Separa los valores de la variable frase.
  temperatura = frase.substring(4,0);
  humedad = frase.substring(8,4);
  frase = "";
  Serial.println(String("Humedad: ") + humedad + String("% Temperatura: ") + temperatura + String("ºC"));
  Serial.println("Conectando...");
  if (conn.connectNonBlocking(server_addr, server_port, user, password) != RESULT_FAIL)
  {
    delay(500);   
    runInsert();
    conn.close();                     // Cierra la conexión
  } else {
    Serial.println("\nConexión fallida. Se intentará en la próxima iteración.");
  }
  Serial.println("\nEn pausa...");
  Serial.println("================================================");
  delay(40000);
}
