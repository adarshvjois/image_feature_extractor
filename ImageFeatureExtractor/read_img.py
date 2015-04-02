'''
Created on 15-Mar-2015

@author: adarsh
'''
import numpy as np
# import matplotlib.pyplot as plt

from sklearn import cross_validation
from sklearn import tree
from sklearn import svm
from sklearn import ensemble
from sklearn import neighbors
# from sklearn import linear_model
from sklearn import metrics
from sklearn import preprocessing

import time

def gimme_data():
    data = None
    labels = np.array([])
    dims_array = []
    
    # brute forcing this baby coz pandas and all that other stuff started cribbing
    # who know what they doing internally. Some bloated non-sense.
    t0 = time.time()
    f = open('outfile.python', 'r')
    count = 0
    for l in f:
        count += 1
        a_line = l.split(',')  # split our csv file
        fname = a_line[0]  # reading in the filename
        print(fname)  # i dont trust myself. 
        label = a_line[1]  # fun stuff. 
        labels = np.hstack([labels, float(label)])
        dims = (int(a_line[2]), int(a_line[3]))  # figuring out what to reshape to if we need to display stuff.
        dims_array.append(dims)
        img = np.array(map(float, a_line[4:4 + int(dims[0] * dims[1])]))  # reading how much ever we need from the csv line
        if data != None:  # does it exist? If not create it.
            data = np.vstack([data, img])  # if it exists add a row of data.
        else:
            data = [img]
    t1 = time.time()
    print ("Read", count, "lines of data in ", str(t1 - t0), "sec")
    return data, labels

def mae_and_prescision(true_vals, predictions):
    count = 0.0
    mae = 0.0
    rounded_predictions = np.rint(predictions)
    for i in range(len(true_vals)):
        mae += abs(true_vals[i] - predictions[i])
        if (true_vals[i] == rounded_predictions[i]):
            count += 1
    return mae / float(len(true_vals)), count / float(len(true_vals))
        
    

def main():
    # need to tune this. Isn't proper.
    
    print("Fetching data..")
    data, labels = gimme_data()
    scaler = preprocessing.StandardScaler()
    X_Data = scaler.fit_transform(data)
    del data
    
    print ("Split into training and testing..")
    X_train, X_test, y_train, y_test = cross_validation.train_test_split(X_Data, labels, test_size=0.3, random_state=0)
    del X_Data
    for c in [0.001,0.03,0.05,0.08,0.1]:
        print("training SVR..")
        t0 = time.time()
        est = svm.SVR(kernel='rbf', degree=4,C=c, gamma=1/2000,tol=0.08e-3,cache_size=500)
        est.fit(X_train, y_train)
        t1 = time.time()
        print("Time taken to train:", str(t1 - t0), "sec")
        
        t0 = time.time()
        predictions = est.predict(X_test);
        t1 = time.time()
        print("Time taken to predict:", str(t1 - t0), "sec")
        mae, presc = mae_and_prescision(y_test, est.predict(X_test))
        print('MAE: %.4f' % mae)
        print('PRescision: %.4f' % presc)


if __name__ == "__main__":
    main()
