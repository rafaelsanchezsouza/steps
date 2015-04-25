// variaveis ajustaveis
int vel = 5; //determina velocidade geral do sitema; valores de 1 a 10
int vel1 = 10; //velocidade motor 1; valores acima de 8
int vel2 = 8; //velocidade motor 2; valores acima de 8
int vel3 = 10; //velocidade motor 3; valores acima de 8
int vel4 = 10; //velocidade motor 4; valores acima de 8
int vel5 = 10; //velocidade motor 5; valores acima de 8
int vel6 = 10; //velocidade motor 6; valores acima de 8
int vel7 = 10; //velocidade motor 7; valores acima de 8
int vel8 = 10; //velocidade motor 8; valores acima de 8

// variaveis auxiliares (nao mexer)
int atraso = (40000-3500*vel)/100;
int contador_1 = 0;
int contador_2 = 0;
static int cont_passos_1_high = 8;
static int cont_passos_1_low = 8;
static int cont_passos_2_high = 8;
static int cont_passos_2_low = 8;
int passos_temp1 = 0;
int passos_temp2 = 0;
int passos_temp3 = 0;
int passos_temp4 = 0;
int passos_temp5 = 0;
int passos_temp6 = 0;
int passos_temp7 = 0;
int passos_temp8 = 0;
static int cont1 = vel1;
static int cont2 = vel2;
static int cont3 = vel3;
static int cont4 = vel4;
static int cont5 = vel5;
static int cont6 = vel6;
static int cont7 = vel7;
static int cont8 = vel8;

// referencias
int para_motor_1 = 40;
int para_motor_2 = 1015;
int para_motor_3 = 1015;
int para_motor_4 = 40;
int para_motor_5 = 40;
int para_motor_6 = 40;
int para_motor_7 = 40;
int para_motor_8 = 40;

// botao para ligar motores
int pinoBotao = 38;
int botao = 0;

// declaracao da variavel sensor 
volatile int sensor = LOW;

// stepper 1
int pinoDirecao1 = 22;
int pinoPassos1 = 3;
int passos1 = 0;

// stepper 2
int pinoDirecao2 = 24;
int pinoPassos2 = 4;
int passos2 = 0;

// stepper 3
int pinoDirecao3 = 26;
int pinoPassos3 = 5;
int passos3 = 0;

// stepper 4
int pinoDirecao4 = 28;
int pinoPassos4 = 6;
int passos4 = 0;

// stepper 5
int pinoDirecao5 = 30;
int pinoPassos5 = 7;
int passos5 = 0;

// stepper 6
int pinoDirecao6 = 32;
int pinoPassos6 = 8;
int passos6 = 0;

// stepper 7
int pinoDirecao7 = 34;
int pinoPassos7 = 9;
int passos7 = 0;

// stepper 8
int pinoDirecao8 = 36;
int pinoPassos8 = 10;
int passos8 = 0;

void setup() {
  Serial.begin(9600);
  pinMode(pinoDirecao1, OUTPUT); 
  pinMode(pinoDirecao2, OUTPUT);
  pinMode(pinoDirecao3, OUTPUT);
  pinMode(pinoDirecao4, OUTPUT);
  pinMode(pinoDirecao5, OUTPUT);
  pinMode(pinoDirecao6, OUTPUT);
  pinMode(pinoDirecao7, OUTPUT);
  pinMode(pinoDirecao8, OUTPUT);
  pinMode(pinoPassos1, OUTPUT);
  pinMode(pinoPassos2, OUTPUT);
  pinMode(pinoPassos3, OUTPUT);
  pinMode(pinoPassos4, OUTPUT);
  pinMode(pinoPassos5, OUTPUT);
  pinMode(pinoPassos6, OUTPUT);
  pinMode(pinoPassos7, OUTPUT);
  pinMode(pinoPassos8, OUTPUT);
  pinMode(pinoBotao,INPUT);
  pinMode(2,INPUT);

  attachInterrupt(0,sensor_1, RISING);
}

void loop(){
  botao = digitalRead(pinoBotao);

  if (botao == HIGH) {
    //    step_um(false,pinoDirecao4, pinoPassos4, 200, atraso);

    step_1(
    false, pinoDirecao1, pinoPassos1, 
    false, pinoDirecao2, pinoPassos2, 
    true, pinoDirecao3, pinoPassos3, 
    false, pinoDirecao4, pinoPassos4, 
    true, pinoDirecao5, pinoPassos5, 
    true, pinoDirecao6, pinoPassos6, 
    true, pinoDirecao7, pinoPassos7, 
    true, pinoDirecao8, pinoPassos8,
    5000, 
    atraso);

//    Serial.println("Passos1 = ");
//    Serial.println(passos1);
//    
//    Serial.println("Passos2 = ");
//    Serial.println(passos2);

       passos_temp1=passos1;
       passos_temp2=passos2;
       passos_temp3=passos3;
       passos_temp4=passos4;
       passos_temp5=passos5;
       passos_temp6=passos6;
       passos_temp7=passos7;
       passos_temp8=passos8;
       
//    Serial.println("sensor = ");
//    Serial.println(sensor);    
    
       step_2(
       false, pinoDirecao1, pinoPassos1, 
       false, pinoDirecao2, pinoPassos2, 
       true, pinoDirecao3, pinoPassos3, 
       false, pinoDirecao4, pinoPassos4, 
       true, pinoDirecao5, pinoPassos5, 
       true, pinoDirecao6, pinoPassos6, 
       true, pinoDirecao7, pinoPassos7, 
       true, pinoDirecao8, pinoPassos8,
       5000, 
       atraso);

//    Serial.println("Passos1_2 = ");
//    Serial.println(passos1);
//    
//    Serial.println("Passos2_2 = ");
//    Serial.println(passos2);
//
//    Serial.println("Passos_temp1 = ");
//    Serial.println(passos_temp1);
//    
//    Serial.println("Passos_temp2 = ");
//    Serial.println(passos_temp2);
//    
//    Serial.println("cont1 = ");
//    Serial.println(cont1);
//    
//    Serial.println("cont2 = ");
//    Serial.println(cont2);

  }
}

