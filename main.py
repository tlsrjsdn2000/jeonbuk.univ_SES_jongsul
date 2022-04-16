import numpy as np
import cv2

img1 = cv2.imread('lec11 resource/lec11_field.bmp')
img2 = cv2.imread('lec11 resource/lec11_airplane.bmp')
width, height = img1.shape[1], img1.shape[0]
print(width, height)

fourcc = cv2.VideoWriter_fourcc(*'DIVX')
fps = 20
out = cv2.VideoWriter('output_201918150.avi',fourcc, fps, (width, height))

for i in range(100):
    if i < 20:
        img_out = img1
    elif i < 100-20:
        alpha = (i-20)/60
        img_out = cv2.addWeighted(img1, 1-alpha, img2, alpha, 0)
    else:
        img_out = img2

    out.write(img_out)

out.release()

#아~ 존나힘드네~ 무릎시려~~~
#wtf
#다시 해본다..