####################################################################################################
#                                                                                                  #
#  Set up tools and tool configurations.                                                           #
#                                                                                                  #
####################################################################################################
# for IoTehca board
# export  path (see commands below)
#ensure you set up export before using this file
#export PATH=$PATH:~/Documents/EPRI/spin/mevse_toolchain/arm-2009q1/bin

CROSS=arm-none-linux-gnueabi-
CC := $(CROSS)gcc
CFLAGS := -v -Wall -Wno-missing-braces -DPF_CAN=29 -DAF_CAN=PF_CAN
STRIP := $(CROSS)strip

all: can2sep2

can2sep2: can2sep2.c can.c usock.c
	${CC} $(CFLAGS) -o $@ can2sep2.c -lrt -lm 
	$(STRIP) -g $@

test_can2sep2_usock: test_can2sep2_usock.c can2sep2_proxy.c
	${CC} $(CFLAGS) -o $@ test_can2sep2_usock.c -lrt -lm 
	$(STRIP) -g $@
	

clean: 
	rm -f can2sep2