/*
 ******************************************************************
 * HISTORY
 * 15-Oct-94  Jeff Shufelt (js), Carnegie Mellon University
 *      Prepared for 15-681, Fall 1994.
 *
 * Tue Oct  7 08:12:06 EDT 1997, bthom, added a few comments,
 *       tagged w/bthom
 *
 ******************************************************************
 */

#include <stdio.h>
#include <math.h>
#include <pgmimage.h>
#include <backprop.h>

extern char *strcpy();
extern void exit();

double performance_on_imagelist_err(net, il, list_errors)
BPNN *net;
IMAGELIST *il;
int list_errors;
{
  double err, val;
  int i, n, j, correct;

  err = 0.0;
  correct = 0;
  n = il->n;
  if (n > 0) {
    for (i = 0; i < n; i++) {

      /*** Load the image into the input layer. **/
      load_input_with_image(il->list[i], net);

      /*** Run the net on this input. **/
      bpnn_feedforward(net);

      /*** Set up the target vector for this image. **/
      load_target(il->list[i], net);

      /*** See if it got it right. ***/
      if (evaluate_performance(net, &val, 0)) {
        correct++;
      } else if (list_errors) {
	printf("%s - outputs ", NAME(il->list[i]));
	for (j = 1; j <= net->output_n; j++) {
	  printf("%.3f ", net->output_units[j]);
	}
	putchar('\n');
      }
      err += val;
    }

    err = err / (double) n;

    if (!list_errors)
      
	  return err;
  } else {
    if (!list_errors)
      return 0.0;
  }
}

double performance_on_imagelist_per(net, il, list_errors)
BPNN *net;
IMAGELIST *il;
int list_errors;
{
  double err, val;
  int i, n, j, correct;

  err = 0.0;
  correct = 0;
  n = il->n;
  if (n > 0) {
    for (i = 0; i < n; i++) {

      /*** Load the image into the input layer. **/
      load_input_with_image(il->list[i], net);

      /*** Run the net on this input. **/
      bpnn_feedforward(net);

      /*** Set up the target vector for this image. **/
      load_target(il->list[i], net);

      /*** See if it got it right. ***/
      if (evaluate_performance(net, &val, 0)) {
        correct++;
      } else if (list_errors) {
	printf("%s - outputs ", NAME(il->list[i]));
	for (j = 1; j <= net->output_n; j++) {
	  printf("%.3f ", net->output_units[j]);
	}
	putchar('\n');
      }
      err += val;
    }

    err = err / (double) n;

    if (!list_errors)
      
	  return ((double) correct / (double) n) * 100.0;
  } else {
    if (!list_errors)
      return 0.0;
  }
}

double ** get_initial_population(num_of_units,num_of_solutions)

int num_of_solutions,num_of_units;
	{
	int i,j;
	
	double ** weights = alloc_2d_dbl(num_of_solutions, num_of_units);
		
	for(i=0;i<num_of_solutions;i++){
		
		for(j=0;j<num_of_units;j++){
			
			weights[i][j] = dpn1();
			
			
		}
		
		
		
	}
	
	return weights;
	
	}
	
	
double calculate_fitness(per_train,per_test1,per_test2,err_train,err_test1,err_test2)

double per_train,per_test1,per_test2,err_train,err_test1,err_test2;
{
	
	
	return ((per_train+per_test1+per_test2)/(err_train*err_test1*err_test2))/1000000.0;
	
}

int find_max(fitness_array,size)
double * fitness_array;
int size;
{
	int i;
	int index=0;
	double max = -1.0;
	
	for(i=0;i<size;i++){
		
		if(fitness_array[i]>max){
			
			max = fitness_array[i];
			index=i;
			
		}
		
	}
	
	return index;
	
	
}

double ** apply_mutation(solutions,num_of_solutions,length_of_solution,p)
int num_of_solutions,length_of_solution,p;
double ** solutions;
{

int i,j;

double ** solutions_after_mutation = alloc_2d_dbl(num_of_solutions,length_of_solution);

for(i=0;i<num_of_solutions;i++){
	
	for(j=0;j<length_of_solution;j++){
		
	int random_num = random()%100;
	if(random_num<p){
		
		//printf("****************************** mutation ***********************************  \n");
			solutions_after_mutation[i][j] = solutions[i][j]+dpn1();

	}else{
		
			solutions_after_mutation[i][j] = solutions[i][j];

	}
	}
	
	
}



return solutions_after_mutation;
	
}

