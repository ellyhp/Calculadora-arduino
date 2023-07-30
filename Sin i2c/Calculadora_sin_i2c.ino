#include <Keypad.h>
#include <Wire.h>
#include <LiquidCrystal.h>

LiquidCrystal lcd(13, 12, 11, 10, 9, 8);

long first = 0;
long second = 0;
double total = 0;

char customKey;
const byte ROWS = 4;
const byte COLS = 4;

char keys[ROWS][COLS] = {
  {'1','2','3','+'},
  {'4','5','6','-'},
  {'7','8','9','*'},
  {'C','0','=','/'}
};
byte rowPins[ROWS] = {7,6,5,4}; // Conectar a los pines de fila del teclado
byte colPins[COLS] = {3,2,1,0}; // Conectar a los pines de columna del teclado

// Inicializar una instancia de la clase Keypad
Keypad customKeypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

void setup()
{
  lcd.begin(16, 2); // Iniciar la pantalla LCD
  for (int i = 0; i <= 3; i++); // No es necesario el punto y coma aquí, podría eliminarse
  lcd.setCursor(0, 0);
  lcd.print("Calculadora");
  delay(4000); // Esperar 4 segundos antes de continuar
  lcd.clear();
  lcd.setCursor(0, 0);
}

void loop()
{
  // Obtener la tecla presionada
  customKey = customKeypad.getKey();
  switch (customKey)
  {
    case '0' ... '9': // Si se presionan números del 0 al 9, se irá formando el primer número
      lcd.setCursor(0, 0);
      first = first * 10 + (customKey - '0');
      lcd.print(first);
      break;

    case '+': // Si se presiona el operador de suma
      first = (total != 0 ? total : first);
      lcd.setCursor(0, 1);
      lcd.print("+");
      second = SecondNumber(); // Obtener el segundo número ingresado
      total = first + second; // Realizar la suma
      lcd.setCursor(0, 3);
      lcd.print(total); // Mostrar el resultado
      first = 0, second = 0; // Reiniciar los valores para el próximo uso
      break;

    case '-': // Si se presiona el operador de resta
      first = (total != 0 ? total : first);
      lcd.setCursor(0, 1);
      lcd.print("-");
      second = SecondNumber(); // Obtener el segundo número ingresado
      total = first - second; // Realizar la resta
      lcd.setCursor(0, 3);
      lcd.print(total); // Mostrar el resultado
      first = 0, second = 0; // Reiniciar los valores para el próximo uso
      break;

    case '*': // Si se presiona el operador de multiplicación
      first = (total != 0 ? total : first);
      lcd.setCursor(0, 1);
      lcd.print("*");
      second = SecondNumber(); // Obtener el segundo número ingresado
      total = first * second; // Realizar la multiplicación
      lcd.setCursor(0, 3);
      lcd.print(total); // Mostrar el resultado
      first = 0, second = 0; // Reiniciar los valores para el próximo uso
      break;

    case '/': // Si se presiona el operador de división
      first = (total != 0 ? total : first);
      lcd.setCursor(0, 1);
      lcd.print("/");
      second = SecondNumber(); // Obtener el segundo número ingresado
      lcd.setCursor(0, 3);

      // Verificar si el divisor es cero para evitar la división por cero
      second == 0 ? lcd.print("Invalido") : total = (float)first / (float)second;

      lcd.print(total); // Mostrar el resultado
      first = 0, second = 0; // Reiniciar los valores para el próximo uso
      break;

    case 'C': // Si se presiona 'C' (borrar/cancelar), reiniciar la calculadora
      total = 0;
      lcd.clear();
      break;
  }
}

long SecondNumber()
{
  while (1)
  {
    customKey = customKeypad.getKey();
    if (customKey >= '0' && customKey <= '9')
    {
      second = second * 10 + (customKey - '0');
      lcd.setCursor(0, 2);
      lcd.print(second);
    }

    if (customKey == '=') break; // Si se presiona '=', se ha ingresado el segundo número
  }
  return second;
}
