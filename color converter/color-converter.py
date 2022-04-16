import PIL.Image, PIL.ImageTk
import numpy as np
import math
import tkinter 
from tkinter import *
import tkinter.filedialog
import sys

#This program converts images from a regular 3-color cone view into a tritanopic view.
#This is accomplished by referencing a preprocessed view of a grid that contains
#the appropriate tritanoptic substitute for any particular color. The location of this
#pixel is determined by a bijective function that maps each possible RBG value to a location
#in a square with a width of 4096 pixels. It allows the user to select an image from the 
#local storage using the tkinter view, and then converts it according to the supplied
#tritanopic grid file. The converted image can be saved as 'out.png'.

#Generates a grid of colors as a reference. The grid is exported as 'colorgrid.png'.
#This grid demonstrates the positioning of each pixel in the grid according to its RGB values.
def genGrid():
    colorgrid = np.zeros([256*16,256*16,3], dtype=np.uint8)
    for b in range(0, 256):
        for g in range(0, 256):
            for r in range(0, 256):
                x = b % 16
                y = math.floor(b/16)
                colorgrid[y*256 + r][x*256 + g] = [r, g, b]
    cgimg = PIL.Image.fromarray(colorgrid, 'RGB')
    cgimg.save('colorgrid.png')
    print('done')

#Uses the tritangrid.png image as a lookup table. 
#param image_array_in: a numpy array representing the image data which will be converted
#param adjusted_grid: the adjusted_grid color grid which new colors will be referenced from.
#return: a new numpy array representing the image_array_in converted to the new coloring system specified by adjusted_grid.
def convertImg(image_array_in, adjusted_grid):
    p = image_array_in.copy()
    for xLoc in range(0, len(p[0])):
        for yLoc in range(0, len(p)):
            r = p[yLoc][xLoc][0]
            g = p[yLoc][xLoc][1]
            b = p[yLoc][xLoc][2]
            
            #The index of each color is based on the RGB values of the color it replaces.
            x = b % 16
            y = math.floor(b/16)
            p[yLoc][xLoc] = adjusted_grid[y*256 + r][x*256 + g]
    return p;

#Converts an image to a tritanopic view
#param image_in: the PIL.Image to be converted to a tritanopic color view
#return: a PIL.Image of the original image_in converted to tritanopic colors
def convertToTri(image_in):
    pal = np.array(image_in.convert('RGB'))
    try:
        grid = np.array(PIL.Image.open("tritangrid.png"))
    except IOError:
        print("tritangrid.png missing! The file must be in the directory which the execution is started from.")
        input("Press 'Enter' to exit...")
        sys.exit(1)
    f = convertImg(pal, grid)
    final = PIL.Image.fromarray(f, 'RGB')
    return final

#Lets the user select an image from the device's local storage, and loads in into the tkinter view
def select_image():
    #global variables required to avoid destruction of the image data after the function exits
    global pil_image
    global color_replaced_pil_image
    global image
    global color_replaced_image
    global canvas
    static_height = 250
    file = tkinter.filedialog.askopenfile(parent=root,mode='rb',title='Choose a file')
    pil_image = PIL.Image.open(file)
    iwidth, iheight = pil_image.size
    new_width = int(static_height * iwidth/iheight)
    color_replaced_pil_image = convertToTri(pil_image)
    image = PIL.ImageTk.PhotoImage(pil_image.resize((new_width, static_height)))
    color_replaced_image = PIL.ImageTk.PhotoImage(color_replaced_pil_image.resize((new_width, static_height)))
    imagesprite_o = canvas.create_image(new_width // 2, static_height // 2,image=image)
    imagesprite_n = canvas.create_image(new_width // 2, (static_height * 3 ) // 2,image=color_replaced_image)
    canvas.config(width=new_width,height=int(static_height * 2.5))
    file.close()
    
#Saves the image with replaced colors 
def save_image():
    global color_replaced_pil_image
    color_replaced_pil_image.save('out.png')

root = tkinter.Tk()
root.geometry('900x700')
canvas = tkinter.Canvas(root,width=0,height=0)
canvas.pack(expand=True, fill='y')
open_button = Button(root,text='Open File',command=select_image)
open_button.pack(expand=True, fill='y', side=RIGHT)
save_button = Button(root,text='Save Recolored Image',command=save_image)
save_button.pack(expand=True, fill='y', side=RIGHT)
root.mainloop()
