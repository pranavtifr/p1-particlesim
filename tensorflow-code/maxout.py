import tensorflow as tf

res = 28*28
n_classes = 2
n_maxout1 = 3
n_maxout2 = 3
n_maxout3 = 3
n_nodes_hl1 = 128
n_nodes_hl2 = 64
n_nodes_hl3 = 32

def maxout(x,n):
  out = x[0]
  for i in range(n):
    out = tf.maximum(x[i],out)
#
  return out

def neural_network_model(data):
  hl1 = []
  hl2 = []
  hl3 = []
  for i in range(n_maxout1):
    hl1.append({'weights':tf.Variable(tf.random_normal([res, n_nodes_hl1])),
                    'biases':tf.Variable(tf.random_normal([n_nodes_hl1]))})
  for i in range(n_maxout2):
    hl2.append({'weights':tf.Variable(tf.random_normal([n_nodes_hl1, n_nodes_hl2])),
                    'biases':tf.Variable(tf.random_normal([n_nodes_hl2]))})
  for i in range(n_maxout3):
    hl3.append({'weights':tf.Variable(tf.random_normal([n_nodes_hl2, n_nodes_hl3])),
                    'biases':tf.Variable(tf.random_normal([n_nodes_hl3]))})

#  for i in range(n_maxout4):
#    hl4.append({'weights':tf.Variable(tf.random_normal([n_nodes_hl3, n_nodes_hl4])),
#                    'biases':tf.Variable(tf.random_normal([n_nodes_hl4]))})

  output_layer = {'weights':tf.Variable(tf.random_normal([n_nodes_hl3, n_classes])),
                    'biases':tf.Variable(tf.random_normal([n_classes])),}

  l1 = []
  for i in range(n_maxout1):
    l1.append(tf.add(tf.matmul(data,hl1[i]['weights']), hl1[i]['biases']))
    
  fl1 = maxout(l1,n_maxout1)

  l2 = []
  for i in range(n_maxout2):
    l2.append(tf.add(tf.matmul(fl1,hl2[i]['weights']), hl2[i]['biases']))
    
  fl2 = maxout(l2,n_maxout2)

  l3 = []
  for i in range(n_maxout3):
    l3.append(tf.add(tf.matmul(fl2,hl3[i]['weights']), hl3[i]['biases']))

  fl3 = maxout(l3,n_maxout3)

#  l4 = []
#  for i in range(n_maxout4):
#    l4.append(tf.add(tf.matmul(fl3,hl4[i]['weights']), hl4[i]['biases']))

#  fl4 = maxout(l4,n_maxout4)

  output = tf.matmul(fl3,output_layer['weights']) + output_layer['biases']

  return output


