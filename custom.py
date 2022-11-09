api_url = 'IoTtalk Ver. 2 Server IP'
device_model = 'MCU_board'
device_name = None
# device_addr = 'your device addr'
username = None
push_interval = 0.5  # global interval

def odf():
    return [
        ('D2-O', ('int', )),
        ('D3-O', ('int', )),
        ('D4-O', ('int', )),
        ('D5Pwm-O', ('int', )),
        ('D6Pwm-O', ('int', )),
        ('D7-O', ('int', )),
        ('D8-O', ('int', )),
        ('D9Pwm-O', ('int', )),
    ]

def idf():
    return [
        ('A0-I', ('int', )),
        ('A1-I', ('int', )),
        ('A2-I', ('int', )),
        ('A3-I', ('int', )),
        ('A4-I', ('int', )),
        ('A5-I', ('int', )),
    ]