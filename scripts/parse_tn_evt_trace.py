
import click
import numpy as np
import pandas as pd
from cffi import FFI
ffi = FFI()
#ffi.cdef("""
#typedef uint_fast16_t id_type; //!< id type is used for local mapping functions - there should be $n$ of them depending on CORE_SIZE
#typedef int32_t volt_type; //!< volt_type stores voltage values for membrane potential calculations
#typedef int64_t weight_type;//!< seperate type for synaptic weights.
#typedef uint32_t thresh_type;//!< Type for weights internal to the neurons.
#typedef uint16_t random_type;//!< Type for random values in neuron models.
#typedef uint64_t size_type; //!< size_type holds sizes of the sim - core size, neurons per core, etc.
#typedef uint64_t stat_type;
#
#typdef uint64_t tw_lpid;
#typedef double tw_stime;
#
#
#
#
#""")
#ffi.cdef("""
#struct neuronEvtDat{
#     id_type localID;
#     tw_lpid globalID;
#     tw_stime eventTime;
#     volt_type neuronVoltage;
# }__attribute__((__packed__));
# typedef struct neuronEvtDat nevtdat;
# """)
#


endian = 'little'
## Reminder:
	# src_lp	dest_lp	recv_ts_vt	send_ts_vt	recv_ts_rt	duration	local_id	global_id	event_time	neuronvoltage
#id_type :	: 2
# volt_type :	: 4
# tw_lpid :	: 8
# tw_stime :	: 8
# struct neuronEvtDat :	: 22

predefined_types = 'u8,u8,f8,f8,f8,f8'
nemo_struct = "u2,u8,f8,i4"

def saveIt(data,savefn):

	with open(savefn, 'w') as f:
		f.write('source_lp,dest_lp,recv_ts_vt,send_ts_vt,recv_ts_rt,duration,local_ID,core_ID,current_neuro_time,neuron_voltage,event_type 1=hb 2=out\n')
		for ln in data:
			sline = str(ln).lstrip('(').rstrip(')') + "\n"
			f.write(sline)


@click.command()
@click.option('-f',"--file",help="Load this File")
@click.option('-s',"--save", help="save as this csv", default="nemo_events.csv")
def readFile(file,save):

	if endian == "big":
		e = '>'
	else:
		e = '<'

	#e = ''
	#dataPtr = ffi.new("nevtdat *")
	#dsize = ffi.sizeof(dataPtr)
	#with open('file', 'rb') as bfile:
	#	bdat = bfile.readinto()
	
	
	tps = e + ( predefined_types + "," + nemo_struct ).replace(",","," + e)
	#temp testing:
	tps = f"{tps},{e}u1"
	print(tps)
	cdt = np.dtype(tps,align=False)
	print(cdt.isalignedstruct)
	fullData = np.fromfile(file, dtype=cdt)
	assert(isinstance(fullData, np.ndarray))
	print(fullData[0])
	print(fullData[1])
	print(fullData.shape)
	saveIt(fullData, save)









if __name__ == '__main__':
	readFile()


