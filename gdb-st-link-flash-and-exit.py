# Load the serial number of the ST-Link to use from a file, if it exists.
serial_command = ''
try:
    with open('../../st-link-serial.txt') as f:
        st_link_serial = f.read().strip()
        serial_command = '-c "adapter serial ' + st_link_serial + '"'
        print('Using ST-Link: ' + st_link_serial)
except:
    serial_command = ''
    print('No ST-Link serial number configured')

# Start openocd and connect to it directly via pipe.
# Use the selected serial number, if one exists.
try:
    gdb.execute('target extended-remote | openocd ' + serial_command + ' -f interface/stlink-dap.cfg -f target/stm32f3x.cfg'
                                                                       ' -c "gdb_port pipe; log_output openocd.log"')
    gdb.execute('load')
    gdb.execute('monitor reset')
    gdb.execute('detach')
except Exception as e:
    print('** Error connecting to target **')
    print(e)
finally:
    gdb.execute('quit')
