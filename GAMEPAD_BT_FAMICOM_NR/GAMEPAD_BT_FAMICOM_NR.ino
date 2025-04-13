// Versión 0.1.0 GAMEPAD BT FAMICOM NovenRetro
// DEBE ESTAR INSTALADA LA VERSIÓN 2.0.11 DE PLACA ESP32 Y VERSIÓN 0.7.3 DE LIBRERÍA ESP32_BLE_Gamepad
#include <BleGamepad.h>

BleGamepad bleGamepad("FAMICOM BT GAMEPAD", "ESP32", 100);

// Pines asignados al mando Famicom
const int pinLed = 2;
const int pinArriba = 27;
const int pinAbajo = 14;
const int pinIzquierda = 12;
const int pinDerecha = 15;
const int pinBotonA = 26;
const int pinBotonB = 25;
const int pinStart = 33;
const int pinSelect = 32;

void setup() {
  Serial.begin(115200);
  bleGamepad.begin();

  pinMode(pinLed, OUTPUT);
  pinMode(pinArriba, INPUT_PULLUP);
  pinMode(pinAbajo, INPUT_PULLUP);
  pinMode(pinIzquierda, INPUT_PULLUP);
  pinMode(pinDerecha, INPUT_PULLUP);
  pinMode(pinBotonA, INPUT_PULLUP);
  pinMode(pinBotonB, INPUT_PULLUP);
  pinMode(pinStart, INPUT_PULLUP);
  pinMode(pinSelect, INPUT_PULLUP);
}

void loop() {
  if (bleGamepad.isConnected()) {
    // DIRECCIONALES (DPAD)
    uint8_t hatValue = HAT_CENTERED;

    if (digitalRead(pinArriba) == LOW) {
      if (digitalRead(pinIzquierda) == LOW) hatValue = HAT_UP_LEFT;
      else if (digitalRead(pinDerecha) == LOW) hatValue = HAT_UP_RIGHT;
      else hatValue = HAT_UP;
    } else if (digitalRead(pinAbajo) == LOW) {
      if (digitalRead(pinIzquierda) == LOW) hatValue = HAT_DOWN_LEFT;
      else if (digitalRead(pinDerecha) == LOW) hatValue = HAT_DOWN_RIGHT;
      else hatValue = HAT_DOWN;
    } else if (digitalRead(pinIzquierda) == LOW) {
      hatValue = HAT_LEFT;
    } else if (digitalRead(pinDerecha) == LOW) {
      hatValue = HAT_RIGHT;
    }

    bleGamepad.setHat(hatValue);

    // BOTONES
    actualizarBoton(pinBotonA, BUTTON_1);
    actualizarBoton(pinBotonB, BUTTON_2);
    actualizarBoton(pinStart, BUTTON_3);    // ← START
    actualizarBoton(pinSelect, BUTTON_4);   // ← SELECT

    digitalWrite(pinLed, HIGH);
  } else {
    digitalWrite(pinLed, millis() % 1000 < 500 ? HIGH : LOW);
  }

  delay(10);
}

void actualizarBoton(int pin, int boton) {
  if (digitalRead(pin) == LOW) {
    bleGamepad.press(boton);
  } else {
    bleGamepad.release(boton);
  }
}
