# Analysis of K Nearest Neighbour Classifier written in Python and C

### Build

```sh
$ git clone https://github.com/mabdullahsoyturk/K-Nearest-Neighbour-Analysis.git
$ cd K-Nearest-Neighbour-Analysis
$ make
```

### Run
```sh
$ ./output
```

### Running times of Cross Validation Experiments

| Python | C |
| ------ | ------ |
| 1.08 s | 0.07 s |

### Accuracy

|  | Python | C |
| ------  | ------ | ------ |
| k = 1  | 0.957 | 0.951 |
| k = 3  | 0.964 | 0.971 |
| k = 5  | 0.969 | 0.965 |

Since K Nearest Neighbour algorithm does not contain any randomness the accuracies should have been the same. There is probably a small bug that waits to be fixed. 

### Development

Want to contribute? Great!

[Contact Me](http://muhammetsoyturk.com/)
