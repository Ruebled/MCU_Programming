extern int main(void);
// Startup code
__attribute__((naked, noreturn)) void _reset(void) {
	// memset .bss to zero, and copy .data section to RAM region
	extern long _sbss, _ebss, _sdata, _edata, _sidata;
	for (long *src = &_sbss; src < &_ebss; src++) *src = 0;
	for (long *src = &_sdata, *dst = &_sidata; src < &_edata;) *src++ = *dst++;

	main();             // Call main()
	for (;;) (void) 0;  // Infinite loop in the case if main() returns
}
