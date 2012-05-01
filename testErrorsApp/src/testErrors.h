/*
 * testErrors.h
 * 
 * Asyn driver that inherits from the asynPortDriver class to test error handling in both normally scanned
 * and I/O Intr scanned records
 *
 * Author: Mark Rivers
 *
 * Created April 29, 2012
 */

#include "asynPortDriver.h"

#define MAX_ARRAY_POINTS 100
#define OCTET_LENGTH 20

/* These are the drvInfo strings that are used to identify the parameters.
 * They are used by asyn clients, including standard asyn device support */
#define P_GenerateErrorsString        "GENERATE_ERRORS"       /* asynInt32,    r/w */
#define P_Int32ValueString            "INT32_VALUE"           /* asynInt32,    r/w */
#define P_Float64ValueString          "FLOAT64_VALUE"         /* asynFloat64,  r/w */
#define P_UInt32DigitalValueString    "UINT32D_VALUE"         /* asynUInt32Digital,  r/w */
#define P_OctetValueString            "OCTET_VALUE"           /* asynOctet,    r/w */
#define P_Int8ArrayValueString        "INT8_ARRAY_VALUE"      /* asynInt8Array,    r/w */
#define P_Int16ArrayValueString       "INT16_ARRAY_VALUE"     /* asynInt16Array,    r/w */
#define P_Int32ArrayValueString       "INT32_ARRAY_VALUE"     /* asynInt32Array,    r/w */
#define P_Float32ArrayValueString     "FLOAT32_ARRAY_VALUE"   /* asynFloat32Array,    r/w */
#define P_Float64ArrayValueString     "FLOAT64_ARRAY_VALUE"   /* asynFloat64Array,    r/w */

/** Class that tests error handing of the asynPortDriver base class using both normally scanned records and I/O Intr
  * scanned records. */
class testErrors : public asynPortDriver {
public:
    testErrors(const char *portName);
                 
    /* These are the methods that we override from asynPortDriver */
    virtual asynStatus writeInt32(asynUser *pasynUser, epicsInt32 value);
    virtual asynStatus writeFloat64(asynUser *pasynUser, epicsFloat64 value);
    virtual asynStatus writeUInt32D(asynUser *pasynUser, epicsUInt32 value, epicsUInt32 mask);
    virtual asynStatus readInt8Array   (asynUser *pasynUser, epicsInt8 *value,
                                        size_t nElements, size_t *nIn);
    virtual asynStatus readInt16Array  (asynUser *pasynUser, epicsInt16 *value,
                                        size_t nElements, size_t *nIn);
    virtual asynStatus readInt32Array  (asynUser *pasynUser, epicsInt32 *value,
                                        size_t nElements, size_t *nIn);
    virtual asynStatus readFloat32Array(asynUser *pasynUser, epicsFloat32 *value,
                                        size_t nElements, size_t *nIn);
    virtual asynStatus readFloat64Array(asynUser *pasynUser, epicsFloat64 *value,
                                        size_t nElements, size_t *nIn);

    /* These are the methods that are new to this class */
    void callbackTask(void);

protected:
    /** Values used for pasynUser->reason, and indexes into the parameter library. */
    int P_GenerateErrors;
    #define FIRST_COMMAND P_GenerateErrors
    int P_Int32Value;
    int P_Float64Value;
    int P_UInt32DigitalValue;
    int P_OctetValue;
    int P_Int8ArrayValue;
    int P_Int16ArrayValue;
    int P_Int32ArrayValue;
    int P_Float32ArrayValue;
    int P_Float64ArrayValue;
    #define LAST_COMMAND P_Float64ArrayValue
 
private:
    /* Our data */
    epicsInt8     int8ArrayValue_[MAX_ARRAY_POINTS];
    epicsInt16    int16ArrayValue_[MAX_ARRAY_POINTS];
    epicsInt32    int32ArrayValue_[MAX_ARRAY_POINTS];
    epicsFloat32  float32ArrayValue_[MAX_ARRAY_POINTS];
    epicsFloat64  float64ArrayValue_[MAX_ARRAY_POINTS];
    template <typename epicsType> 
        asynStatus doReadArray(asynUser *pasynUser, epicsType *value, 
                               size_t nElements, size_t *nIn, int paramIndex, epicsType *pValue);
};


#define NUM_PARAMS (&LAST_COMMAND - &FIRST_COMMAND + 1)

