
// incluye librerías
#include "defines.h"
#include "Credentials.h"
#include <MySQL_Generic_WiFi.h>
// Valores de la base de datos
IPAddress server_addr(192, 168, 1, 148);
uint16_t server_port = 3306;    // Opción de puerto: 5698
char default_database[] = "iot";     
char default_table[]    = "lampara";        
String default_column   = "estado";
String default_value    = "";
String Estado_lampara   = "";
// Variable con la instrucción de la consulta a la base de datos
String query = String("SELECT ") + default_column + " FROM " + default_database + "." + default_table;
//Conexión a la base de datos
MySQL_Connection conn((Client *)&client);
MySQL_Query sql_query = MySQL_Query(&conn);

// El código de la función setup() se ejecuta una sola vez
void setup()
{
  Serial.begin(115200);
  pinMode(2, OUTPUT);
  while (!Serial);
  WiFi.begin(ssid, pass);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  // Muestra a través del monitor serie
  Serial.print("Conectando a la red. La dirección IP del ESP8266 es: ");
  Serial.println(WiFi.localIP());
  Serial.print("Conectando al servidor con IP ");
  Serial.print(server_addr);
  Serial.println(String(", Puerto de comunicación = ") + server_port);
  Serial.println(String("Usuario = ") + user + String(", Contraseña = ") + password + String(", Base de datos = ") + default_database);
}
// Función para la consulta, se ejecuta cuando es llamada
void runQuery(void)
{
  row_values *row = NULL;
  long head_count = 0;
  MySQL_Query query_mem = MySQL_Query(&conn);
  Serial.println(query);
  if ( !query_mem.execute(query.c_str()) )
  {
    Serial.println("Error en la consulta");
    return;
  }
  column_names *columns = query_mem.get_columns();
  do
  {
    row = query_mem.get_next_row();
    
    if (row != NULL)
    {
      head_count = atol(row->values[0]);
      Estado_lampara = head_count;
    }
  } while (row != NULL);
  // Muestra el resultado de la consulta
  Serial.print("  Estado de la lámpara = ");
  Serial.println(head_count);
  delay(500);
  sql_query.close();
}
// Esta función se ejecuta indefinidamente
void loop()
{
  Serial.println("Conectando...");
  if (conn.connectNonBlocking(server_addr, server_port, user, password) != RESULT_FAIL)
  {
    delay(500);
    runQuery();
    if (Estado_lampara=="1"){
        digitalWrite(2, HIGH);   //  Enciende lámpara poniendo en alto el pin 2
    }else{
        digitalWrite(2, LOW);    // Apaga lámpara poniendo en 0 el pin 2
    }
    conn.close();                     // Cierra la conexión
  }
  else
  {
    Serial.println("\nConexión fallida. Se intentará en la próxima iteración.");
  }
  Serial.println("\nEn pausa...");
  Serial.println("================================================");
  // Espera 3000 milisegundos, 3 segundos para la siguiente iteración.
  delay(3000);
}
