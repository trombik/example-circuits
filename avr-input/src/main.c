/* include avr/io.h, which defines I/O resisters and addresses.
 * see https://www.nongnu.org/avr-libc/user-manual/group__avr__io.html
 */
#include <avr/io.h>

/* survival bitwise operations.
 *
 * AND:
 * | X | Y | X & Y |
 * |---|---|-------|
 * | 1 | 1 |   1   |
 * | 1 | 0 |   0   |
 * | 0 | 1 |   0   |
 * | 0 | 0 |   0   |
 *
 * 0b1111 & 0b0010 == 0b0010
 *
 * OR:
 *
 * | X | Y | X | Y |
 * |---|---|-------|
 * | 1 | 1 |   1   |
 * | 1 | 0 |   1   |
 * | 0 | 1 |   1   |
 * | 0 | 0 |   0   |
 *
 * 0b1110 | 0b0101 == 0b1111
 *
 * XOR:
 *
 * | X | Y | X ^ Y |
 * |---|---|-------|
 * | 1 | 1 |   0   |
 * | 1 | 0 |   1   |
 * | 0 | 1 |   1   |
 * | 0 | 0 |   0   |
 *
 * 0b0100 ^ 0b1110 == 0b1010
 *
 * SHIFT:
 *
 * 0b0001 << 0 == 0b0001
 * 0b0001 << 1 == 0b0010
 * 0b0001 << 2 == 0b0100
 * 0b0001 << 3 == 0b1000
 * 0b1000 >> 1 == 0b0100
 * 0b1000 >> 2 == 0b0010
 *
 * NOT:
 *
 * | X | !X |
 * |---|----|
 * | 1 |  0 |
 * | 0 |  1 |
 *
 * COMPLEMENT:
 *
 * ~0b1001 == 0b0110
 *
 * to set Nth bit logical 1 in X, use:
 *
 * X = X | (1 << N);
 *
 * or
 *
 * X |= 1 << N;
 *
 * to set Nth and Mth bit logical 1 in X, use:
 *
 * X |= (1 << N) | (1 << M);
 *
 * to set Nth bit logical 0 in X, use:
 *
 * X = X & ~(1 << N);
 *
 * or
 *
 * X &= ~(1 << N);
 *
 * to query Nth bit in X is set or not, use:
 *
 * X & (1 << N)
 */

void loop();

int
main()
{
	/* set PB3 as input.
	 *
	 * DDRB is a resister to set direction of GPIOs.  when logic 1, the
	 * pin is configured as output pin.  when logic 0, the pin is
	 * configured as input. the bit position of pin N is "DDB${N}", i.e.
	 * DDB1 for pin PB1, and DDB3 for pin PB3.
	 *
	 * Bit  | 7 | 6 | 5  | 4  | 3  | 2  | 1  | 0  |
	 * DDRB | - | - |DDB5|DDB4|DDB3|DDB2|DDB1|DDB0|
	 *
	 * see "10.2.1 Configuring the Pin" in the datasheet.
	 */
	DDRB &= ~(1 << DDB3);

	/* enable pull-up resistor on PB3.
	 *
	 * --------.
	 *   Vcc   |
	 *    |    |
	 *   .+.   |
	 *   | |   |
	 *   | | internal pull-up
	 *   `+'   |
	 *    |    |       /
	 * ---+--- PB3 ---/  ---.
	 *         |    switch  |
	 *   MCU   |            |
	 *         |           GND
	 *         |
	 * --------'
	 *
	 * PORTB is a data resister.
	 *
	 * when the pin is configured as input, setting 1 enables pull-up
	 * resistor, and setting 0 disables the pull-up resistor.
	 *
	 * when the pin is configured as output, setting 1 drives the pin HIGH,
	 * and setting 0 drives the pin LOW.
	 */
	PORTB |= 1 << PORTB3;

	/* configure PB1 as output */
	DDRB |= 1 << DDB1;

	/* set initial state on PB1 as off */
	PORTB &= ~(1 << PORTB1);

	loop();
}

void loop()
{
	while (1) {
		/* when PORTB3 is HIGH, drive PORTB1 HIGH, else LOW.
		 *
		 * PINB is input pins address, which contains pin values. test
		 * if PORTB3 is HIGH.
		 *
		 * Bit  | 7 | 6 |  5  |  4  |  3  |  2  |  1  |  0  |
		 * PINB | - | - |PINB5|PINB4|PINB3|PINB2|PINB1|PINB0|
		 *
		 * to test, use AND like this:
		 *
		 * PINB & (1 << PORTB3)
		 *
		 * if PORTB3 is HIGH, the result is true. otherwise false.
		 *
		 * avr/sfr_defs.h defines a helper macro, bit_is_set(). the
		 * above is equivalent to:
		 *
		 * bit_is_set(PINB, PORTB3)
		 */
		if (bit_is_set(PINB, PORTB3)) {

			/* set PORTB1 to 1 */
			PORTB |= 1 << PORTB1;
		} else {

			/* set PORTB1 to 0 */
			PORTB &= ~(1 << PORTB1);
		}
	}
}
