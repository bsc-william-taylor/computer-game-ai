
/*
 * Copyright [yyyy] [name of copyright owner]
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *    http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 * 
 */

using System.Windows.Media.Imaging;
using System.Collections.Generic;
using System.Windows.Navigation;
using System.Windows.Documents;
using System.Windows.Controls;
using System.Windows.Shapes;
using System.Threading.Tasks;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Data;
using System.Diagnostics;
using System.Windows;
using System.Linq;
using System.Text;
using System.Xml;
using System.IO;
using System;

namespace Trainer
{
    /// <summary>
    /// Interaction logic for EditorWindow.xaml
    /// </summary>
    public partial class EditorWindow : Window
    {
        /// <summary>
        /// Constructor
        /// </summary>
        public EditorWindow()
        {
            InitializeComponent();
            SetupDefaultValues();
            SetupComboBox();
        }

        /// <summary>
        /// This function sets up the initial values for the labels
        /// </summary>
        private void SetupDefaultValues()
        {
            // The inital values for the MLP test
            MLP_ErrorThreshold.Text = "0.01";
            MLP_LearningRate.Text = "0.1";
            MLP_Epochs.Text = "50000";

            // The inital values for the RBF test
            RBF_ErrorThreshold.Text = "0.01";
            RBF_LearningRate.Text = "0.1";
            RBF_Epochs.Text = "50000";
        }

        /// <summary>
        /// This sets up a list of values to choose from
        /// when it comes to the two combo boxes on the
        /// user interface
        /// </summary>
        private void SetupComboBox()
        {
            // First create a list of noise values
            List<string> noiseValues = new List<string>();
            noiseValues.Add("0.20");
            noiseValues.Add("0.10");
            noiseValues.Add("0.05");

            // Then set this as the source and set the starting point
            NoiseComboBox.ItemsSource = noiseValues;
            NoiseComboBox.SelectedIndex = 2;

            // Then create a list of training set size values
            List<string> trainingSetSize = new List<string>();
            trainingSetSize.Add("5");
            trainingSetSize.Add("10");
            trainingSetSize.Add("20");

            // Then set this as the source and set the starting point
            TrainingComboBox.ItemsSource = trainingSetSize;
            TrainingComboBox.SelectedIndex = 1;
        }

        /// <summary>
        /// Handles when an item on the menu is clicked
        /// </summary>
        /// <param name="sender">The sender as an object</param>
        /// <param name="e">Params for the event</param>
        private void MenuItem_Click(object sender, RoutedEventArgs e)
        {
            // if the exit menu item was clicked
            if(sender == Exit)
            {
                // close the application
                Application.Current.Shutdown();
            }

            // if the about item was clicked 
            if(sender == About)
            {
                // Show a simple about box
                MessageBox.Show("This is a simple simulation toolkit for RBF's & MLP's for the GameAI module", "About ", MessageBoxButton.OK);
            }
            
            // if the run menu item was clicked
            if(sender == Run)
            {
                // then run the simulator
                RunSimulator();
            }
        }

        /// <summary>
        /// Tests to make sure all paramters are double numbers
        /// </summary>
        /// <param name="arguments">A list of strings which represent inputs</param>
        /// <returns>true if all strings in the array arev valid double numbers</returns>
        private bool TestInputValues(params string[] arguments)
        {
            // Not used
            double dummy;
            // Check to see how many test passes there are
            int passes = 0;

            // For each string in the array we first
            foreach(string str in arguments)
            {
                // see if it can be converted to a double and if so
                if (double.TryParse(str, out dummy))
                {
                    // increment the pass integer
                    ++passes;
                }
            }

            // if the number of passes equals the arguments length then we know all tests were passed
            return (passes == arguments.Length);
        }

        /// <summary>
        /// 
        /// </summary>
        private void RunSimulator()
        {
            // Test to make sure all values in the input boxes are correct
            if (TestInputValues(MLP_ErrorThreshold.Text, MLP_LearningRate.Text, MLP_Epochs.Text))
            {
                // Test again to make sure all values in the input boxes are correct
                if (TestInputValues(RBF_ErrorThreshold.Text, RBF_LearningRate.Text, RBF_Epochs.Text))
                {
                    // Then alter the XML file which will be read by the simulator
                    XmlDocument settings = new XmlDocument();
                    settings.Load(@"settings.xml");
                    
                    // Update the training set values and the noise values in the xml file
                    settings.SelectSingleNode("/Settings/TrainingSet").InnerText = TrainingComboBox.Text;
                    settings.SelectSingleNode("/Settings/Noise").InnerText = NoiseComboBox.Text;

                    // Then update the setting values contained in SettingsMLP xml node
                    settings.SelectSingleNode("/Settings/SettingsMLP/ErrorThreshold").InnerText = MLP_ErrorThreshold.Text;
                    settings.SelectSingleNode("/Settings/SettingsMLP/LearningRate").InnerText = MLP_LearningRate.Text;
                    settings.SelectSingleNode("/Settings/SettingsMLP/Iterations").InnerText = MLP_Epochs.Text;

                    // And last update the setting values contained in SettingsRBF xml node
                    settings.SelectSingleNode("/Settings/SettingsRBF/ErrorThreshold").InnerText = RBF_ErrorThreshold.Text;
                    settings.SelectSingleNode("/Settings/SettingsRBF/LearningRate").InnerText = RBF_LearningRate.Text;
                    settings.SelectSingleNode("/Settings/SettingsRBF/Iterations").InnerText = RBF_Epochs.Text;

                    // The save the updated file & start the simulator
                    settings.Save(@"settings.xml");
                    Process.Start("simulator.exe");
                }
                else
                {
                    // on fail say that the paramets in the RBF boxes are incorrect
                    MessageBox.Show("RBF Input Boxes do not contain valid values");
                }
            }
            else
            {
                // on fail say that the paramets in the MLP boxes are incorrect
                MessageBox.Show("MLP Input Boxes do not contain valid values");
            }
        }     
    }
}
