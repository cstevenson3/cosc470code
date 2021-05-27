import cv2
import numpy as np

def import_image(filename):
    return cv2.imread(filename)

def gray(img):
    img = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)
    return img

def threshold(img, min=128):
    ret, t = cv2.threshold(img, min, 255, cv2.THRESH_BINARY)
    return t

def binarize(img):
    img = gray(img)
    img = threshold(img)
    return img

def find_contours(img):
    contours, hierarchy = cv2.findContours(img, cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE)
    return contours

def opencv_contour_to_list(c1, z=0):
    result = []
    for point in c1:
        fullpoint = [point[0][0], point[0][1], z]
        result.append(fullpoint)
    return result

def get_contour_from_image(filename):
    img = import_image(filename)
    img = binarize(img)
    c = find_contours(img)[0]

    return c

def centroid(ctr):
    M = cv2.moments(ctr)
    cX = int(M["m10"] / M["m00"])
    cY = int(M["m01"] / M["m00"])
    return (cX, cY)

def translate(points, x=0, y=0, z=0):
    ''' create new points list translated '''
    result = []
    for p in points:
        result.append([p[0] + x, p[1] + y, p[2] + z])
    return result

def starting_point(ctr):
    ''' looks for the furthest point out with near zero angle from the centroid '''

    # find starting candidates 
    candidates = []  # indices
    tolerance = 1.0  # in pixels
    while len(candidates) == 0:
        # try with current tolerance
        for i in range(len(ctr)):
            p = ctr[i]
            if abs(p[1]) < tolerance:
                candidates.append(i)
        tolerance += 1.0 # if nothing found increase tolerance

    # find rightmost out of these
    rightmost = candidates[0]
    rightmost_point = ctr[rightmost]
    for index in candidates:
        p = ctr[index]
        if p[0] > rightmost_point[0]:
            rightmost = index
            rightmost_point = p
    return rightmost

def correspond(ctr1, ctr2):
    ''' c1 and c2 are contours as lists of size-3 lists '''
    # find centroids
    c1x, c1y = centroid(ctr1)
    c2x, c2y = centroid(ctr2)

    # add in z
    oc1 = opencv_contour_to_list(ctr1, z=0)
    oc2 = opencv_contour_to_list(ctr2, z=128)

    # make it so each contour's centroid is at 0, 0
    c1 = translate(oc1, x=-c1x, y=-c1y)
    c2 = translate(oc2, x=-c2x, y=-c2y)

    c1start = starting_point(c1)
    c2start = starting_point(c2)
    print()

def main():
    ''' tests '''
    contour1 = get_contour_from_image("Modifications/data/contour_single.png")
    contour2 = get_contour_from_image("Modifications/data/contour_double.png")
    correspond(contour1, contour2)
    print()

if __name__ == "__main__":
    main()