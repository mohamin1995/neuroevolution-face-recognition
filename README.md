# neuroevolution-face-recognition
Evolutionary(GA) weight updating of ANN for face recognition</br>

![dataset](https://www.researchgate.net/profile/Margarita_Gamarra/publication/220838886/figure/fig4/AS:394081231491078@1470967695318/Examples-of-faces-dataset-To-train-and-test-the-classifier-are-used-10-images-of-each.png)


based on this project : http://www.cs.cmu.edu/afs/cs.cmu.edu/user/mitchell/ftp/faces.html

1.Download dataset from mentioned project page

2.Compile codes with make command(Makefile is existed in directory)

3.Set paths to images of dataset in straightrnd_train.list, straightrnd_test1.list and straightrnd_test2.list

4.Run with below command:

/.facetrain t -t  straightrnd_train.list -1 straightrnd_test1.list -2 straightrnd_test2.list  -n 40 -p 40 -h 11 -g 50 

-n : number of solutions

-p : probability of mutation

-h : number of hidden layer units

-g : max of generations
