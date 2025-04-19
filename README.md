# Grupo 16: TBD

## Tabla de Contenidos
- [Participantes](#participantes)
- [Introducción](#introducción)
- [Funcionamiento](#funcionamiento)
- [Material Usado y Costes](#material-usado-y-costes)
- [🔥 Diseño](#-diseño)
- [Implementación](#implementación)
- [Construcción](#construcción)
- [Demostración](#demostración)

## Participantes
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

## Introducción
**BREVE INTRODUCCIÓN DEL PROYECTO**

## Funcionamiento
El comportamiento de este sistema es bastante similar al de un sistema de seguridad común que se puede encontrar en el día a día. Para este proyecto, se decidió dividir el sistema en 2 bloques independientes, en uno se iba a encontrar toda la lógica y gestión de la caja fuerte, y en la otra, todo lo relacionado con la cámara y su pequeño sistema de refrigeración.

### Bloque 1
Se dispone de una matriz de botones 4x4 en el que el usuario tendrá 3 intentos para introducir la contraseña correcta; en caso de agotar todos los intentos, el sistema se bloqueará, y solo el dueño de la caja fuerte podrá habilitar nuevamente el sistema. En caso contrario, el usuario deberá de validar su huella dactilar haciendo uso del lector de huellas, como último factor de autenticación antes de poder acceder a la caja fuerte. Una vez la huella sea reconocida, la caja fuerte se abrirá desplegando consigo un brazo mecánico que tendrá cosnsigo el objeto que se guardó en dicha caja fuerte.

A continuación, se muestra un diagrama de actividad que refleja el funcionamiento de este primer bloque de una forma más visual, para así complementar con lo dicho previamente.

### Bloque 2
Para añadir una mejor seguridad y proporcionar mayor información sobre lo que está sucediendo cuando un usuaro intenta interacturar con el sistema, se utilizó una cámara de seguridad cuyo funcionamiento es indepediente del bloque anterior. Esta cámara transmitirá en vivo y en directo todo lo que suceda mientras un usuario se encuentre interactuando con el sistema. Sin embargo, esta cámara tiene un ligero defecto y es el aumento de temperatura que puede sufrir mientras esté operativa, es por ello, que se decidió controlar dicha temperatura haciendo uso de un sensor de temperatura, que, tras superar una temperatura umbral, activaría un ventilador para enfriar un poco dicha cámara.

A continuación, se muestra un diagrama de actividad que refleja el funcionamiento de este último bloque de una forma más visual, para así complementar con lo dicho previamente.

>[!NOTE]
> La transmisión en vivo ofrecida por la cámara, se puede ver introduciendo en cualquier navegador web, la IP que dicha cámara devuelve una vez esté correctamente operativa.

> [!WARNING]
> Es importante que usted tenga en cuenta que el ventilador que se usó para refrigerar la cámara, no es el más sofisticado ni potente que existe, es debido a ello que usted pueda apreciar que la temperatura de la cámara tarda un poco más de lo que debería en bajar.
> Además, también es importante que usted tenga en cuenta que debido a que la cámara no es la más sofisticada que hay, es posible que la transmisión se aprecie a una calidad inferior a la deseada o que la imagen se pueda congelar. Esto como ya digo, sucede por la calidad de la cámara.

## Material Usado y Costes
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
      <td>TBD</td>
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
      <td><strong>TOTAL</strong></td>
      <td><strong>14</strong></td>
      <td><strong>59.82</strong></td>
    </tr>
  </tbody>
</table>

## 🔥 Diseño
**AQUÍ SE VAN A METER LAS FOTOS DE LOS DIAGRAMAS DE CONEXIÓN**
**ADEMÁS, SE HARÁN UNAS TABLAS MOSTRANDO LAS CONEXIONES DE CADA COMPOENTE PARA QUEA MÁS VISUAL**

## Implementación
**AQUÍ SE VA A EXPLICAR COMO ESTÁ DISTRIBUIDO EL CÓDIGO, Y NO ESTOY SEGURO SI TAMBIÉN HARÍA FALTA METER EL CÓDIGO DE CADA PARTE**

## Construcción
**AQUÍ SE MENCIONARÁN LAS FASES EN LA QUE SE ORGANIZÓ EL PROYECTO PARA CONSTRUIR LA PARTE FÍSICA**

## Demostración
**AQUÍ VA A IR EL VIDEO DE DEMOSTRACIÓN**
