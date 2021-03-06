#!/usr/bin/env python3 

#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
# Copyright: 2010 to the present, California Institute of Technology.
# ALL RIGHTS RESERVED. United States Government Sponsorship acknowledged.
# Any commercial use must be negotiated with the Office of Technology Transfer
# at the California Institute of Technology.
# 
# This software may be subject to U.S. export control laws. By accepting this
# software, the user agrees to comply with all applicable U.S. export laws and
# regulations. User has the responsibility to obtain export licenses,  or other
# export authority as may be required before exporting such information to
# foreign countries or providing access to foreign persons.
# 
# Installation and use of this software is restricted by a license agreement
# between the licensee and the California Institute of Technology. It is the
# User's responsibility to abide by the terms of the license agreement.
#
# Author: Giangi Sacco
#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~






from __future__ import print_function
import sys
import os
import math
from iscesys.Compatibility import Compatibility
Compatibility.checkPythonVersion()

class ImageUtil:

    def copyAttributes(self,fromIm,toIm, listAtt = None):
        if not (listAtt == None):
            self._listOfAttributes = listAtt
        for att in self._listOfAttributes:
            try:
                fromAtt = getattr(fromIm,att)
                setattr(toIm,att,fromAtt)
            except Exception:
                pass# the image might not have the attributes listed by default

    def __init__(self):

        self._listOfAttributes = ['width','filename','byteOrder','dataType','xmin','xmax','numberGoodBytes','firstLatitude','firstLongitude','deltaLatitude','deltaLongitude']
