# Grupo 16: TBD

## Tabla de Contenidos
- [Participantes](#-participantes)
- [Librerías Necesarias](#-librerías-necesarias)
- [Introducción](#-introducción)
- [Funcionamiento](#-funcionamiento)
- [Material Usado y Costes](#-material-usado-y-costes)
- [Diseño](#-diseño)
- [Estructura del Proyecto](#-estructura-del-proyecto)
- [Implementación](#-implementación)
- [Construcción](#-construcción)
- [Demostración](#-demostración)

## 👥 Participantes
<table>
  <thead>
    <th>Nombre</th>
    <th>Cuenta de la Universidad</th>
  </thead>
  <tbody>
    <tr>
      <td>Alfonso Rodríguez Gutt</td>
      <td>a.rodriguezgu.2022@alumnos.urjc.es</td>
    </tr>
    <tr>
      <td>Raúl Sánchez Benítez</td>
      <td>TBD</td>
    </tr>
    <tr>
      <td>Héctor González Viñas</td>
      <td>TBD</td>
    </tr>
    <tr>
      <td>Andrés Muñoz Muñoz</td>
      <td>TBD</td>
    </tr>
  </tbody>
</table>

## 📚 Librerías Necesarias
Para el desarrollo de este proyecto, se hicieron uso de algunas librerías externas que es probable que no estén instaladas por defecto en su IDE de Arduino, a continuación se mencionarán dichas librerías:
- Keypad.h
- LiquidCrystal_I2C.h
- IRremote.h
- TaskScheduler.h
- DHT.h
- Adafruit_Fingerprint.h
- Servo.h

## 🚀 Introducción
**BREVE INTRODUCCIÓN DEL PROYECTO**

## 🧠 Funcionamiento
El comportamiento de este sistema es bastante similar al de un sistema de seguridad común que se puede encontrar en el día a día. Para este proyecto, se decidió dividir el sistema en 2 bloques independientes, en uno se iba a encontrar toda la lógica y gestión de la caja fuerte, y en la otra, todo lo relacionado con la cámara y su pequeño sistema de refrigeración.

### 🔒 Bloque 1
Se dispone de una matriz de botones 4x4 en el que el usuario tendrá 3 intentos para introducir la contraseña correcta; en caso de agotar todos los intentos, el sistema se bloqueará, y solo el dueño de la caja fuerte podrá habilitar nuevamente el sistema. En caso contrario, el usuario deberá de validar su huella dactilar haciendo uso del lector de huellas, como último factor de autenticación antes de poder acceder a la caja fuerte; en donde tendrá un total de 5 intentos para colocar la huella correcta, en caso de agotar los intentos, el sistema se bloqueará. Una vez la huella sea reconocida, la caja fuerte se abrirá desplegando consigo un brazo mecánico que tendrá consigo el objeto que se guardó.

### 📷❄️ Bloque 2
Para añadir una mejor seguridad y proporcionar mayor información sobre lo que está sucediendo cuando un usuaro intenta interacturar con el sistema, se utilizó una cámara de seguridad cuyo funcionamiento es indepediente del bloque anterior. Esta cámara transmitirá en vivo y en directo todo lo que suceda mientras un usuario se encuentre interactuando con el sistema. Sin embargo, esta cámara tiene un ligero defecto y es el aumento de temperatura que puede sufrir mientras esté operativa, es por ello, que se decidió controlar dicha temperatura haciendo uso de un sensor de temperatura, que, tras superar una temperatura umbral, activaría un ventilador para enfriar un poco dicha cámara.

### 📡 Personalización mediante IR y Comunicación Serial
Como se explicó previamente, una vez que se agotan todos los intentos disponibles (ya sea para ingresar la contraseña o verificar la huella dactilar), el sistema entra en un estado de bloqueo permanente. Sin embargo, existe un mecanismo especial para que el propietario pueda desbloquearlo: el uso de un control remoto infrarrojo (IR). Al presionar un botón específico en el control, se envía una señal que es captada por un receptor IR, lo cual permite al sistema salir del estado de bloqueo.

Cabe destacar que la comunicación entre los componentes encargados de este proceso se realiza mediante `comunicación serial` entre dos microcontroladores Arduino. En este esquema, el Arduino `emisor` está conectado al receptor IR, siendo responsable de leer las señales del control remoto. Una vez capturada una señal, esta `se traduce a un caracter`, que es enviado a través del puerto serial al Arduino `receptor`. Este último, al recibir el caracter correspondiente, ejecuta la acción asociada, como por ejemplo desbloquear el sistema.

>[!IMPORTANT]
> Se considera que el mando IR únicamente lo tiene el dueño o alguien de confianza del dueño, en caso de pérdida o de que caiga en manos equivocadas, no nos hacemos responsables ya que cae de la responsabilidad del dueño quién tiene acceso a dicho control remoto.

>[!IMPORTANT]
> Hay funcionalidades del IR que su uso es únicamente para la presentación del proyecto, por cuestiones de agilizar la presentación. Es decir, dichas funcionalidades no estarán disponibles para el usuario final del sistema.

A continuación, se presenta una tabla mostrando de una forma mñás visual lo mencionado previamente:
<table>
  <thead>
    <th>Botón Pulsado</th>
    <th>Señal Correspondiente (Dec)</th>
    <th>Caracter que se Envía</th>
    <th>Acción que realiza el Arduino Receptor</th>
    <th>¿Uso único para la Presentación?</th>
  </thead>
  <tbody>
    <tr>
      <td>0</td>
      <td>22</td>
      <td>'R'</td>
      <td>Resetea el sistema, volviendo al estado inicial.</td>
      <td>NO</td>
    </tr>
    <tr>
      <td>1</td>
      <td>TBD</td>
      <td>TBD</td>
      <td>Omite la autenticación</td>
      <td>SI</td>
    </tr>
    <tr>
      <td>+</td>
      <td>TBD</td>
      <td>TBD</td>
      <td>Encender Ventilador</td>
      <td>SI</td>
    </tr>
  </tbody>
</table>

>[!IMPORTANT]
> Inicialmente, el apagado del ventilador también iba a ser controlado mediante IR. Sin embargo, una vez que el motor DC que alimenta el ventilador se encuentra encendido, el receptor IR deja de recibir correctamente las señales enviadas por el control remoto. Esto se debe al `ruido eléctrico`, también conocido como `interferencia electromagnética (EMI)` generado por el motor, el cual impide que las señales IR sean leídas de forma adecuada. Como resultado, se optó por controlar el apagado del ventilador mediante un `botón`.

A continuación, se muestra un diagrama de actividad que refleja el funcionamiento del sistema de una forma más visual, para así complementar con lo dicho previamente.

![Diagrama de Actividad Bloque 1](Proyecto/Diagrams/Others/DiagramaActividad1.jpg)

>[!NOTE]
> La transmisión en vivo ofrecida por la cámara, se puede ver introduciendo en cualquier navegador web, la IP que dicha cámara devuelve una vez esté correctamente operativa.

> [!WARNING]
> Es importante que usted tenga en cuenta que el ventilador que se usó para refrigerar la cámara, no es el más sofisticado ni potente que existe, es debido a ello que usted pueda apreciar que la temperatura de la cámara tarda un poco más de lo que debería en bajar.
> Además, también es importante que usted tenga en cuenta que debido a que la cámara no es la más sofisticada que hay, es posible que la transmisión se aprecie a una calidad inferior a la deseada o que la imagen se pueda congelar. Esto como ya digo, sucede por la calidad de la cámara.

## 📋 Material Usado y Costes
<table>
  <thead>
    <th>Componente</th>
    <th>Cantidad</th>
    <th>Precio (€)</th>
  </thead>
  <tbody>
    <tr>
      <td>Sensor de movimiento PIR</td>
      <td>1</td>
      <td>6.80</td>
    </tr>
    <tr>
      <td>Módulo de cámara ESP32-CAM</td>
      <td>1</td>
      <td>21.05</td>
    </tr>
    <tr>
      <td>Detector de huella dactilar</td>
      <td>1</td>
      <td>18.99</td>
    </tr>
    <tr>
      <td>Adaptador FTDI</td>
      <td>1</td>
      <td>12.98</td>
    </tr>
    <tr>
      <td>Pantalla LCD</td>
      <td>1</td>
      <td>0</td>
    </tr>
    <tr>
      <td>Interfaz I2C</td>
      <td>1</td>
      <td>0</td>
    </tr>
    <tr>
      <td>LEDs</td>
      <td>2</td>
      <td>0</td>
    </tr>
    <tr>
      <td>Matriz de botones 4x4</td>
      <td>1</td>
      <td>0</td>
    </tr>
    <tr>
      <td>Resistencias 1K</td>
      <td>4</td>
      <td>0</td>
    </tr>
    <tr>
      <td>Transistor NPN</td>
      <td>1</td>
      <td>0</td>
    </tr>
    <tr>
      <td>Buzzer pasivo</td>
      <td>1</td>
      <td>0</td>
    </tr>
    <tr>
      <td>Sensor de temperatura y humedad DHT11</td>
      <td>1</td>
      <td>0</td>
    </tr>
    <tr>
      <td>Diodo rectificador</td>
      <td>1</td>
      <td>0</td>
    </tr>
    <tr>
      <td>Ventilador</td>
      <td>1</td>
      <td>0</td>
    </tr>
    <tr>
      <td>Set IR</td>
      <td>1</td>
      <td>0</td>
    </tr>
    <tr>
      <td>Botón</td>
      <td>1</td>
      <td>0</td>
    </tr>
      <tr>
      <td><strong>TOTAL</strong></td>
      <td><strong>20</strong></td>
      <td><strong>59.82</strong></td>
    </tr>
  </tbody>
</table>

## 🧩 Diseño
En esta sección, se mostrarán las conexiones realizadas para llevar a cabo este proyecto.

>[!NOTE]
> Debido a que en Tinkercard no existen ciertos módulos, se mostrarán las conexiones respectivas a dichos módulos en una tabla.

### Bloque 1
![Conexiones Bloque 1](Proyecto/Diagrams/Connections/Bloque1.png)

>[!NOTE]
> También se proporciona el diagrama eléctrico de este bloque, si desea consultarlo, haga click en este [enlace](Proyecto/Diagrams/Electric/Bloque1.pdf)

### Sensor de Huella Dactilar
<table>
  <thead>
    <th>Origen</th>
    <th>Destino</th>
  </thead>
  <tbody>
    <tr>
      <td>5V</td>
      <td>5V</td>
    </tr>
    <tr>
      <td>TX</td>
      <td>Pin Digital 2</td>
    </tr>
    <tr>
      <td>RX</td>
      <td>Pin Digital 3</td>
    </tr>
    <tr>
      <td>GND</td>
      <td>GND</td>
    </tr>
  </tbody>
</table>

### Bloque 2
![Conexiones Bloque 2](Proyecto/Diagrams/Connections/Bloque2.png)

>[!NOTE]
> También se proporciona el diagrama eléctrico de este bloque, si desea consultarlo, haga click en este [enlace](Proyecto/Diagrams/Electric/Bloque2.pdf)

### Sensor de Temperatura y Humedad DHT11
<table>
  <thead>
    <th>Origen</th>
    <th>Destino</th>
  </thead>
  <tbody>
    <tr>
      <th>5V</th>
      <th>5V</th>
    </tr>
    <tr>
      <th>GND</th>
      <th>GND</th>
    </tr>
    <tr>
      <th>DATA</th>
      <th>Pin Digital 5</th>
    </tr>
  </tbody>
</table>

### Módulo ESP32-CAM
Este módulo simplemente va conectado vía USB a la computadora.

Finalmente, las conexiones del sistema en su totalidad tiene el siguiente aspecto:
![Conexiones Sistema Entero](Proyecto/Diagramas/Connections/Sistema.png)

>[!NOTE]
> También se proporciona el diagrama eléctrico del sistema, si desea consultarlo, haga click en este [enlace](Proyecto/Diagrams/Electric/Sistema.pdf)

## 📚 Estructura del Proyecto
A continuación, se describirá la estructura del proyecto, especificando la organización modular del código, la responsabilidad funcional de cada archivo fuente y la forma en que los distintos componentes interactúan entre sí dentro del sistema.

>[!NOTE]
> Tenga en cuenta que a pesar de que solo se haga mención al nombre del archivo como tal, cada uno de los archivos tiene su correspondiete interfaz (.h) y su implementación (.cpp)

<table>
  <thead>
    <th>Nombre del Archivo</th>
    <th>Responsabilidad</th>
    <th>Archivos con los que se relaciona</th>
  </thead>
  <tbody>
    <tr>
      <td>MainProgram.ino</td>
      <td>Es el archivo principal del proyecto. Es donde se realiza la ejecución del software</td>
      <td>PasswordManager, Fingerprint, MotorLock</td>
    </tr>
    <tr>
      <td>PasswordManager</td>
      <td>Gestiona la interacción con la matriz de botones, verificando si la contraseña introducida es correcta</td>
      <td>NA</td>
    </tr>
    <tr>
      <td>Fingerprint</td>
      <td>Gestiona el segundo y último factor de autenticación del sistema, mediante el sensor de huella dactilar</td>
      <td>PasswordManager</td>
    </tr>
    <tr>
      <td>MotorLock</td>
      <td>Se encarga de gestionar el motor que opera el pestillo de la caja fuerte</td>
      <td>NA</td>
    </tr>
    <tr>
      <td>RemoteControl.ino</td>
      <td>Archivo .ino del segundo Arduino (emisor). Se encarga de recibir las señales IR para luego enviarlas mediante comunicación serial al Arduino receptor. También, se encarga de controlar el ventilador que tiene el sistema si la temperatura de la cámara supera cierto umbral</td>
      <td>TemperatureFanController</td>
    </tr>
    <tr>
      <td>TemperatureFanController</td>
      <td>Es el sistema de refrigeración de la cámara. Se encarga de medir la temperatura del módulo ESP32-CAM, y al superar cierto umbral, activa el ventilador</td>
      <td>NA</td>
    </tr>
    <tr>
      <td>CameraWebServer</td>
      <td>Sketch extraído de los ejemplos de Arduino, que se encarga de la operatibilidad de la cámara, mostrando la dirección IP accesible vía web donde se podrá ver la transmisión en vivo.</td>
      <td>NA</td>
    </tr>
  </tbody>
</table>

A continuación, se muestra un `diagrama de clases` para reflejar de una forma más visual lo mencionado con anterioridad.

![Diagrama de Clases](Proyecto/Diagrams/Others/DigClases.jpg)

## 🧑‍💻 Implementación
En esta sección se mostrará la implementación de cada uno de los archivos mencionados en la sección anterior.
**IN PROGRESS**

### MainProgram
````cpp
````

### PasswordManager
````cpp
````

### Fingerprint
````cpp
````

### MotorLock
````cpp
````

### RemoteControl
````cpp
````

### TemperatureFanController
````cpp
/**
 * @file TemperatureFanController.cpp
 * @author Alfonso Rodríguez.
 * @brief Implementation file for temperature and fan control using a DHT11 sensor.
 */

#include "TemperatureFanController.h"

// Create the DHT sensor object
DHT dht(DHTPIN, DHTTYPE);

bool manualOverride = false;
 
/**
 * @brief Initializes serial communication, the DHT sensor, and fan control pin.
 *
 * This function sets up the hardware required for temperature monitoring.
 * It begins the serial interface, initializes the DHT11 sensor, and configures
 * the fan control pin as an output, starting in the OFF state.
 */
void setupTemperatureFan() {
  Serial.begin(9600);
  dht.begin();
 
  pinMode(FAN_PIN, OUTPUT);
  digitalWrite(FAN_PIN, LOW); // Ensure fan is off at startup
}

/**
 * @brief Checks if the given temperature exceeds the predefined threshold.
 *
 * This function compares the provided temperature with the threshold value (TEMPERATURE_TRESHOLD).
 * If the temperature is higher than the threshold, it returns true; otherwise, it returns false.
 *
 * @param temperature The current temperature value.
 * @return A boolean value indicating whether the temperature exceeds the threshold.
 */
bool exceededTreshold(float temperature) {
  return temperature > TEMPERATURE_TRESHOLD;
}

/**
 * @brief Controls the activation of the fan based on the current temperature.
 * This function checks if the current temperature exceeds the predefined threshold.
 * If it does, the fan is turned on, and a message is printed to the serial monitor.
 * If the temperature is below the threshold, the fan is turned off, and a message is printed to the serial monitor.
 * The fan's state is controlled via the FAN_PIN, and the fan's status is communicated via the serial monitor.
 *
 * @param temperature is the temperature that has been read.
 */
void fanActivation(float temperature) {
  if (manualOverride) {
    return;
  }
  if (exceededTreshold(temperature)) {
    digitalWrite(FAN_PIN, HIGH);
    Serial.println("Fan ON (Auto)");
  } 
  else {
    digitalWrite(FAN_PIN, LOW);
    Serial.println("Fan OFF (Auto)");
  }
}

/**
 * @brief Manually turns on the fan and overrides automatic control.
 *
 * This function sets the fan to the ON state regardless of the current temperature.
 * It enables manual override, preventing automatic temperature-based control
 * from modifying the fan state until manual override is disabled.
 */
void turnOnFan() {
  manualOverride = true;
  digitalWrite(FAN_PIN, HIGH);
  Serial.println("Fan ON (Manual)");
}

/**
 * @brief Manually turns off the fan and overrides automatic control.
 *
 * This function sets the fan to the OFF state regardless of the current temperature.
 * It enables manual override, preventing automatic temperature-based control
 * from modifying the fan state until manual override is disabled.
 */
void turnOffFan() {
  if (digitalRead(BUTTON) == HIGH) {
    if (digitalRead(FAN_PIN) == HIGH) {
      manualOverride = false;
    }
    else {
      manualOverride = true;
    }
    Serial.println("Boton Presionado");
    digitalWrite(FAN_PIN, LOW);
    Serial.println("Fan OFF (Manual)");
  }
}

/**
 * @brief Prints the current temperature and humidity data to the serial monitor.
 * This function outputs the current temperature and humidity readings to the serial monitor,
 * formatted as "Temperature: <value> °C | Humidity: <value> %".
 * The information helps to monitor the environment and assess the performance of the system.
 *
 * @param temperature is the temperature that has been read.
 * @param humidity is the humidity that has been read.
 */
void printData(float temperature, float humidity) {
  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.print(" °C  |  Humidity: ");
  Serial.print(humidity);
  Serial.println(" %");
}
 
/**
 * @brief Reads temperature and humidity from the DHT11 sensor and controls the fan.
 *
 * If the temperature exceeds 30°C, the fan is turned on; otherwise, it remains off.
 * Sensor data and fan status are printed to the serial monitor.
 * If the sensor fails to provide valid readings, an error message is shown instead.
 */
void updateTemperatureFan() {
  float humidity = dht.readHumidity();
  float temperature = dht.readTemperature();
 
  // Validate readings
  if (isnan(humidity) || isnan(temperature)) {
    Serial.println("Failed to read from DHT11 sensor!");
    return;
  }
  printData(temperature, humidity);
  fanActivation(temperature);
} 
````

## 🔧 Construcción
**AQUÍ SE MENCIONARÁN LAS FASES EN LA QUE SE ORGANIZÓ EL PROYECTO PARA CONSTRUIR LA PARTE FÍSICA**

## 🧪 Demostración
**AQUÍ VA A IR EL VIDEO DE DEMOSTRACIÓN**
