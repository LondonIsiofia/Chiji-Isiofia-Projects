import threading
import cv2
import cv2.data
from deepface import DeepFace

#change to log faces
#change to apply to phone camera

print ("Loading FaceCardv2...")
print ("Activating webcam...")

cap = cv2.VideoCapture(0)

if not cap.isOpened():
    print("Error: Could not open webcam.")
if cap.isOpened:
    print("Webcam is live!. Press 'q' to quit.")
else:
    print("Unknown Error Occured.")

reference_images = [
    {"name": "London", "img": cv2.imread("/Users/london/Desktop/londonface.jpg")},
    {"name": "Ryan", "img": cv2.imread("/Users/london/Desktop/ryanface.jpg")},
    {"name": "LeBron James", "img": cv2.imread("/Users/london/C/Python Path/json/lebron.jpg.webp")}
]

for ref in reference_images:
    if ref["img"] is None:
        print(f"Error: Reference image for {ref['name']} not found.")
    else:
        print(f"Reference image for {ref['name']} loaded...")

cap.set(cv2.CAP_PROP_FRAME_WIDTH, 1920)
cap.set(cv2.CAP_PROP_FRAME_HEIGHT, 1080)

counter = 0
face_matches = []

def check_face(frame, face_roi, face_id):
    global face_matches
    try:
        for ref in reference_images:
            result = DeepFace.verify(face_roi, ref["img"])['verified']
            if result:
                face_matches[face_id] = ref["name"]
                return
            else:
                face_matches[face_id] = "Unknown"
    except Exception as e:
        print(f"Unable to verify. {e}")
        face_matches[face_id] = "Error"

while True:
    ret, frame = cap.read()

    if ret:
        cv2.putText(frame, "Searching for faces...", (20, 30), cv2.FONT_ITALIC, 1, (255, 255, 0), 2)

        if counter % 30 == 0:
            face_matches = ["Analyze"] * 5

            gray_frame = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)
            face_cascade = cv2.CascadeClassifier(cv2.data.haarcascades + "haarcascade_frontalface_default.xml")
            faces = face_cascade.detectMultiScale(gray_frame, scaleFactor=1.1, minNeighbors=5, minSize=(50, 50))

            for i, (x, y, w, h) in enumerate(faces):
                face_roi = frame[y:y+h, x:x+w]
                threading.Thread(target = check_face, args=(frame, face_roi.copy(), i)).start()

        counter += 1

        for i, (x, y, w, h) in enumerate(faces):
            cv2.rectangle(frame, (x, y), (x + w, y + h), (255, 0, 0), 2)
            if len(face_matches) > i and face_matches[i] != "Checking":
                label = face_matches[i]
                cv2.putText(frame, label, (x, y - 10), cv2.FONT_HERSHEY_COMPLEX, 1, (0, 255, 0) if label != "Unknown" else (0, 0, 255), 2)

        cv2.imshow("Ayala Feed", frame)

    key = cv2.waitKey(1)
    if key == ord("e"):
        break

cap.release()
cv2.destroyAllWindows()    
        