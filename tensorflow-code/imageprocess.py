import numpy as np
import random
def readfile(sample,classification):
    dataset = []
    hm_lines = 100000
    with open(sample) as f:
        data = [float(x) for x in next(f).split()] # read first line
        for line in f: # read rest of lines
            data = [float(x) for x in line.split()] # read first line
            dataset.append([data,classification])
            #print(dataset[:,0][0])
            #input("Press enter to continue")

    return dataset

def create_data(quark,gluon,test_size = 0.1):
    features = []
    features += readfile(quark,[1,0])
    features += readfile(gluon,[0,1])

    random.shuffle(features)
    features = np.array(features)
    print('Length of Features is')
    print(len(features))
    testing_size = int(test_size*len(features))

    train_x = list(features[:,0][:-testing_size])
    train_y = list(features[:,1][:-testing_size])
    test_x = list(features[:,0][-testing_size:])
    test_y = list(features[:,1][-testing_size:])

    return train_x,train_y,test_x,test_y

