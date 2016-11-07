

#ifndef SETUP_H
#define SETUP_H

/*
 * Configure the clocks, GPIO and other peripherals as required by the demo.
 */
void prvSetupHardware( void );

// Debugging: enable "assert"

#undef assert
#define assert(expr) ((expr) ? (void)0 : assert_failed(__FILE__, __LINE__))
#define assert_param(expr) ((expr) ? (void)0 : assert_failed(__FILE__, __LINE__))
void assert_failed(unsigned char* file, unsigned int line);

#endif
