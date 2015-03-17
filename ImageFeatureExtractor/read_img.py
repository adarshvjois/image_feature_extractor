'''
Created on 15-Mar-2015

@author: adarsh
'''
import numpy as np
import matplotlib.pyplot as plt

def main():
    # brute forcing this baby coz pandas and all that other stuff started cribbing
    # who know what they doing internally. Some bloated non-sense.
    data = None
    labels = np.array([])
    dims_array= []

    f = open('/home/adarsh/git/adarshvjois/image_feature_extractor/ImageFeatureExtractor/outfile.python', 'r')
    for l in f:
        a_line = l.split(',') # split our csv file
        fname = a_line[0] # reading in the filename
        print fname+"\n" # i dont trust myself. 
        label = a_line[1] # fun stuff. 
        labels = np.hstack([labels,label])
        dims = (int(a_line[2]), int(a_line[3]))  # figuring out what to reshape to if we need to display stuff.
        dims_array.append()
        img = np.array(map(float, a_line[4:4 + int(dims[0] * dims[1])]))  # reading how much ever we need from the csv line
        if data != None: #does it exist? If not create it.
            data = np.vstack([data,img]) # if it exists add a row of data.
        else:
            data = [img]


if __name__ == "__main__":
    main()
