#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#include "pbPlots.h"
#include "supportLib.h"
#include "FileManagement.h"

// Define essential variables
float LEARNING_RATE =  0.0001;
int EPOCHS = 200000;

// Neural Network struct
struct NeuralNet 
{
    double weight;
    double bias;
    double weight_grad;
    double bias_grad;
};

// Lists for training and testing data
double intitialTestResults[10];
double finalTestResults[10];

// Forward pass function
double forward(struct NeuralNet *nn, double input) 
{
    return (nn->weight) * input + (nn->bias);
}

// Calculates the loss and backpropagates.
// Uses basic loss function where the loss for the given run is the square of the result minus the target
double lossAndBackprop(double output, double input, double target, struct NeuralNet *nn) 
{
    nn->weight_grad += 2*(output - target)*input;
    nn->bias_grad += 2*(output - target);
    return pow(output - target, 2);
}

// Basic gradient descent function for the weight and bias
void step(struct NeuralNet *nn) 
{
    nn->weight -= LEARNING_RATE*nn->weight_grad;
    nn->bias -= LEARNING_RATE*nn->bias_grad; 
}

int main(int argc, char *argv[]) 
{

    // Make sure user input is correct
    if (argc < 2) 
    {
        printf("Need a file name for dataset\n");
        return 1;
    }

    if (argc != 2 && argc != 4) {
        printf("Incorrect number of arguments\n");
        return 1;
    }

    else if (argc == 4) {
        LEARNING_RATE = atof(argv[2]);
        EPOCHS = atoi(argv[3]);

        if (LEARNING_RATE == 0.0f || EPOCHS == 0) {
            printf("Failed to convert string to number\n");
            return 1;
        }
    }


    // Open file
    FILE *dataset = fopen(argv[1], "r");
    if (dataset == NULL) 
    {
        printf("File Read Failed\n");
        return 1;
    }

    // Count number of lines in the dataset file
    int numLines = countLines(dataset);
    
    // Create data lists
    double *data = malloc(numLines*sizeof(double));
    double *xs = malloc(numLines*sizeof(double));
    double *regression = malloc(numLines*sizeof(double));

    // Put data from text file into the xs and data lists
    parseFile(dataset, xs, data, numLines);

    srand(time(NULL));

    // Make neural network
    struct NeuralNet *model_0 = malloc(sizeof(struct NeuralNet));

    // randomly set weight and bias values
    model_0->weight = -((float)rand()/(float)(RAND_MAX/10));
    model_0->bias = -((float)rand()/(float)(RAND_MAX/10));

    double loss = 0;

    // Main training loop
    for (int i=0; i<EPOCHS; ++i) 
    {
        // Calculate the loss and backpropagate for each element in the training list
        for (int j=0; j<numLines; ++j) 
        {
            double output = forward(model_0, xs[j]);
            loss += lossAndBackprop(output, xs[j], data[j], model_0);
        }

        // Divide the loss and the gradients by the total number of elements in the training list
        loss /= numLines;
        model_0->weight_grad /= numLines;
        model_0->bias_grad /= numLines;



        // Calculate the step             
        step(model_0);

        // Optional print statements for troubleshooting

        //printf("%f   %f\n", model_0->weight_grad, model_0->bias_grad);
        //printf("Loss: %f     Weight: %f      Bias: %f\n", loss, model_0->weight, model_0->bias);
    }

    printf("Weight: %lf   | Bias: %lf\n", model_0->weight, model_0->bias);

    for (int i=0; i<numLines; i++) 
    {
        regression[i] = forward(model_0, xs[i]);
    }

    // Plot settings for the testing data
    ScatterPlotSeries *dataSeries = GetDefaultScatterPlotSeriesSettings();
    dataSeries->xs = xs;
    dataSeries->xsLength = numLines;
    dataSeries->ysLength = numLines;
    dataSeries->ys = data;
    dataSeries->linearInterpolation = false;
    dataSeries->color = CreateRGBColor(0, 0, 0);
    dataSeries->pointType = L"dots";
    dataSeries->pointTypeLength = wcslen(dataSeries->pointType);

    // Plot settings for the linear regression graph
    ScatterPlotSeries *linearRegressionSeries = GetDefaultScatterPlotSeriesSettings();
    linearRegressionSeries->xs = xs;
    linearRegressionSeries->xsLength = numLines;
    linearRegressionSeries->ysLength = numLines;
    linearRegressionSeries->ys = regression;
    linearRegressionSeries->linearInterpolation = true;
    linearRegressionSeries->lineType = L"solid";
    linearRegressionSeries->lineTypeLength = wcslen(linearRegressionSeries->lineType);
    linearRegressionSeries->lineThickness = 2;
    linearRegressionSeries->color = CreateRGBColor(0, 0, 1);
    
    // Graph settings for the before training graph
    ScatterPlotSettings *beforeSettings = GetDefaultScatterPlotSettings();
    beforeSettings->width = 600;
    beforeSettings->height = 400;
    beforeSettings->autoBoundaries = true;
    /*beforeSettings->xMax = 70;
    beforeSettings->xMin = 15;
    beforeSettings->yMin = 100;
    beforeSettings->yMax = 160;*/
    beforeSettings->autoPadding = true;
    beforeSettings->title = L"Raw Data";
    beforeSettings->titleLength = wcslen(beforeSettings->title);
    ScatterPlotSeries *s [] = {dataSeries};
    beforeSettings->scatterPlotSeries = s;
    beforeSettings->scatterPlotSeriesLength = 1;

    // Graph settings for the linear regression graph
    ScatterPlotSettings *afterSettings = GetDefaultScatterPlotSettings();
    afterSettings->width = 600;
    afterSettings->height = 400;
    afterSettings->autoBoundaries = true;
    /*afterSettings->xMax = 70;
    afterSettings->xMin = 15;
    afterSettings->yMin = 100;
    afterSettings->yMax = 160;*/
    afterSettings->autoPadding = true;
    afterSettings->title = L"Linear Regression";
    afterSettings->titleLength = wcslen(afterSettings->title);
    ScatterPlotSeries *t [] = {dataSeries, linearRegressionSeries};
    afterSettings->scatterPlotSeries = t;
    afterSettings->scatterPlotSeriesLength = 2;

    // Graph canvas
    RGBABitmapImageReference *canvasReference = CreateRGBABitmapImageReference();

    // Draw the before graph
    DrawScatterPlotFromSettings(canvasReference, beforeSettings);

    // Output the before graph into an image
    size_t length;
    double *pngdata = ConvertToPNG(&length, canvasReference->image);
    WriteToFile(pngdata, length, "raw.png");

    // Draw the after graph
    DrawScatterPlotFromSettings(canvasReference, afterSettings);
    
    // Output the after graph into an image
    pngdata = ConvertToPNG(&length, canvasReference->image);
    WriteToFile(pngdata, length, "regression.png");

    //printf("%ls\n", dataSeries->pointType);
    
    DeleteImage(canvasReference->image);
    free(model_0); 
    free(data);
    free(xs);
    free(regression);
}
