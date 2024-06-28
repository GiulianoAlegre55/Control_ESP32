# Repositorio Creado para Desarrollar Control Remoto

---

En los siguientes apartados están los enlaces para poder acceder a las paguinas donde se extrajo el contenido con el que se trabajó.

### Pagina principal:

[Enlace Hacia la Pagina Principal](https://randomnerdtutorials.com/projects-esp32/)

---

### Detalles ESP32

Nosotros utilizamos la placa Esp32 gracias a sus caracteristicas, costos y rendimiento a la hora de procesar tareas. En el siguiente enlace se pueden ver las [caracteristicas del ESP32](https://randomnerdtutorials.com/getting-started-with-esp32/).

En la siguiente imagen hay un estracto de la conexion de la placa:
![Imagen de los pines](https://i0.wp.com/randomnerdtutorials.com/wp-content/uploads/2018/08/ESP32-DOIT-DEVKIT-V1-Board-Pinout-36-GPIOs-updated.jpg?w=750&quality=100&strip=all&ssl=1)

---

### Arduino IDE

#### Arduino IDE 1.8.x

para configurar el arduino IDE para que sea compatible con las placas ESP32 debemos meternos al ajuste avanzados de placas y pegar los siguientes enlaces:

- https://raw.githubusercontent.com/espressif/arduino-esp32/gh-pages/package_esp32_index.json
- http://arduino.esp8266.com/stable/package_esp8266com_index.json

Estos son enlaces hacia archivos de configuracion.

![imagen configuracion](https://i0.wp.com/randomnerdtutorials.com/wp-content/uploads/2022/10/Additional-Boards-Manager-URL.png?w=750&quality=100&strip=all&ssl=1)

Luego descargamos la libreria ESP32:

![libreria Esp32](https://i0.wp.com/randomnerdtutorials.com/wp-content/uploads/2022/10/Boards-Manager-ESP32-Arduino-IDE.png?w=750&quality=100&strip=all&ssl=1)

En el siguiente Blog se explica más detalladamente:
[Clic aquí](https://randomnerdtutorials.com/installing-the-esp32-board-in-arduino-ide-windows-instructions/)

#### Arduino IDE 2.0.x

El siguiente enlace te llevara al blog donde podrás descargar las librerias necesarias para poder utilizar las Placas Esp32 en las nuevas versiones de Arduino IDE. [Enlace](https://randomnerdtutorials.com/installing-esp32-arduino-ide-2-0/)

---

### Proyecto

A partir de este modulo se van a detallar como se piensa crear el control, haciendo referencia a cada blog donde se obtiene la información.

#### Acelerador

El acelerador es un elemento fundamental a la hora de desplazar el vehiculo.
Lo ideal seria que el usuario pueda regular el acelerador a gusto dentro de un rango, de una forma dinamica. Para ello se plantea el uso de las slider o barras de deslizamiento.

Las sliders va a permitir al usuario regular de manera dinamica la velocidad del vehiculo. En el siguiente enlace se puede acceder al blog donde se se crean sliders para controlar unos leds. [Enlace](https://randomnerdtutorials.com/esp32-web-server-websocket-sliders/).

La ventaja de usar esto es que es asyncrono, por lo que no tendremos que recargar la pagina para ver los cambios de otro cliente.

#### Botones Para Control

En este modulo se propone utilizar, modificandolo en el proceso, el siguiente blog para poder controlar, con botones, el movimiento de cada par de ruedas.

El enlace al blog es el de [aqui](https://randomnerdtutorials.com/esp32-websocket-server-arduino/).

En el blog se pulsa una sola vez y se mantiene el estado del boton. En nuestro caso lo ideal seria que regrese a su estado base periodicamente, de modo que debamos mantenerlo pulsado.
De esta forma, los usuarios deberan mantener los botones pulsados para poder controlar el vehiculo.

#### Diseño controles

En la siguiente imagen se puede ver como podrian quedar los controles utilizando unicamente botones

![ejemplo controles](https://play-lh.googleusercontent.com/b1YhAZWbyiQ35VUn7VZWaV3ju9Ht0MaSMDJj09eE_dmlsXPLJTixyx3wAeWhviK_2Q=w526-h296-rw)

![ejemplo controles ](https://blog.uptodown.com/wp-content/uploads/hot-wheels-infinite.jpg)

![ejemplo controles ](https://www.mobilegamer.com.br/wp-content/uploads/2023/04/Drive-Zone-Online.webp)

![ejemplo controles](https://i0.wp.com/solotendencias.net/wp-content/uploads/2021/07/mejores-juegos-de-carrera.jpg?fit=779%2C437&ssl=1)

#### OTA

##### Definicion de OTA

[Video De Youtube](https://www.youtube.com/watch?v=kfCInkH-0nw)

Para utilizar OTA debemos realizar los siguientes pasos: [clic.](https://youtu.be/LUcKoJGX38M)

![meme](https://lastminuteengineers.com/wp-content/uploads/2023/11/ESP32-Static-or-Fixed-IP-Address-Tutorial.png)
