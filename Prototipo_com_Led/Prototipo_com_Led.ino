#include <Ultrasonic.h>                                                                                        //INCLUSÃO DA BIBLIOTECA NECESSÁRIA PARA FUNCIONAMENTO DOS SENSORES ULTRASSONICOS
#include <Wire.h>                                                                                                //INCLUSÃO DA BIBLIOTECA NECESSÁRIA PARA FUNCIONAMENTO DO I2E                                                                                       //INCLUSÃO DA BIBLIOTECA NECESSÁRIA PARA FUNCIONAMENTO DO SENSOR LASER
#include <VL53L0X.h>      
 
const int echoPin = 2;                                                                                         //PINO DIGITAL UTILIZADO PELO HC-SR04 ECHO FRENTE
const int trigPin = 3;                                                                                         //PINO DIGITAL UTILIZADO PELO HC-SR04 TRIG FRENTE
const int echoPin2 = 4;                                                                                        //PINO DIGITAL UTILIZADO PELO HC-SR04 ECHO TRÁS
const int trigPin2 = 7;                                                                                        //PINO DIGITAL UTILIZADO PELO HC-SR04 TRIG TRÁS
const int echoPin3 = 13;                                                                                       //PINO DIGITAL UTILIZADO PELO HC-SR04 ECHO LATERAL
const int trigPin3 = 12;                                                                                       //PINO DIGITAL UTILIZADO PELO HC-SR04 TRIG LATERAL
VL53L0X sensor;   

int XIS = 0;                                                                                                   //DEFINIÇÃO DA VARIÁVEL PARA DECOBRIR O X DO JOYSTICK
int YPS = 0;                                                                                                   //DEFINIÇÃO DA VARIÁVEL PARA DECOBRIR O Y DO JOYSTICK


Ultrasonic ultrasonic(trigPin,echoPin);                                                                        //SENSOR FRENTE
Ultrasonic ultrasonic2(trigPin2,echoPin2);                                                                     //SENSOR TRÁS
Ultrasonic ultrasonic3(trigPin3,echoPin3);                                                                     //SENSOR LATERAL
 
int distancia1, distancia2, distancia3, distancia4;                                                                        //VARIÁVEL DISTANCIA DO TIPO INTEIRO
 
void setup(){
  pinMode(6, OUTPUT);                                                                                          //PINO QUE ENVIA A RESPOSTA DO JOYSTICK EM X
  pinMode(5, OUTPUT);                                                                                          //PINO QUE ENVIA A RESPOSTA DO JOYSTICK EM Y
  pinMode(A0, INPUT);                                                                                          //PINO QUE RECEBE O X DO JOYSTICK
  pinMode(A1, INPUT);                                                                                          //PINO QUE RECEBE O X DO JOYSTICK
  pinMode(echoPin, INPUT);                                                                                     //DEFINE O PINO COMO ENTRADA (RECEBE)
  pinMode(trigPin, OUTPUT);                                                                                    //DEFINE O PINO COMO SAIDA (ENVIA)
  Serial.begin(9600);                                                                                          //INICIALIZA A PORTA SERIAL

Wire.begin();
  sensor.setTimeout(500);
  if (!sensor.init())
  {
    Serial.println("Failed to detect and initialize sensor!");
    while (1) {}
  }
  sensor.startContinuous();            
}
  
