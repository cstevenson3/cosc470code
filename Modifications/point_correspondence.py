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

def draw_contours(img, contours, min_size=0, x=0, y=0):
    if len(contours) > 0 and not isinstance(contours[0], list):
        contours = [opencv_contour_to_list(c) for c in contours]
    contours = [translate(c, x=x, y=y) for c in contours]
    contours = [list_to_opencv_contour(c) for c in contours]
    contours_drawn = img.copy()
    for contour in contours:
        area = cv2.contourArea(contour)
        if area < min_size:
            continue
        contours_drawn = cv2.drawContours(contours_drawn, [contour], -1, (0,0,255), 2)
    return contours_drawn

def display_contours(contours):
    black = np.zeros((128, 128, 3), np.uint8) # 128 is width/height of test images
    black = draw_contours(black, contours, x=64, y=64)
    display(black)

def draw_line(img, start, finish, color=(0, 255, 0), thickness=1):
    return cv2.line(img, start, finish, color, thickness)

def draw_dot(img, centre, size=2, color=(0, 255, 0), thickness=-1):
    return cv2.circle(img, centre, size, color, thickness)

def opencv_contour_to_list(c1, z=0):
    result = []
    for point in c1:
        fullpoint = [point[0][0], point[0][1], z]
        result.append(fullpoint)
    result.reverse()
    return result

def list_to_opencv_contour(ctr):
    squashed = [[p[0:2]] for p in ctr]
    out = np.array(squashed, dtype=np.int32)
    return out

def get_contour_from_image(filename):
    img = import_image(filename)
    img = binarize(img)
    c = find_contours(img)[0]

    return c

def multiply(scale, vec):
    return [scale * vec[i] for i in range(len(vec))]

def add(left, right):
    return [left[i] + right[i] for i in range(len(left))]

def subtract(left, right):
    return [left[i] - right[i] for i in range(len(left))]

def cross(p0, p1):
    return p0[0] * p1[1] - p0[1] * p1[0]

def centroid(ctr):
    ''' centroid of list of points defining counter-clockwise closed curve ''' 
    triangles = []
    for i in range(0, len(ctr) - 2):
        p0 = ctr[0]
        p1 = ctr[i + 1]
        p2 = ctr[i + 2]

        triangle_centroid = multiply(1.0 / 3.0, [sum(x) for x in zip(p0, p1, p2)])
        triangle_area = cross(subtract(p1, p0), subtract(p2, p0)) / 2.0
        triangles.append((triangle_centroid, triangle_area))

    total_area = 0
    centroid = [0, 0]
    for tri in triangles:
        part = multiply(tri[1], tri[0])
        centroid = add(centroid, part)
        total_area += tri[1]
    centroid = multiply(1.0 / total_area, centroid)
    return centroid

def centroid_opencv(ctr):
    M = cv2.moments(ctr)
    cX = int(M["m10"] / M["m00"])
    cY = int(M["m01"] / M["m00"])
    return (cX, cY)

def translate(points, x=0, y=0, z=0):
    ''' create new points list translated '''
    result = []
    for p in points:
        p_new = p[:]
        if x != 0:
            p_new[0] += x
        if y != 0:
            p_new[1] += y
        if z != 0:
            p_new[2] += z
        result.append(p_new)
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
    # add in z
    oc1 = opencv_contour_to_list(ctr1, z=0)
    oc2 = opencv_contour_to_list(ctr2, z=128)

    # find centroids
    # c1x, c1y = centroid_opencv(ctr1)
    # c2x, c2y = centroid_opencv(ctr2)
    c1x, c1y = centroid(oc1)
    c2x, c2y = centroid(oc2)

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
    ANG_WEIGHT = 0.3
    c1metrics = [ANG_WEIGHT * c1angs[i] + (1 - ANG_WEIGHT) * c1para[i] for i in range(len(c1angs))]
    c2metrics = [ANG_WEIGHT * c2angs[i] + (1 - ANG_WEIGHT) * c2para[i] for i in range(len(c2angs))]

    # path finding
    i = 0
    j = 0
    matches = [(0, 0)]
    while i < len(c1metrics) - 1 and j < len(c2metrics) - 1:
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
    
    return matches_fixed_order, [(c1x, c1y), (c2x, c2y)]