double ** apply_crossover(solutions,num_of_solutions,length_of_solution)
int num_of_solutions,length_of_solution;
double ** solutions;
{

int i,j;
double ** solutions_after_crossover = alloc_2d_dbl(num_of_solutions,length_of_solution);


for(i=0;i<num_of_solutions;i++){
	
	for(j=0;j<length_of_solution;j++){
		
			solutions_after_crossover[i][j] = solutions[i][j];

	}
}
	
	


// implementation of uniform crossover

int num_of_positions = 0.06*length_of_solution;

int * selected_positions = alloc_1d_dbl(num_of_positions);

for(i=0;i<num_of_positions;i++)
	selected_positions[i]=random()%length_of_solution;

int num_of_selected_solutions = 0.06*num_of_solutions;

if(num_of_selected_solutions%2!=0)
	num_of_selected_solutions=num_of_selected_solutions+1;

int * selected_solutions = alloc_1d_dbl(num_of_selected_solutions);

for(i=0;i<num_of_selected_solutions;i++)
	selected_solutions[i]=random()%num_of_solutions;



for(i=0;i<num_of_selected_solutions-1;i=i+2){
	
	for(j=0;j<num_of_positions;j++){
		
		double temp = solutions_after_crossover[i][selected_positions[j]];
		solutions_after_crossover[i][selected_positions[j]]=solutions_after_crossover[i+1][selected_positions[j]];
		solutions_after_crossover[i+1][selected_positions[j]] = temp;
		
	}
	
}


return solutions_after_crossover;
	
}

int check_stop_condition(generation_con,max_generation,best_fitness)
int generation_con,max_generation;
double best_fitness;
{
	
	if(generation_con>=max_generation || best_fitness>=2399.0)
		return 0;
	else return 1;
	
}

main(argc, argv)
int argc;
char *argv[];
{
  char netname[256], trainname[256], test1name[256], test2name[256];
  IMAGELIST *trainlist, *test1list, *test2list;
  int ind, seed,n,p,hidden_units,list_errors,g;
  list_errors=0;
  
  n=20; // number of solutions
  p=20; // probability of mutation
  hidden_units=11; // number of hidden layer neuron
  g = 100 ; //number of generations
  
  

  seed = 102194;   /*** today's date seemed like a good default ***/
 
  //list_errors = 0;
  netname[0] = trainname[0] = test1name[0] = test2name[0] = '\0';

 

  /*** Create imagelists ***/
  trainlist = imgl_alloc();
  test1list = imgl_alloc();
  test2list = imgl_alloc();

  /*** Scan command line ***/
  for (ind = 1; ind < argc; ind++) {

    /*** Parse switches ***/
    if (argv[ind][0] == '-') {
      switch (argv[ind][1]) {  
	  
		case 'g': g = atoi(argv[++ind]);
				  break;
		case 'h': hidden_units = atoi(argv[++ind]);
				  break;
		case 'p': p = atoi(argv[++ind]);
				  break;
		case 'n': n = atoi(argv[++ind]);
				  break;
        case 's': seed = atoi(argv[++ind]);
                  break;
        case 't': strcpy(trainname, argv[++ind]);
                  break;
        case '1': strcpy(test1name, argv[++ind]);
                  break;
        case '2': strcpy(test2name, argv[++ind]);
                  break;
        default : printf("Unknown switch '%c'\n", argv[ind][1]);
                  break;
      }
    }
  }

  /*** If any train, test1, or test2 sets have been specified, then
       load them in. ***/
  if (trainname[0] != '\0') 
    imgl_load_images_from_textfile(trainlist, trainname);
  if (test1name[0] != '\0') 
    imgl_load_images_from_textfile(test1list, test1name);
  if (test2name[0] != '\0')
    imgl_load_images_from_textfile(test2list, test2name);

 
  /*** Initialize the neural net package ***/
  bpnn_initialize(seed);

  /*** Show number of images in train, test1, test2 ***/
  printf("%d images in training set\n", trainlist->n);
  printf("%d images in test1 set\n", test1list->n);
  printf("%d images in test2 set\n", test2list->n);

  /*** If we've got at least one image to train on, go train the net ***/
  evo_face(trainlist, test1list, test2list, netname,
		list_errors,n,p,hidden_units,g);

  exit(0);
}


evo_face(trainlist, test1list, test2list, netname,
	      list_errors,n,p,hidden_units,g)
