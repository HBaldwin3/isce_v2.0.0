//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Copyright: 2012 to the present, California Institute of Technology.
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
#include "mocompTSXmodule.h"
#include <cmath>
#include <sstream>
#include <iostream>
#include <string>
#include <stdint.h>
#include <vector>
using namespace std;

static char * const __doc__ = "Python extension for mocompTSX.F";

PyModuleDef moduledef = {
    // header
    PyModuleDef_HEAD_INIT,
    // name of the module
    "mocompTSX",
    // module documentation string
    __doc__,
    // size of the per-interpreter state of the module;
    // -1 if this state is global
    -1,
    mocompTSX_methods,
};

// initialization function for the module
// *must* be called PyInit_mocompTSX
PyMODINIT_FUNC
PyInit_mocompTSX()
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

PyObject * allocate_dopplerCentroidCoefficients_C(PyObject* self, PyObject* args)
{
    int dim1 = 0;
    if(!PyArg_ParseTuple(args, "i", &dim1))
    {
        return NULL;
    }
    allocate_dopplerCentroidCoefficients_f(&dim1);
    return Py_BuildValue("i", 0);
}

PyObject * deallocate_dopplerCentroidCoefficients_C(PyObject* self, PyObject* args)
{
    deallocate_dopplerCentroidCoefficients_f();
    return Py_BuildValue("i", 0);
}

PyObject * allocate_time_C(PyObject* self, PyObject* args)
{
    int dim1 = 0;
    if(!PyArg_ParseTuple(args, "i", &dim1))
    {
        return NULL;
    }
    allocate_time_f(&dim1);
    return Py_BuildValue("i", 0);
}

PyObject * deallocate_time_C(PyObject* self, PyObject* args)
{
    deallocate_time_f();
    return Py_BuildValue("i", 0);
}

PyObject * allocate_sch_C(PyObject* self, PyObject* args)
{
    int dim1 = 0;
    int dim2 = 0;
    if(!PyArg_ParseTuple(args, "ii", &dim1, &dim2))
    {
        return NULL;
    }
    allocate_sch_f(&dim1, &dim2);
    return Py_BuildValue("i", 0);
}

PyObject * deallocate_sch_C(PyObject* self, PyObject* args)
{
    deallocate_sch_f();
    return Py_BuildValue("i", 0);
}




PyObject * mocompTSX_C(PyObject* self, PyObject* args)
{
    uint64_t var0;
    uint64_t var1;
    if(!PyArg_ParseTuple(args, "KK",&var0,&var1))
    {
        return NULL;
    }
    mocompTSX_f(&var0,&var1);
    return Py_BuildValue("i", 0);
}
PyObject * setStdWriter_C(PyObject* self, PyObject* args)
{
    uint64_t var;
    if(!PyArg_ParseTuple(args, "K", &var))
    {
        return NULL;
    }
    setStdWriter_f(&var);
    return Py_BuildValue("i", 0);
}
PyObject * setNumberRangeBins_C(PyObject* self, PyObject* args)
{
    int var;
    if(!PyArg_ParseTuple(args, "i", &var))
    {
        return NULL;
    }
    setNumberRangeBins_f(&var);
    return Py_BuildValue("i", 0);
}
PyObject * setNumberAzLines_C(PyObject* self, PyObject* args)
{
    int var;
    if(!PyArg_ParseTuple(args, "i", &var))
    {
        return NULL;
    }
    setNumberAzLines_f(&var);
    return Py_BuildValue("i", 0);
}
PyObject * setLookSide_C(PyObject* self, PyObject* args)
{
    int var;
    if(!PyArg_ParseTuple(args,"i", &var))
    {
    return NULL;
    }
    setLookSide_f(&var);
    return Py_BuildValue("i",0);
}
PyObject * setDopplerCentroidCoefficients_C(PyObject* self, PyObject* args)
{
    int dim1 = 0;
    PyObject * list;
    if(!PyArg_ParseTuple(args, "Oi", &list,&dim1))
    {
        return NULL;
    }
    if(!PyList_Check(list))
    {
        cout << "Error in file " << __FILE__ << " at line " << __LINE__ <<
                ". Expecting a list type object" << endl;
        exit(1);
    }
    double *  vectorV = new double[dim1];
    for(int i = 0; i  < dim1; ++i)
    {
        PyObject * listEl = PyList_GetItem(list,i);
        if(listEl == NULL)
        {
            cout << "Error in file " << __FILE__ << " at line " << __LINE__ <<
                    ". Cannot retrieve list element" << endl;
            exit(1);
        }
        vectorV[i] = (double) PyFloat_AsDouble(listEl);
        if(PyErr_Occurred() != NULL)
        {
            cout << "Error in file " << __FILE__ << " at line " << __LINE__ <<
                    ". Cannot convert Py Object to C " << endl;
            exit(1);
        }
    }
    setDopplerCentroidCoefficients_f(vectorV, &dim1);
    delete [] vectorV;
    return Py_BuildValue("i", 0);
}

