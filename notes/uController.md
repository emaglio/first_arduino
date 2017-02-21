ADC (10 bit)
- select input with MUX and ADMUX
- to ENABLE the ADC set high the ADC Enable bit (ADEN in ADCSRA) and 0 to PRADC
- to DISABLE the ADC clear ADEN
ADC Result
10 bit result in ADC Data register, ADCH and ADCL (default right adjusted)
- to read --> before ADCL (ADC data register not readable) then read ADCH (ADC readable)
ADC Trigger
- own trigger when the conversion is done even if it has been lost because read in the wrong way 
- use automatic trigger for it
Timing:
- 25 clock to initiate the ADC
- 10 clock for a normal conversion
