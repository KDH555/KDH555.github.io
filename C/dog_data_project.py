import numpy as np
import matplotlib.pyplot as plt
from sklearn.neighbors import KNeighborsClassifier
from sklearn import metrics

# 기존 데이터
dachshund_length = [77, 78, 85, 83, 73, 77, 73, 88]
dachshund_height = [25, 28, 29, 38, 21, 22, 17, 35]
samoyed_length = [75, 77, 86, 86, 79, 83, 83, 88]
samoyed_height = [56, 57, 50, 53, 60, 53, 49, 61]

# 무작위 데이터 생성 함수
def generate_data_random(lengths, heights, n=200):
    data = []
    for _ in range(n):
        idx = np.random.randint(0, len(lengths))  # 기존 데이터에서 무작위 선택
        length = lengths[idx] + np.random.uniform(-5, 5)  # 길이 -5 ~ 5 랜덤 변형
        height = heights[idx] + np.random.uniform(-5, 5)  # 높이 -5 ~ 5 랜덤 변형
        data.append([length, height])
    return np.array(data)

# 닥스훈트와 사모예드 데이터 생성
dachshund_data = generate_data_random(dachshund_length, dachshund_height, 200)
samoyed_data = generate_data_random(samoyed_length, samoyed_height, 200)

# 레이블 생성 (0은 닥스훈트, 1은 사모예드)
dachshund_label = np.zeros(dachshund_data.shape[0])
samoyed_label = np.ones(samoyed_data.shape[0])

# 전체 데이터 합치기
dogs = np.vstack((dachshund_data, samoyed_data))
labels = np.concatenate((dachshund_label, samoyed_label))

# KNN 모델 학습
k = 3
knn = KNeighborsClassifier(n_neighbors=k)
knn.fit(dogs, labels)

# 5마리의 새로운 강아지 데이터 입력 (새로운 강아지 5마리)
new_dogs = np.array([
    [78, 29],  # (길이, 높이)
    [85, 34],
    [75, 53],
    [79, 23],
    [81, 32]])

# 예측
predictions = knn.predict(new_dogs)

# 결과 출력
dog_classes = {0: "닥스훈트", 1: "사모예드"}

# 입력 데이터와 결과 출력
print("입력 데이터와 예측 결과:\n")
for i, (data, prediction) in enumerate(zip(new_dogs, predictions)):
    print(f"강아지 {i+1} - 입력 데이터: (길이: {data[0]}, 높이: {data[1]}) --> 예측: {dog_classes[prediction]}")

# 정확도 출력
print("\n모델 정확도:", metrics.accuracy_score(labels, knn.predict(dogs)))

# 데이터 시각화
plt.scatter(dachshund_data[:, 0], dachshund_data[:, 1], c='blue', label='Dachshund', alpha=0.5)
plt.scatter(samoyed_data[:, 0], samoyed_data[:, 1], c='red', label='Samoyed', alpha=0.5)

# 예측한 데이터 시각화 (새로운 강아지)
for i, (data, prediction) in enumerate(zip(new_dogs, predictions)):
    plt.scatter(data[0], data[1], c='green', marker='*', edgecolors='black', s=150, label="New Dog" if i == 0 else "")

# 그래프 설정
plt.xlabel("Length")
plt.ylabel("Height")
plt.title("Dog Size")
plt.legend(loc='upper left')
plt.show()