PyObject * setTime_C(PyObject* self, PyObject* args)
{
    int dim1 = 0;
    PyObject * list;
    if(!PyArg_ParseTuple(args, "Oi", &list,&dim1))
    {
        return NULL;
    }
    if(!PyList_Check(list))
    {
        cout << "Error in file " << __FILE__ << " at line " << __LINE__ <<
                ". Expecting a list type object" << endl;
        exit(1);
    }
    double *  vectorV = new double[dim1];
    for(int i = 0; i  < dim1; ++i)
    {
        PyObject * listEl = PyList_GetItem(list,i);
        if(listEl == NULL)
        {
            cout << "Error in file " << __FILE__ << " at line " << __LINE__ <<
                    ". Cannot retrieve list element" << endl;
            exit(1);
        }
        vectorV[i] = (double) PyFloat_AsDouble(listEl);
        if(PyErr_Occurred() != NULL)
        {
            cout << "Error in file " << __FILE__ << " at line " << __LINE__ <<
                    ". Cannot convert Py Object to C " << endl;
            exit(1);
        }
    }
    setTime_f(vectorV, &dim1);
    delete [] vectorV;
    return Py_BuildValue("i", 0);
}

PyObject * setPosition_C(PyObject* self, PyObject* args)
{
    PyObject * list;
    int dim1 = 0;
    int dim2 = 0;
    if(!PyArg_ParseTuple(args, "Oii", &list, &dim1, &dim2))
    {
        return NULL;
    }
    if(!PyList_Check(list))
    {
        cout << "Error in file " << __FILE__ << " at line " << __LINE__ <<
                ". Expecting a list type object" << endl;
        exit(1);
    }
    double *  vectorV = new double[dim1*dim2];
    for(int i = 0; i  < dim1; ++i)
    {
        PyObject * listEl = PyList_GetItem(list,i);
        if(!PyList_Check(listEl))
        {
            cout << "Error in file " << __FILE__ << " at line " << __LINE__ <<
                    ". Expecting a list type object" << endl;
            exit(1);
        }
        for(int j = 0; j < dim2; ++j)
        {
            PyObject * listElEl = PyList_GetItem(listEl,j);
            if(listElEl == NULL)
            {
                cout << "Error in file " << __FILE__ << " at line " <<
                        __LINE__ << ". Cannot retrieve list element" << endl;
                exit(1);
            }
            vectorV[dim2*i + j] = (double) PyFloat_AsDouble(listElEl);
            if(PyErr_Occurred() != NULL)
            {
                cout << "Error in file " << __FILE__ << " at line " <<
                        __LINE__ << ". Cannot convert Py Object to C " << endl;
                exit(1);
            }
        }
    }
    setPosition_f(vectorV, &dim1, &dim2);
    delete [] vectorV;
    return Py_BuildValue("i", 0);
}