IMAGELIST *trainlist, *test1list, *test2list;
int  list_errors;
int p,n,hidden_units,g;
char *netname;
{
	
	
  IMAGE *iimg;
  BPNN *net;
  int train_n, epoch, i, imgsize;
  double out_err, hid_err, sumerr;

  train_n = trainlist->n;

    
  iimg = trainlist->list[0];
  imgsize = ROWS(iimg) * COLS(iimg);
	  
  
  int output_units = 1;
  int num_of_solutions = n;
  int max_generation = g;
	  
  int num_of_units = (((imgsize+1) * (hidden_units+1)) + ((hidden_units+1) * (output_units+1)));
  
  printf("num of units is : %d \n",num_of_units);
  
  
  double ** solutions = get_initial_population(num_of_units,num_of_solutions);
  
  double best_fitness = -1.0;
  double * best_solution;
  
  int generation_con = 0;
  while(check_stop_condition(generation_con,max_generation,best_fitness)){
	  
	  double * solutions_fitness = alloc_1d_dbl(num_of_solutions);
	  
	  int iter;
	  for(iter=0;iter<num_of_solutions;iter++){
			net = bpnn_create(imgsize, hidden_units, output_units,solutions[iter]);
			double per_train = performance_on_imagelist_per(net,trainlist,0);
			double per_test1 = performance_on_imagelist_per(net,test1list,0);
			double per_test2 = performance_on_imagelist_per(net,test2list,0);
			
			double err_train = performance_on_imagelist_err(net,trainlist,0);
			double err_test1 = performance_on_imagelist_err(net,test1list,0);
			double err_test2 = performance_on_imagelist_err(net,test2list,0);
	
		    solutions_fitness[iter] = calculate_fitness(per_train,per_test1,per_test2,err_train,err_test1,err_test2);	
			bpnn_free(net);

		  
	  }
	  
	  int index_of_max = find_max(solutions_fitness,num_of_solutions);
	  //printf("max: %d  \n",index_of_max);

	  if(solutions_fitness[index_of_max]>best_fitness){
	  best_fitness = solutions_fitness[index_of_max];
	  best_solution = solutions[index_of_max];
	  
	  }
	  
	 free((double *)solutions_fitness);
	 
	 printf("generation[%d] - best fitness: %f \n",generation_con+1,best_fitness);
	 
	 
	 // selection and reproduction
	 for(iter=0;iter<num_of_solutions;iter++){
		 
		 solutions[iter] = solutions[index_of_max];
	 }
	
	
	solutions = apply_crossover(solutions,num_of_solutions,num_of_units);
	solutions = apply_mutation(solutions,num_of_solutions,num_of_units,p);
		
		


	  generation_con++;
	  
  }
  
  
  net = bpnn_create(imgsize, hidden_units, output_units,best_solution);
			
			double per_train = performance_on_imagelist_per(net,trainlist,0);
			double per_test1 = performance_on_imagelist_per(net,test1list,0);
			double per_test2 = performance_on_imagelist_per(net,test2list,0);
			
			double err_train = performance_on_imagelist_err(net,trainlist,0);
			double err_test1 = performance_on_imagelist_err(net,test1list,0);
			double err_test2 = performance_on_imagelist_err(net,test2list,0);
	
			printf("final result : %f %f %f %g %g %g \n",per_train,per_test1,per_test2,err_train,err_test1,err_test2);
  
 			bpnn_free(net);

    
  
}


/*** Computes the performance of a net on the images in the imagelist. ***/
/*** Prints out the percentage correct on the image set, and the
     average error between the target and the output units for the set. ***/



evaluate_performance(net, err)
BPNN *net;
double *err;
{
  double delta;

  delta = net->target[1] - net->output_units[1];

  *err = (0.5 * delta * delta);

  /*** If the target unit is on... ***/
  if (net->target[1] > 0.5) {

    /*** If the output unit is on, then we correctly recognized me! ***/
    if (net->output_units[1] > 0.5) {
      return (1);

    /*** otherwise, we didn't think it was me... ***/
    } else {
      return (0);
    }

  /*** Else, the target unit is off... ***/
  } else {

    /*** If the output unit is on, then we mistakenly thought it was me ***/
    if (net->output_units[1] > 0.5) {
      return (0);

    /*** else, we correctly realized that it wasn't me ***/
    } else {
      return (1);
    }
  }

}



printusage(prog)
char *prog;
{
  printf("USAGE: %s\n", prog);
  printf("       -n <network file>\n");
  printf("       [-e <number of epochs>]\n");
  printf("       [-s <random number generator seed>]\n");
  printf("       [-S <number of epochs between saves of network>]\n");
  printf("       [-t <training set list>]\n");
  printf("       [-1 <testing set 1 list>]\n");
  printf("       [-2 <testing set 2 list>]\n");
  printf("       [-T]\n");
}
