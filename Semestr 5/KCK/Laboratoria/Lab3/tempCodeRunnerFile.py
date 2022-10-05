gradient_hsv_map(v):
    h = 120-v*120
    return hsv2rgb(h,1,1)