PyObject * setPlanetLocalRadius_C(PyObject* self, PyObject* args)
{
    double var;
    if(!PyArg_ParseTuple(args, "d", &var))
    {
        return NULL;
    }
    setPlanetLocalRadius_f(&var);
    return Py_BuildValue("i", 0);
}
PyObject * setBodyFixedVelocity_C(PyObject* self, PyObject* args)
{
    double var;
    if(!PyArg_ParseTuple(args, "d", &var))
    {
        return NULL;
    }
    setBodyFixedVelocity_f(&var);
    return Py_BuildValue("i", 0);
}
PyObject * setSpacecraftHeight_C(PyObject* self, PyObject* args)
{
    double var;
    if(!PyArg_ParseTuple(args, "d", &var))
    {
        return NULL;
    }
    setSpacecraftHeight_f(&var);
    return Py_BuildValue("i", 0);
}
PyObject * setPRF_C(PyObject* self, PyObject* args)
{
    double var;
    if(!PyArg_ParseTuple(args, "d", &var))
    {
        return NULL;
    }
    setPRF_f(&var);
    return Py_BuildValue("i", 0);
}
PyObject * setRangeSamplingRate_C(PyObject* self, PyObject* args)
{
    double var;
    if(!PyArg_ParseTuple(args, "d", &var))
    {
        return NULL;
    }
    setRangeSamplingRate_f(&var);
    return Py_BuildValue("i", 0);
}
PyObject * setRadarWavelength_C(PyObject* self, PyObject* args)
{
    double var;
    if(!PyArg_ParseTuple(args, "d", &var))
    {
        return NULL;
    }
    setRadarWavelength_f(&var);
    return Py_BuildValue("i", 0);
}
PyObject * setRangeFisrtSample_C(PyObject* self, PyObject* args)
{
    double var;
    if(!PyArg_ParseTuple(args, "d", &var))
    {
        return NULL;
    }
    setRangeFisrtSample_f(&var);
    return Py_BuildValue("i", 0);
}
PyObject * getMocompIndex_C(PyObject* self, PyObject* args)
{
    int dim1 = 0;
    if(!PyArg_ParseTuple(args, "i", &dim1))
    {
        return NULL;
    }
    PyObject * list = PyList_New(dim1);
    double *  vectorV = new double[dim1];
    getMocompIndex_f(vectorV, &dim1);
    for(int i = 0; i  < dim1; ++i)
    {
        PyObject * listEl =  PyFloat_FromDouble((double) vectorV[i]);
        if(listEl == NULL)
        {
            cout << "Error in file " << __FILE__ << " at line " << __LINE__ <<
                    ". Cannot set list element" << endl;
            exit(1);
        }
        PyList_SetItem(list,i, listEl);
    }
    delete [] vectorV;
    return Py_BuildValue("N",list);
}

PyObject * getMocompPositionSize_C(PyObject* self, PyObject* args)
{
    int var;
    getMocompPositionSize_f(&var);
    return Py_BuildValue("i",var);
}

PyObject * getStartingRange_C(PyObject* self, PyObject *args)
{
    double var;
    getStartingRange_f(&var);
    return Py_BuildValue("d",var);
}

PyObject * getMocompPosition_C(PyObject* self, PyObject* args)
{
    int dim1 = 0;
    int dim2 = 0;
    if(!PyArg_ParseTuple(args, "ii", &dim1, &dim2))
    {
        return NULL;
    }
    PyObject * list1 = PyList_New(dim1);
    double *  vectorV = new double[dim1*dim2];
    getMocompPosition_f(vectorV, &dim1, &dim2);
    for(int i = 0; i  < dim1; ++i)
    {
        PyObject * list2 = PyList_New(dim2);
        for(int j = 0; j  < dim2; ++j)
        {
            PyObject * listEl =  PyFloat_FromDouble(
                (double) vectorV[i*dim2 + j]);
            if(listEl == NULL)
            {
                cout << "Error in file " << __FILE__ << " at line " <<
                        __LINE__ << ". Cannot set list element" << endl;
                exit(1);
            }
            PyList_SetItem(list2,j,listEl);
        }
        PyList_SetItem(list1,i,list2);
    }
    delete [] vectorV;
    return Py_BuildValue("N",list1);
}


// end of file
