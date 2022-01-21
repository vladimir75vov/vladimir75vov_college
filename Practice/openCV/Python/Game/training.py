import os
import numpy as np
from numpy.core.defchararray import mod
import tensorflow as tf
from tensorflow import keras
from tensorflow.keras.models import Sequential
from tensorflow.keras.layers import Conv2D, MaxPooling2D, Dense, Flatten, Dropout, Convolution2D, Activation, GlobalAveragePooling2D
from tensorflow.keras import utils
from tensorflow.keras.preprocessing import image
from tensorflow.keras.preprocessing import image_dataset_from_directory
import matplotlib.pyplot as plt


BATCH_SIZE = 32
IMAGE_SIZE = (300, 300)
PATH = 'images'

train_dataset = image_dataset_from_directory(PATH,
                                     subset='training',
                                     seed=42,
                                     validation_split=0.1,
                                     batch_size=BATCH_SIZE,
                                     image_size=IMAGE_SIZE)

validation_dataset = image_dataset_from_directory(PATH,
                                     subset='validation',
                                     seed=42,
                                     validation_split=0.1,
                                     batch_size=BATCH_SIZE,
                                     image_size=IMAGE_SIZE)

class_names = train_dataset.class_names
print(class_names)

test_dataset = image_dataset_from_directory(PATH,
                                     batch_size=BATCH_SIZE,
                                     image_size=IMAGE_SIZE)

AUTOTUNE = tf.data.experimental.AUTOTUNE

train_dataset = train_dataset.prefetch(buffer_size=AUTOTUNE)
validation_dataset = validation_dataset.prefetch(buffer_size=AUTOTUNE)
test_dataset = test_dataset.prefetch(buffer_size=AUTOTUNE)

model = keras.Sequential([
    Flatten(input_shape=(300,300,3)),
    Dense(32, activation='relu'),
    Dense(64, activation='relu'),
    Dense(32, activation='relu'),
    Dense(3, activation='softmax')
])

model.compile(loss='sparse_categorical_crossentropy',
              optimizer="adam",
              metrics=['accuracy'])

history = model.fit(train_dataset, 
                    validation_data=validation_dataset,
                    epochs=1000,
                    verbose=2)

scores = model.evaluate(test_dataset, verbose=1)

print("Доля верных ответов на тестовых данных, в процентах:", round(scores[1] * 100, 4))

plt.plot(history.history['accuracy'], 
         label='Доля верных ответов на обучающем наборе')
plt.plot(history.history['val_accuracy'], 
         label='Доля верных ответов на проверочном наборе')
plt.xlabel('Эпоха обучения')
plt.ylabel('Доля верных ответов')
plt.legend()
plt.show()

#----

plt.plot(history.history['loss'], 
         label='Ошибка на обучающем наборе')
plt.plot(history.history['val_loss'], 
         label='Ошибка на проверочном наборе')
plt.xlabel('Эпоха обучения')
plt.ylabel('Ошибка')
plt.legend()
plt.show()

model.save("game-model.h5")