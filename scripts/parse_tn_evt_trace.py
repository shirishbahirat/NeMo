import types
from cffi import FFI

#define the CFFI for NeMo data structures saved in the file:
#first, some common typedefs:

ffi.cdef("""
typedef struct neuronEvtDat{
    id_type localID;
    tw_lpid globalID;
    tw_stime eventTime;
    volt_type neuronVoltage;
}nevtdat;

""")