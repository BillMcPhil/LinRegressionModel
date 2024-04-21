# LinRegressionModel
A very simple model that uses principles of backpropagation and gradient descent to calculate linear regressions.

# How it works
The model starts by initializing a single random weight and bias. A basic cost function of $(output - target)^2$ is applied to calculate the loss and then 
backpropagation is applied. 

Since the model consists of only a single weight and bias backpropagation is very simple. Since the cost function is simply $(output - target)^2$ where
$output = weight\*input + bias$, taking the partial derivatives with respect to the weight and bias gives $2(input)(output-target)$ and $2(output - target)$ respectively.
Then we sum up all the loss functions and gradients for every point in the dataset before dividing them by the size of the data set, so 

$$loss = \frac{1}{n}\sum_{k=1}^n (wx_n+b - t)^2\$$ 

$$w_g = \frac{1}{n}\sum_{k=1}^n 2x_n(wx_n+b - t)$$

$$b_g = \frac{1}{n}\sum_{k=1}^n 2(wx_n+b - t)$$

Where $w$ and $w_g$ are the weight and its gradient, $b$ and $b_g$ are the bias and it's gradient, $x$ is the input value, and $t$ is the target value.

A very simple gradient descent function is then applied to update the weights and biases:
$$w_n = w - w_gdl$$

$$b_n = b - b_gdl$$
Where $w_n$ and $b_n$ are the new weight and bias values and $dl$ is the learning rate, and after running this many times we get a linear function that approximates the given dataset.

This code also uses the pbPlots library to visualize the results of the linear regression. To learn more check [here](https://github.com/InductiveComputerScience/pbPlots/tree/v0.1.7.1)

