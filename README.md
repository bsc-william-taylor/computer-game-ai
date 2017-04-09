
<img src='preview.gif' />

<img src='icon.png' width='150' height='150' align='right'/>

# Compute Game AI

The Computer Game AI module taught students basic neural network types such as the multi layered perceptron (MLP) and radial basis function (RBF) networks. The module was assessed with a report where we had to compare these to network types for approximating a function and an exam which asked questions on neural networks and pathfinding.  
 
## Assignment

The assignment was to design and compare a RBF and a MLP for approximating a fixed function. With each network designed we were then asked to vary the following parameters in the networds

* MLP
   * Number of hidden neurons
   * The learning rate
   * Values of momentum term

* RBF
   * Number of RBFs
   * The RBFs width
   * The position of the RBFs

## Submission

Once I had designed a basic RBF and MLP I then decided to write two application to aid in writing the report.

### Network Program

The network program was a C++ application that would take neural network settings in from an XML file, train both the RBF and MLP networks and output the trained networks approximations using FreeGlut and OpenGL. This OpenGL output can also be inspected by using the arrow keys for moving around the graph and the W and S keys for zooming in and out.

### Ui Program

A UI program was also written in C# with WPF which runs the network program and provides a clean way to mutate the XML file that is read in the first program. The user can specify all fields found in the XML file and launch off multiple instances to view the results in real time.

## License

MIT