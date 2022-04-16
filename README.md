# python scripting examples
 A description for each script can be found as a comment inside the code, and example screenshots are included.

Description of each project:

circuit_tester.py

The following script uses a truth table to test a rudimentary circuit I constructed several years ago. The circuit has a 2-bit memory made of flip-flops, which store opcode instructions. These instructions tell the data register to store 0, 1, or tell the adder to add 0+1, or 1+1. It will perform each of these operations and check to make sure the circuit puts out the right values, by controlling the pulse of the clock and reading values of each port. It accomplishes this using the general purpose IO on a Raspberry Pi. The program will print out a description of the test progress as it goes along, and at the end will show a count of how many errors occurred.

ti-img.py

This program takes an image as input and converts it to a Ti-83 image, in two formats. The program will produce a file named img_instructions.txt which contains Ti-BASIC code that will generate the image when executed, as well as a file named image.8xi, which contains the image compiled into the Ti-83 format. Bitmaps already at a depth of 1 bit and of resolution 96x63 will be converted directly into this format, while any other image formats will be translated first, and may come out less clear due to lower resolution and color reduction. The option to highlight edges may be helpful in remedying this, by outlining objects in the image. If the image supplied had to be translated during the formatting, a third file will be produced, '1-bit processed.bmp', which contains the resized & recolored image that will be converted to Ti-83 format.

message_deleter.py

This script will automatically fetch messages from Discord.com (IRC service) using their API, and delete all messages matching the parameters entered by the user. This includes the ID of the user who posted the messages, the channel they are in, and filtering to specific text.

color-converter.py

This program converts images from a regular 3-color cone view into a tritanopic view. This is accomplished by referencing a preprocessed view of a grid that contains the appropriate tritanoptic substitute for any particular color. The location of this pixel is determined by a bijective function that maps each possible RBG value to a location in a square with a width of 4096 pixels. It allows the user to select an image from the local storage using the tkinter view, and then converts it according to the supplied tritanopic grid file. The converted image can be saved as 'out.png'.

cipher tool.py

This script was made when one of my friends created a cipher and challenged me to crack it. While cracking the cipher, I made this script to encode and decode it. It was also helpful during the process of cracking it to have python handy, because its string manipulation capabilities are very versatile and assist in brute-forcing possible encodings. The format is as follows: "hello (there) world!" encodes to the numeric equivalent of "htw-ello(-here)-orld"
