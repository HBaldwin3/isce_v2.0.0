//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Copyright: 2009 to the present, California Institute of Technology.
// ALL RIGHTS RESERVED. United States Government Sponsorship acknowledged.
// Any commercial use must be negotiated with the Office of Technology Transfer
// at the California Institute of Technology.
// 
// This software may be subject to U.S. export control laws. By accepting this
// software, the user agrees to comply with all applicable U.S. export laws and
// regulations. User has the responsibility to obtain export licenses,  or other
// export authority as may be required before exporting such information to
// foreign countries or providing access to foreign persons.
// 
// Installation and use of this software is restricted by a license agreement
// between the licensee and the California Institute of Technology. It is the
// User's responsibility to abide by the terms of the license agreement.
//
// Author: Giangi Sacco
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~




#include <Python.h>
#include "LineAccessor.h"
#include "LineAccessormodule.h"
#include <cmath>
#include <sstream>
#include <iostream>
#include <string>
#include <vector>
#include <stdint.h>
using namespace std;

static char * const __doc__ = "module for LineAccessor.cpp";

PyModuleDef moduledef = {
    // header
    PyModuleDef_HEAD_INIT,
    // name of the module
    "LineAccessor",
    // module documentation string
    __doc__,
    // size of the per-interpreter state of the module;
    // -1 if this state is global
    -1,
    LineAccessor_methods,
};

// initialization function for the module
// *must* be called PyInit_LineAccessor
PyMODINIT_FUNC
PyInit_LineAccessor()
{
    // create the module using moduledef struct defined above
    PyObject * module = PyModule_Create(&moduledef);
    // check whether module creation succeeded and raise an exception if not
    if (!module) {
        return module;
    }
    // otherwise, we have an initialized module
    // and return the newly created module
    return module;
}

PyObject * getLineAccessorObject_C(PyObject* self, PyObject* args)
{
    uint64_t ptLineAccessor = 0;
    LineAccessor * tmp =  new LineAccessor;
    (ptLineAccessor) = (uint64_t ) tmp;
    return Py_BuildValue("K",ptLineAccessor);
}

PyObject * getMachineEndianness_C(PyObject* self, PyObject* args)
{
    uint64_t ptLineAccessor = 0;
    if(!PyArg_ParseTuple(args, "K", &ptLineAccessor))
    {
        return NULL;
    }
    char endian = ((LineAccessor * )(ptLineAccessor))->getMachineEndianness();
    return Py_BuildValue("c",endian );
}
PyObject * finalizeLineAccessor_C(PyObject* self, PyObject* args)
{
    uint64_t ptLineAccessor = 0;
    if(!PyArg_ParseTuple(args, "K", &ptLineAccessor))
    {
        return NULL;
    }
    if(((LineAccessor * )(ptLineAccessor))->isInit())
    {
        ((LineAccessor * )(ptLineAccessor))->finalizeLineAccessor();
    }
    LineAccessor * tmp = (LineAccessor *) (ptLineAccessor);
    delete tmp;
    return Py_BuildValue("i", 0);
}

