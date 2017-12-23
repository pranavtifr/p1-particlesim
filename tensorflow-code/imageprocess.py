import numpy as np
from sklearn.metrics import roc_curve, auc
import matplotlib.pyplot as plt
from mpl_toolkits.axes_grid1 import host_subplot
import mpl_toolkits.axisartist as AA
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

def roc_plot(predicted_ans,correct_ans,ep,acc,loss,n_classes = 2):
    fpr = dict()
    tpr = dict()
    roc_auc = dict()
    for i in range(n_classes):
        fpr[i], tpr[i], _ = roc_curve(correct_ans[:, i], predicted_ans[:, i])
        roc_auc[i] = auc(fpr[i], tpr[i])
    return roc_auc
    '''
    plt.figure()
    host = host_subplot(122, axes_class=AA.Axes)
    host.plot(ep,acc,label='Accuracy')
    host.set_title('Learning Rates')
    host.set_xlabel('Epochs')
    host.set_ylabel('Accuracy')
    host.set_ylim(min(acc)*0.9, max(acc)*1.1)

    par1 = host.twinx()
    par1.set_ylabel("Temperature")
    par1.axis["right"].toggle(all=True)
    par1.plot(ep,loss,label='Loss')
    par1.set_ylabel('Loss')
    par1.set_ylim(0, max(loss)*1.1)
    host.legend()

    plt.subplot(121)
    lw = 2
    plt.plot(fpr[0], tpr[0], color='darkorange', lw=lw, label='ROC curve (area = %0.2f)' % roc_auc[0])
    plt.plot([0, 1], [0, 1], color='navy', lw=lw, linestyle='--')
    plt.xlim([0.0, 1.0])
    plt.ylim([0.0, 1.05])
    plt.xlabel('False Positive Rate')
    plt.ylabel('True Positive Rate')
    plt.title('ROC')
    plt.legend(loc="lower right")
    plt.tight_layout()
    plt.savefig('roc_curve.png', bbox_inches='tight')   
    plt.close()
    '''
