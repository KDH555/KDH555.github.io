import matplotlib.pyplot as plt
import tensorflow as tf
import keras

# mnist_data = keras.datasets.mnist.load_data()
# print(mnist_data)
# (X_train, y_train), (X_test, y_test) = mnist_data
# print(X_train.shape)
# print(X_test.shape)
#
# X_train = X_train.reshape((-1, 28*28))
# X_test = X_test.reshape((-1, 28*28))
#
# # 스케일링 해줘야 합니다.
# X_train = X_train.astype('float32') / 255.0
# X_test = X_test.astype('float32') / 255.0
#
# # plt.imshow(X=X_train[0], cmap='gray')
# # print(y_train[0])
# # plt.show()
#
# # 신경망 구현
# model = keras.models.Sequential(layers=[], name="MNIST_MODEL")
# input_layer = keras.Input(shape=(28*28,), name="Input_Layer")
# model.add(layer=input_layer)
# layer1 = keras.layers.Dense(units=512, activation="relu")
# model.add(layer=layer1)
# output_layer = keras.layers.Dense(units=10, activation='softmax')
# model.add(output_layer)
#
# model.compile(optimizer='adam', loss='sparse_categorical_crossentropy', metrics=['accuracy'])
# model.summary()
# history = model.fit(x=X_train, y=y_train, epochs=10, verbose='auto')
# print(f'예측 정확도 : {model.evaluate(x=X_test, y=y_test)}')
# print(history.history['accuracy'])
#
# model.save('2025-03-25_MNIST.keras')

# good_model = keras.models.load_model('2025-03-25_MNIST.keras') # (주석)코드 40줄이랑 교환
good_model = keras.models.load_model('2025_03_27_CNN.keras') # MaxPooling 방식으로 저장한 파일 불러옴
# y_predict = good_model.predict(x=X_test)

import cv2 as cv
original = cv.imread('test4.png', cv.IMREAD_GRAYSCALE)
# original = 255 - original
image = cv.resize(original,(28, 28))
image = 255 - image
image = image.astype('float32')
# image = image.reshape(-1, 784) # 평탄화 (주석)코드 50줄이랑 교환
image = image.reshape(-1, 28, 28, 1) # MaxPooling 파일로 바꾸면서 평탄화 코드 변경(코드 49줄 -> 50줄)
image = image / 255.0

predict_image = good_model.predict(image)
print(f'그림이미지 값은 : {predict_image}')
print(f'추정된 숫자 : {predict_image.argmax()}')

"""
313/313 ━━━━━━━━━━━━━━━━━━━━ 0s 868us/step - accuracy: 0.9367 - loss: 0.4442
예측 정확도 : [0.3987062871456146, 0.9456999897956848]
"""
