import math
from time import sleep

import cv2
import numpy as np

def display(img):
    cv2.imshow('Output', img)
    if cv2.waitKey(0) & 0xFF == ord('q'):
        cv2.destroyAllWindows()
        cv2.waitKey(1)
    sleep(1)

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

def draw_contours(img, contours, min_size=0):
    contours_drawn = img.copy()
    for contour in contours:
        area = cv2.contourArea(contour)
        if area < min_size:
            continue
        contours_drawn = cv2.drawContours(contours_drawn, [contour], -1, (0,0,255), 2)
    return contours_drawn

def draw_line(img, start, finish, color=(0, 255, 0), thickness=1):
    return cv2.line(img, start, finish, color, thickness)

def opencv_contour_to_list(c1, z=0):
    result = []
    for point in c1:
        fullpoint = [point[0][0], point[0][1], z]
        result.append(fullpoint)
    result.reverse()
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
    for i in range(len(ctr)):
        i1 = i
        i2 = (i + 1) % len(ctr)
        p1 = ctr[i1]
        p2 = ctr[i2]
        if p1[1] * p2[1] < 0:  # signs have swapped, so has crossed x-axis
            # append point above x-axis
            if p1[1] > 0:
                candidates.append(i1)
            else:
                candidates.append(i2)

    # find rightmost out of these
    rightmost = candidates[0]
    rightmost_point = ctr[rightmost]
    for index in candidates:
        p = ctr[index]
        if p[0] > rightmost_point[0]:
            rightmost = index
            rightmost_point = p
    return rightmost

def angle_of_point(point):
    ''' find angle between 0 and 1 where 0 is x-axis and 1 is full revolution '''
    if point[0] == 0:
        if point[1] >= 0:
            return 0.25
        else:
            return 0.75
    ang = math.atan(point[1] / point[0])
    if point[0] < 0:
        # left half
        ang += math.pi
    if point[0] >= 0 and point[1] < 0:
        # bottom right quadrant
        ang += 2 * math.pi
    return ang / (2 * math.pi)

def reorder_from_index(lis, start):
    result = []
    for i in range(len(lis)):
        index = (start + i) % len(lis)
        result.append(lis[index])
    return result

def angle_monoticity(angs):
    ''' ensure angle is always increasing '''
    result = angs[:]
    for i in range(len(result)):
        if i == 0:
            continue
        ang_current = result[i]
        ang_previous = result[i - 1]
        if ang_current < ang_previous:
            result[i] = ang_previous
    return result

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

    c1reordered = reorder_from_index(c1, c1start)
    c2reordered = reorder_from_index(c2, c2start)
    
    c1angs = [angle_of_point(p) for p in c1reordered]
    c2angs = [angle_of_point(p) for p in c2reordered]

    c1angs = angle_monoticity(c1angs)
    c2angs = angle_monoticity(c2angs)

    # distance around contour by point count
    c1para = [x / len(c1angs) for x in range(len(c1angs))]
    c2para = [x / len(c2angs) for x in range(len(c2angs))]

    # weighted sum of angles and parameterisation
    ANG_WEIGHT = 0.7
    c1metrics = [ANG_WEIGHT * c1angs[i] + (1 - ANG_WEIGHT) * c1para[i] for i in range(len(c1angs))]
    c2metrics = [ANG_WEIGHT * c2angs[i] + (1 - ANG_WEIGHT) * c2para[i] for i in range(len(c2angs))]

    # path finding
    i = 0
    j = 0
    matches = [(0, 0)]
    while i < len(c1metrics) and j < len(c2metrics):
        # advance i and j so the metrics leapfrog
        if c1metrics[i] < c2metrics[j]:
            i += 1
        else:
            j +=1
        matches.append((i, j))
    
    # triangle fan match remaining points
    # note i == len(c1metrics) when starting point has been cycled to
    while i < len(c1metrics): 
        i += 1
        matches.append((i, j))

    # and respectively for j
    while j < len(c2metrics):
        j += 1
        matches.append((i, j))
    
    matches_fixed_order = []
    for match in matches:
        i = (match[0] + c1start) % len(c1metrics)
        j = (match[1] + c2start) % len(c2metrics)
        matches_fixed_order.append((i, j))
    
    #find (0, 0) in new list
    actual_start = None
    for m in range(len(matches_fixed_order)):
        match = matches_fixed_order[m]
        if match == (0, 0):
            actual_start = m
    original_matches = reorder_from_index(matches_fixed_order, actual_start)
    # TODO may have to change 0 indices at end of original_matches
    return original_matches

def main():
    ''' tests '''
    contour1 = get_contour_from_image("Modifications/data/contour_single.png")
    contour2 = get_contour_from_image("Modifications/data/contour_double.png")
    matches = correspond(contour1, contour2)

    black = np.zeros((128, 128, 3), np.uint8) # 128 is width/height of test images
    black = draw_contours(black, [contour1, contour2])
    STEP = 4
    for m in range(0, len(matches), STEP):
        match = matches[m]
        start = tuple(contour1[match[0]][0])
        end = tuple(contour2[match[1]][0])
        black = draw_line(black, start, end)
    display(black)

if __name__ == "__main__":
    main()