PyObject * initLineAccessor_C(PyObject* self, PyObject* args)
{
    uint64_t ptLineAccessor = 0;
    string filename;
    char * filenameCh;
    string filemode;
    char * filemodeCh;
    char endianFile;
    string type;
    char * typeCh;
    int row = 0;
    int col = 0;

    if(!PyArg_ParseTuple(args, "Ksscsii", &ptLineAccessor, &filenameCh,
        &filemodeCh, &endianFile, &typeCh, &row, &col))
    {
        return NULL;
    }
    filename = filenameCh;
    filemode = filemodeCh;
    type = typeCh;
    ((LineAccessor * )(ptLineAccessor))->initLineAccessor(filename, filemode,
        endianFile,type,row,col);
    return Py_BuildValue("i", 0);
}
PyObject * changeBandScheme_C(PyObject* self, PyObject* args)
{
    uint64_t ptLineAccessor = 0;
    string filein;
    char * fileinCh;
    string fileout;
    char * fileoutCh;
    string type;
    char * typeCh;
    int width = 0;
    int numBands = 0;
    int bandIn = 0;
    int bandOut = 0;
    if(!PyArg_ParseTuple(args, "Ksssiiii", &ptLineAccessor, &fileinCh,
        &fileoutCh, &typeCh, &width, &numBands, &bandIn, &bandOut))
    {
        return NULL;
    }
    filein = fileinCh;
    fileout = fileoutCh;
    type = typeCh;
    BandSchemeType  bandI = convertIntToBandSchemeType(bandIn);
    BandSchemeType  bandO = convertIntToBandSchemeType(bandOut);
    ((LineAccessor * )(ptLineAccessor))->changeBandScheme(filein, fileout,
        type, width, numBands, bandI, bandO);
    return Py_BuildValue("i", 0);
}
PyObject * convertFileEndianness_C(PyObject* self, PyObject* args)
{
    uint64_t ptLineAccessor = 0;
    string filein;
    char * fileinCh;
    string fileout;
    char * fileoutCh;
    string type;
    char * typeCh;
    if(!PyArg_ParseTuple(args, "Ksss", &ptLineAccessor, &fileinCh, &fileoutCh,
        &typeCh))
    {
        return NULL;
    }
    filein = fileinCh;
    fileout = fileoutCh;
    type = typeCh;
    ((LineAccessor * )(ptLineAccessor))->convertFileEndianness(filein, fileout,
        type);
    return Py_BuildValue("i", 0);
}
PyObject * getFileLength_C(PyObject* self, PyObject* args)
{
    uint64_t ptLineAccessor = 0;
    if(!PyArg_ParseTuple(args, "K",&ptLineAccessor))
    {
        return NULL;
    }
    int length = 0;
    ((LineAccessor * )(ptLineAccessor))->getFileLength(&length);
    return Py_BuildValue("i",length);
}
PyObject * getFileWidth_C(PyObject* self, PyObject* args)
{
    uint64_t ptLineAccessor = 0;
    if(!PyArg_ParseTuple(args, "K",&ptLineAccessor))
    {
        return NULL;
    }
    int width = 0;
    ((LineAccessor * )(ptLineAccessor))->getFileWidth(&width);
    return Py_BuildValue("i",width);
}
PyObject * createFile_C(PyObject* self, PyObject* args)
{
    uint64_t ptLineAccessor = 0;
    int length = 0;
    if(!PyArg_ParseTuple(args, "Ki",&ptLineAccessor,&length))
    {
        return NULL;
    }
    ((LineAccessor * )(ptLineAccessor))->createFile(&length);
    return Py_BuildValue("i",0);
}
PyObject * rewindImage_C(PyObject* self, PyObject* args)
{
    uint64_t ptLineAccessor = 0;
    if(!PyArg_ParseTuple(args, "K",&ptLineAccessor))
    {
        return NULL;
    }
    ((LineAccessor * )(ptLineAccessor))->rewindImage();
    return Py_BuildValue("i",0);
}
PyObject * getTypeSize_C(PyObject* self, PyObject* args)
{
    uint64_t ptLineAccessor = 0;
    string type;
    char * typeCh;
    if(!PyArg_ParseTuple(args, "Ks",&ptLineAccessor,&typeCh))
    {
        return NULL;
    }
    type = typeCh;
    int size = 0;
    size = ((LineAccessor * )(ptLineAccessor))->getTypeSize(type);
    return Py_BuildValue("i",size);
}
PyObject * printObjectInfo_C(PyObject* self, PyObject* args)
{
    uint64_t ptLineAccessor = 0;
    if(!PyArg_ParseTuple(args, "K",&ptLineAccessor))
    {
        return NULL;
    }
    ((LineAccessor * )(ptLineAccessor))->printObjectInfo();
    return Py_BuildValue("i",0);
}
PyObject * printAvailableDataTypesAndSizes_C(PyObject* self, PyObject* args)
{
    uint64_t ptLineAccessor = 0;
    if(!PyArg_ParseTuple(args, "K",&ptLineAccessor))
    {
        return NULL;
    }
    ((LineAccessor * )(ptLineAccessor))->printAvailableDataTypesAndSizes();
    return Py_BuildValue("i",0);
}
BandSchemeType convertIntToBandSchemeType(int band)
{
    BandSchemeType ret = BNULL;
    switch (band)
    {
    case 0:
    {
        break;
    }
    case 1:
    {
        ret = BSQ;
        break;
    }
    case 2:
    {
        ret = BIP;
        break;
    }
    case 3:
    {
        ret = BIL;
        break;
    }
    default:
    {
        cout << "Error. Band scheme is an integer number between 0 and 3." <<
            endl;
        ERR_MESSAGE;
    }
    }
    return ret;
}

// end of file
