'''
Created on 15-Mar-2015

@author: adarsh
'''
import numpy as np
import matplotlib.pyplot as plt

def main():
    f = open('/home/adarsh/git/adarshvjois/image_feature_extractor/ImageFeatureExtractor/outfile.python', 'r')
    # for l in f:
    a = f.readline().split(',')
    fname = a[0]
    label = a[1]
    print "File name" + fname + "labeled as " + label + "\n"
    dims = (int(a[2]), int(a[3]))  # figuring out what to reshape to
    img = np.array(map(float, a[4:4 + int(dims[0] * dims[1])]))  # reading how much ever we need from the csv line
    plt.imshow(img.reshape(dims[0], dims[1]))
    plt.show()

if __name__ == "__main__":
    main()