void loop(){
  distancia1 = (ultrasonic.Ranging(CM));                                                                       //VARIÁVEL GLOBAL RECEBE O VALOR DA DISTÂNCIA MEDIDA FRENTE
  distancia2 = (ultrasonic2.Ranging(CM));                                                                      //VARIÁVEL GLOBAL RECEBE O VALOR DA DISTÂNCIA MEDIDA TRÁS  
  distancia3 = (ultrasonic3.Ranging(CM));                                                                      //VARIÁVEL GLOBAL RECEBE O VALOR DA DISTÂNCIA MEDIDA LATERAL
  distancia4 = sensor.readRangeContinuousMillimeters();
  while(distancia4<210 || distancia4>800){                                                                    //CASO A DISTÂNCIA MEDIDA DO LASER FOR MENOR QUE 600 E MAIOR QUE 1050 FAÇA ESTE LAÇO
    distancia4 = sensor.readRangeContinuousMillimeters();                                                      //ATUALIZAR VALOR DA DISTÂNCIA DO LASER
    Serial.print("Distancia Laser ");                                                                          //IMPRIME O TEXTO NO MONITOR SERIAL
    Serial.print(distancia4);                                                                                  //IMPRIME NO MONITOR SERIAL A DISTÂNCIA MEDIDA
    Serial.println("mm");
    XIS= map(analogRead(A1),0,1023, 0 ,100);                                                                    //VERIFICAR O VALOR EM X DO JOYSTICK
    YPS= map(analogRead(A0),0,1023, 0 ,100);                                                                    //VERIFICAR O VALOR EM Y DO JOYSTICK
    XIS = 50;                                                                                                  //MUDAR O VALOR EM X DO JOYSTICK PARA 50, OU SEJA PARADO
    YPS = 50;                                                                                                  //MUDAR O VALOR EM Y DO JOYSTICK PARA 50, OU SEJA PARADO
    analogWrite(5,YPS);                                                                                        //ESCREVER O VALOR DE Y NA PORTA 5
    analogWrite(6,XIS);                                                                                        //ESCREVER O VALOR DE X NA PORTA 6
    YPS= map(analogRead(A0),0,1023, 0 ,100);                                                                    //VERIFICAR O VALOR EM Y DO JOYSTICK
    if(YPS<50){                                                                                                //CASO O USUÁRIO COLOQUE O JOYSTICK PARA TRÁS PARA DAR RÉ
      YPS= map(analogRead(A0),0,1023, 0 ,100);                                                                  //ATUALIZAR NOVAMENTE O Y
      analogWrite(5,YPS);                                                                                      //ESCREVER O VALOR DE Y NA PORTA 5
      Serial.println(YPS);
    }
  }
  while(distancia1<=70 && distancia1>0 && distancia1<distancia2 && distancia1!=0 && distancia2!=0){            //LAÇO PARA CONDIÇÃO DO SENSOR 1 
    Serial.print("Distancia ");                                                                                //IMPRIME O TEXTO NO MONITOR SERIAL
    Serial.print(distancia1);                                                                                  //IMPRIME NO MONITOR SERIAL A DISTÂNCIA MEDIDA
    Serial.println("cm");                                                                                      //IMPRIME O TEXTO NO MONITOR SERIAL
    distancia1 = (ultrasonic.Ranging(CM));                                                                     //VARIÁVEL GLOBAL ATUALIZA O VALOR DA DISTÂNCIA MEDIDA
    distancia2 = (ultrasonic2.Ranging(CM));
    XIS= map(analogRead(A1),0,1023, 0 ,100);
    YPS= map(analogRead(A0),0,1023, 0 ,100); 
    if(distancia1<=22 && YPS>50){
      YPS=50;
      analogWrite(5,YPS);
      Serial.println(YPS);
    }
    else if(distancia1<=30 && YPS>50){
      YPS=55;
      analogWrite(5,YPS);
      Serial.println(YPS);
    }
    else if(distancia1<=40 && YPS>50){
      YPS=58;
      analogWrite(5,YPS);
      Serial.println(YPS);
    }
    else if(distancia1<=50 && YPS>50){
      YPS=60;
      analogWrite(5,YPS);
      Serial.println(YPS);
    }
    else if(distancia1<=60 && YPS>50){
      YPS=70;
      analogWrite(5,YPS);
      Serial.println(YPS);
    }
    else if(distancia1<=70 && YPS>50){
      YPS=80;
      analogWrite(5,YPS);
      Serial.println(YPS);
    }
    if(YPS<49){
      analogWrite(5,YPS);
      Serial.println(YPS);
    }
    if(distancia1>30 && XIS!=50){
      distancia3 = (ultrasonic3.Ranging(CM));                                                                      //VARIÁVEL GLOBAL RECEBE O VALOR DA DISTÂNCIA MEDIDA LATERAL
      if(distancia3>50){
           analogWrite(6,XIS);
           Serial.println(XIS);
      }
    }
  }
   while(distancia2<=75 && distancia2>0 && distancia2<distancia1 && distancia1!=0 && distancia2!=0){             //LAÇO PARA CONDIÇÃO DO SENSOR 2
    Serial.print("Distancia2 ");                                                                                 //IMPRIME O TEXTO NO MONITOR SERIAL
    Serial.print(distancia2);                                                                                    //IMPRIME NO MONITOR SERIAL A DISTÂNCIA MEDIDA
    Serial.println("cm");                                                                                        //IMPRIME O TEXTO NO MONITOR SERIAL
    distancia1 = (ultrasonic.Ranging(CM));                                                                       //VARIÁVEL GLOBAL RECEBE O VALOR DA DISTÂNCIA MEDIDA FRENTE
    distancia2 = (ultrasonic2.Ranging(CM));                                                                      //VARIÁVEL GLOBAL RECEBE O VALOR DA DISTÂNCIA MEDIDA TRÁS  
    XIS= map(analogRead(A1),0,1023, 0 ,100);
    YPS= map(analogRead(A0),0,1023, 0 ,100); 
    if(distancia2<=40 && YPS<50){
      YPS=50;
      analogWrite(5,YPS);
      Serial.println(YPS);
    }
    else if(distancia2<=45 && YPS<50){
      YPS=45;
      analogWrite(5,YPS);
      Serial.println(YPS);
    }
    else if(distancia2<=50 && YPS<50){
      YPS=42;
      analogWrite(5,YPS);
      Serial.println(YPS);
    }
    else if(distancia2<=60 && YPS<50){
      YPS=35;
      analogWrite(5,YPS);
      Serial.println(YPS);
    }
    else if(distancia2<=70 && YPS<50){
      YPS=25;
      analogWrite(5,YPS);
      Serial.println(YPS);
    }
    else if(distancia2<=75 && YPS<50){
      YPS=15;
      analogWrite(5,YPS);
      Serial.println(YPS);
    }
    if(YPS>50){
      analogWrite(5,YPS);
      Serial.println(YPS);
    }
    if(distancia2>30 && XIS!=50){
      distancia3 = (ultrasonic3.Ranging(CM));                                                                      //VARIÁVEL GLOBAL RECEBE O VALOR DA DISTÂNCIA MEDIDA LATERAL
      if(distancia3>50){
           analogWrite(6,XIS);
           Serial.println(XIS);
      }
    }
  }
  while(distancia3<=50 && distancia3>0 && distancia1!=0 && distancia2!=0){    //LAÇO PARA CONDIÇÃO DO SENSOR 3
    Serial.print("Distancia3 ");                                                                                 //IMPRIME O TEXTO NO MONITOR SERIAL
    Serial.print(distancia3);                                                                                    //IMPRIME NO MONITOR SERIAL A DISTÂNCIA MEDIDA
    Serial.println("cm");                                                                                        //IMPRIME O TEXTO NO MONITOR SERIAL
    distancia1 = (ultrasonic.Ranging(CM));                                                                       //VARIÁVEL GLOBAL RECEBE O VALOR DA DISTÂNCIA MEDIDA FRENTE
    distancia2 = (ultrasonic2.Ranging(CM));                                                                      //VARIÁVEL GLOBAL RECEBE O VALOR DA DISTÂNCIA MEDIDA TRÁS  
    distancia3 = (ultrasonic3.Ranging(CM));                                                                      //VARIÁVEL GLOBAL RECEBE O VALOR DA DISTÂNCIA MEDIDA LATERAL
    XIS= map(analogRead(A1),0,1023, 0 ,100);
    YPS= map(analogRead(A0),0,1023, 0 ,100); 
    analogWrite(5,YPS);
    Serial.println(YPS);
    if(YPS>=85 && distancia3>=20 && distancia3!=0){
      if(XIS==50){
        analogWrite(5,YPS);
        Serial.println(YPS);
      }
      if(XIS<50){
        XIS=40;
        analogWrite(5,YPS);
        analogWrite(6,XIS);
        Serial.println(YPS);
        Serial.println(XIS);
      }
      else if(XIS>50){
        XIS=60;
        analogWrite(5,YPS);
        analogWrite(6,XIS);
        Serial.println(YPS);
        Serial.println(XIS);
      }
    }
    else if(distancia3<=50 && XIS!=50){
      XIS=50;
      analogWrite(6,XIS);
      Serial.println(XIS);
    }
   }
  XIS= map(analogRead(A1),0,1023, 0 ,100);                         
  analogWrite(6,XIS);
  YPS= map(analogRead(A0),0,1023, 0 ,100);
  analogWrite(5,YPS);
  Serial.println(XIS);
  Serial.println(YPS);
}
