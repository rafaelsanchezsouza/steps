// variaveis ajustaveis
int vel = 9; //determina velocidade geral do sitema; valores de 1 a 10
int vel1 = 50; //velocidade motor 1; valores acima de 8
int vel2 = 10; //velocidade motor 2; valores acima de 8
int vel3 = 10; //velocidade motor 3; valores acima de 8
int vel4 = 60; //velocidade motor 4; valores acima de 8
int vel5 = 70; //velocidade motor 5; valores acima de 8
int vel6 = 30; //velocidade motor 6; valores acima de 8
int vel7 = 30; //velocidade motor 7; valores acima de 8
int vel8 = 25; //velocidade motor 8; valores acima de 8
int loops_step_1 = 15000;
int loops_step_2 = 32000;

// referencias
int para_motor_1 = 40;
int para_motor_2 = 1000;
int para_motor_3 = 1000;
int liga_motor_4 = 200; //referente ao numero de passos dado pelo motor2
int extra_motor_4 = 40; //referente ao avanco extra que o motor 4 da antes de voltar
int para_motor_5 = 40;
int para_motor_6 = 40;
int liga_motor_7 = 2000;
int para_motor_8 = 40;

// variaveis auxiliares (nao mexer)
int atraso = (40000-3500*vel)/100;
int vel_cont = vel2;
static int cont1 = vel1;
static int cont2 = vel2;
static int cont3 = vel3;
static int cont4 = vel4;
static int cont5 = vel5;
static int cont6 = vel6;
static int cont7 = vel7;
static int cont8 = vel8;
static int cont = vel_cont;
int contador;
int passos1 = 0;
int passos2 = 0;
int passos3 = 0;
int passos4 = 0;
int passos5 = 0;
int passos6 = 0;
int passos7 = 0;
int passos8 = 0;

//PINAGEM

// botao para ativar motores
int pinoBotao = 38;
int botao = 0;

// declaracao da variavel sensor 
volatile int sensor = LOW;

// stepper 1
int pinoDirecao1 = 22;
int pinoPassos1 = 3;

// stepper 2
int pinoDirecao2 = 24;
int pinoPassos2 = 4;

// stepper 3
int pinoDirecao3 = 26;
int pinoPassos3 = 5;

// stepper 4
int pinoDirecao4 = 28;
int pinoPassos4 = 6;

// stepper 5
int pinoDirecao5 = 30;
int pinoPassos5 = 7;

// stepper 6
int pinoDirecao6 = 32;
int pinoPassos6 = 8;

// stepper 7
int pinoDirecao7 = 34;
int pinoPassos7 = 9;

// stepper 8
int pinoDirecao8 = 36;
int pinoPassos8 = 10;

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
  pinMode(2,OUTPUT);

  attachInterrupt(0,sensor_1, RISING);
}

