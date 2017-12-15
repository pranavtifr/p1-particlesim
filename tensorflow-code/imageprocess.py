import numpy as np
from sklearn.metrics import roc_curve, auc
import matplotlib.pyplot as plt
import random
def readfile(sample,classification,lines):
    dataset = []
    i = 0
    with open(sample) as f:
        data = [float(x) for x in next(f).split()] # read first line
        for line in f: # read rest of lines
            i+=1
            if(i>lines):
                break
            data = [float(x) for x in line.split()] # read first line
            dataset.append([data,classification])
            #print(dataset[:,0][0])
            #input("Press enter to continue")
    print(len(dataset))
    return dataset,len(dataset)

def create_data(quark,gluon,test_size = 0.1,lines = 100000000):
    features = []
    qu,qu_l = readfile(quark,[1,0],lines)
    gu,gu_l = readfile(gluon,[0,1],lines)
    features += qu[:min(qu_l,gu_l)]
    features += gu[:min(qu_l,gu_l)]

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

def roc_plot(predicted_ans,correct_ans,n_classes = 2):
    fpr = dict()
    tpr = dict()
    roc_auc = dict()
    for i in range(n_classes):
        fpr[i], tpr[i], _ = roc_curve(correct_ans[:, i], predicted_ans[:, i])
        roc_auc[i] = auc(fpr[i], tpr[i])

    plt.figure()
    lw = 2
    plt.plot(fpr[0], tpr[0], color='darkorange', lw=lw, label='ROC curve (area = %0.2f)' % roc_auc[0])
    plt.plot([0, 1], [0, 1], color='navy', lw=lw, linestyle='--')
    plt.xlim([0.0, 1.0])
    plt.ylim([0.0, 1.05])
    plt.xlabel('False Positive Rate')
    plt.ylabel('True Positive Rate')
    plt.title('Receiver operating characteristic example')
    plt.legend(loc="lower right")
    plt.savefig('roc_curve.png', bbox_inches='tight')   
    plt.show()
