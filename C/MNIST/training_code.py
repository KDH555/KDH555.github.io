import cv2  # OpenCV
import numpy as np
import matplotlib.pyplot as plt
import keras
import tensorflow as tf

# 이미지 로드 함수
def load_images_from_folder(folder:str, img_count:int) -> list[np.ndarray]:
    images = []
    for i in range(img_count):
        file = f'{folder}/img{i + 1:02d}.jpg'
        img = cv2.imread(file)  # 이미지로 변환
        img = cv2.resize(img, dsize=(64, 64))  # 크기 조정
        img = cv2.cvtColor(img, cv2.COLOR_BGR2RGB)  # BGR -> RGB로 변환
        images.append(img)
    return images

# 얼굴 및 동물 이미지 로드
face_images = load_images_from_folder('./faces', 15)
animal_images = load_images_from_folder('./animals', 15)

# 라벨 생성 (사람 [1, 0], 동물 [0, 1])
y = [(1, 0)] * len(face_images) + [(0, 1)] * len(animal_images)
y = np.array(y)  # numpy 배열로 변환

# 데이터 배열 생성
X = np.array(face_images + animal_images)
X = X / 255.0  # 정규화

# CNN 모델 정의
model = keras.Sequential(name='FACEDETECTOR')
model.add(keras.Input(shape=(64, 64, 3), name='Input_Layer'))
model.add(keras.layers.Conv2D(filters=128, kernel_size=3, activation='relu'))
model.add(keras.layers.MaxPooling2D(pool_size=(2, 2), strides=2))
model.add(keras.layers.Conv2D(filters=64, kernel_size=(3, 3), activation='relu'))
model.add(keras.layers.MaxPooling2D(pool_size=(2, 2), strides=2))
model.add(keras.layers.Conv2D(filters=32, kernel_size=(3, 3), activation='relu'))
model.add(keras.layers.MaxPooling2D(pool_size=(2, 2), strides=2))
model.add(keras.layers.Flatten(name='Flatten'))
model.add(keras.layers.Dense(units=128, activation='relu', name='HD1'))
model.add(keras.layers.Dense(units=32, activation='relu', name='HD2'))
model.add(keras.layers.Dense(units=2, activation='softmax', name='Output_Layer'))

# 모델 요약 출력
model.summary()

# 모델 컴파일
model.compile(optimizer='adam', loss='categorical_crossentropy', metrics=['accuracy'])

# 모델 훈련
history = model.fit(X, y, epochs=200, batch_size=8, validation_split=0.2)

# 훈련 정확도 평가
train_loss, train_accuracy = model.evaluate(X, y)
print(f"훈련 정확도 : {train_accuracy * 100:.2f}%")

# 모델 저장
model.save('FACE_CNN.keras')

# 테스트 이미지 로드 및 예측
test_images = load_images_from_folder('./faces', 10)
test_images = np.array(test_images) / 255.0  # 정규화
predict = model.predict(test_images)

# 예측 결과 출력
print(predict)

# 예측 결과 시각화
def show_image(row:int, col:int, image:list[np.ndarray]) -> None:
    (fig, ax) = plt.subplots(row, col, figsize=(col * 2, row * 2))
    for i in range(row):
        for j in range(col):
            axis = ax[i, j] if row > 1 else ax[j]
            axis.get_xaxis().set_visible(False)
            axis.get_yaxis().set_visible(False)
            axis.imshow(image[i * col + j])
    plt.show()
    return None

show_image(row=2, col=5, image=test_images)
