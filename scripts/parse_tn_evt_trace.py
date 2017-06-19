
import click
import numpy as np
import pandas as pd


endian = 'little'
@click.command()
@click.option('-f',"--file",help="Load this File")
@click.option('-s',"--save", help="save as this csv")


# struct neuronEvtDat{
#     id_type localID;
#     tw_lpid globalID;
#     tw_stime eventTime;
#     volt_type neuronVoltage;
# }__attribute__((__packed__));
# typedef struct neuronEvtDat nevtdat;

def readFile(file,save):

	if endian == "big":
		e = '>'
	else:
		e = '<'

	#dataPtr = ffi.new("nevtdat *")
	#dsize = ffi.sizeof(dataPtr)
	#with open('file', 'rb') as bfile:
	#	bdat = bfile.readinto()
	tps = e + "u2,u8,f8,i4".replace(",","," + e)
	cdt = np.dtype(tps,align=False)
	fullData = np.fromfile(file, dtype=cdt)
	assert(isinstance(fullData, np.ndarray))
	print(fullData[0])
	print(fullData[1])




if __name__ == '__main__':
	readFile()


