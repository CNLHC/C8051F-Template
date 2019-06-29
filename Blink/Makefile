.PHONY: clean download

DEBUGGER_SN = "EC800270115"
EXTRA_C_FILE = foo
SDCC_FLAGS= -mmcs51

download: main.hex
	FlashUtilCL DownloadUSB -R $< $(DEBUGGER_SN)  0 0
	
main.hex:main.ihx
	copy  main.ihx main.hex

main.ihx: main.c $(addsuffix .rel, $(EXTRA_C_FILE))
	sdcc $(SDCC_FLAGS) $?

%.rel: src/%.c
	sdcc $(SDCC_FLAGS) -c $<

clean:
	del -Force  *.hex *.ihx *.lk *.lst *.map *.mem *.rel *.rst *.sym *.asm


	



