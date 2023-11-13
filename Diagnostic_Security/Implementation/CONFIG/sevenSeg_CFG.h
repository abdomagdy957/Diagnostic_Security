

#ifndef SEVENSEG_CFG_H_
#define SEVENSEG_CFG_H_

//BCD pins are PB0,PB1,PB2,PB3
/*
#define BCD0_PIN PINB1
#define BCD1_PIN PINB1
#define BCD2_PIN PINB2
#define BCD3_PIN PINB4
*/
#define DATA_BCD	PB

//to enable each one we need to enable and disable each one at a time
#define ENABLE_DIGIT1_PIN	PINA3
#define ENABLE_DIGIT2_PIN	PINA2
#define ENABLE_DIGIT3_PIN	PINB5
#define ENABLE_DIGIT4_PIN	PINB6

#endif /* SEVENSEG_CFG_H_ */