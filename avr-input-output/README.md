# AVR I/O example

An example to demonstrate input and output on AVR MCUs.

When `SW1` is released, the `D1` turns on. When `SW1` is pushed, the `D1`
turns off.

The program uses resisters related to GPIOs, `DDRB`, `PORTB`, and `PINB`. A
pin is used as input, and another as output.

The target is ATTiny85, but can be used with other AVR MCUs.

## Schematic

![Schematic](kicad/avr-input-output.svg)
