/*
   Irrigação automática de plantas com Arduino
   @author Bruno Constantino
*/

// Define as Pinagens
#define pSinalAnalogico A0
#define pLedVermelho 5
#define pLedAmarelo 6
#define pLedVerde 7
#define pReleBomba 9

// Declara as variaveis utilizadas no programa
int valor_analogico;
int status_solo;
int ultimo_status_solo;

void setup()
{
  // Inicializa a Comunicação Serial
  Serial.begin(9600);

  // Define as pinagens. INPUT ou OUTPUT.
  pinMode(pSinalAnalogico, INPUT);
  pinMode(pLedVermelho, OUTPUT);
  pinMode(pLedAmarelo, OUTPUT);
  pinMode(pLedVerde, OUTPUT);
  pinMode(pReleBomba, OUTPUT);
}

void loop()
{
  // Le o valor do pino do sensor (A0)
  valor_analogico = analogRead(pSinalAnalogico);

  /////////////////////////////////////////////////
  // digitalWrite LED HIGH => Led Ligado
  // digitalWrite LED LOW => Led Desligado
  /////////////////////////////////////////////////
  // digitalWrite Relé Bomba HIGH => Relé Desligado
  // digitalWrite Relé Bomba LOW => Relé Ligado
  /////////////////////////////////////////////////

  // Solo umido, acende o led verde
  if (valor_analogico > 0 && valor_analogico < 400)
  {
    status_solo = 3; // 3 - Status: Solo umido
    apagaleds();
    digitalWrite(pLedVerde, HIGH); // Liga Led Verde
    digitalWrite(pReleBomba, HIGH);  // Desliga Bomba
  }

  // Solo com umidade moderada, acende led amarelo
  if (valor_analogico > 400 && valor_analogico < 800)
  {
    status_solo = 2; // 2 - Status: Umidade moderada
    apagaleds();
    digitalWrite(pLedAmarelo, HIGH); // Liga Led Amarelo
    digitalWrite(pReleBomba, HIGH); // Desliga Bomba
  }

  // Solo seco, acende led vermelho
  if (valor_analogico > 800 && valor_analogico < 1024)
  {
    status_solo = 1; // 1 - Status: Solo seco
    apagaleds();
    digitalWrite(pLedVermelho, HIGH); // Liga Led Vermelho
    digitalWrite(pReleBomba, LOW); // Liga Bomba
  }
  exibirConsole();
  delay(100);
}

void apagaleds()
{
  digitalWrite(pLedVermelho, LOW);
  digitalWrite(pLedAmarelo, LOW);
  digitalWrite(pLedVerde, LOW);
}


void exibirConsole()
{
  // Só exibe no Console Serial se tiver alteração no Status do Solo
  if (ultimo_status_solo != status_solo) {
    // Mostra o valor da porta analogica no serial monitor
    Serial.print("Porta analogica: ");
    Serial.print(valor_analogico);

    if ( status_solo == 1 ) {
      Serial.println(" Status: Solo seco");
    }
    if ( status_solo == 2 ) {
      Serial.println(" Status: Umidade moderada");
    }
    if ( status_solo == 3 ) {
      Serial.println(" Status: Solo umido");
    }
    ultimo_status_solo = status_solo;
  }
}
