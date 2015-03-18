'''
Created on 15-Mar-2015

@author: adarsh
'''
import numpy as np
import matplotlib.pyplot as plt

from sklearn import cross_validation
from sklearn import tree
from sklearn import svm
from sklearn import ensemble
from sklearn import neighbors
from sklearn import linear_model
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
        count+=1
        a_line = l.split(',')  # split our csv file
        fname = a_line[0]  # reading in the filename
        print fname + "\n"  # i dont trust myself. 
        label = a_line[1]  # fun stuff. 
        labels = np.hstack([labels, label])
        dims = (int(a_line[2]), int(a_line[3]))  # figuring out what to reshape to if we need to display stuff.
        dims_array.append()
        img = np.array(map(float, a_line[4:4 + int(dims[0] * dims[1])]))  # reading how much ever we need from the csv line
        if data != None:  # does it exist? If not create it.
            data = np.vstack([data, img])  # if it exists add a row of data.
        else:
            data = [img]
    t1 = time.time()
    print "Read",count,"lines of data in ",str(t1-t0),"\n"
    return data, labels

def main():
    print "Fetching data..\n"
    data, labels = gimme_data()
    scaler = preprocessing.StandardScaler()  # scale the data
    X_Data = scaler.fit_transform(data)
    del data
    
    print "Split into training and testing..\n"
    X_train, X_test, y_train, y_test = cross_validation.train_test_split(X_Data, labels, test_size=0.3, random_state=0)
    del X_Data
    
    print "training GradientBoostingRegressor.."
    t0 = time.time()
    #need to tune this. Isn't proper.
    est = ensemble.GradientBoostingRegressor(learning_rate=0.03,n_estimators=650,max_depth=8,min_samples_leaf=3)
    est.fit(X_train,y_train)
    t1 = time.time()
    print "Time taken to train:",str(t1-t0),"\n"
    t0 = time.time()
    predictions = est.predict(X_test);
    t1 = time.time()
    print "Time taken to predict:",str(t1-t0),"\n"
    mae = mean_absolute_error(y_test, est.predict(X_test))
    print('MAE: %.4f' % mae)


if __name__ == "__main__":
    main()
