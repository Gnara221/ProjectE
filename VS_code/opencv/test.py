'''
description:
param:
return:
'''
import numpy as np
import cv2
img=cv2.imread('123456.png',cv2.IMREAD_UNCHANGED)
cv2.namedWindow('img',cv2.WINDOW_AUTOSIZE)
cv2.imshow('img',img)
cv2.waitKey(0)
