#ifndef DataAccessorCaster_h
#define DataAccessorCaster_h

#ifndef MESSAGE
#define MESSAGE cout << "file " << __FILE__ << " line " << __LINE__ << endl;
#endif
#ifndef ERR_MESSAGE
#define ERR_MESSAGE cout << "Error in file " << __FILE__ << " at line " << __LINE__  << " Exiting" <<  endl; exit(1);
#endif

#include "InterleavedAccessor.h"
#include "DataAccessor.h"
#include "DataCaster.h"
#include <stdint.h>
using namespace std;

class DataAccessorCaster : public DataAccessor
{
    public:
        DataAccessorCaster(InterleavedAccessor * accessor, DataCaster * caster)
        {
            Accessor = accessor;
            Caster = caster;
            LineWidth = Accessor->getLineWidth();
            Bands = Accessor->getBands();
            DataSizeIn  = Caster->getDataSizeIn();
            DataSizeOut  = Caster->getDataSizeOut();
            LineCounter = 0;
        }           
        ~DataAccessorCaster(){}
        void getStreamAtPos(char * buf,int & pos,int & numEl);
        void setStreamAtPos(char * buf,int & pos,int & numEl);
        void getStream(char * buf,int & numEl);
        void setStream(char * buf,int & numEl);
        int getLine(char * buf, int  pos);
        int getLineBand(char * buf, int pos, int band);
        void setLine(char * buf, int pos);
        void setLineBand(char * buf, int pos, int band);
        void setLineSequential(char * buf);
        void setLineSequentialBand(char * buf, int band);
        int getLineSequential(char * buf);
        int getLineSequentialBand(char * buf, int band);
        void getSequentialElements(char * buf, int row, int col, int & numEl);
        void setSequentialElements(char * buf, int row, int col, int  numEl);
        void finalize();
    protected:
        
};

#endif //DataAccessorCaster_h
