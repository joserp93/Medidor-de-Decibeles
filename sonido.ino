/*CODIGO QUE MIDE LOS DECIBELES DEL SONIDO Y MANDA UNA ALERTA POR GSM SMS


DISEÑADO Y CREADO POR DEYBY STIVEN GARCIA MONTES & IVAN JOSE DIAZ MORALES
estudiantes de ingenieria de sistemas de la universidad de cordoba monteria colombia




requerimientos 

  *sensor de sonido dfr0034
  *Arduino GSM/GPRS Shield product from TINYSINE
  *arduino uno 
  
  nota: la shield gsm/gprs solo es compatibe con la arduino uno
  
  librerias y datasheet de la shield
  http://www.tinyosshop.com/index.php?route=product/product&product_id=464
  
  sensor de sonido datasheet
  http://www.dfrobot.com/wiki/index.php/Analog_Sound_Sensor_SKU:_DFR0034
  
*/


//  Incluimos las librerias necesarias
#include "SIM900.h"
#include <SoftwareSerial.h>
#include "sms.h"


//Creamos un objeto de tipo SMSGSM
SMSGSM sms;

//Declaracion de las variables
int numdata;
boolean started=false;
char smsbuffer[160];
char n[20];
char sms_position;
char phone_number[20]; //arreglo donde se guarda el numero de telefono
char sms_text[100];//arreglo donde se guarda el texto
int i;

void setup()
{
  Serial.begin(9600);
  Serial.println("GSM Shield testing.");
    //Inicializamos el boundrate en 4800
    //Probamos que la shield gsms sms este ready o no
    if (gsm.begin(4800)) 
    {
        Serial.println("\nstatus=READY"); //Indica que la shield gsm sms esta lista
        started=true;
        
    } 
    else 
        Serial.println("\nstatus=IDLE"); //Indica que la shield gsm sms no esta lista ya sea por compatibilidad, mala conexion o falta de energia.

}
void loop()
{
      //Leemos los valores del sensor y los guardamos en una variable values
      // conectado al pin analogo A0
      int values= analogRead(A0);
      
      if (values>0){
        // Convertimos los datos a decibeles
         long x=10*values;
         long y=100*x;
         double z=log10(y);
         double decibeles=10*z;
         
         // imprimimos los datos que arroja el sensor
         Serial.print(values);
         Serial.print("    ");      
         // imprimimos los decibeles
         Serial.println(decibeles);
        delay(500);
        
        if (started){
          
          if(decibeles>=55){
          
            //declaramos el numero de telefono y el mensaje que se desea enviar
          sms.SendSMS("1234567890", "sms a enviar");
          }
        }
      }    
}
