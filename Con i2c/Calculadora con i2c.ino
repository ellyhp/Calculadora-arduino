#include <Keypad.h>
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

// Inicializar la pantalla LCD
LiquidCrystal_I2C lcd(0x27, 20, 4);

long first = 0;    // Variable para almacenar el primer número
long second = 0;   // Variable para almacenar el segundo número
double total = 0;  // Variable para almacenar el resultado de la operación

char customKey;    // Variable para almacenar el botón presionado en el teclado

const byte ROWS = 4;  // Número de filas en el teclado
const byte COLS = 4;  // Número de columnas en el teclado

// Definir la disposición de las teclas en el teclado
char keys[ROWS][COLS] = {
  {'=', '/', '0', 'C'},
  {'9', '*', '8', '8'},
  {'6', '-', '5', '4'},
  {'3', '+', '2', '1'}
}; // tu puedes modificar esta opcion dependindo tu teclado
//char keys[ROWS][COLS] = {
//  {'1','2','3','+'},
//  {'4','5','6','-'},
//  {'7','8','9','*'},
//  {'C','0','=','/'}
// };



byte rowPins[ROWS] = {4, 5, 6, 7};   // Pines utilizados para las filas del teclado
byte colPins[COLS] = {8, 9, 10, 11}; // Pines utilizados para las columnas del teclado

// Inicializamos el teclado
Keypad customKeypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

void setup() {
  // Inicializar la pantalla LCD
  lcd.init();
  lcd.backlight();
  lcd.begin(16, 2);

  // Mostrar mensaje de bienvenida en la pantalla LCD
  lcd.setCursor(3, 0);
  lcd.print("Calculadora");

  delay(4000);

  // Limpiar la pantalla y posicionar el cursor en la esquina superior izquierda
  lcd.clear();
  lcd.setCursor(0, 0);
}

void loop() {
  customKey = customKeypad.getKey();

  // Procesar el botón presionado en el teclado
  switch(customKey) 
  {
    case '0' ... '9': // Si se presiona un dígito, se agrega al número actual
      lcd.setCursor(0,0);
      first = first * 10 + (customKey - '0');
      lcd.print(first);
      break;

    case '+': // Si se presiona el botón de suma
      first = (total != 0 ? total : first);
      lcd.setCursor(0,1);
      lcd.print("+");
      second = SecondNumber(); // Obtener el segundo número ingresado
      total = first + second;  // Realizar la suma
      lcd.setCursor(0,1); // Colocar el cursor en la segunda columna
      lcd.print(total);   // Mostrar el resultado en la segunda columna
      first = 0, second = 0;   // Reiniciar los valores para el siguiente uso
      break;

    case '-': // Si se presiona el botón de resta
      first = (total != 0 ? total : first);
      lcd.setCursor(0,1);
      lcd.print("-");
      second = SecondNumber();
      total = first - second;  // Realizar la resta
      lcd.setCursor(0,1); // Colocar el cursor en la segunda columna
      lcd.print(total);   // Mostrar el resultado en la segunda columna
      first = 0, second = 0;
      break;

    case '*': // Si se presiona el botón de multiplicación
      first = (total != 0 ? total : first);
      lcd.setCursor(0,1);
      lcd.print("*");
      second = SecondNumber();
      total = first * second;  // Realizar la multiplicación
      lcd.setCursor(0,1); // Colocar el cursor en la segunda columna
      lcd.print(total);   // Mostrar el resultado en la segunda columna
      first = 0, second = 0;
      break;

    case '/': // Si se presiona el botón de división
      first = (total != 0 ? total : first);
      lcd.setCursor(0,1);
      lcd.print("/");
      second = SecondNumber();
      lcd.setCursor(0,1); // Colocar el cursor en la segunda columna

      // Verificar si el segundo número es cero para evitar división por cero
      second == 0 ? lcd.print("Invalid") : total = (float)first / (float)second;

      lcd.print(total);   // Mostrar el resultado en la segunda columna
      first = 0, second = 0;
      break;

    case 'C': // Si se presiona el botón de borrado (clear)
      total = 0;
      lcd.clear();
      break;
  }
}

// Función para obtener el segundo número ingresado
long SecondNumber()
{
  while( 1 )
  {
    customKey = customKeypad.getKey();
    if(customKey >= '0' && customKey <= '9')
    {
      second = second * 10 + (customKey - '0');
      lcd.setCursor(0,0); // Colocar el cursor en la primera columna
      lcd.print("        "); // Limpiar la primera columna antes de mostrar el número
      lcd.setCursor(0,1); // Colocar el cursor en la segunda columna
      lcd.print(second); // Mostrar el segundo número en la segunda columna
    }

    if(customKey == '=') break;
  }
 return second; 
}
