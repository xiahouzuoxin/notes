-c
-x
-l rts6700.lib
-heap  200h
-stack 300h
MEMORY
{
    BOOT_RAM : o=0,l=400h
    IRAM     : o=400h,l=0x00040000

}
SECTIONS
{
      .boot_load :> BOOT_RAM
      .vectors  :> IRAM
      .bss		:> IRAM
      .cinit  	:> IRAM
      .far    	:> IRAM
      .stack  	:> IRAM
      .const    :> IRAM
      .switch   :> IRAM
      .cio      :> IRAM
      .sysmem   :> IRAM   
}