# LoRaMeshCapstone

## How to Access The Doxygen Library Documentation

1. The first step is to download the LoraMeshCapstone repository to your computer
2. Next open a terminal and navigate using the `cd [filepath]` command to the folders location
3. Once in the LoraMeshCapstone directory use the comand `make deepclean` followed by `make docs`, this will generate the doxygen documentations in the new docs directory in LoRaMeshCapstone, if the compile errors try instead the command `doxygen doxygen.conf`
4. You can access the docs file through file explorer and to access the documentation find the file labeled as index.html and double click to run it
this will open the document as a website to navigate in your web browser of choice


## How to Implement The Library

### Arduino Libraries needed

#### For MKRWAN1300
1. Arduino Low Power - by Arduino LLC
2. TimmerInterrupt_Generic - by Khoi Hoang
3. RTCZero - by Arduino LLC
4. Lora.h - by Sandeep Mistry