## `Spooling` is a technique or algorithm used by Operating Systems to manage the task of printing and interaction with devices that access printing services. `"Simulatenous Peripherals Opertions On-line"`.

- When a user process is initiated to print some document.

  - The OS will not directly send the doc to printer, a digital copy of media is created and stored temoprarily in a designated area of storage called `print queue` or `spool`.
  - The OS free the resources of the process which gave the command to print.

- An OS daemon called `print daemon` or `print spoolers` is created, which is a background process ,now this daemon will.
  - This daemon will communicate with the device drivers and controllers to acess the printer device.
  - manage the `print queue` and error handling.