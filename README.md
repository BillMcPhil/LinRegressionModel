# LinRegressionModel
A very simple model written from scratch in C that uses principles of backpropagation and gradient descent to calculate linear regressions.

# Explanation
The model starts by initializing a single random weight and bias. A basic cost function of $(output - target)^2$ is applied to calculate the loss and then 
backpropagation is applied. 

Since the model consists of only a single weight and bias backpropagation is very simple. Since the cost function is simply $(output - target)^2$ where
$output = weight\*input + bias$, taking the partial derivatives with respect to the weight and bias gives $2(input)(output-target)$ and $2(output - target)$ respectively.
Then we sum up all the loss functions and gradients for every point in the dataset before dividing them by the size of the data set, so 

$$loss = \frac{1}{n}\sum_{k=1}^n (wx_n+b - t_n)^2\$$ 

$$w_g = \frac{1}{n}\sum_{k=1}^n 2x_n(wx_n+b - t_n)$$

$$b_g = \frac{1}{n}\sum_{k=1}^n 2(wx_n+b - t_n)$$

Where $w$ and $w_g$ are the weight and its gradient, $b$ and $b_g$ are the bias and it's gradient, $x_n$ is the input value, and $t_n$ is the target value.

A very simple gradient descent function is then applied to update the weights and biases:
$$w_n = w - w_gdl$$

$$b_n = b - b_gdl$$
Where $w_n$ and $b_n$ are the new weight and bias values and $dl$ is the learning rate, and after running this many times we get a linear function that approximates the given dataset.

This code also uses the pbPlots library to visualize the results of the linear regression. To learn more check [here](https://github.com/InductiveComputerScience/pbPlots/tree/v0.1.7.1)

# Usage
The code can be compiled using the Makefile in the folder, and takes in a text file at runtime with xs and ys data. It will print the final weight and bias to 
the terminal as well as create a "raw.png" image that only shows the data points as well as a "regression.png" image that shows the linear regression along with the data points.

![image](https://github.com/BillMcPhil/LinRegressionModel/assets/125710492/b4113463-b043-429d-99dd-903f737c8476)

![image](https://github.com/BillMcPhil/LinRegressionModel/assets/125710492/2c478cc7-3f0b-4898-a633-fd847840c285)

# Using your own data
 There is a data.txt file in the repo, but you can use any .txt file that contains xs and ys data with a linear relation. The data in the data.txt file is formatted so that there is a single x and y value int each line, separated by a space, and this is how the code is set up to parse the inputted file. 
 
 But it may be the case that the data is not formatted in this way in your text file. If this is the case you can easily change the code to be able to parse your file by going to line 26 in FileManagement.c

This line reads ```fscanf(file, "%lf %lf", trainxs+i, trainys+i);``` where ```"%lf %lf"``` is a format of two doubles separated by a space on each line. You can 
update this parameter to reflect whatever your .txt file format is, using '%*' to indicate an element you want the function to skip over. You should ensure that only the values you want as your xs and ys are being read by the fscanf function. If you want to better understand the fscanf method check [here](https://www.geeksforgeeks.org/scanf-and-fscanf-in-c/) (In the future I might make it easier to change how the code reads your file but for now this is the best way to do it).

If the program isn't giving you the regression you want or breaking entirely it's probably an issue with the learning rate and number of training epochs, and fiddling around with these numbers will probably fix the problem. There are also optional print statements in the training loop that you can uncomment to see exactly what's going on with your weights, biases, loss and gradients.

# Graph Settings

The borders of the graph in the settings is set to auto, so it should automatically determine what the xMax, yMax, xMin and yMin values of your graph 
should be, but if it doesn't you can manually set them by going to lines 145 and 165 in the main.c file and changing autoBoundaries to false, and then uncommenting the code below those lines and setting the xMax, xMin, yMax and yMin variables to whatever you want.

The plot settings are set to "dots" in the code, but if you are working with a very large dataset they may be too big and crowd on each other, so by simply changing "dots" to "pixels" you can get a much smaller point on the graph. You can see other ways to customize your graph settings by going to the pbPlots GitHub, which is linked in the explanation section.




