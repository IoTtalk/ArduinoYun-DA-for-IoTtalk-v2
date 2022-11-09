ArduinoYun DA for IoTtalk v2
============================
For iottalk v2 client, you have to install ``paho-mqtt``. Remember to install version 1.4.0: https://pypi.org/project/paho-mqtt/1.4.0/.

.. code-block:: 

    wget https://files.pythonhosted.org/packages/25/63/db25e62979c2a716a74950c9ed658dce431b5cb01fde29eb6cba9489a904/paho-mqtt-1.4.0.tar.gz
    
    pip install paho-mqtt-1.4.0.tar.gz


To use this code, only ``custom.py`` needs to be modified.
This code uses device model ``MCU_board`` as an example, that is, the IDFs/ODFs are

.. code-block:: python

    def odf():
        return [  # ('odf_name', (param_strings in tuple))
          ('D2-O', ('int', )),
          ('D3-O', ('int', )),
          ('D4-O', ('int', )),
          ('D5Pwm-O', ('int', )),
          ('D6Pwm-O', ('int', )),
          ('D7-O', ('int', )),
          ('D8-O', ('int', )),
          ('D9Pwm-O', ('int', )),
        ]

.. code-block:: python

    def idf():

        return [  # ('idf_name', (params in tuple))
          (('A0-I', ('int', )),
          ('A1-I', ('int', )),
          ('A2-I', ('int', )),
          ('A3-I', ('int', )),
          ('A4-I', ('int', )),
          ('A5-I', ('int', )),
         ]
