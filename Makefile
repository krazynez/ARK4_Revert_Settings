TARGET = ark4_settings_revert

OBJS = main.o


CFLAGS = -Wall -std=c99

EXTRA_TARGETS = EBOOT.PBP

PSP_EBOOT_TITLE = ARK-4 Revert Settings

BUILD_PRX = 1

LIBS = -lpspdebug -lpspctrl


EXTRA_CLEAN:
	rm -rf PSP *zip


PSPSDK=$(shell psp-config -p)
include $(PSPSDK)/lib/build.mak

clean: EXTRA_CLEAN
	rm -f $(TARGET).prx $(TARGET).elf main.o PARAM.SFO EBOOT.PBP

pkg: clean EXTRA_CLEAN all
	-rm -rf PSP
	-mkdir -p PSP/GAME/ARK4-Revert-Settings
	-cp EBOOT.PBP PSP/GAME/ARK4-Revert-Settings/
	-zip -r ARK4-Revert-Settings.zip PSP

