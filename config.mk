
# Project name
PROJECT = cacomantis

# CPU architecture : {avr0|...|avr6}
# Parts : {at90usb646|at90usb647|at90usb1286|at90usb1287|at90usb162|at90usb82}
MCU = at90usb1286

# Source files
CSRCS = \
    main.c\
    hid_task.c\
    usb_descriptors.c\
    usb_specific_request.c\
    at90usb128/lib_board/usb_key/usb_key.c\
    at90usb128/lib_mcu/usb/usb_drv.c\
    at90usb128/lib_mcu/util/start_boot.c\
    at90usb128/modules/usb/device_chap9/usb_device_task.c\
    at90usb128/modules/usb/device_chap9/usb_standard_request.c\
    at90usb128/modules/usb/usb_task.c\
    common/lib_mcu/wdt/wdt_drv.c\
    common/modules/scheduler/scheduler.c\

# Assembler source files
ASSRCS = \

