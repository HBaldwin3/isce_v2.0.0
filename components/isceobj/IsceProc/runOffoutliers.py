#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
# Copyright: 2013 to the present, California Institute of Technology.
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
# Author: Kosal Khun
#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~



# Comment: Adapted from InsarProc/runOffoutliers.py
import logging
import isceobj

logger = logging.getLogger('isce.isceProc.runOffoutliers')


def runOffoutliers(self, distance):
    refPol = self._isce.refPol
    stdWriter = self._stdWriter
    for sceneid1, sceneid2 in self._isce.pairsToCoreg:
        pair = (sceneid1, sceneid2)
        rgOffsets = self._isce.refinedOffsetFields[pair]
        catalog = isceobj.Catalog.createCatalog(self._isce.procDoc.name)
        sid = self._isce.formatname(pair)
        offsetField = run(rgOffsets, distance, stdWriter, catalog=catalog, sceneid=sid)
        self._isce.procDoc.addAllFromCatalog(catalog)
        self._isce.refinedOffsetFields[pair] = offsetField


def run(rgOffsets, distance, stdWriter, catalog=None, sceneid='NO_ID'):
    #offoutliers returns a list of modified locations
    #the list of lists is
    #list[0] = location across
    #list[1] = location  across offset
    #list[2] = location down
    #list[3] = location  down offset
    #list[4] = snr
    #list[5] = sig

    logger.info("Culling offset field outliers: %s" % sceneid)
    objOff = isceobj.createOffoutliers()
    objOff.wireInputPort(name='offsets', object=rgOffsets)
    objOff.setSNRThreshold(2.0)
    objOff.setDistance(distance)
    #set the tag used in the outfile. each message is precided by this tag
    #is the writer is not of "file" type the call has no effect
    stdWriter.setFileTag("offoutliers", "log")
    stdWriter.setFileTag("offoutliers", "err")
    stdWriter.setFileTag("offoutliers", "out")
    objOff.stdWriter = stdWriter.set_file_tags("offoutliers",
                                               "log",
                                               "err",
                                               "out")

    objOff.offoutliers()

    if catalog is not None:
        # Record the inputs and outputs
        isceobj.Catalog.recordInputsAndOutputs(catalog, objOff,
                                               "runOffoutliers.%s" % sceneid,
                                               logger,
                                               "runOffoutliers.%s" % sceneid)

    return objOff.getRefinedOffsetField()
