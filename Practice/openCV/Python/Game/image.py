import cv2
import os
import sys

cam = cv2.VideoCapture(0)

start = False
counter = 0
try:
    num_samples = int(sys.argv[1])
except:
    num_samples = 300

print(num_samples)

IMG_SAVE_PATH = 'images'
START_SIZE_WINDOW = (10,70)
SIZE_WINDOW = (300,300)

while True:
    ret, img = cam.read()
    
    if not ret:
        break
    
    if counter == num_samples:
       break
   
    cv2.rectangle(img, START_SIZE_WINDOW, (START_SIZE_WINDOW[0] + SIZE_WINDOW[0],START_SIZE_WINDOW[1] + SIZE_WINDOW[1]), (0, 255, 0), 2)
    
    k = cv2.waitKey(1)
    
    if k == ord('r'):
        name = '/scissors'
        IMG_SAVE_PATH += name
        try:
            os.mkdir(IMG_SAVE_PATH)
        except:
            pass
    
    if k == ord('a'):
        start = True
    
    if k == ord('q'):
        break
    
    if start:

        roi = img[START_SIZE_WINDOW[1]:START_SIZE_WINDOW[1] + SIZE_WINDOW[0],START_SIZE_WINDOW[0]:START_SIZE_WINDOW[0] + SIZE_WINDOW[1]]

        save_path = os.path.join(IMG_SAVE_PATH, '{}.jpg'.format(counter + 1))

        print(save_path)

        cv2.imwrite(save_path, roi)

        counter += 1
    
    cv2.imshow("Collecting images", img)

cam.release()
cv2.destroyAllWindows()
