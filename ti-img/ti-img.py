#This program takes an image as input and converts it to a Ti-83 image, in two formats. The program will produce
#a file named img_instructions.txt which contains Ti-BASIC code that will generate the image when executed, as 
#well as a file named image.8xi, which contains the image compiled into the Ti-83 format. Bitmaps already at a depth
#of 1 bit and of resolution 96x63 will be converted directly into this format, while any other image formats will
#be translated first, and may come out less clear due to lower resolution and color reduction. The option to highlight
#edges may be helpful in remedying this, by outlining objects in the image. If the image supplied had to be translated
#during the formatting, a third file will be produced, '1-bit processed.bmp', which contains the resized & recolored 
#image that will be converted to Ti-83 format.

import math
from PIL import Image,ImageFilter
g_width = -1
g_height = -1

#Reads the contents of a 1-bit bitmap file. This is a file that only has 2 possible colors.
#If the image is not in 96x63 1-bit depth bitmap format, a ValueError will be raised.
#param fileName: the name of the bitmap file to read.
#return: a 1-dimensional array of every pixel in the bitmap, left to right and top to bottom. Each pixel is converted to a byte of value 0 or 1.
def read_bmp(fileName):
    global g_width 
    global g_height 
    if fileName[-4:] != ".bmp":
        raise ValueError
    file = open(fileName, "rb")
    
    # Bitmap format has 54 byte header
    head = file.read(54)
    width = head[18] + (int(head[19]) << 8) + (int(head[20]) << 16) + (int(head[21]) << 24)
    height = head[22] + (int(head[23]) << 8) + (int(head[24]) << 16) + (int(head[25]) << 24)
    depth = head[28] + (int(head[29]) << 8)
    #Validate image format
    if width != 96 or height != 63 or depth != 1:
        raise ValueError
    g_width = width
    g_height = height
    
    # the lines of pixels are aligned on a 4-byte boundary
    lineSize = (width // 8 + (width // 8) % 4)
    fileSize = lineSize * height

    #Allocate space to write image data, 1 byte for each bit
    img = [None] * width * height

    #skip the header and palette. 0 means absolute pos
    file.seek(62, 0)
    data = file.read(fileSize)

    #decode pixel bytes into bits
    for row in range(height): 
        for column in range(width // 8):
            #current_pixel_byte is the current byte, holding 8 pixels
            current_pixel_byte = row * lineSize + column
            position = (height - 1 - row) * width + column * 8
            for k in range(8):
                img[position + (7 - k)] = (data[current_pixel_byte] >> k ) & 1
    file.close()
    return img

#Reads images and converts them into 96x63 1-bit depth bitmap format.
#param fileName: the name of the image file to read.
#return: a 1-dimensional array of every pixel in the image after it is converted to a 96x63 bitmap with 1 bit depth, left to right and top to bottom. Each pixel is converted to a byte of value 0 or 1.
def read_image(fileName):
    global g_width
    global g_height
    filter = input("You have entered an image without 1-bit depth 96x63 bitmap format. Would you like to filter the image to highlight outlines? (Enable this if images come out hard to see. y/n)")
    img = Image.open(fileName)
    w, h = img.size
    aspect = min(96 / w, 63 / h)
    if filter == 'y':
        img = img.resize((int(w * aspect), int(h * aspect)), Image.BICUBIC).filter(ImageFilter.FIND_EDGES).convert('1')
    else:
        img = img.resize((int(w * aspect), int(h * aspect)), Image.BICUBIC).convert('1')
    img.save('1-bit processed.bmp')
    data = [x & 1 for x in list(img.getdata())]
    g_width, g_height = img.size
    return data

print("Note: Ti-83 devices have a 96x63 pixel display, with 1-bit color depth. Images matching this profile will work best. Bitmaps must be 1-bit depth & 96x63 already. The program will attempt to resize and recolor any other images, however, they may not be clearly visible.\n\nEnter file name: ", end='')
fileName = str(input())
#Attempt to read the image as a 96x63 1-bit depth bitmap, otherwise try to reformat it.
try:
    data = read_bmp(fileName)
except ValueError:
    data = read_image(fileName)
print("Image data:")
#Create an array with the image's data, padded to fill out the 96x63 pixel space (resized images may not be wide or tall enough without padding)
#var_data_bytes holds the bytes from data[] but padded
#var_data will contain the bytes from var_data_bytes but formatted for Ti 83 variable data specifications.
var_data_bytes = bytearray()
var_data = bytearray()
for j in range(g_height):
    for i in range(96):
        if i < g_width:
            var_data_bytes = var_data_bytes + (data[j * g_width + i]).to_bytes(1, byteorder='little')
            print('&&' if data[j * g_width + i] == 0 else '  ', end='')
        else:
            var_data_bytes = var_data_bytes + (0).to_bytes(1, byteorder='little')
    print("")
print("\nCreating Ti-83 formatted image data for the picture above...\n")
#If the image is too short to fill the Ti 83's screen, extend it with empty spaces.
if len(var_data_bytes) < 6048:
    var_data_bytes = var_data_bytes + [0] * 6048

for x in range(len(var_data_bytes) // 8):
    b = 0
    for y in range(8):
        b = b + (var_data_bytes[x + y] << (7 - y))
    var_data = var_data + b.to_bytes(1, byteorder='little')
#Add the Ti 83 format header to the variable data
var_data = b"\xf4\x02" + var_data[:756]

#Create a file containing the necessary Ti-BASIC instructions
output = open("img_instructions.txt", "w+")
output.write("ClrDraw\nAxesOff\n")
for pointer in range(len(data)):
    #0 indicates a black pixel, which is enabled on the Ti 83 screen
    if data[pointer] == 0:
        #identify coords
        xPos = pointer % g_width
        yPos = pointer // g_width
        output.write("Pxl-On(" + str(yPos) + "," + str(xPos) + ")\n")
        #Pixels disabled by default on Ti systems
output.close()
print("File created: img_instructions.txt")

#Write 8xi compiled Ti 83 image file
#Signature bytes, variable data size, var type ID, var name, flags, var data size (again)
data_size = (len(var_data)).to_bytes(2, byteorder='little', signed=False)
data8xi = bytearray(b"\x0d\x00" + data_size + b"\x05" + b"IMAGE\x00\x00\x00" + b"\x00\x00" + data_size)
data8xi = data8xi + var_data
data8xi[2:3] = ()
data8xi[15:16] = (len(var_data)).to_bytes(2, byteorder='little', signed=False)

full8xi = bytearray(b"**TI83F*" + b"\x1A\x0A\x00" + b"\x00" * 42 + (len(data8xi)).to_bytes(2, byteorder='little', signed=False) + data8xi + b"\x44\x44")

checksum = 0
for byte in data8xi:
    checksum = checksum + int(byte)
full8xi[-2:] = (checksum).to_bytes(20, byteorder='little', signed=False)[:2]

output2 = open("image.8xi", "w+b")
output2.write(full8xi)
output2.close()
print("File created: image.8xi")