void loop(){
  botao = digitalRead(pinoBotao);

  if (botao == HIGH) {
    //    step_um(false,pinoDirecao4, pinoPassos4, 200, atraso);

    step_1(
    false, pinoDirecao1, pinoPassos1, 
    true, pinoDirecao2, pinoPassos2, 
    false, pinoDirecao3, pinoPassos3, 
    false, pinoDirecao4, pinoPassos4, 
    true, pinoDirecao5, pinoPassos5, 
    true, pinoDirecao6, pinoPassos6, 
    true, pinoDirecao7, pinoPassos7, 
    true, pinoDirecao8, pinoPassos8,
    loops_step_1, 
    atraso);

    step_2(
    false, pinoDirecao1, pinoPassos1, 
    true, pinoDirecao2, pinoPassos2, 
    false, pinoDirecao3, pinoPassos3, 
    false, pinoDirecao4, pinoPassos4, 
    true, pinoDirecao5, pinoPassos5, 
    true, pinoDirecao6, pinoPassos6, 
    true, pinoDirecao7, pinoPassos7, 
    true, pinoDirecao8, pinoPassos8,
    loops_step_2, 
    atraso);
    
    Serial.println("passos4 = ");
    Serial.println(passos4);
    
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
  passos1= 0;
  passos2= 0;
  passos3= 0;
  passos4= 0;
  passos5= 0;
  passos6= 0;
  passos7= 0;
  passos8= 0;
  contador= 0;
  sensor = LOW;
  //  passos4=281;
  delay(50);

  for(int i=0;i<loops;i++){

    if((cont2==0)&&(passos2<1201)){
      digitalWrite(pinoPassos2,HIGH);
    }

    if((cont3==0)&&(passos2<1201)){
      digitalWrite(pinoPassos3,HIGH);
    } 

    if((cont4==0)&&(passos2>100)&&(passos4<200+extra_motor_4+1)){
      digitalWrite(pinoPassos4,HIGH);
    }

    if((cont4==0)&&(passos4>200+extra_motor_4)&&(passos4<200+2*(extra_motor_4+1))){
      digitalWrite(pinoDirecao4,!dir4);
      digitalWrite(pinoPassos4, HIGH);
      digitalWrite(pinoDirecao4,!dir4);
    }
    
    if((cont5==0)&&((passos4>200)&&(passos5<100+1))){
      digitalWrite(pinoPassos5, HIGH);
    }

    if((cont5==0)&&((passos6>200)&&(passos5<200))){
      digitalWrite(pinoPassos5, HIGH);
    }    
    
    if((cont6==0)&&(passos5>100)&&(passos6<200+1)){
      digitalWrite(pinoPassos6, HIGH);
    }
    
    if(cont==0){
      contador++;
    }

    delayMicroseconds(atraso);

    if(cont2){
      cont2--;
    }
    else{
      if((passos2<1201)){
        digitalWrite(pinoPassos2, LOW);
        passos2++;
        cont2 = vel2;
      }
    }    
    if(cont3){
      cont3--;
    }
    else{
      if(passos2<1201){
        digitalWrite(pinoPassos3, LOW);
        passos3++;
        cont3 = vel3;
      }
    } 

    if(cont4){
      cont4--;
    }
    else{
      if((passos2>100)&&(passos4<200+extra_motor_4+1)){
        digitalWrite(pinoPassos4, LOW);
        passos4++;
        cont4 = vel4;
      }
      if((passos4>200+extra_motor_4)&&(passos4<200+2*(extra_motor_4+1))){
        digitalWrite(pinoDirecao4,!dir4);
        digitalWrite(pinoPassos4, LOW);
        digitalWrite(pinoDirecao4,!dir4);
        passos4++;
        cont4 = vel4;        
      } 
    }
    
    if(cont5){
      cont5--;
    }
    else{
      if((passos4>200)&&(passos5<100+1)){
        digitalWrite(pinoPassos5, LOW);
        passos5++;
        cont5 = vel5;
      }
      if((passos6>200)&&(passos5<200)){
        digitalWrite(pinoPassos5, LOW);
        passos5++;
        cont5 = vel5;        
      } 
    }

    if(cont6){
      cont6--;
    }
    else{
      if((passos5>100)&&(passos6<200+1)){
        digitalWrite(pinoPassos6, LOW);
        passos6++;
        cont6 = vel6;
      }
    }

    if(cont){
      cont--;
    }
    else{
      cont = vel_cont;
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
  //  passos1 = 0;
  passos2 = 0;
  passos3 = 0;
  //  passos4 = 0;
  //  passos5 = 0;
  //  passos6 = 0;
  //  passos7 = 0;
  //  passos8 = 0;
  //  sensor = LOW;
  delay(1);

  for(int i=0;i<loops;i++){

    if((cont2==0)&&(passos2<para_motor_2+1)){
      digitalWrite(pinoPassos2,HIGH);
    }

    if((cont3==0)&&(passos3<para_motor_3+1)){
      digitalWrite(pinoPassos3,HIGH);
    }

    if((cont4==0)&&(passos2>100)&&(passos4<200+extra_motor_4+1)){
      digitalWrite(pinoPassos4,HIGH);
    }

    if((cont4==0)&&(passos4>200+extra_motor_4)&&(passos4<200+2*(extra_motor_4+1))){
      digitalWrite(pinoDirecao4,!dir4);
      digitalWrite(pinoPassos4, HIGH);
      digitalWrite(pinoDirecao4,!dir4);
    } 

    if((cont5==0)&&((passos4>200)&&(passos5<100+1))){
      digitalWrite(pinoPassos5, HIGH);
    }

    if((cont5==0)&&((passos6>200)&&(passos5<200))){
      digitalWrite(pinoPassos5, HIGH);
    }

    if((cont6==0)&&(passos5>100)&&(passos6<200+1)){
      digitalWrite(pinoPassos6, HIGH);
    }

    if((cont7==0)&&(contador>liga_motor_7)&&(passos7<200+1)){
      digitalWrite(pinoPassos7, HIGH);
    }

    if((cont8==0)&&(passos5>199)&&(passos8<200+1)){
      digitalWrite(pinoPassos8, HIGH);
    }
    
    if((cont1==0)&&(passos8>110)&&(passos1<para_motor_1+1)){
      digitalWrite(pinoPassos1,HIGH);
    }

    if(cont==0){
      contador++;
    }

    delayMicroseconds(atraso);

    if(cont2){
      cont2--;
    }
    else{
      if((passos2<para_motor_2+1)){
        digitalWrite(pinoPassos2, LOW);
        passos2++;
        cont2 = vel2;
      }
    }    
    if(cont3){
      cont3--;
    }
    else{
      if((passos3<para_motor_3+1)){
        digitalWrite(pinoPassos3, LOW);
        passos3++;
        cont3 = vel3;
      }
    }

    if(cont4){
      cont4--;
    }
    else{
      if((passos2>100)&&(passos4<200+extra_motor_4+1)){
        digitalWrite(pinoPassos4, LOW);
        passos4++;
        cont4 = vel4;
      }
      if((passos4>200+extra_motor_4)&&(passos4<200+2*(extra_motor_4+1))){
        digitalWrite(pinoDirecao4,!dir4);
        digitalWrite(pinoPassos4, LOW);
        digitalWrite(pinoDirecao4,!dir4);
        passos4++;
        cont4 = vel4;        
      } 
    }

    if(cont5){
      cont5--;
    }
    else{
      if((passos4>200)&&(passos5<100+1)){
        digitalWrite(pinoPassos5, LOW);
        passos5++;
        cont5 = vel5;
      }
      if((passos6>200)&&(passos5<200)){
        digitalWrite(pinoPassos5, LOW);
        passos5++;
        cont5 = vel5;        
      } 
    }

    if(cont6){
      cont6--;
    }
    else{
      if((passos5>100)&&(passos6<200+1)){
        digitalWrite(pinoPassos6, LOW);
        passos6++;
        cont6 = vel6;
      }
    }

    if(cont7){
      cont7--;
    }
    else{
      if((contador>liga_motor_7)&&(passos7<200+1)){
        digitalWrite(pinoPassos7, LOW);
        passos7++;
        cont7 = vel7;
      }
    }

    if(cont8){
      cont8--;
    }
    else{
      if((passos5>199)&&(passos8<200+1)){
        digitalWrite(pinoPassos8, LOW);
        passos8++;
        cont8 = vel8;
      }
    }        

    if(cont1){
      cont1--;
    }
    else{
      if((passos8>110)){
        digitalWrite(pinoPassos1, LOW);
        passos1++;
        cont1 = vel1;
      }
    }

    if(cont){
      cont--;
    }
    else{
      cont = vel_cont;
    } 

    delayMicroseconds(atraso);    
  }
}


