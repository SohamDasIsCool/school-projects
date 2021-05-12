from __future__ import print_function

from sense_hat import SenseHat
import time

import string
from PIL import Image, ImageFont, ImageDraw
import numpy as np

from utils import compress_and_average

sense = SenseHat()

def char_to_pixels(text, path='arialbd.ttf', fontsize=14):
    font = ImageFont.truetype(path, fontsize)
    w, h = font.getsize(text)
    h *= 2
    image = Image.new('L', (w, h), 1)
    draw = ImageDraw.Draw(image)
    draw.text((0, 0), text, font=font)
    arr = np.asarray(image)
    arr = np.where(arr, 0, 1)
    arr = arr[(arr != 0).any(axis=1)]
    return arr

def display(arr):
    for x in range(8):
        for y in range(8):
            arrItem = arr[x][7 - y]

            b = round(255 * arrItem)

            if b < 0:
                b = 0
            if b > 255:
                b = 255

            sense.set_pixel(x, y, [b, b, b])

try:
    while True:
        sense.clear()

        for c in input(") ").upper():
            display(
                compress_and_average(
                    char_to_pixels(
                        c,
                        path='Vera.ttf',
                        fontsize=32
                    ),
                    (8, 8)
                ).tolist()
            )

            time.sleep(.35)
except KeyboardInterrupt:
    sense.clear()