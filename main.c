#include <pspsdk.h>
#include <pspinit.h>
#include <pspdebug.h>
#include <pspctrl.h>
#include <psptypes.h>
#include <pspiofilemgr.h>

PSP_MODULE_INFO("ARK4_Settings_Reverter", 0, 1, 0);

#define printf pspDebugScreenPrintf

const char settings[] = "always, usbcharge, on\nalways, overclock, on\nalways, powersave, off\nalways, defaultclock, off\nalways, launcher, off\nalways, disablepause, off\nalways, highmem, off\nalways, mscache, on\nalways, infernocache:lru, on\nalways, oldplugin, on\nalways, skiplogos, off\nalways, hidepics, off\nalways, hibblock, on\nalways, hidemac, on\nalways, hidedlc, off\nalways, noled, off\nalways, noumd, off\nalways, noanalog, off\nalways, qaflags, on\n# Luxor doesn't like Inferno Cache\nULUS10201, infernocache, off";

int main(int argc, char *args[]) {

	pspDebugScreenInit();
	printf("This will revert both CFW Settings and Custom Launcher Settings\nto Default.\n\nRevert ARK-4 Settings?\n");
	printf("X - Rervert\n");
	printf("O - Exit\n");
	SceCtrlData pad;

	while(1) {

		
		sceCtrlReadBufferPositive(&pad, 1);
		if (pad.Buttons == PSP_CTRL_CROSS) {
			int fd = sceIoOpen("ms0:/PSP/SAVEDATA/ARK_01234/ARKMENU.BIN", PSP_O_RDONLY, 0);
			if(fd) {
				sceIoClose(fd);
				sceIoRemove("ms0:/PSP/SAVEDATA/ARK_01234/ARKMENU.BIN");
				sceIoRemove("ms0:/PSP/SAVEDATA/ARK_01234/SETTINGS.TXT");
				sceKernelDelayThread(8000);
				int settings_file = sceIoOpen("ms0:/PSP/SAVEDATA/ARK_01234/SETTINGS.TXT", PSP_O_CREAT | PSP_O_WRONLY, 0777);
				sceIoWrite(settings_file, settings, sizeof(settings));
				sceKernelDelayThread(8000);
				sceIoClose(settings_file);
				printf("Exiting....\n");
				sceKernelDelayThread(8000000);
				sceKernelExitGame();

			}
			fd = sceIoOpen("ef0:/PSP/SAVEDATA/ARK_01234/ARKMENU.BIN", PSP_O_RDONLY, 0);
			if(fd) {
				sceIoClose(fd);
				sceIoRemove("ef0:/PSP/SAVEDATA/ARK_01234/ARKMENU.BIN");
				sceIoRemove("ef0:/PSP/SAVEDATA/ARK_01234/SETTINGS.TXT");
				printf("Exiting....\n");
				sceKernelDelayThread(8000000);
				sceKernelExitGame();
			}
		}
		else if (pad.Buttons == PSP_CTRL_CIRCLE) {
			printf("Exiting....\n");
			sceKernelDelayThread(8000000);
			sceKernelExitGame();
		}


	}


	return 0;
}

