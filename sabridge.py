from functools import partial
from uuid import getnode
import time, sys, os, Queue
from dan import NoData
import struct
import custom

sys.path.insert(0, '/usr/lib/python2.7/bridge/')
from bridgeclient import BridgeClient

idfInfo = custom.idf()
odfInfo = custom.odf()
ODFcache = {}
IDFcache = {}

IDFsignal = {}
odf2Bridge = {}

incomming = {}
for f_name in [t[0] for t in odfInfo]:
    incomming[f_name] = 0
timestamp = time.time()

odfMap = {
    odf[0]: odf[1]
    for odf in odfInfo
}

os.system(r'echo "none" > /sys/class/leds/ds:green:usb/trigger')
os.system(r'echo "none" > /sys/class/leds/ds:green:wlan/trigger')


class app(dict):
    global ODFcache, IDFcache, odf2Bridge, odfMap

    host = custom.api_url
    device_name = custom.device_name
    device_model = custom.device_model
    device_addr = custom.device_addr
    username = custom.username   # optional
    push_interval = custom.push_interval  # global interval

    idf_list = [t[0] for t in idfInfo]
    odf_list = [t[0] for t in odfInfo]

    def __init__(self):	
                                                                                                                                                
        for DF in idfInfo:
            function_name = DF[0].replace('-','_')
            self.__dict__[function_name] = partial(self.forIDF, DF[0])

        for DF in self.odf_list:
            function_name = DF.replace('-','_')
            self.__dict__[function_name] = partial(self.forODF, DF)

        for ODF in self.odf_list:
            ODFcache[ODF] = Queue.Queue(maxsize=1)
            
        for IDF in self.idf_list:
            IDFcache[IDF] = Queue.Queue(maxsize=1)

        print('Detected idf:')
        for idf in self.idf_list:
            print('    {}'.format(idf))
        print('Detected odf:')
        for odf in self.odf_list:
            print('    {}'.format(odf))
                                            
            
    @staticmethod
    def forIDF(idf_name):
        global IDFcache, IDFsignal
        IDFsignal[idf_name] = 1
        if IDFcache[idf_name].qsize():
            os.system(r'echo "default-on" > /sys/class/leds/ds:green:wlan/trigger')
            value = IDFcache[idf_name].get()

            '''
            print 'IDF:({f}, {v!r})'.format(
                         f=idf_name, v=value,)
            '''
        
            os.system(r'echo "none" > /sys/class/leds/ds:green:wlan/trigger')
            return value
        else:
            return NoData()
            
    @staticmethod
    def forODF(odf_name, data):
        print(odf_name, data)
        os.system(r'echo "default-on" > /sys/class/leds/ds:green:wlan/trigger')
        global ODFcache 

        if ODFcache[odf_name].qsize():
            ODFcache[odf_name].get()
            ODFcache[odf_name].put(data)
        else:
            ODFcache[odf_name].put(data)
      
        os.system(r'echo "none" > /sys/class/leds/ds:green:wlan/trigger')

def odfdata_to_string(data, params):
    r = ''
    for i in range(len(data)):
        if params[i] == 'int':
            r += ',%9d' % int(data[i])
        elif params[i] == 'float':
            r += ',%9f' % float(data[i])
        else:
            r += ',%9d' % 0
    return r[1:]

def string_to_idfdata(data_list, params):
    if len(data_list) != len(params):
        return None
    r = []
    for i in range(len(params)):
        try:
            if params[i] == 'int':
                r.append(int(data_list[i]))
            elif params[i] == 'float':
                r.append(float(data_list[i]))
            else:
                return None
        except:
            return None
    return r 

BClient = BridgeClient()
def Bridge2Arduino():
    global incomming, ODFcache, IDFcache, timestamp, IDFsignal, odfMap

    while True:  
        for ODF in ODFcache:
            if ODFcache[ODF].qsize():	
                data = ODFcache[ODF].get()
            
                if data == None:
                    continue

                if len(data) != len(odfMap[ODF]):
                    print('ODF: %s, get data which wrong dimension' % ODF)
                BClient.put(ODF, odfdata_to_string(data, odfMap[ODF]))
                incomming[ODF] = incomming[ODF] ^ 1
                BClient.put('incomming_'+ODF, str(incomming[ODF]))
                print('BClient.put [%s]: %s. Incomming: %s' % (ODF, odfdata_to_string(data, odfMap[ODF]), str(incomming[ODF])))
                continue
                
            else:
                pass

        if time.time() - timestamp >= app.push_interval*0.5:
            for IDF in idfInfo:
                idfName = IDF[0]
                idfParams = IDF[1]
                if IDFsignal.get(idfName):
                    getValue = BClient.get(idfName)
                    IDFsignal[idfName] = 0
                else:
                    getValue = None    

                if getValue is None:
                    pass
                else:
                    v = string_to_idfdata(getValue.split(','), idfParams)
                    if v is not None:
                        print('BClient.get [%s]: %s.' % (idfName, v))
                        if IDFcache[idfName].qsize():
                            IDFcache[idfName].get()
                            IDFcache[idfName].put(v)
                        else:
                            IDFcache[idfName].put(v)
            timestamp = time.time()        