void sensor_1(){
  sensor = HIGH;
}

// primeira etapa
void step_1(
boolean dir1, int pinoDirecao1, int pinoPassos1, 
boolean dir2, int pinoDirecao2, int pinoPassos2,
boolean dir3, int pinoDirecao3, int pinoPassos3, 
boolean dir4, int pinoDirecao4, int pinoPassos4,
boolean dir5, int pinoDirecao5, int pinoPassos5,
boolean dir6, int pinoDirecao6, int pinoPassos6,
boolean dir7, int pinoDirecao7, int pinoPassos7,
boolean dir8, int pinoDirecao8, int pinoPassos8,
int loops, 
int atraso
){

  digitalWrite(pinoDirecao1,dir1);
  digitalWrite(pinoDirecao2,dir2);
  digitalWrite(pinoDirecao3,dir3);
  digitalWrite(pinoDirecao4,dir4);
  digitalWrite(pinoDirecao5,dir5);
  digitalWrite(pinoDirecao6,dir6);
  digitalWrite(pinoDirecao7,dir7);
  digitalWrite(pinoDirecao8,dir8);
//  passos1= 0;
//  passos2= 0;
//  passos3= 0;
//  passos4= 0;
//  passos5= 0;
//  passos6= 0;
//  passos7= 0;
//  passos8= 0;
//  sensor = LOW;
  delay(50);

  for(int i=0;i<loops;i++){

    if((cont1==0)&&(passos1<400)){
      digitalWrite(pinoPassos1,HIGH);
    }
    
    if((cont2==0)&&(passos2<500)){
      digitalWrite(pinoPassos2,HIGH);
    }

    delayMicroseconds(atraso);

    if(cont1){
      cont1--;
      //      Serial.println("Entrou cont 1");
    }
    else{
      if((passos1<400)){
        digitalWrite(pinoPassos1, LOW);
        //        Serial.println("Entrou cont 1_2");        
        passos1++;
        cont1 = vel1;
      }
    }
    
    if(cont2){
      cont2--;
    }
    else{
      if((passos2<500)){
        digitalWrite(pinoPassos2, LOW);
        passos2++;
        cont2 = vel2;
      }
    }

    delayMicroseconds(atraso);

    // leitura pelo sensor de posicao 
    if(sensor == HIGH){
      sensor = LOW;
      i = loops;
    }     
  }
}

// segunda etapa
void step_2(
boolean dir1, int pinoDirecao1, int pinoPassos1, 
boolean dir2, int pinoDirecao2, int pinoPassos2,
boolean dir3, int pinoDirecao3, int pinoPassos3, 
boolean dir4, int pinoDirecao4, int pinoPassos4,
boolean dir5, int pinoDirecao5, int pinoPassos5,
boolean dir6, int pinoDirecao6, int pinoPassos6,
boolean dir7, int pinoDirecao7, int pinoPassos7,
boolean dir8, int pinoDirecao8, int pinoPassos8,
int loops, 
int atraso
){

  digitalWrite(pinoDirecao1,dir1);
  digitalWrite(pinoDirecao2,dir2);
  digitalWrite(pinoDirecao3,dir3);
  digitalWrite(pinoDirecao4,dir4);
  digitalWrite(pinoDirecao5,dir5);
  digitalWrite(pinoDirecao6,dir6);
  digitalWrite(pinoDirecao7,dir7);
  digitalWrite(pinoDirecao8,dir8);
  passos1 = 0;
  passos2 = 0;
  passos3 = 0;
  passos4 = 0;
  passos5 = 0;
  passos6 = 0;
  passos7 = 0;
  passos8 = 0;
  sensor = LOW;
  delay(200);

  for(int i=0;i<loops;i++){

//     Serial.println("ENTROU");
          
    if((cont1==0)&&(passos1<200)){
      digitalWrite(pinoPassos1,HIGH);
    }
    
    if((cont2==0)&&(passos2<300)){
      digitalWrite(pinoPassos2,HIGH);
    }

    delayMicroseconds(atraso);

    if(cont1){
      cont1--;
//      Serial.println("Entrou cont 1");
    }
    else{
      if((passos1<200)){
        digitalWrite(pinoPassos1, LOW);
//        Serial.println("Entrou cont 1_2");        
        passos1++;
        cont1 = vel1;
      }
    }
    
    if(cont2){
      cont2--;
    }
    else{
      if((passos2<300)){
        digitalWrite(pinoPassos2, LOW);
        passos2++;
        cont2 = vel2;
      }
    }

    delayMicroseconds(atraso);
   
  }
}