def linear_regression(points):
    ''' return (m, b) so that y = mx + b is best fit of points '''
    x_mean = sum([p[0] for p in points]) / len(points)
    SSxx = sum([(p[0] - x_mean) ** 2 for p in points])

    y_mean = sum([p[1] for p in points]) / len(points)
    SSxy = sum([(p[0] - x_mean) * (p[1] - y_mean) for p in points])  # TODO may need abs()

    slope = SSxy / SSxx if SSxx !=0 else 9999
    b = y_mean - slope * x_mean

    return (slope, b)

def linear_regression_2(points):
    n = len(points)
    xs = [p[0] for p in points]
    ys = [p[1] for p in points]
    sumX = sum(xs)
    sumX2 = sum([x * x for x in xs])
    sumY = sum(ys)
    sumXY = sum([p[0] * p[1] for p in points])

    b = (n * sumXY - sumX * sumY) / (n * sumX2 - sumX * sumX)
    m = (sumY - b * sumX) / n

    return (m, b)

def linear_regression_3(points):
    sum_x = 0
    sum_y = 0
    for p in points:
        if p[0] < 0:
            sum_x += -p[0]
            sum_y += -p[1]
        else:
            sum_x += p[0]
            sum_y += p[1]
    return (sum_y/sum_x if sum_x != 0 else 9999), 0

def linear_regression_4(points):
    # find best ax + by = 0
    best_distance = float("inf")
    best_a = 1
    best_b = 1
    for a in range(10):
        for b in range(10):
            total_distance = 0
            for p in points:
                distance = abs(a * p[0] + b * p[1]) / math.sqrt(a * a + b * b)
                total_distance += distance
            if total_distance < best_distance:
                best_distance = total_distance
                best_a = a
                best_b = b
    return -best_a/best_b, 0


def rotate_point(p, ang):
    x_new = p[0] * math.cos(ang) - p[1] * math.sin(ang)
    y_new = p[0] * math.sin(ang) + p[1] * math.cos(ang)

    point_new = [x_new, y_new] + list(p)[2:]

    return point_new

def rotate_contour(ctr, ang):
    return [rotate_point(p, ang) for p in ctr]

def aligned_dtw(ctr1, ctr2):
    oc1 = opencv_contour_to_list(ctr1, z=0)
    oc2 = opencv_contour_to_list(ctr2, z=128)

    c1x, c1y = centroid(oc1)
    c2x, c2y = centroid(oc2)

    # make it so each contour's centroid is at 0, 0
    c1 = translate(oc1, x=-c1x, y=-c1y)
    c2 = translate(oc2, x=-c2x, y=-c2y)
    display_contours([c1, c2])

    # find dominant axis first contour
    c1m, c1b = linear_regression_4(c1)

    # rotate both contours by this amount
    c1rad = math.atan(c1m)
    c1r = rotate_contour(c1, -c1rad)
    c2r1 = rotate_contour(c2, -c1rad)
    display_contours([c1r, c2r1])

    # correct second contour
    c2m, c2b = linear_regression_4(c2r1)
    c2rad = math.atan(c2m)
    c2r = rotate_contour(c2r1, -c2rad)

    display_contours([c1r, c2r])

    # run DTW on each of these
    # for this python test, will use point_angle as a substitute
    # matches = correspond(c1r, c2r)

def test_point_angle(contour1, contour2):
    matches, centroids = correspond(contour1, contour2)

    black = np.zeros((128, 128, 3), np.uint8) # 128 is width/height of test images
    black = draw_contours(black, [contour1, contour2])
    STEP = 4
    for m in range(0, len(matches), STEP):
        match = matches[m]
        start = tuple(contour1[match[0]][0])
        end = tuple(contour2[match[1]][0])
        black = draw_line(black, start, end)
    centroids = [(int(c[0]), int(c[1])) for c in centroids]
    # for centroid in centroids:
    #     draw_dot(black, centroid, color=(255, 255, 255))
    draw_dot(black, centroids[0], color=(255, 255, 255))
    display(black)

def main():
    ''' tests '''
    contour1 = get_contour_from_image("Modifications/data/contour1.png")
    contour2 = get_contour_from_image("Modifications/data/contour2.png")
    
    aligned_dtw(contour1, contour2)

if __name__ == "__main__":
    main()