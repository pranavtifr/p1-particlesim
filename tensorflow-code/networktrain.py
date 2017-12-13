from decimal import Decimal
import tensorflow as tf
import maxout
import convnet
import numpy as np
import imageprocess as im

train_x,train_y,test_x,test_y = im.create_data('quark.img','gluon.img')

n_classes = 2
res = 28*28
hm_epochs = 15
batch_size = 100

x = tf.placeholder('float', [None, res])
y = tf.placeholder('float')

def train_neural_network(x):
	prediction = maxout.neural_network_model(x)
	cost = tf.reduce_mean( tf.nn.softmax_cross_entropy_with_logits(logits=prediction,labels=y) )
	optimizer = tf.train.AdamOptimizer(learning_rate=0.001).minimize(cost)

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

				_, c = sess.run([optimizer, cost], feed_dict={x: batch_x,
				                                              y: batch_y})
				epoch_loss += c
				i+=batch_size
				
			print('Epoch', epoch+1, 'completed out of',hm_epochs,'loss:','%.6E' % Decimal(epoch_loss))
		correct = tf.equal(tf.argmax(prediction, 1), tf.argmax(y, 1))
		accuracy = tf.reduce_mean(tf.cast(correct, 'float'))

		print('Accuracy:',accuracy.eval({x:test_x, y:test_y}))

if __name__ == '__main__':
  print('Begin')
  train_neural_network(x)
  print('End')

      #print('Epoch', epoch+1, 'completed out of',hm_epochs,'loss:','%.5E' % Decimal(epoch_loss))
