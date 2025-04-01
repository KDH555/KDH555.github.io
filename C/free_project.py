import serial
import tkinter as tk
from tkinter import filedialog
import cv2
import numpy as np
import keras

# 아두이노 시리얼 설정
ser = serial.Serial(port='COM3', baudrate=115200, timeout=2)

# 학습된 모델 불러오기
model = keras.models.load_model('FACE_CNN.keras')

# GUI 설정
window = tk.Tk()
window.title("사람 인식 및 LED 제어")
window.geometry("400x400")

# 이미지 업로드 및 예측 함수
def upload_image():
    filename = filedialog.askopenfilename()
    image = cv2.imread(filename)
    image = cv2.resize(image, (64, 64))  # 입력 크기에 맞게 조정
    image = np.expand_dims(image, axis=0) / 255.0  # 정규화
    prediction = model.predict(image)
    class_index = np.argmax(prediction)

    # 사람 인식 여부에 따라 LED 제어
    handle_prediction(class_index)

def handle_prediction(class_index):
    if class_index == 0:  # 사람 클래스
        ser.write(b'ON\n')  # LED 켜기
        result_label.config(text="사람을 인식함: LED 켜짐")
    else:
        ser.write(b'OFF\n')  # LED 끄기
        result_label.config(text="사람을 인식 못함: LED 꺼짐")

# GUI 요소
upload_button = tk.Button(window, text="이미지 업로드", command=upload_image)
upload_button.pack(pady=20)

result_label = tk.Label(window, text="")
result_label.pack(pady=20)

window.mainloop()
