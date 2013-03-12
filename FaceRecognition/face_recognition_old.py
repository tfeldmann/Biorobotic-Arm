import cv
import numpy as np

CASCADE_PATH = "/usr/local/Cellar/opencv/2.4.3/share/OpenCV/haarcascades/"
FRONTALFACE_PATH = CASCADE_PATH+"haarcascade_frontalface_alt.xml"
PROFILEFACE_PATH = CASCADE_PATH+"haarcascade_profileface.xml"

CAMERA_INDEX = 0

def detect_faces(image):
    faces = []
    detected = cv.HaarDetectObjects(image, frontalface_cascade, storage, 1.2, 2,
        cv.CV_HAAR_DO_CANNY_PRUNING, (100,100))
    if detected:
        for (x,y,w,h),n in detected:
            faces.append((x,y,w,h))

    if len(faces) == 0:
        detected = cv.HaarDetectObjects(image, profileface_cascade, storage, 1.2, 2,
            cv.CV_HAAR_DO_CANNY_PRUNING, (100,100))
        if detected:
            for (x,y,w,h),n in detected:
                faces.append((x,y,w,h))

    return faces

if __name__ == "__main__":
    cv.NamedWindow("Face recognition", cv.CV_WINDOW_AUTOSIZE)

    capture = cv.CaptureFromCAM(CAMERA_INDEX)
    storage = cv.CreateMemStorage()
    frontalface_cascade = cv.Load(FRONTALFACE_PATH)
    profileface_cascade = cv.Load(PROFILEFACE_PATH)
    faces = []

    while True:
        image = cv.QueryFrame(capture)
        faces = detect_faces(image)

        for (x,y,w,h) in faces:
            cv.Rectangle(image, (x, y), (x+w, y+h), 255)

        cv.ShowImage("Video", image)

        if cv.WaitKey(33) == 27:
            break
