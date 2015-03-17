Feature Extractor for images: (ML Project)
=============================
Command line tool to extract features from images, its use is somewhat specific.
- 1) Images are resized to a fixed size.
- 2) Can use by calling
``` Downsampler <csv_file_with_file_names and labels_of_images>  <output file> [width height] [-v] [file extension]```
- 3) CSV File has a format as outlined below.
 -- ```<filename> <label> <original width> <original height> <feat1> <feat2> ......<featn>```
 