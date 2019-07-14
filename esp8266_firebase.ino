#include <ESP8266WiFi.h>
#include <FirebaseArduino.h>

#define WIFI_SSID "xxxxxxxxxxxxxxxxxxxxxxx"
#define WIFI_PASSWORD "xxxxxxxxxxxxxxxxxxxxxxx"

#define FIREBASE_HOST  "xxxxxxxxxxxxxxxxxxxxxxxxxxxx"
#define FIREBASE_AUTH  "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx




#define  PULSADOR1   2
#define  RELE1       0
int StatusPulsador1 ;
int StatusRele = 0;
int ledStatus ;

//---------------------------prototipoi de função -----------------------
void FUNCAO_PULSADOR1();


//--------------------------- fim prototipoi de função -----------------------

void setup() 
{
  Serial.begin(115200);

  // connect to wifi.
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("connecting");
  while (WiFi.status() != WL_CONNECTED) 
  {
    Serial.print(".");
    delay(500);
  }
  Serial.println();
  Serial.print("connected: ");
  Serial.println(WiFi.localIP());


  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  pinMode(RELE1,OUTPUT);
  digitalWrite(RELE1, HIGH);

}



void loop() 
{
  ledStatus = Firebase.getInt("placateste");
  //int pulsador = Firebase.getInt("");

    StatusRele = digitalRead(RELE1);
    Firebase.setInt("stausplacateste", StatusRele);

    FUNCAO_PULSADOR1();

    delay(200);



    switch (ledStatus) 
    {
        case 1:
          Serial.println(ledStatus);
          digitalWrite(RELE1, HIGH);
          delay(100);
          break;

        case 0:
          Serial.println(ledStatus);
          digitalWrite(RELE1, LOW);
          delay(100);
          break;

        default:
        Serial.println("Diferente de 0 e 1");
          
    }


}


// funções ----------------------------------------------------------------------------------------------

/// ---------------------------- função pulsador --------------------------------------------------------

void FUNCAO_PULSADOR1() {



  if ( (digitalRead(PULSADOR1) == LOW)) 
  {

    if (StatusPulsador1 == LOW) 
    {
      //digitalWrite(RELE1, !digitalRead(RELE1));
     // delay(300);

      ledStatus = Firebase.getInt("placateste");

      delay(100);

      switch (ledStatus) 
    {
        case 1:
          Serial.println("Rele pulsador  0");
          Firebase.setInt("placateste", 0);
          delay(100);
          break;

        case 0:
           Serial.println("Rele pulsador  1");
          Firebase.setInt("placateste", 1);
          delay(100);
          break;
       
    
     }
    }
  }
}

/// ----------------------------  fim função pulsador --------------------------------------------------------
