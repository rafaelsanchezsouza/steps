# 
# Makefile for Linux and QNX
#  
# For other operating systems see the build files in these subdirectories.
# Linux and QNX users just type "make" in this directory to build all 
# the demo programs for this board.
#

LIB=-L/usr/local/dscud5 -L/opt/dscud5 -ldscud5 -pthread -lm
INC=-I/usr/local/dscud5 -I/opt/dscud5

DEMOS=\
DSCADAutoCal/DSCADAutoCal \
DSCADSample/DSCADSample \
DSCADSampleInt/DSCADSampleInt \
DSCADScan/DSCADScan \
DSCADScanInt/DSCADScanInt \
DSCDAAutoCal/DSCDAAutoCal \
DSCDAConvert/DSCDAConvert \
DSCDAConvertScan/DSCDAConvertScan \
DSCDAConvertScanInt/DSCDAConvertScanInt \
DSCDIOFunctions/DSCDIOFunctions \
DSCSetUserInt/DSCSetUserInt \
DSCUserInt/DSCUserInt \
MeasureReferences/MeasureReferences

all: $(DEMOS)

clean:
	rm -f $(DEMOS)

$(DEMOS):
	( gcc -o $@ $@.c $(LIB) $(INC) )

