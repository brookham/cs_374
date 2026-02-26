## Building
Command Line:
- `make` to build the executable called grayscaler

## Files
- `grayscaler.c`: main code to launch the program
- `ppm.c`: defines ppm functions
- `ppm.h`: used to import ppm functions to main file

## Data
ppm files to be altered, size can vary

## Functions

- `main()`
  - `pthread_create()`: creates ne thread
  - `run()`: thread function
    - `ppm_get_pixel()`: gets pixel
    - `PPM_PIXEL_R()`: extract red channel
    - `PPM_PIXEL_G()`: extract green channel
    - `PPM_PIXEL_B()`: extract blue channel
    - `PPM_PIXEL()`: rturn rgb values into one pixel
    - `ppm_set_pixel()`: sets a pixel
  - `pthread_join()`: joins threads
  - `ppm_write()`: writes image data in the ppm struct
  - `ppm_free`: frees memory associated with ppm