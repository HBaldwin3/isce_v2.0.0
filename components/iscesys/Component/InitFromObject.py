#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
# Copyright: 2009 to the present, California Institute of Technology.
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
##
#This class is an initializer and can be used with all the objects that inherit the Component class. It allows to initialize an object  
# by using other objects that contains the same variables. If the name of some variables in the initializing object differ from the names of the object
#that needs to be initialized then one could provide a translator, i.e. a dictionary where the key is to name of the variable as known in the 
#initialinzing object and the value is the name of the variable as known in the object to be initialized. The name of the variables are the ones 
#specified in the self.dictionaryOfVariables of each object (see Component). 
# Once an instance of this class is created (say obj), the object that needs to be initialized invokes the initComponent(obj) method (inherited from the Component class)  passing the instance as argument.
#@see Component::initComponent()
##
class InitFromObject(object):
    

##
# This method must be implemented by each initializer class. It returns a dictionary of dictionaries. The argument passed is the object from which the variables are extracted. 
#@return retDict dictionary of dictinaries.
    def init(self,object2Init):
        
        retDict = self.getValuesFromObject(object2Init,self.object,self.translator)
    
        return retDict

    
    
    # if a keyword used in object is called differently in object2Init, then put it in the dictionary translator where key = keyword in object2Init and value = keyword in object 
    def getValuesFromObject(self,object2Init,object,translator = None):

        retDict = {}
        if translator == None:
            translator = {}
        for key in object2Init.dictionaryOfVariables:
            if key in object.dictionaryOfVariables:
                val = object.dictionaryOfVariables[key]
                isUndef = False
                
                # hack to replace the word self with object
                exec('if (not ' + val[0].replace('self.','object.') + ') and (not ' + val[0].replace('self.','object.') + ' == 0) :isUndef = True')
                if not isUndef:
                    # hack to replace the word self with object
                    exec ('retDict[key] = {\'value\':'  + object.dictionaryOfVariables[key][0].replace('self.','object.') + '}')
            
            elif key in translator:
                val = object.dictionaryOfVariables[translator[key]]
                isUndef = False
                # hack to replace the word self with object
                exec ('if (not ' + val[0].replace('self.','object.') + ') and (not ' + val[0].replace('self.','object.') + ' == 0) :isUndef = True')
                if not isUndef:
                    exec ('retDict[key] = {\'value\':' + object.dictionaryOfVariables[translator[key]][0].replace('self.','object.') + '}')
        
        return retDict


##
# Constructor. It takes as argument the source object used to initialize the target object. Optionally it also takes a dictionary that fucntions as translator if some of the variables in the source and target object have different names.
#@param object source object from whcih to initialize the target object
#@param translator optional dictionary used if the source and taget object have variables with different names.
    def __init__(self, object, translator=None):
        self.object = object
        self.translator = translator
        return None

