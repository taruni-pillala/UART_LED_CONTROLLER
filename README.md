# STM32 UART LED Controller

## Overview

This project demonstrates UART communication on the STM32F103C8T6 Blue Pill using bare-metal register programming. The microcontroller receives commands from a PC through Tera Term and controls the onboard LED connected to PC13.

The project was implemented without using HAL libraries, STM32CubeMX-generated code, or Arduino libraries. All peripheral configuration is performed through direct register access.

---

## Hardware Used

* STM32F103C8T6 Blue Pill
* CH340 USB-to-UART Converter
* Jumper Wires
* PC with Tera Term
* STM32CubeIDE
* STM32CubeProgrammer

---

## Connections

| CH340 | STM32 Blue Pill  |
| ----- | ---------------- |
| TX    | PA10 (USART1_RX) |
| RX    | PA9 (USART1_TX)  |
| GND   | GND              |

The onboard LED connected to PC13 is used for visual indication.

---

## UART Configuration

| Parameter  | Value  |
| ---------- | ------ |
| Peripheral | USART1 |
| Baud Rate  | 9600   |
| Data Bits  | 8      |
| Parity     | None   |
| Stop Bits  | 1      |

---

## Working Principle

1. STM32 initializes GPIO and USART1.
2. A welcome message is transmitted to Tera Term.
3. The microcontroller waits for user input.
4. When a command is received:

   * '1' turns the LED ON.
   * '0' turns the LED OFF.
5. A status message is sent back to Tera Term.

---

## Supported Commands

| Command | Action       |
| ------- | ------------ |
| 1       | Turn LED ON  |
| 0       | Turn LED OFF |

### Example

Input:

```text
1
```

Output:

```text
LED ON
```

Input:

```text
0
```

Output:

```text
LED OFF
```

---

## Features

* Bare-metal register programming
* USART1 communication
* UART transmit and receive
* Real-time LED control
* Command-based interface
* No HAL libraries
* No Arduino framework

---

## Concepts Learned

* STM32 clock configuration (RCC)
* GPIO output configuration
* USART1 initialization
* UART data transmission
* UART data reception
* Polling-based communication
* Embedded command processing

---

## Future Improvements

* PWM brightness control through UART
* Multi-character command parsing
* UART command menu system
* OLED status display
* GSM-based remote control
* Interrupt-driven UART communication

---

## Author

Taruni

Electronics and Communication Engineering

Sathyabama Institute of Science and Technology
