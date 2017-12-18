import tensorflow as tf
import numpy as np
import math
import os
from glob import glob
from sklearn.ensemble import RandomForestClassifier
from sklearn.ensemble import ExtraTreesClassifier
from sklearn.ensemble import AdaBoostClassifier
from sklearn import tree
import imageprocess as im

#tf.logging.set_verbosity(tf.logging.DEBUG)
train_x,train_y,test_x,test_y = im.create_data('quark-phy.txt','gluon-phy.txt',0.1)
#train_x,train_y,test_x,test_y = im.create_data('quark.img','gluon.img',0.1)
train_y = np.array(train_y)[:,1]

#params = tf.contrib.tensor_forest.python.tensor_forest.ForestHParams( num_classes=3, num_features=4, num_trees=5, max_nodes=100, split_after_samples=50).fill()
#classifier = tf.contrib.tensor_forest.client.random_forest.TensorForestEstimator( params, model_dir="./tmp/")
#classifier.fit(x=x_train, y=y_train)
#classifier = tree.DecisionTreeClassifier()
classifier = AdaBoostClassifier()
classifier.fit(train_x, train_y)

#y_out = classifier.predict(x=x_test)
y_out = classifier.predict_proba(test_x)
print('Test Labels')
print(test_y[:20])
print(y_out[:20])

correct_ans1 = np.array(test_y)
predicted_ans1 = np.array(y_out)



classifier = RandomForestClassifier(n_jobs = -1,verbose = 1)
classifier.fit(train_x, train_y)

#y_out = classifier.predict(x=x_test)
y_out = classifier.predict_proba(test_x)
print('Test Labels')
print(test_y[:20])
print(y_out[:20])

correct_ans2 = np.array(test_y)
predicted_ans2 = np.array(y_out)

predicted_ans = list([predicted_ans1,predicted_ans2])
correct_ans = list([correct_ans1,correct_ans2])

im.roc_plot(predicted_ans,correct_ans)

