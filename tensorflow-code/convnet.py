import tensorflow as tf
import numpy as np

res = 56
n_classes = 2
fi = int(res/8) # Make sure you divide by 2^number of pools you do , and also make sure it divides nicely

keep_rate = 0.8
keep_prob = tf.placeholder(tf.float32)



def neural_network_model(x,k = 11):
  print("Convolutional Neural Network")
  weights = {'W_conv1':tf.Variable(tf.random_normal([k,k,1,32])),
             'W_conv2':tf.Variable(tf.random_normal([3,3,32,32])),
             'W_conv3':tf.Variable(tf.random_normal([3,3,32,32])),
             'W_fc':tf.Variable(tf.random_normal([fi*fi*32,64])),
             'out':tf.Variable(tf.random_normal([64, n_classes]))} 
  biases = {'b_conv1':tf.Variable(tf.random_normal([32])),
            'b_conv2':tf.Variable(tf.random_normal([32])),
            'b_conv3':tf.Variable(tf.random_normal([32])),
            'b_fc':tf.Variable(tf.random_normal([64])),
            'out':tf.Variable(tf.random_normal([n_classes]))}  
  x = tf.reshape(x,shape=[-1,res,res,1])
  x = tf.nn.dropout(x,keep_rate)
  conv1  = tf.nn.relu(conv2d(x,weights['W_conv1']) + biases['b_conv1'])
  conv1 = maxpool2d(conv1)
  print(conv1.get_shape())
  conv1 = tf.nn.dropout(conv1,keep_rate)
  conv2  = tf.nn.relu(conv2d(conv1,weights['W_conv2']) + biases['b_conv2'])
  conv2 = maxpool2d(conv2)
  print(conv2.get_shape())

  conv2 = tf.nn.dropout(conv2,keep_rate)
  conv3  = tf.nn.relu(conv2d(conv2,weights['W_conv3']) + biases['b_conv3'])
  conv3 = maxpool2d(conv3)

  fc = tf.nn.lrn(conv3)
  fc = tf.reshape(fc,[-1,fi*fi*32])
  fc = tf.nn.dropout(fc,keep_rate)
  fc = tf.nn.relu(tf.matmul(fc,weights['W_fc']) + biases['b_fc'])

  fc = tf.nn.dropout(fc,keep_rate)
  output = tf.matmul(fc,weights['out']) + biases['out']

  return output


def conv2d(x,W):
  return tf.nn.conv2d(x,W,strides=[1,1,1,1],padding='SAME')
'''
Comments and Links for Max Pool:

Check the following 2 links for more information regarding maxpool

https://stackoverflow.com/questions/37674306/what-is-the-difference-between-same-and-valid-padding-in-tf-nn-max-pool-of-t#39371113
https://www.tensorflow.org/api_docs/python/tf/nn/max_pool

TD;LR SAME Refers to zero padding
'''

def maxpool2d(x):
  return tf.nn.max_pool(x,ksize = [1,2,2,1],strides=[1,2,2,1],padding='SAME')

