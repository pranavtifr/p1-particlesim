from decimal import Decimal
import tensorflow as tf
import fcc
import convnet
import numpy as np
import imageprocess as im
import matplotlib.pyplot as plt
train_x,train_y,test_x,test_y = im.create_data('quark.img','gluon.img',0.1)
tf.logging.set_verbosity(tf.logging.DEBUG) 
n_classes = 2
res = 56*56 
hm_epochs = 10
batch_size = 400

x = tf.placeholder('float', [None, res])
y = tf.placeholder('float')

def train_neural_network(x):
  #prediction = convnet.neural_network_model(x)
  #prediction = fcc.neural_network_model_maxout(x)
  prediction = fcc.neural_network_model_relu(x)
  cost = tf.reduce_mean( tf.nn.softmax_cross_entropy_with_logits(logits=prediction,labels=y) )
  optimizer = tf.train.AdamOptimizer(learning_rate=0.001).minimize(cost)
  correct = tf.equal(tf.argmax(prediction, 1), tf.argmax(y, 1))
  accuracy = tf.reduce_mean(tf.cast(correct, 'float'))
  epoch_data = []
  accuracy_data = []
  loss_data = []
  with tf.Session() as sess:
    sess.run(tf.global_variables_initializer())
      
    for epoch in range(hm_epochs):
      epoch_loss = 0
      i=0
      while i < len(train_x):
        start = i
        end = i+batch_size
        batch_x = np.array(train_x[start:end])
        batch_y = np.array(train_y[start:end])

        _, c = sess.run([optimizer, cost], feed_dict={x: batch_x, y: batch_y})
        epoch_loss += c
        i+=batch_size
      epoch_data.append(epoch)           
      accuracy_data.append(accuracy.eval({x:test_x,y:test_y}))
      loss_data.append(epoch_loss)
      print('Epoch', epoch+1, 'completed out of',hm_epochs,'loss:','%.6E' % Decimal(epoch_loss))
#Plotting Code
    plt.plot(epoch_data,accuracy_data)
    plt.xlabel('Epochs')
    plt.ylabel('Accuracy')
    plt.savefig('acc_curve.png', bbox_inches='tight')   
    plt.show()
    plt.plot(epoch_data,loss_data)
    plt.xlabel('Epochs')
    plt.ylabel('Loss')
    plt.savefig('loss_curve.png', bbox_inches='tight')   
    plt.show()
#End Plotting Code
    correct_ans = np.array(test_y)
    myans = tf.nn.softmax(prediction)
    predicted_ans = np.array(myans.eval({x:test_x}))
    im.roc_plot(predicted_ans,correct_ans)
    print('Accuracy:',accuracy.eval({x:test_x, y:test_y}))

if __name__ == '__main__':
  print('Begin')
  train_neural_network(x)
  print('End')

