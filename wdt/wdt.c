#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <linux/watchdog.h>


static int app_wdt_enableWatchdog(void)
{
	int wdg_fd;
	int enable = WDIOS_ENABLECARD;
	wdg_fd = open("/dev/watchdog", O_RDWR);
	if(wdg_fd < 0){
		printf("%s, line:%d, wdg_fd:%d \n", __func__, __LINE__, wdg_fd);
		return -1;
	}

	if(ioctl(wdg_fd, WDIOC_SETOPTIONS, &enable) < 0)
	{
		printf("app_wdt_eableWatchdog ioctl error !!!! \n");
		close(wdg_fd);
		return -1;
	}

	printf("app_wdt_enableWatchdog init  ok !\n");
	close(wdg_fd);
	return 0;
}

static int app_wdt_dsiableWatchdog(void)
{
	int wdg_fd;
	int disable = WDIOS_DISABLECARD;
	
	wdg_fd = open("/dev/watchdog", O_RDWR);
	if(wdg_fd < 0){
		printf("%s, line:%d, wdg_fd:%d \n", __func__, __LINE__, wdg_fd);
		return -1;
	}
	
	if(ioctl(wdg_fd, WDIOC_SETOPTIONS, &disable) < 0)
	{
		printf("app_wdt_dsiableWatchdog ioctl error !!!! \n");
		close(wdg_fd);
		return -1;
	}

	close(wdg_fd);
	return 0;
}

int main(int argc, char *argv[])
{
	unsigned long switchFlag;
	if(argc < 2) {//若参数个数少于两个则打印此工具的使用方法
        fprintf(stderr, "\nUsage:\t%s { 0:off, 1:on }  \n",
            argv[0]);
        exit(1);
    }
	
	switchFlag = strtoul(argv[1], 0, 0);
	if (switchFlag == 0){
		app_wdt_dsiableWatchdog();
	} else if (switchFlag == 1){
		app_wdt_enableWatchdog();
	} else {
		printf("argument not valid! \n");
		exit(1);
	}
	
	return 0;
}