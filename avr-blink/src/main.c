#include <avr/io.h>
#include <util/delay.h>

static void
loop();

int
main()
{
	/* configure PB0 as output */
	DDRB |= 1 << DDB0;

	/* set initial state on PB0 as off */
	PORTB &= ~(1 << PORTB0);
	loop();
}

static void
loop()
{
	while (1) {

        /* toggle PORTB0 in PORTB */
        PORTB ^= 1 << PORTB0;
        _delay_ms(1000);
	}
}
