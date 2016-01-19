ENTRY(start)

MEMORY
{
	FLASH (rx) : ORIGIN = 0x08000000, LENGTH = 64K
	RAM (rwx) : ORIGIN = 0x20000000, LENGTH = 20K
}

SECTIONS
{
	.text :
	{
		KEEP(*(.isr_vector))
		*(.text)
		*(.text.*)
        application_init_begin = .;
		KEEP(*(.application.init))
		application_init_end = .;
		shell_cmd_begin = .;
		KEEP(*(.shell.cmd))
		shell_cmd_end = .;
		*(.rodata)
		*(.rodata.*)
		_sidata = .;
	} >FLASH

	.data : AT(_sidata)
	{
		_sdata = .;
		*(.data)
        *(.shell.cmd)
        *(.idle)
		_edata = .;
	} >RAM

	.bss :
	{
		_sbss = .;
		*(.bss)
		_ebss = .;
	} >RAM

	_estack = ORIGIN(RAM) + LENGTH(RAM);
	kernel_end = .;
}
